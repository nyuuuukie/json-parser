#include "JSON.hpp"

namespace JSON {

	JSON::JSON(void) : _rawLoaded(false) {}

	JSON::JSON(const std::string &filename) 
	:_filename(filename), _rawLoaded(false) {
		this->loadFile();
	}

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
		
		if (!isCorrectExt()) {
			throw JSON::FileException("File extension is not .json");
		}

		if (!fileExists()) {
			throw JSON::FileException("File does not exist");
		}

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

		return new Object(_raw);
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

		return (curlyBracketsOK && squareBracketsOK);
	}

	bool JSON::isCorrectExt( void ) const {
		std::string ext = ".json";

		int extLen = ext.length();
		int fileLen = _filename.length();
		if (extLen >= fileLen)
			return false;

		return (_filename.substr(fileLen - extLen, extLen) == ext);
	}

	bool JSON::fileExists( void ) const {
		struct stat buf;   
  		return (stat(_filename.c_str(), &buf) == 0); 
	}

	//Exceptions
	JSON::FileException::FileException(std::string message) : _message(message) {}

	JSON::FileException::~FileException() throw() {}

	const char *JSON::FileException::what(void) const throw() {
		return _message.c_str();
	}

}
