#include "Object.hpp"

namespace JSON {

Object::Object(const string &rawjson) : AType("object", rawjson) {
	this->nullobj = new Null("null");
	this->cutBraces();
	this->parse();
}

Object::Object(void) : AType("object", "") {
	this->nullobj = new Null("null");
}

Object::~Object(void) {
	delete nullobj;

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
		return dynamic_cast<AType *>(nullobj);
	}
}

size_t Object::countKeys(int depth) const {
	size_t count = 0;
	int currentDepth = 1;
	
	const string &raw = getRaw();
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

	if (s[i++] != '\"')
		throw AType::ParseException("Key should start with \"");

	size_t start;
	size_t count = 0;
	size_t len = s.length();
	for (start = i; i < len; i++, count++) {
		if (s[i] == '\"' && s[i - 1] != '\\') {
			i++;
			break;
		}
	}
	
	if (s[i - 1] != '\"')
		throw AType::ParseException("Key should ends with \"");

	if (i == len)
		throw AType::ParseException("Unexpected end of file");

	return s.substr(start, count);
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


size_t Object::endOfScope(const std::string &text, size_t beg, char begScope, char endScope) {

	int depth = 0;

	size_t pos;
	size_t len = text.length();
	for (pos = beg; pos < len; pos++) {
		if (text[pos] == begScope)
			depth++;
		else if (text[pos] == endScope) {
			if (depth > 0) {
				depth--;
			}
			else {
				break ;
			}
		}
	}

	return pos;
}

//void skipWhitespaces(const string &s, size_t &i) {

//	const size_t len = s.length();
//	for (; i < len; i++) {
//		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\r' && s[i] != '\t')
//			break ;
//	}
//}

//void skipWhitespacesBack(const string &s, size_t &i) {

//	for (; i > 0; i--) {
//		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\r' && s[i] != '\t')
//			break ;
//	}
//}

//void checkColon(const string &s, size_t &i) {
//	if (s[i] != ':' || (s[i] == ':' && s[i - 1] == '\\'))
//		throw AType::ParseException("Key and value parts must be separated with \":\"");
//	i++;
//}

//void checkComma(const string &s, size_t &i) {
//	if (s[i] != ',' || (s[i] == ',' && s[i - 1] == '\\'))
//		throw AType::ParseException("Key-value pair must be separated with \",\"");
//	i++;
//}

void Object::cutBraces(void) {
	size_t i = 0;
	
	const string &raw = getRaw();
	const size_t len = raw.length();
	int depth = 0;
	Utils::skipWhitespaces(raw, i);

	if (raw[i] != '{')
		throw AType::ParseException("Object must start with \"{\"");
	
	size_t start = i;
	size_t end = i;
	for (; i < len; i++) {
		if (raw[i] == '{') {
			if (!depth)
				start = i;
			depth++;
		}
		else if (raw[i] == '}') {
			depth--;
			if (!depth)
				end = i;
		}

		if (depth == 0) {
			break ;
		}	
	}
	if (raw[i] != '}')
		throw AType::ParseException("Object must end with \"}\"");

	setRaw(raw.substr(start + 1, end - start - 1));
}

AType *Object::identify(const string &rawvalue) {
	
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

void Object::parse(void) {
	
	AType *value = NULL;
	
	const string &raw = getRaw();
	const size_t len = raw.length();
	const size_t keys = countKeys();
	
	size_t currentKey = 1;
	//if first not { parse error
	char typeSignature; 
	for (size_t i = 0; i < len && currentKey <= keys; i++) {
		
		Utils::skipWhitespaces(raw, i);	
		string rawkey = getRawKey(raw, i);
		
		Utils::skipWhitespaces(raw, i);
		
		if (!Utils::checkColon(raw, i))
			throw AType::ParseException("Key-value pair must be separated with \",\"");
		
		Utils::skipWhitespaces(raw, i);
		typeSignature = raw[i];
		string rawvalue = getRawValue(raw, i);
		
		Utils::skipWhitespaces(raw, i);
		value = identify(rawvalue);

		Utils::skipWhitespaces(raw, i);

		if (currentKey != keys && !Utils::checkComma(raw, i))
			throw AType::ParseException("Key-value pair must be separated with \",\"");

		//check for existence value
		_map.insert(std::pair<string, AType *>(rawkey, value));
		currentKey++;
	}
}

}
