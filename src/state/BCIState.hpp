#ifndef BCISTATE_H
#define BCISTATE_H
#include <string>

namespace BCIEvent{

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
