#ifndef STATE_H
#define STATE_H
#include <string>
#include "BCIEventApplication.hpp"

namespace BCIEvent{

    /**
     * A BCI2000 state. BCIEvent does not add these states automatically, you must add them
     * in the Publish function of BCIEventApplication.
     */
    enum StateType{ Boolean, u8, i8, u64, i64 };
    class State{
	BCIEventApplication* _app;
        std::string _name;
        StateType _type;
    public:
        State(BCIEventApplication* app, StateType type, std::string name);
        void set(int);	
        void set(bool);
	void set(char);
	int get();
	StateType type();
	std::string name();
    };
}
#endif
