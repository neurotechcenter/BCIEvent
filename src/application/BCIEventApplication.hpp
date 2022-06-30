#ifndef BCIEVENT_APPLICATION_H
#define BCIEVENT_APPLICATION_H
#include "ApplicationBase.h"
#include "Actor.hpp"
#include "ApplicationWindow.h"
#include "GenericSignal.h"
#include "SignalProperties.h"
#include "TextField.h"
#include <vector>

namespace BCIEvent{
    class BCIEventApplication : public ApplicationBase{
	public:
	BCIEventApplication();
	void Publish() override;
	void Preflight(const SignalProperties&, SignalProperties&) const override;
	void Initialize(const SignalProperties&, SignalProperties&) override;
	void Process(const GenericSignal&, GenericSignal&) override;
	void Resting(const GenericSignal&, GenericSignal&) override;
	void StartRun() override;
	void StopRun() override;
	void Halt() override;

	void setState(std::string name, int value);
	int getState(std::string name);
	private:
	ApplicationWindow& _window;
	std::unique_ptr<TextField> _messageField;
	SignalProperties& properties;

	void OnPreflight(const SignalProperties& input) const;
	void OnInitialize(const SignalProperties& input);
	void OnStartRun();
	void OnStopRun();
	void OnHalt();

	/**
	 * Use this method to initialize all of the 
	 */
	void InitBCIEvent();
	void update();
	enum States {Running, Paused};
	States _currentState = Paused;	
	std::vector<std::unique_ptr<Actor>> _actors;
    };
}

#endif
