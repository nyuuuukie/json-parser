#include "Parser.hpp"

namespace JSON {

	Parser::Parser(void) : _rawLoaded(false) {}

	Parser::Parser(const std::string &filename) 
	:_filename(filename), _rawLoaded(false) {
		this->loadFile();
	}

	Parser::~Parser(void) {}

	Parser::Parser(const Parser &other) { 
		*this = other;
	}

	Parser &Parser::operator=(const Parser &other) {
		if (this != &other) {
			_filename = other._filename;
			_raw = other._raw;
			_rawLoaded = other._rawLoaded;
		}
		return *this;
	}

	// Methods
	void	Parser::loadFile(void) {
		
		if (!isCorrectExt()) {
			throw Parser::FileException("Error:: File extension is not .json");
		}

		if (!fileExists()) {
			throw Parser::FileException("Error:: File does not exist");
		}

		ifstream in;
		in.open(_filename.c_str());
		if (!in.is_open()) {
			throw Parser::FileException("Error:: Cannot open file");
		}

		_raw = string(std::istreambuf_iterator<char>(in), 
						std::istreambuf_iterator<char>());

		_rawLoaded = true;
	}

	void	Parser::setRaw(const std::string &rawjson) {
		_raw = rawjson;

		_rawLoaded = true;
	}

	Object *Parser::parse(void) {

		if (!_rawLoaded) {
			return NULL;
		}

		Object *obj = new Object(_raw);
		if (obj == NULL) {
			throw std::runtime_error("Object:: Allocation failed");
		}

		try {
			obj->parse();
		} catch (std::exception &e) {
			delete obj;
			throw std::runtime_error(e.what());
		}

		return obj;
	}

	//Setters
	void Parser::setFilename(const std::string &filename) {
		_filename = filename;
	}

	//Getters
	const std::string &Parser::getFilename(void) const {
		return _filename;
	}

	//Checkers
	bool Parser::isValidJSON( void ) const {
		return isValidJSON(_raw);
	}

	bool Parser::isValidJSON( const string &rawjson ) const {

		bool curlyBracketsOK = (std::count(rawjson.begin(), rawjson.end(), '{') 
							==	std::count(rawjson.begin(), rawjson.end(), '}'));

		bool squareBracketsOK = (std::count(rawjson.begin(), rawjson.end(), '[')
		 					==	 std::count(rawjson.begin(), rawjson.end(), ']'));

		return (curlyBracketsOK && squareBracketsOK);
	}

	bool Parser::isCorrectExt( void ) const {
		std::string ext = ".json";

		int extLen = ext.length();
		int fileLen = _filename.length();
		if (extLen >= fileLen)
			return false;

		return (_filename.substr(fileLen - extLen, extLen) == ext);
	}

	bool Parser::fileExists( void ) const {
		struct stat buf;   
  		return (stat(_filename.c_str(), &buf) == 0); 
	}

	//Exceptions
	Parser::FileException::FileException(std::string message) : _message(message) {}

	Parser::FileException::~FileException() throw() {}

	const char *Parser::FileException::what(void) const throw() {
		return _message.c_str();
	}

}
