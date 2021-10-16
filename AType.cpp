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

	
	Number *AType::toNum(void)  {
		return reinterpret_cast<JSON::Number *>(this);	
	}

	Object *AType::toObj(void)  {
		return reinterpret_cast<JSON::Object *>(this);	
	}

	String *AType::toStr(void)  {
		return reinterpret_cast<JSON::String *>(this);	
	}

	Null  *AType::toNull(void) {
		return reinterpret_cast<JSON::Null *>(this);	
	}

	Array *AType::toArray(void) {
		return reinterpret_cast<JSON::Array *>(this);	
	}

	Boolean *AType::toBool(void) {
		return reinterpret_cast<JSON::Boolean *>(this);
	}



	AType::ParseException::ParseException(std::string message) : _message(message) {}

	AType::ParseException::~ParseException() throw() {}

	const char *AType::ParseException::what(void) const throw() {
		return _message.c_str();
	}

}
