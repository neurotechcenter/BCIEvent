#ifndef PARAMDEF_HPP
#define PARAMDEF_HPP
#include <string>

namespace BCIEvent_N {
	struct ParamDef {
		enum DataType {
			Int,
			String,
			Float
		};
		std::string path;
		DataType type;
		BCIEValue value;
		bool isList;

		ParamDef(std::string _path, DataType _type, bool _isList) : path{ _path }, type{ _type }, isList{ _isList } {}

		std::string typeStr() const {
			std::string r;
			switch (type){
			case Int:
				r = "int";
				break;
			case String:
				r = "string";
				break;
			case Float:
				r = "float";
				break;
			}
			r += isList ? "list" : "";
			return r;
		}
	};
}

#endif