#include "BCIState.hpp"
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


BCIState::BCIState(BCIEventApplication* app, StateType type, std::string name){
    _type = type;
    _name = name;
    _app = app;

}

void BCIState::set(bool value){
   _app->setState(_name, value);
   if (_type == i8 || _type == i32){
	_app->setState(_name + "_sign", 0);
   }
}

void BCIState::set(int8_t value){
    if (_type == Boolean){
	throw std::invalid_argument("Can't set a Boolean state to a 8-bit number");
    } else if (_type == u8 || _type == u32) {
	_app->setState(_name, value > 0 ? value : 0);
    } else if (_type == i8 || _type == i32) {
        _app->setState(_name, std::abs(value));
        _app->setState(_name + "_sign", signbit(value));
    }
}


void BCIState::set(int32_t value){
    if (_type == Boolean || _type == u8 || _type == i8){
	throw std::invalid_argument("Can't set a boolean or 8-bit state to a 64-bit number");
    } else if (_type == u32) {
	_app->setState(_name, value > 0 ? value : 0);
    } else if (_type == i32) {
	_app->setState(_name, std::abs(value));
	_app->setState(_name + "_sign", signbit(value));
    }

}

int BCIState::get() const{
    int ret = _app->getState(_name);
    if (_type == i8 || _type == i32){
	ret *= _app->getState(_name + "_sign") == 0 ? 1 : -1;
    }
    return ret;
}

