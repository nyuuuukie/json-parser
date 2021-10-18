#include "AType.hpp"

namespace JSON {
	
	AType::AType() {}
	
	AType::AType(const string &name, const string &rawjson) 
	: _name(name), _rawjson(rawjson) {}

	AType::~AType() {}
		
	AType::AType(const AType &other) { 
		*this = other; 
	}

	AType &AType::operator=(const AType &other) {
		if (this != &other) {
			_rawjson = other._rawjson;
		}
		return *this;
	}

	const string &AType::getRaw(void) const {
		return _rawjson;
	}

	void AType::setRaw(const string &rawjson) {
		_rawjson = rawjson;	
	}

	const string &AType::getType(void) const {
		return _name;
	}

	
	double AType::toNum(void)  {
		JSON::Number *ptr = dynamic_cast<JSON::Number *>(this);
	
		if (ptr != NULL) {
			return ptr->getValue();
		}
		return strtod("nan", NULL);
	}

	const string AType::toStr(void)  {
		JSON::String *ptr = dynamic_cast<JSON::String *>(this);
	
		if (ptr != NULL) {
			return ptr->getValue();
		}
		return "";
	}

	AType *AType::get(const string &key) {

		JSON::Object *obj = dynamic_cast<JSON::Object *>(this);

		if (obj != NULL) {
			return obj->getValue(key);
		} else {
			return this;
		}
	}

	AType *AType::get(const size_t index) {

		JSON::Array *arr = dynamic_cast<JSON::Array *>(this);

		if (arr != NULL) {
			return arr->getValue(index);
		} else {
			return this;
		}
	}

	bool AType::toBool(void) {
		JSON::Boolean *ptr = dynamic_cast<JSON::Boolean *>(this);
	
		if (ptr != NULL) {
			return ptr->getValue();
		}
		return false;
	}



	AType::ParseException::ParseException(std::string message) : _message(message) {}

	AType::ParseException::~ParseException() throw() {}

	const char *AType::ParseException::what(void) const throw() {
		return _message.c_str();
	}

}
