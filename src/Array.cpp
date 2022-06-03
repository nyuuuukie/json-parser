#include "Array.hpp"

namespace JSON {

	Array::Array(const string &rawjson) : AType("array", rawjson) {
		this->cutBraces();
		this->parse();
	}

	Array::Array(void) : AType("array", "") {
	}

	Array::~Array(void) {

		iterator beg = _arr.begin();
		iterator end = _arr.end();

		for (iterator it = beg; it != end; it++)
		{
			if (*it != NULL) {
				delete *it;
				*it = NULL;
			}
		}
		_arr.clear();
	}

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

	Array::iterator Array::begin(void) { return _arr.begin(); }
	Array::iterator Array::end(void) { return _arr.end(); }
	Array::const_iterator Array::begin(void) const { return _arr.begin(); }
	Array::const_iterator Array::end(void) const { return _arr.end(); }

	AType *Array::getValue(const size_t index) const {
		if (index >= _arr.size()) {
			return dynamic_cast<AType *>(getNull());
		}
		return _arr[index];
	}

	size_t Array::countValues(int depth) const {

		size_t count = 0;
		int currentDepth = 1;

		const string &raw = getRaw();
		
		// Empty array
		if (raw.find_first_not_of(' ') == std::string::npos)
			return 0;
		
		const size_t len = raw.length();
		for (size_t i = 0; i < len; i++) {
			if (raw[i] == '[')
				currentDepth++;
			else if (raw[i] == ']')
				currentDepth--;
			else if (raw[i] == ',' && currentDepth <= depth)
				count++;
		}
		count++;
		
		return count;
	}

	string Array::getRawValue(const string &s, size_t &i) {

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
		return s.substr(start, i - start);
	}

	void Array::cutBraces(void) {
		size_t i = 0;

		const string &raw = getRaw();
		const size_t len = raw.length();
		int depth = 0;
		Utils::skipWhitespaces(raw, i);

		if (raw[i] != '[')
			throw AType::ParseException("Array must start with \"[\"");

		size_t start = i;
		size_t end = i;
		for (; i < len; i++) {
			if (raw[i] == '[') {
				if (!depth)
					start = i;
				depth++;
			}
			else if (raw[i] == ']') {
				depth--;
				if (!depth)
					end = i;
			}

			if (depth == 0) {
				break ;
			}	
		}

		if (raw[i] != ']')
			throw AType::ParseException("Array must end with \"]\"");

		setRaw(raw.substr(start + 1, end - start - 1));
	}

	AType *Array::identify(const string &rawvalue) {

		if ((rawvalue[0] == '-' && isdigit(rawvalue[1])) || (isdigit(rawvalue[0])))
			return new JSON::Number(rawvalue);

		switch (rawvalue[0])
		{
			case 't':
			case 'f':
				return new JSON::Boolean(rawvalue);
			case '{':
				return new JSON::Object(rawvalue);
			case '[':
				return new JSON::Array(rawvalue);
			case 'n':
				return new JSON::Null(rawvalue);
			case '\"':
				return new JSON::String(rawvalue);
			default:
				throw AType::ParseException("Unknown value type");
		}
	}

	void Array::parse(void) {

		AType *value = NULL;

		const string &raw = getRaw();
		const size_t len = raw.length();
		const size_t values = countValues();

		size_t currentValue = 1;
		char typeSignature; 
		for (size_t i = 0; i < len && currentValue <= values; i++) {

			Utils::skipWhitespaces(raw, i);
			typeSignature = raw[i];
			string rawvalue = getRawValue(raw, i);

			Utils::skipWhitespaces(raw, i);
			value = identify(rawvalue);

			Utils::skipWhitespaces(raw, i);

			if (currentValue != values && !Utils::checkComma(raw, i))
				throw AType::ParseException("values must be separated with \",\"");

			_arr.push_back(value);
			currentValue++;
		}		
	}

}
