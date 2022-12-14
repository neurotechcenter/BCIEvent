#ifndef BCIEVALUE_H
#define BCIEVALUE_H

#include <variant>
/*
* Type representing a value of a variable or parameter.
* A variable itself is typeless, and can hold a value of any of these four types, or be empty
* Exceptions caused by an incorrect value type will be thrown before the value is passed to any native c++ function
* inside the callback within a block.
* The reason for having an extra empty variant member instead of default initializing is so that errors relating to 
* uninitialized variables are explicit, rather than the code continuing to run with unintended values.
*/

typedef BCIEValue std::variant<int, bool, double, std::string, std::nullopt_t>;



#endif
