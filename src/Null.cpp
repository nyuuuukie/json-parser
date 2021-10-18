#include "Null.hpp"

namespace JSON
{
	Null::Null(const string &rawjson) : AType("null", rawjson) {}

	Null::~Null() {}
	Null::Null() : AType("null", "") {}

	Null::Null(const Null &other) {
		*this = other;
	}
	
	Null &Null::operator=(const Null &other) {
		if (this != &other) {
			this->AType::operator=(other);
			_value = other._value;
		}
		return *this;
	}

	void Null::parse(void) {

		if (getRaw() != "null")
			throw ParseException("Failed to parse null");

		_value = NULL;		
	}

}
