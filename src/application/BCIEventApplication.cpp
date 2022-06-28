#include "BCIEventApplication.hpp"
#include "Environment.h"


using namespace BCIEvent;


BCIEventApplication::BCIEventApplication() : _window(ApplicationWindowClient::Window("Application")){

}





void BCIEventApplication::Preflight(const SignalProperties &input, SignalProperties& output){

    OnPreflight(input);
}

void BCIEventApplication::Initialize(const SignalProperties& input, SignalProperties& output){
    ApplicationBase::Initialize(input, output);

    OnInitialize(input);
}

void BCIEventApplication::Process(const GenericSignal& input, GenericSignal& output){
    switch (_currentState){
	case Paused:
	    break;
	case Running:
	    update();
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


void BCIEventApplication::update(){
    for (auto &&actor : _actors){
	actor->update();
    }
}

void BCIEventApplication::setState(std::string name, int value){
    State(name) = value;
}

int BCIEventApplication::getState(std::string name){
    return State(name);
}
