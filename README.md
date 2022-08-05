# json-parser

## Dependencies
 * `clang++`

### Compiles the parser
```bash
# This command will сompile the project
make

# This command will re-сompile the project
make re
```

## Usage
1. Add parser object
```C++
#include "Parser.hpp"

int main() {

	JSON::Object *glob = NULL;

	// An exception will be trown in case of
	// problems with file reading or parsing
	try {
		glob = JSON::parseFile(filename);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}


```

2. Get the values you need so much:
```C++
	// Directly accessing fields:
	string v1 = glob->get("keyStr")->toStr();
	double v2 = glob->get("keyObj")->get("keyNum")->toNum();
	bool k3   = glob->get("keyArr")->get(2)->toBool();
	
	// Or iterating through them:

	// JSON::Object
	for (JSON::Object::iterator it = glob->begin(); it != glob->end(); ++it) {
		// Prints all keys,value pairs in object 
		std::cout << it->first << ": " << it->second->toStr() << std::endl;
	}

	// JSON::Array 
	JSON::Array *arr = glob->get("keyArr")->toArr();
	for (JSON::Array::iterator it = arr->begin(); it != arr->end(); ++it) {
		// Prints all values of the array 
		std::cout << (*it)->toStr() << std::endl;
	}
```

3. Compile your project with library
```bash
	#1 option
	clang++ yourfile.cpp libjson.a -o test

	#2 option
	clang++ yourfile.cpp -ljson -L <path_to_lib> -I <path_to_src> -o test
```

## API

```C++
	// Reading json file and parsing it
	Object *JSON::parseFile(const std::string &filename);

	// Parses raw json (must be an object)
	Object *JSON::parseRaw(const std::string &raw);

	// Use get method to access object field:
	AType *get(const string &key);  // For objects
	AType *get(const size_t index); // For arrays

	// Convert json type with following methods:
	double	toNum(void);
	string	toStr(void);
	bool	toBool(void);
	Object *toObj(void);
	Array  *toArr(void);

	// Or check if current type matches expected:
	bool	isStr(void);
	bool	isNum(void);
	bool	isNull(void);
	bool	isBool(void);
	bool	isObj(void);
	bool	isArr(void);
```

## Test
### Compile
```bash
# This command will сompile the test version
make test
```

### conf.json:
```json
{
	"keyString": "secret123",
	"keyNumber": 123.34,
	"keyObj": {
		"key1": true,
		"key2": "string",		
		"key3": 0.1512132
	},
	"keyBool1": false,
	"keyBool2": true,
	"keyArr": [
		"value1",
		"value2",
		"value3"
	]
}
```
### Run
```bash
./test conf.json

# keyString: secret123
# keyDouble: 123.34
# keyObj->key1: 1
# keyObj->key2: string
# keyObj->key3: 0.151213
# keyBool1: 0
# keyBool2: 1
# keyArr->value1: value1
# keyArr->value2: value2
# keyArr->value3: value3
```
