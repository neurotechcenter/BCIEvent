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
	std::vector<Actor> _actors;
	public:
	void Publish();
	void Preflight(const SignalProperties&, SignalProperties&) const override;
	void Initialize(const SignalProperties&, SignalProperties&) override;
	void Process(const GenericSignal&, GenericSignal&) override;
	void Resting(const GenericSignal&, GenericSignal&) override;
	void StartRun() override;
	void StopRun() override;
	void Halt() override;


	private:
	std::unique_ptr<ApplicationWindow> _window;
	std::unique_ptr<TextField> _messageField;

	void OnPreflight(const SignalProperties& input) const;
	void OnInitialize(const SignalProperties& input);
	void OnStartRun();
	void OnStopRun();
	void OnHalt();

	void update();
	

    };
}

#endif
