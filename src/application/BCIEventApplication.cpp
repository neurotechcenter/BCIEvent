#include "BCIEventApplication.hpp"
#include "Environment.h"
#include <memory>
#include <stdexcept>
#include "Shapes.h"
#include "StartEvent.hpp"
#include "WaitForProcessBlock.hpp"
#include "ProcessEvent.hpp"
#include "BCIEvent.h"
#include <iostream>

using namespace BCIEvent_N;


RegisterFilter(BCIEventApplication, 3);


BCIEventApplication::BCIEventApplication() 
    :  _display(ApplicationWindowClient::Window()){
	bciout << "bcieventapp constructor" << std::flush;
    Parameter("ShowAppLog") = 1;
	_processEvent = ProcessEvent::getInstance();
	GUI::Rect rect = {0.5f, 0.4f, 0.5f, 0.6f};
    _messageField = std::make_unique<TextField>(_display);
    _messageField->SetTextHeight(0.8f)
	    .SetColor(RGBColor::Gray)
	    .SetTextColor(RGBColor::Yellow)
	    .SetObjectRect(rect);
    _messageField->SetText("A")
	    .Show();
    InitBCIEvent();
}

BCIEventApplication::~BCIEventApplication(){
	Halt();
}

void BCIEventApplication::addState(std::string name, BCIState::StateType type){
	_states.insert(std::make_pair(name, BCIState(this, type, name)));
}

void BCIEventApplication::addActor(std::unique_ptr<Actor> actor){
    _actors.push_back(std::move(actor));
}

void BCIEventApplication::addVariable(std::string name) {
	_variables.insert(std::make_pair(name, BCIEValue(std::nullopt)));
}

void BCIEventApplication::addVariable(std::string name, BCIEValue value) {
	_variables.insert(std::make_pair(name, value));
}

void BCIEventApplication::addVariable(std::string name, std::function<BCIEValue(SequenceEnvironment&)> value, int priority) {
	_varInits.push(std::make_tuple(name, value, priority));
}

void BCIEventApplication::addTimer(std::string name) {
	_timers.insert(std::make_pair(name, Timer()));
}

Timer& BCIEventApplication::getTimer(std::string name) {
	return 	_timers.at(name);
}

void BCIEventApplication::addStateEvent(std::string name) {
	_bci2000events.push_back(name);
}

void BCIEventApplication::callStateEvent(std::string name, uint32_t value) {
	bcievent << name << " " << value;
}

void BCIEventApplication::subscribeEvent(std::string name, EventListener* listener) {
	_events.at(name).addListener(listener);
}

void BCIEventApplication::addEvent(std::string name) {
	_events.insert(std::make_pair(name, Event()));
}

void BCIEventApplication::callEvent(std::string name) {
	_events.at(name).trigger();
}

void BCIEventApplication::uploadState(std::string name, uint32_t width, int kind){
	if (States->Exists(name)){
	    throw std::invalid_argument("Attempted to define state " + name + ", but that state already exists");
    	}
	else {
	    class State s;
	    s.SetKind(kind);
	    s.FromDefinition(name + " " + std::to_string(width) + " 0 0 0 \n");
	    States->Add(s);
	    OwnedStates()[ObjectContext()].insert(name);
	}
}

void BCIEventApplication::Publish(){
	AppLog << "publishing";
    for (auto state : _states){
        auto name = std::get<1>(state).name();    
	auto type = std::get<1>(state).type();
	if (type == BCIState::Boolean){
	    uploadState(name, 1, State::StateKind);
	} else if (type == BCIState::i8 || type == BCIState::u8){
	    uploadState(name, 8, State::StateKind);
	    if (type == BCIState::i8){
		uploadState(name + "_sign", 1, State::StateKind);
	    }
	} else if (type == BCIState::i32 || type == BCIState::u32){
	    uploadState(name, 32, State::StateKind);
	    if (type == BCIState::i32){
		uploadState(name + "_sign", 1, State::StateKind);
	    }
	}
	for (auto s : _bci2000events) {
		uploadState(s, 32, State::EventKind);
	}
    }
}

void BCIEventApplication::Preflight(const SignalProperties &input, SignalProperties& output) const {
    OnPreflight(input);
}

void BCIEventApplication::Initialize(const SignalProperties& input, const SignalProperties& output){
    ApplicationBase::Initialize(input, output);
    OnInitialize(input);
}


void BCIEventApplication::Process(const GenericSignal& input, GenericSignal& output){
    currentSignal = &input;
	_processEvent->trigger();
    output = input;
}

void BCIEventApplication::Resting(const GenericSignal& input, GenericSignal& output){

}

void BCIEventApplication::StartRun(){
	_currentState = Running;
    OnStartRun();
}

void BCIEventApplication::StopRun(){
	_currentState = Paused;
    OnStopRun();
}

void BCIEventApplication::Halt(){
    OnHalt();
}

void BCIEventApplication::OnPreflight(const SignalProperties& input) const{
}

void BCIEventApplication::OnInitialize(const SignalProperties& input) {
	initialize();
	for (auto& actor : _actors) {
		actor->initialize();
	}
	_appLoopThread = std::thread(&BCIEventApplication::applicationLoop, this);
	StartEvent::getInstance()->trigger();
	_display.Show();
}

void BCIEventApplication::OnStartRun(){
}

void BCIEventApplication::OnStopRun(){
}

void BCIEventApplication::OnHalt(){
	_appLoop = false;
	_appLoopThread.join();
}

void BCIEventApplication::initialize() {
	while (!_varInits.empty()) {
		const VarInitializer& vi = _varInits.top();
		_variables.insert(std::make_pair(std::get<0>(vi), std::get<1>(vi)(*this)));
		_varInits.pop();
	}
}

void BCIEventApplication::applicationLoop() {
	while (_appLoop) {
		switch (_currentState) {
		case Paused:
			break;
		case Running:
			update(*currentSignal);
			break;
		}
	}
}

void BCIEventApplication::update(const GenericSignal& input){
    for (auto &&actor : _actors){
	actor->update(input);
    }
}

void BCIEventApplication::setState(std::string name, int value){
    State(name) = value;
}

int BCIEventApplication::getState(std::string name){
    return State(name);
}

int BCIEventApplication::randInt(int lower, int upper) {
	return RandomNumberGenerator(upper - lower + 1) + lower;
}

std::unique_ptr<Actor> BCIEventApplication::makeActor(){
    return std::make_unique<Actor>(this);
}



void BCIEventApplication::addFunction(std::string name, int numArgs, std::function<BCIEValue(SequenceEnvironment&, std::vector<BCIEValue>)> fn) {
	_functions.insert(std::make_pair(name, fn));
}

BCIEValue BCIEventApplication::callFunction(std::string name, std::vector<BCIEValue> params) {
	return _functions.at(name)(*this, params);
}

BCIEValue BCIEventApplication::getVariable(std::string name) {
	return _variables.at(name);
}

void BCIEventApplication::setVariable(std::string name, BCIEValue value) {
	_variables.at(name) = value;
}
