#include "String.hpp"

namespace JSON
{
	String::String(const string &rawjson) : AType("string", rawjson) {
		this->parse();
	}

	String::~String() {}
	String::String() : AType("string", "") {}

	String::String(const String &other) {
		*this = other;
	}
	
	String &String::operator=(const String &other) {
		if (this != &other) {
			this->AType::operator=(other);
			_value = other._value;
		}
		return *this;
	}

	const string &String::getValue(void) const {
		return _value;
	}

	void String::parse(void) {

		const string &raw = getRaw();
		const size_t len = raw.length();

		_value.resize(len);
		for (size_t i = 0, j = 0; i < len; i++) {
			if (raw[i] != '\"' || (raw[i] == '\"' && i != 0 && raw[i - 1] == '\\')) {
				_value[j++] = raw[i];
			}
		}
	}
}
