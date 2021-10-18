#include "Array.hpp"

namespace JSON {

	Array::Array(const string &rawjson) : AType("array", rawjson) {}

	Array::Array(void) : AType("array", "") {}

	Array::~Array(void) {}

	Array::Array(const Array &other) {
		*this = other;
	}

	Array &Array::operator=(const Array &other) { 
		if (this != &other) {
			this->operator=(other);
			_arr = other._arr;
		}
		return *this;
	}

	AType *Array::getValue(const size_t index) const {
		return _arr[index];
	}
	
	string Object::getRawValue(const string &s, size_t &i) {

	int depthCurly = 0;
	int depthSquare = 0;

	size_t len = s.length();
	size_t start = i;
	for (; i < len; i++) {
		switch (s[i]) {
			case '{':
				depthCurly++;
				break;
			case '}':
				depthCurly--;
				break;
			case '[':
				depthSquare++;
				break;
			case ']':
				depthSquare--;
				break;
			case ',':
				if (s[i - 1] != '\\' && !depthSquare && !depthCurly)
					return s.substr(start, i - start);
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				if (!depthSquare && !depthCurly)
					return s.substr(start, i - start);
		}
	}
	throw AType::ParseException("Cannot get value of object");
}

	void Array::parse(void) {
		AType *value = NULL;
	
		const string &raw = getRaw();
		const size_t len = raw.length();
		const size_t keys = countKeys();
		
		size_t currentKey = 1;
		//if first not { parse error
		char typeSignature; 
		for (size_t i = 0; i < len && currentKey <= keys; i++) {
			
			skipWhitespaces(raw, i);	
			string rawkey = getRawKey(raw, i);
			
			skipWhitespaces(raw, i);
			checkColon(raw, i);
			
			skipWhitespaces(raw, i);
			typeSignature = raw[i];
			string rawvalue = getRawValue(raw, i);
			
			skipWhitespaces(raw, i);
			value = identify(rawvalue);

			skipWhitespaces(raw, i);

			if (currentKey != keys)
				checkComma(raw, i);
			
			//check for existence value
			_map.insert(std::pair<string, AType *>(rawkey, value));
			currentKey++;
		}	
	}
}
