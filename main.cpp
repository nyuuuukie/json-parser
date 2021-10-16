#include "JSON.hpp"

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;
	
	try {
		string filename(argv[1]);
		
		JSON::JSON json(filename);
		json.loadFile();

		JSON::Object &ref = *(json.parse());

		JSON::Boolean *boolean = ref["keyBool"]->toBool();
		JSON::String *str = ref["keyString"]->toStr();

		bool flag = false;
		if (boolean != NULL)
			flag = boolean->getValue();

		std::string secretKey = "";
		if (str != NULL)
			secretKey = str->getValue();

		std::cout << flag << std::endl;
		std::cout << secretKey << std::endl;
	
	} 
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
