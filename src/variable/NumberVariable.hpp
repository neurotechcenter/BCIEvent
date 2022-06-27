#ifndef NUMBERVARIABLE_H
#define NUMBERVARIABLE_H
#include "Variable.hpp"
#include <cmath>
#include <stdexcept>

namespace BCIEvent{
    class NumberVariable : public Variable{
	double _value;

	public:
	bool getAsBool() { throw std::logic_error("Cannot get number as boolean"); }
	int getAsInt() { 
	    if (std::floor(std::abs(_value)) == std::abs(_value)){
		return _value;
	    }
	    else {
		throw std::logic_error("Cannot get integer from non-whole number value.");
	    }
	}
	double getAsDouble() { return _value; }
	
	bool operator==(const Variable &other) { return _value == other.getAsDouble(); }
	bool operator==(const bool other) { throw std::invalid_argument("Cannot compare bool and number"); }
	bool operator==(const int other) { return _value == (float) other; }
	bool operator==(const double other) { return _value == other; }
	

	void operator=(const Variable &other) { _value = other.getAsDouble(); }
	void operator=(const bool other) { throw std::invalid_argument("Cannot assign bool to number"); }
	void operator=(const int other) { _value = other; }
	void operator=(const double other) { _value = other; }
    };
}

#endif
