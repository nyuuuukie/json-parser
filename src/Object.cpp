#include "Object.hpp"

namespace JSON {

	Object::Object(string &rawjson) : AType("object", rawjson) {
		this->cutBraces();
		this->parse();
	}

	Object::Object(void) : AType("object", "") {
	}

	Object::~Object(void) {

		iterator beg = _map.begin();
		iterator end = _map.end();

		for (iterator it = beg; it != end; it++)
		{
			if (it->second != NULL) {
				delete it->second;
				it->second = NULL;
			}
		}
		_map.clear();
	}

	Object::Object(const Object &other) {
		*this = other;
	}

	Object &Object::operator=(const Object &other) { 
		if (this != &other) {
			this->operator=(other);
			_map = other._map;
		}
		return *this;
	}

	Object::iterator Object::begin(void) { return _map.begin(); }
	Object::iterator Object::end(void) { return _map.end(); }
	Object::const_iterator Object::begin(void) const { return _map.begin(); }
	Object::const_iterator Object::end(void) const { return _map.end(); }

	Object::iterator Object::getPair(const string &key) {
		iterator beg = _map.begin();
		iterator end = _map.end();

		for (iterator it = beg; it != end; it++) {
			if (it->first == key) {
				return it;
			}
		}
		return end;
	}

	AType *Object::getValue(const string &key) const {
		try
		{
			return _map.at(key);
		}
		catch(const std::out_of_range& e)
		{
			return dynamic_cast<AType *>(getNull());
		}
	}

	size_t Object::countKeys(int depth) const {
		size_t count = 0;
		int currentDepth = 1;
		
		const string &raw = getRawRef();
		const size_t len = raw.length();

		for (size_t i = 0; i < len; i++) {
			if (raw[i] == '{')
				currentDepth++;
			else if (raw[i] == '}')
				currentDepth--;
			else if (raw[i] == ':' && currentDepth <= depth)
				count++;
		}

		return count;
	}

	string Object::getRawKey(const string &s, size_t &i) {

		if (Utils::isEscChar(s, i, '\"')) {
			throw AType::ParseException("Object:: Key should start with non-escaped \"");
		}
		i++;

		size_t start = i;
		while (i < s.length() && s[i] != '\"') {
			i++;
		}
		
		if (Utils::isEscChar(s, i, '\"')) {
			throw AType::ParseException("Object:: Key should ends with non-escaped \"");
		}
		i++;

		if (i >= s.length()) {
 			throw AType::ParseException("Object:: Unexpected end of file");
		}

		return s.substr(start, i - start - 1);
	}

	string Object::getRawValue(const string &s, size_t &i) {

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
			throw AType::ParseException("Object:: Unclosed context detected");
		}

		return s.substr(start, s.length() - start);
	}

	void Object::cutBraces(void) {

		string &raw = getRaw();
		const size_t len = raw.length();

		if (Utils::isEscChar(raw, 0, '{')) {
			throw AType::ParseException("Object:: Beginning must be non-escaped \"{\"");
		}
		
		if (Utils::isEscChar(raw, len - 1, '}')) {
			throw AType::ParseException("Object:: Ending must be non-escaped \"}\"");
		}

		raw.erase(len - 1, 1);
		raw.erase(0, 1);
	}

	AType *Object::identify(string &rawvalue) {
		
		if ((rawvalue[0] == '-' && isdigit(rawvalue[1])) || (isdigit(rawvalue[0])))
			return new JSON::Number(rawvalue);

		switch (rawvalue[0]) {
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
				throw AType::ParseException("Object:: Unknown value type");
		}
	}

	void Object::parse(void) {
		
		AType *value = NULL;

		const string &raw = getRawRef();
		const size_t len = raw.length();
		const size_t keys = countKeys();
		
		size_t currentKey = 1;
		for (size_t i = 0; i < len && currentKey <= keys;) {
			
			Utils::skipWhitespaces(raw, i);	
			string rawkey = getRawKey(raw, i);
			Utils::skipWhitespaces(raw, i);
			
			if (Utils::isEscChar(raw, i++, ':')) {
				throw AType::ParseException("Object:: Key-value must be separated with non-escaped \":\"");	
			}
			
			Utils::skipWhitespaces(raw, i);
			string rawvalue = getRawValue(raw, i);
			Utils::skipWhitespaces(raw, i);
	
			value = identify(rawvalue);
			Utils::skipWhitespaces(raw, i);

			if (currentKey != keys && Utils::isEscChar(raw, i++, ',')) {
				throw AType::ParseException("Object:: Key-value pairs must be separated with non-escaped \",\"");
			}

			std::pair<JSON::Object::iterator, bool> res;
			res = _map.insert(std::make_pair(rawkey, value));
			if (res.second == false) {
				throw AType::ParseException("Object:: Duplicated key \"" + rawkey + "\"");
			}
			currentKey++;
		}
	}

}
