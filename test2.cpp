#include "JSON.hpp"

int main(int argc, char *argv[]) {

	if (argc != 2)
		return 1;
	
	try {
		string filename(argv[1]);
		
		JSON::JSON json(filename);
		JSON::Object *obj = json.parse();
		
		string k1 = obj->get("error_pages")->get("399")->toStr();
		string k2 = obj->get("server")->get("root")->get("locations")->get("/about")->get("root")->toStr();

		JSON::Object *locations = obj->get("server")->get("locations")->toObj();
		JSON::Object::iterator it = locations->begin();
		JSON::Object::iterator it2 = locations->end();
		for (; it != it2; it++)
		{
			std::cout << it->first << std::endl;
		}

		std::cout << k1 << std::endl;
		std::cout << k2 << std::endl;

		delete obj;	
	} 
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
