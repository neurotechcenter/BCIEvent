#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <cmath>
#include <exception>

namespace BCIEvent{
    /**
     * Represents a general variable. BCIEvent does no type checking,
     * so it's on you to have your variables correct. 
     * Any BCIEvent function will take any variable,
     * but its value may be converted to fit the input type.
     */

    class Variable{
	std::string _name;

	public:
	Variable(std::string name) { _name = name; }
	std::string name() { return _name; }

	virtual bool getAsBool() const = 0;
	virtual int getAsInt() const = 0;
	virtual double getAsDouble() const = 0;
	
	virtual bool operator==(const Variable& other);
	virtual bool operator==(const bool other) = 0;
	virtual bool operator==(const int other) = 0;
	virtual bool operator==(const double other) = 0;

	virtual void operator=(const Variable& other) = 0;
	virtual void operator=(const bool other) = 0;
	virtual void operator=(const int other) = 0;
	virtual void operator=(const double other) = 0;

    };
}

#endif
