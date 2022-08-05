#include "Parser.hpp"

namespace JSON {

bool
isCorrectExt(const std::string &filename) {
	std::string ext = ".json";

	int extLen = ext.length();
	int fileLen = filename.length();
	if (extLen >= fileLen)
		return false;

	return (filename.substr(fileLen - extLen, extLen) == ext);
}

bool
fileExists(const std::string &filename) {
	struct stat buf;   
	return (stat(filename.c_str(), &buf) == 0); 
}

Object *
parseFile(const std::string &filename) {

	if (!isCorrectExt(filename)) {
		throw std::runtime_error("Error:: File extension is not .json");
	}

	if (!fileExists(filename)) {
		throw std::runtime_error("Error:: File " + filename + " does not exist");
	}

	ifstream in(filename.c_str());
	if (!in.is_open()) {
		throw std::runtime_error("Error:: Cannot open file " + filename);
	}

	std::string raw = string(std::istreambuf_iterator<char>(in), 
				  			 std::istreambuf_iterator<char>());

	return parseRaw(raw);
}

Object *
parseRaw(std::string &raw) {
	
	Object *obj = new Object(raw);

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

}
