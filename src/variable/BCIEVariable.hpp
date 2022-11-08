#ifndef BCIEVENTVARIABLE_H
#define BCIEVENTVARIABLE_H

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

    class BCIEVariable{
	public:
		BCIEVariable() {}
		virtual ~BCIEVariable() {}
		virtual std::string name() const  = 0;

		virtual bool getAsBool() const = 0;
		virtual int getAsInt() const = 0;
		virtual double getAsDouble() const = 0;
	
		virtual bool operator==(const BCIEVariable& other) = 0;
		virtual bool operator==(const bool other) = 0;
		virtual bool operator==(const int other) = 0;
		virtual bool operator==(const double other) = 0;

		virtual void operator=(const BCIEVariable& other) = 0;
		virtual void operator=(const bool other) = 0;
		virtual void operator=(const int other) = 0;
		virtual void operator=(const double other) = 0;

    };
}

#endif
