#ifndef BCIEVALUE_H
#define BCIEVALUE_H
#include <functional>
#include <variant>
#include <string>
#include <optional>
#include "SequenceEnvironment.hpp"
/*
* Type representing a value of a variable or parameter.
* A variable itself is typeless, and can hold a value of any of these four types, or be empty
* Exceptions caused by an incorrect value type will be thrown before the value is passed to any native c++ function
* inside the callback within a block.
* The reason for having an extra empty variant member instead of default initializing is so that errors relating to 
* uninitialized variables are explicit, rather than the code continuing to run with unintended values.
*/
namespace BCIEvent {

	typedef std::variant<int, bool, double, std::string, std::nullopt_t> BCIEValue;
	typedef std::tuple < std::string, std::function<BCIEValue(SequenceEnvironment&)>, int> VarInitializer;
	class VarInitCmp {
		public:
		bool operator()(const VarInitializer& l, const VarInitializer& r) const {
			return std::get<2>(l) > std::get<2>(r);
		}
	};
}



#endif
