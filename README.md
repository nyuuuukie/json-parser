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
```C++
// Add this header to your file
#include "Parser.hpp"
...
// Create a json object and pass filename to it;
// An exception will be trown in case of
// problems with file reading or parsing
JSON::Parser prs(filename);

// Another option 
// JSON::Parser prs;
// prs.setFilename(filename);
// prs.loadFile();

// Parse whole file in json object
JSON::Object *obj = prs.parse();

// Get values:
string k1 = obj->get("keyString")->toStr();
string k2 = obj->get("keyObj")->get("key2")->toStr();
string k3 = obj->get("keyArr")->get(2)->toStr();

```

```bash
#Compile project with libjson.a

#1 option
clang++ yourfile.cpp libjson.a -o test

#2 option
clang++ yourfile.cpp -ljson -L <path_to_lib> -I <path_to_src> -o test
```

## API

```C++
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
