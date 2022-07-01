#include "BCIEventApplication.hpp"
#include "Environment.h"
#include <memory>
#include <stdexcept>


using namespace BCIEvent;


BCIEventApplication::BCIEventApplication() 
    : _window(ApplicationWindowClient::Window("Application")), _display(Window()){
    _states = std::make_unique<BCIEvent::States>(this);
    _globalVars = std::make_unique<GlobalVariables>();

}

void BCIEventApplication::addState(std::string name, BCIState::StateType type){
    _states->addState(name, type);
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

void BCIEventApplication::OnInitialize(const SignalProperties& input){
    InitBCIEvent();
}

void BCIEventApplication::Process(const GenericSignal& input, GenericSignal& output){
    switch (_currentState){
	case Paused:
	    break;
	case Running:
	    update(input);
	    break;
    }
    output = input;
}

void BCIEventApplication::Resting(const GenericSignal& input, GenericSignal& output){

}

void BCIEventApplication::StartRun(){
    OnStartRun();
}

void BCIEventApplication::StopRun(){
    OnStopRun();
}

void BCIEventApplication::Halt(){
    OnHalt();
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

std::unique_ptr<Actor> BCIEventApplication::makeActor(){
    return std::move(std::make_unique<BCIEvent::Actor>(&*_globalVars, &*_states, _display));
}
