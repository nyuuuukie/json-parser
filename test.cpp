#include "Parser.hpp"

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;
	
	try {
		//Converting filename to string
		string filename(argv[1]);
		
		//Creating json object
		JSON::Parser parser(filename);

		//Trying to load json file
		parser.loadFile();

		//Parsing whole file in json object
		JSON::Object *obj = parser.parse();

		//Using method get to access object fields and converting it to primitive type
		// string keyString = obj->get("keyString")->toStr();
		// double keyDouble = obj->get("keyNumber")->toNum();
		
		//get method will return a pointer to base type, that can be used to access internal 
		bool keyObj_key1 = obj->get("keyObj")->get("key1")->toBool();
		string keyObj_key2 = obj->get("keyObj")->get("key2")->toStr();
		double keyObj_key3 = obj->get("keyObj")->get("key3")->toNum();

		// bool keyBool1 = obj->get("keyBool1")->toBool();
		// bool keyBool2 = obj->get("keyBool2")->toBool();
		
		//Printing received values
		// std::cout << "keyString: " << keyString << std::endl;
		// std::cout << "keyDouble: " << keyDouble << std::endl;

		std::cout << "keyObj->key1: " << keyObj_key1 << std::endl;
		std::cout << "keyObj->key2: " << keyObj_key2 << std::endl;
		std::cout << "keyObj->key3: " << keyObj_key3 << std::endl;

		// std::cout << "keyBool1: " << keyBool1 << std::endl;
		// std::cout << "keyBool2: " << keyBool2 << std::endl;


		string keyArr_value1 = obj->get("keyArr")->get(0)->toStr();
		string keyArr_value2 = obj->get("keyArr")->get(1)->toStr();
		string keyArr_value3 = obj->get("keyArr")->get(2)->toStr();

		std::cout << "keyArr->value1: " << keyArr_value1 << std::endl;
		std::cout << "keyArr->value2: " << keyArr_value2 << std::endl;
		std::cout << "keyArr->value3: " << keyArr_value3 << std::endl;
		
		
		string proxy = obj->get("proxytest")->get("proxy")->get("pass")->toStr();
		std::cout << "pass: " << proxy << std::endl;

		delete obj;	
	} 
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
