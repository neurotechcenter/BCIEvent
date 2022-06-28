#include "State.hpp"
#include "BCIEventApplication.hpp"
#include <algorithm>
#include <stdexcept>

using namespace BCIEvent;


int signbit(int val){
    if (val < 0){
	return 1;
    }
    return 0;
}


State::State(BCIEventApplication* app, StateType type, std::string name){
    _type = type;
    _name = name;
    _app = app;

}

void State::set(bool value){
   _app->setState(_name, value);
   if (_type == StateType::i8 || _type == StateType::i64){
	_app->setState(_name + "_sign", 0);
   }
}

void State::set(char value){
    if (_type == Boolean){
	throw std::invalid_argument("Can't set a Boolean state to a 8-bit number");
    } else if (_type == u8 || _type == u64) {
	_app->setState(_name, value > 0 ? value : 0);
    } else if (_type == i8 || _type == i64) {
        _app->setState(_name, std::abs(value));
        _app->setState(_name + "_sign", signbit(value));
    }
}


void State::set(int value){
    if (_type == Boolean || _type == u8 || _type == i8){
	throw std::invalid_argument("Can't set a boolean or 8-bit state to a 64-bit number");
    } else if (_type == u64) {
	_app->setState(_name, value > 0 ? value : 0);
    } else if (_type == i64) {
	_app->setState(_name, std::abs(value));
	_app->setState(_name + "_sign", signbit(value));
    }

}

int State::get(){
    int ret = _app->getState(_name);
    if (_type == i8 || _type == i64){
	ret *= _app->getState(_name + "_sign") == 0 ? 1 : -1;
    }
    return ret;
}
