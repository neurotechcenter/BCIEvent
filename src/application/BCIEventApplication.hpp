#ifndef BCIEVENT_APPLICATION_H
#define BCIEVENT_APPLICATION_H
#include "ApplicationBase.h"
#include "ApplicationWindow.h"
#include "GenericSignal.h"
#include "GraphDisplay.h"
#include "SignalProperties.h"
#include "TextField.h"
#include "BCIState.hpp"
#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include "BCIEValue.hpp"

namespace BCIEvent{
	class WaitForProcessBlock;
	class ProcessEvent;
	class Actor;
	class SequenceEnvironment;
	class Event;
	class Sequence;
	class Timer;

    class BCIEventApplication : public ApplicationBase {
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

	


	void addState(std::string name, BCIState::StateType type);
	void setState(std::string name, int value);
	int getState(std::string name);
	BCIState getBCIState(std::string name);

	int randInt(int lowerBound, int upperBound);

	void addVariable(std::string);
	void addVariable(std::string, BCIEValue);
	void addVariable(std::string, std::function<BCIEValue(SequenceEnvironment&)>, int);

	BCIEValue getVariable(std::string);
	void setVariable(std::string, BCIEValue);
	
	void addTimer(std::string name);
	Timer& getTimer(std::string name);

	const GenericSignal* currentSignal;
	GUI::GraphDisplay& getDisplay() { return _display; }

	void addEvent();
	void callEvent();

	void addBCI2000Event();
	void callBCI2000Event();

	void addFunction(std::string name, int numArgs, std::function<BCIEValue(std::vector<BCIEValue>)> fn);
	BCIEValue callFunction(std::string name, std::vector<BCIEValue> params);


	private:
	ApplicationWindow& _display;
	std::unique_ptr<TextField> _messageField;
	std::thread _appLoopThread;
	bool _appLoop = true;

	void initialize();
	void applicationLoop();
	void update(const GenericSignal&);
	void addActor(std::unique_ptr<Actor>);

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
	std::map<std::string, BCIEValue> _variables;
	std::priority_queue<VarInitializer, std::deque<VarInitializer>, VarInitCmp> _varInits;
	std::map<std::string, BCIState> _states;
	std::map<std::string, Event> _events;
	std::vector<std::string> _bci2000events;
	std::map < std::string, std::function<BCIEValue (Sequence&, std::vector<BCIEValue>)>> _functions;
	std::map<std::string, Timer> _timers;


	Actor* makeActor();
	void uploadState(std::string name, int width);
    };
}

#endif
