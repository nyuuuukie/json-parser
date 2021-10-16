#include "JSON.hpp"

namespace JSON {

	JSON::JSON(void) : _rawLoaded(false) {}

	JSON::JSON(const std::string &filename) 
	:_filename(filename), _rawLoaded(false) {}

	JSON::~JSON(void) {}

	JSON::JSON(const JSON &other) { 
		*this = other;
	}

	JSON &JSON::operator=(const JSON &other) {
		if (this != &other) {
			_filename = other._filename;
			_raw = other._raw;
			_rawLoaded = other._rawLoaded;
		}
		return *this;
	}

	// Methods
	void	JSON::loadFile(void) {
		
		ifstream in;
		in.open(_filename.c_str());

		if (!in.is_open()) {
			throw JSON::FileException("Cannot open file");
		}

		_raw = string(std::istreambuf_iterator<char>(in), 
						  std::istreambuf_iterator<char>());

		_rawLoaded = true;
	}

	void	JSON::setRaw(const std::string &rawjson) {
		_raw = rawjson;

		_rawLoaded = true;
	}

	Object *JSON::parse(void) {

		if (!isValidJSON() || !_rawLoaded) {

			return NULL;
		}

		Object *object = new Object(_raw);

		return object;
	}

	//Setters
	void JSON::setFilename(const std::string &filename) {
		_filename = filename;
	}

	//Getters
	const std::string &JSON::getFilename(void) const {
		return _filename;
	}

	//Checkers
	bool JSON::isValidJSON( void ) const {
		return isValidJSON(_raw);
	}

	bool JSON::isValidJSON( const string &rawjson ) const {

		bool curlyBracketsOK = (std::count(rawjson.begin(), rawjson.end(), '{') 
							==	std::count(rawjson.begin(), rawjson.end(), '}'));

		bool squareBracketsOK = (std::count(rawjson.begin(), rawjson.end(), '[')
		 					==	 std::count(rawjson.begin(), rawjson.end(), ']'));

		//bool attributesCountOK = (std::count(rawjson.begin(), rawjson.end(), ':')
		// 					==	 std::count(rawjson.begin(), rawjson.end(), ',') + 1);

		//bool doubleQuotesOK = (std::count(rawjson.begin(), rawjson.end(), '\"') % 2 == 0);
		//bool singleQuotesOK = (std::count(rawjson.begin(), rawjson.end(), '\'') % 2 == 0);

		return (curlyBracketsOK && squareBracketsOK); // && doubleQuotesOK && singleQuotesOK && attributesCountOK);
	}

	bool JSON::isCorrectExt( void ) const {
		std::string ext = ".json";

		int extLen = ext.length();
		int fileLen = _filename.length();

		return (_filename.substr(fileLen - extLen, extLen) == ext);
	}

	bool JSON::fileExists( void ) const {
		std::ifstream test;
		
		test.open(_filename.c_str());

		return test.is_open() ? true : false; 
	}

	//Exceptions
	JSON::FileException::FileException(std::string message) : _message(message) {}

	JSON::FileException::~FileException() throw() {}

	const char *JSON::FileException::what(void) const throw() {
		return _message.c_str();
	}

}
