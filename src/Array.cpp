#include "Array.hpp"

namespace JSON {

	Array::Array(string &rawjson) : AType("array", rawjson) {
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

		const string &raw = getRawRef();
		
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

		int inObject = 0;
		int inArray = 0;
		bool inDQuoteString = false;
		bool inQuoteString = false;

		size_t start = i;
		for (; i < s.length(); i++) {
			switch (s[i]) {
				case '{':
					if (!Utils::isEscChar(s, i, '{'))
						inObject++;
					break;
				case '}':
					if (!Utils::isEscChar(s, i, '}'))
						inObject--;
					break;
				case '[':
					if (!Utils::isEscChar(s, i, '['))
						inArray++;
					break;
				case ']':
					if (!Utils::isEscChar(s, i, ']'))
						inArray--;
					break;
				case '\'':
					if (!Utils::isEscChar(s, i, '\''))
						inQuoteString = !inQuoteString;
					break;
				case '\"':
					if (!Utils::isEscChar(s, i, '\"'))
						inDQuoteString = !inDQuoteString;
					break;
				case ',':
					if (!inArray && !inObject && !inQuoteString && !inDQuoteString && 
						!Utils::isEscChar(s, i - 1, ',') )
						return s.substr(start, i - start);
				case ' ':
				case '\n':
				case '\r':
				case '\t':
					if (!inArray && !inObject && !inQuoteString && !inDQuoteString)
						return s.substr(start, i - start);
			}
		}
		if (inArray || inObject || inQuoteString || inDQuoteString) {
			throw AType::ParseException("Array:: Unclosed context detected");
		}
		return s.substr(start, s.length() - start);
	}

	void Array::cutBraces(void) {

		string &raw = getRaw();
		const size_t len = raw.length();

		if (Utils::isEscChar(raw, 0, '['))
			throw AType::ParseException("Array:: Beginning must be non-escaped \"[\"");
		
		if (Utils::isEscChar(raw, len - 1, ']'))
			throw AType::ParseException("Array:: Ending must be non-escaped \"]\"");

		raw.erase(len - 1, 1);
		raw.erase(0, 1);
	}

	AType *Array::identify(string &rawvalue) {

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
				throw AType::ParseException("Array:: Unknown value type");
		}
	}

	void Array::parse(void) {

		AType *value = NULL;

		const string &raw = getRawRef();
		const size_t len = raw.length();
		const size_t values = countValues();

		size_t currentValue = 1;
		for (size_t i = 0; i < len && currentValue <= values;) {

			Utils::skipWhitespaces(raw, i);
			string rawvalue = getRawValue(raw, i);

			Utils::skipWhitespaces(raw, i);
			value = identify(rawvalue);

			Utils::skipWhitespaces(raw, i);

			if (currentValue != values && Utils::isEscChar(raw, i++, ',')) {
				throw AType::ParseException("Array:: Values must be separated with non-escaped \",\"");
			}

			_arr.push_back(value);
			currentValue++;
		}		
	}

}
