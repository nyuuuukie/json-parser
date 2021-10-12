#include "JSON.hpp"

JSON::JSON(void) {}

JSON::JSON(const std::string &filename) :_filename(filename) {}

JSON::~JSON(void) {}

// Not implemented yet
JSON::JSON(const JSON & other) {}
JSON &JSON::operator=(const JSON & other) {}


// Methods
void JSON::serialize(const JSON &json) {

}

const JSON &JSON::parse(void) {

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

}

bool JSON::isCorrectExt( void ) const {
	
}

bool JSON::fileExists( void ) const {
	std::ifstream test(_filename); 
	
	return test ? true : false; 
}