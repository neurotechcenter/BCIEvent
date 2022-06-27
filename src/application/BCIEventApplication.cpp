#include "BCIEventApplication.hpp"
#include "Environment.h"


using namespace BCIEvent;

void BCIEventApplication::Publish(){
    BEGIN_PARAMETER_DEFINITIONS
    END_PARAMETER_DEFINITIONS



    BEGIN_STATE_DEFINITIONS
    END_STATE_DEFINITIONS
}



void BCIEventApplication::Preflight(const SignalProperties &input, SignalProperties& output){

    OnPreflight(input);
}

void BCIEventApplication::Initialize(const SignalProperties& input, SignalProperties& output){
    ApplicationBase::Initialize(input, output);

    OnInitialize(input);
}

void BCIEventApplication::Process(const GenericSignal& input, GenericSignal& output){

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
