#include "BCIEventApplication.hpp"
#include "Environment.h"
#include <memory>
#include <stdexcept>
#include "Shapes.h"
#include "StartEvent.hpp"
#include "WaitForProcessBlock.hpp"
#include "ProcessEvent.hpp"

using namespace BCIEvent;


RegisterFilter(BCIEventApplication, 3);


BCIEventApplication::BCIEventApplication() 
    :  _display(ApplicationWindowClient::Window()){
	    /**
    _display.SetHeight(200)
    .SetWidth(300)
    .SetVisible(true);
    */
    Parameter("ShowAppLog") = 1;
    _states = std::make_unique<BCIEvent::States>(this);
    _globalVars = std::make_unique<GlobalVariables>();
	_processEvent = ProcessEvent
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
    _states->addState(name, type);
}

void BCIEventApplication::addActor(std::unique_ptr<Actor> actor){
    _actors.push_back(std::move(actor));
}

void BCIEventApplication::addVar(std::unique_ptr<Variable> v) {
	_globalVars->addVariable(std::move(v));
}

void BCIEventApplication::uploadState(std::string name, int width){
	if (States->Exists(name)){
	    throw std::invalid_argument("Attempted to define state " + name + ", but that state already exists");
    	}
	else {
	    class State s;
	    s.SetKind(State::StateKind);
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
	    uploadState(name, 1);
	} else if (type == BCIState::i8 || type == BCIState::u8){
	    uploadState(name, 8);
	    if (type == BCIState::i8){
		uploadState(name + "_sign", 1);
	    }
	} else if (type == BCIState::i32 || type == BCIState::u32){
	    uploadState(name, 32);
	    if (type == BCIState::i32){
		uploadState(name + "_sign", 1);
	    }
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

void BCIEventApplication::addProcessBlock(std::shared_ptr<WaitForProcessBlock> pBlock) {
	_processBlocks.push_back(pBlock);
}
