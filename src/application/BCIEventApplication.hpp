#ifndef BCIEVENT_APPLICATION_H
#define BCIEVENT_APPLICATION_H
#include "ApplicationBase.h"
#include "Actor.hpp"
#include "ApplicationWindow.h"
#include "GenericSignal.h"
#include "GlobalVariables.hpp"
#include "GraphDisplay.h"
#include "SignalProperties.h"
#include "States.hpp"
#include "TextField.h"
#include "WaitForProcessBlock.hpp"
#include <vector>
#include <thread>

namespace BCIEvent{
	class WaitForProcessBlock;

    class BCIEventApplication : public ApplicationBase{
	public:
	BCIEventApplication();
	~BCIEventApplication();
	void Publish() override;
	void Preflight(const SignalProperties&, SignalProperties&) const override;
	void Initialize(const SignalProperties&, const SignalProperties&) override;
	void Process(const GenericSignal&, GenericSignal&) override;
	void Resting(const GenericSignal&, GenericSignal&) override;
	void StartRun() override;
	void StopRun() override;
	void Halt() override;

	void setState(std::string name, int value);
	int getState(std::string name);
	
	const GenericSignal* currentSignal;

	private:
	ApplicationWindow& _display;
	std::unique_ptr<TextField> _messageField;
	std::thread _appLoopThread;
	bool _appLoop = true;

	void applicationLoop();
	void update(const GenericSignal&);
	void addActor(std::unique_ptr<Actor>);
	void addProcessBlock(std::shared_ptr<WaitForProcessBlock>);

	void OnPreflight(const SignalProperties& input) const;
	void OnInitialize(const SignalProperties& input);
	void OnStartRun();
	void OnStopRun();
	void OnHalt();

	/**
	 * Initializes BCIEvent framework 
	 */
	void InitBCIEvent();
	enum RunState {Running, Paused};
	RunState _currentState = Paused;	
	std::vector<std::unique_ptr<Actor>> _actors;
	std::shared_ptr<GlobalVariables> _globalVars;
	std::shared_ptr<BCIEvent::States> _states;
	std::vector<std::shared_ptr<WaitForProcessBlock>> _processBlocks;


	Actor* makeActor();
	void addState(std::string name, BCIState::StateType type);
	void uploadState(std::string name, int width);
    };
}

#endif
