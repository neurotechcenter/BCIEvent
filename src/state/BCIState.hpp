// This file is part of BCIEvent, a framework for developing 
// asynchronous, event-driven native BCI2000 application modules.
//
// Copyright (C) 2022-23 Ty Butler
// tytbu@tytbutler.com
//
// BCIEvent is distrubuted under the terms of the GNU General Public License, Version 3.
// You should have received a copy of the GNU GPL with BCIEvent. If not, go to 
//     https://www.gnu.org/licenses/
#ifndef BCISTATE_H
#define BCISTATE_H
#include <string>

namespace BCIEvent_N{

    /**
     * A BCI2000 state. BCIEvent does not add these states automatically, you must add them
     * in the Publish function of BCIEventApplication.
     */
    class BCIEventApplication;
    class BCIState{
    public:
	enum StateType { Boolean, u8, i8, u32, i32 };
    private:
	BCIEventApplication* _app;
        std::string _name;
        StateType _type;
    public:
        BCIState(BCIEventApplication* app, StateType type, std::string name);
        void set(int32_t);	
        void set(bool);
	    void set(int8_t);
	int get() const;
	StateType type() const { return _type; };
	std::string name() const { return _name; };
    };
}
#endif

