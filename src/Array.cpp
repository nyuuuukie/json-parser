#include "Array.hpp"

namespace JSON {

	Array::Array(string &rawjson) : AType("array", rawjson) {
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

	size_t Array::countValues(void) const {

		size_t count = 0;
		int inObject = 0;
		int inArray = 0;
		bool inDQuoteString = false;
		bool inQuoteString = false;
		
		const string &s = getRawRef();
		const size_t len = s.length();

		// Empty array
		if (s.find_first_not_of(' ') == std::string::npos)
			return 0;
		
		for (size_t i = 0; i < len; i++) {
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
					if (!Utils::isEscChar(s, i, ',') && !inArray && !inObject &&
						!inQuoteString && !inDQuoteString)
						count++;
					break;
				default:
					break;
			}
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

		AType *val = NULL;

		if ((rawvalue[0] == '-' && isdigit(rawvalue[1])) || (isdigit(rawvalue[0]))) {
			val = new JSON::Number(rawvalue);
		} else {
			switch (rawvalue[0]) {
				case 't':
				case 'f':
					val = new JSON::Boolean(rawvalue);
					break ;
				case '{':
					val = new JSON::Object(rawvalue);
					break ;
				case '[':
					val = new JSON::Array(rawvalue);
					break ;
				case 'n':
					val = new JSON::Null(rawvalue);
					break ;
				case '\"':
					val = new JSON::String(rawvalue);
					break ;
				default:
					throw AType::ParseException("Array:: Unknown value type");
			}
		}

		if (val == NULL) {
			throw std::runtime_error("Array:: Allocation failed");
		}

		try {
			val->parse();
		} catch (std::exception &e) {
			delete val;
			throw std::runtime_error(std::string(e.what()));
		}

		return val;
	}

	void Array::parse(void) {
		this->cutBraces();

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
				if (value != NULL) {
					delete value;
				}
				throw AType::ParseException("Array:: Values must be separated with non-escaped \",\"");
			}

			_arr.push_back(value);
			currentValue++;
		}		
	}

}
