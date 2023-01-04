#include "BCIEventApplication.hpp"
#include "Environment.h"
#include <memory>
#include <stdexcept>
#include "Shapes.h"
#include "StartEvent.hpp"
#include "WaitForProcessBlock.hpp"
#include "ProcessEvent.hpp"
#include "BCIEVariable.hpp"

using namespace BCIEvent;


RegisterFilter(BCIEventApplication, 3);


BCIEventApplication::BCIEventApplication() 
    :  _display(ApplicationWindowClient::Window()){
    Parameter("ShowAppLog") = 1;
    _states = std::make_unique<BCIEvent::States>(this);
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
	_states.emplace(name, type);
}

void BCIEventApplication::addActor(std::unique_ptr<Actor> actor){
    _actors.push_back(std::move(actor));
}

void BCIEventApplication::addVariable(std::string name, BCIEValue value) {
	_variables.insert(name, value);
}

void BCIEventApplication::addVariable(std::string name) {
	_variables.insert(name, std::nullopt);
}

void BCIEventApplication::addBCI2000Event(std::string name) {
	_bci2000states.push_back(name);
}

void BCIEventApplication::callBCI2000Event(std::string name, uint32_t value) {
	bcievent << name << " " << value;
}

void BCIEventApplication::uploadState(std::string name, int width, int kind){
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
    for (const BCIState* state : _states->getStates()){
        auto name = state->name();    
	auto type = state->type();
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
		uploadState(name, 32, State::EventKind);
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

Actor* BCIEventApplication::makeActor(){
    return new Actor(this);
}



void BCIEventApplication::addFunction(std::string name, int numArgs, std::function<(std::vector<BCIEValue>), BCIEValue> fn) {
	_functions.insert(name, fn);
}

BCIEValue BCIEventApplication::callFunction(std::string name, std::vector<BCIEValue> params) {
	_functions.at(name)(params);
}
