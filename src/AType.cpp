#include "AType.hpp"

namespace JSON {

	Null null;
	Object nullobj;
	Array nullArr;

	Null *AType::getNull() const {
		return &null;
	}

	AType::AType() {}
	
	AType::AType(const string &name, string rawjson) 
	: _name(name), _rawjson(rawjson) {
		Utils::trim(rawjson, " \t\n\r");
	}

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

	string &AType::getRaw(void) {
		return _rawjson;
	}

	const string &AType::getRawRef(void) const {
		return _rawjson;
	}

	void AType::setRaw(const string &rawjson) {
		_rawjson = rawjson;	
	}

	const string &AType::getType(void) const {
		return _name;
	}
	
	double AType::toNum(void)  {
		JSON::Number *p1 = dynamic_cast<JSON::Number *>(this);
		if (p1 != NULL) {
			return p1->getValue();
		}

		JSON::Boolean *p2 = dynamic_cast<JSON::Boolean *>(this);
		if (p2 != NULL) {
			return p2->getValue();
		}
		return strtod("nan", NULL);
	}

	const string AType::toStr(void)  {

		JSON::String *p = dynamic_cast<JSON::String *>(this);
		if (p != NULL) {
			return p->getValue();
		}
		
		JSON::Null *p2 = dynamic_cast<JSON::Null *>(this);
		if (p2 != NULL) {
			return p2->getType();
		}
		
		JSON::Number *p3 = dynamic_cast<JSON::Number *>(this);
		if (p3 != NULL) {
			return Utils::to_string(p3->getValue());
		}
		
		JSON::Boolean *p4 = dynamic_cast<JSON::Boolean *>(this);
		if (p4 != NULL) {
			return p4->getValue() ? "true" : "false";
		}

		JSON::Object *p5 = dynamic_cast<JSON::Object *>(this);
		if (p5 != NULL) {
			return "[object]";
		}

		JSON::Array *p6 = dynamic_cast<JSON::Array *>(this);
		if (p6 != NULL) {
			return "[array]";
		}
		return "unknown";
	}

	Object *AType::toObj(void) {
		JSON::Object *ptr = dynamic_cast<JSON::Object *>(this);
		if (ptr != NULL) {
			return ptr;
		} else {
			return &nullobj;
		}
	}

	Array *AType::toArr(void) {
		JSON::Array *ptr = dynamic_cast<JSON::Array *>(this);
		if (ptr != NULL) {
			return ptr;
		} else {
			return &nullArr;
		}
	}

	bool AType::toBool(void) {
		JSON::Boolean *ptr = dynamic_cast<JSON::Boolean *>(this);
	
		if (ptr != NULL) {
			return ptr->getValue();
		}
		return false;
	}

	AType *AType::get(const string &key) {

		JSON::Object *obj = dynamic_cast<JSON::Object *>(this);

		if (obj != NULL) {
			return obj->getValue(key);
		} else {
			return &null;
		}
	}

	AType *AType::get(const size_t index) {

		JSON::Array *arr = dynamic_cast<JSON::Array *>(this);

		if (arr != NULL) {
			return arr->getValue(index);
		} else {
			return &null;
		}
	}

	bool AType::isNum(void) {
		return (dynamic_cast<JSON::Number *>(this) != NULL);
	}

	bool AType::isStr(void) {
		return (dynamic_cast<JSON::String *>(this) != NULL);
	}

	bool AType::isBool(void) {
		return (dynamic_cast<JSON::Boolean *>(this) != NULL);
	}

	bool AType::isArr(void) {
		return (dynamic_cast<JSON::Array *>(this) != NULL);
	}

	bool AType::isObj(void) {
		return (dynamic_cast<JSON::Object *>(this) != NULL);
	}

	bool AType::isNull(void) {
		return (this == &null || this == &nullobj || this == &nullArr);
	}

	AType::ParseException::ParseException(std::string message) : _message(message) {}

	AType::ParseException::~ParseException() throw() {}

	const char *AType::ParseException::what(void) const throw() {
		return _message.c_str();
	}

}
