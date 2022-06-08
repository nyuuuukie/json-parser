#include "Number.hpp"

namespace JSON
{
	Number::Number(const string &rawjson) : AType("number", rawjson) {
		this->parse();
	}

	Number::~Number() {}
	Number::Number() : AType("number", "") {}

	Number::Number(const Number &other) {
		*this = other;
	}
	
	Number &Number::operator=(const Number &other) {
		if (this != &other) {
			this->AType::operator=(other);
			_value = other._value;
		}
		return *this;
	}

	double Number::getValue(void) const {
		return _value;
	}

	void Number::parse(void) {

		const string &raw = getRawRef();

		char *end = 0;
		double num = std::strtod(raw.c_str(), &end);
	
		std::string e(end);
		if (e != "" && e != "f")
			throw AType::ParseException("Invalid symbols in number");

		_value = num;
	}
}
