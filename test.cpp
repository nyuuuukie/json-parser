#include "Parser.hpp"

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;
	
	JSON::Object *obj = NULL;
	try {
		// Parsing whole file in json object
		obj = JSON::parseFile(argv[1]);

		// get will return AType * that can be used to access internal 
		bool keyObj_key1 = obj->get("keyObj")->get("key1")->toBool();
		string keyObj_key2 = obj->get("keyObj")->get("key2")->toStr();
		double keyObj_key3 = obj->get("keyObj")->get("key3")->toNum();

		// Printing received values
		std::cout << "keyObj->key1: " << keyObj_key1 << std::endl;
		std::cout << "keyObj->key2: " << keyObj_key2 << std::endl;
		std::cout << "keyObj->key3: " << keyObj_key3 << std::endl;

		string keyArr_value1 = obj->get("keyArr")->get(0)->toStr();
		string keyArr_value2 = obj->get("keyArr")->get(1)->toStr();
		string keyArr_value3 = obj->get("keyArr")->get(2)->toStr();

		std::cout << "keyArr->value1: " << keyArr_value1 << std::endl;
		std::cout << "keyArr->value2: " << keyArr_value2 << std::endl;
		std::cout << "keyArr->value3: " << keyArr_value3 << std::endl;
		
		delete obj;
	} 
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
