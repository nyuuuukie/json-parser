#include "Boolean.hpp"

namespace JSON
{
	Boolean::Boolean(const string &rawjson) : AType("boolean", rawjson) {
	}

	Boolean::~Boolean() {}
	Boolean::Boolean() : AType("boolean", "") {}

	Boolean::Boolean(const Boolean &other) {
		*this = other;
	}
	
	Boolean &Boolean::operator=(const Boolean &other) {
		if (this != &other) {
			this->AType::operator=(other);
			_value = other._value;
		}
		return *this;
	}

	bool Boolean::getValue(void) const {
		return _value;
	}
	
	void Boolean::parse(void) {

		if (getRawRef() == "true") {
			_value = true;
		}
		else if (getRawRef() == "false") {
			_value = false;
		}
		else {
			throw ParseException("Unknown boolean value");
		}
	}
}
