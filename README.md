# json-parser

## Dependencies
 * `clang++`

This project was builded with 

### Compiles the parser
```bash
# This command will сompile the project
make

# This command will re-сompile the project
make re
```

# Usage
```C++
// Add this header to your file
#include "JSON.hpp"
```

```bash
#Compile project with libjson.a

#1 option
clang++ yourfile.cpp libjson.a -o test

#2 option
clang++ yourfile.cpp -ljson -L <path_to_lib> -I <path_to_src> -o test
```

# Test
## Compile
```bash
# This command will сompile the test version
make test
```

## conf.json:
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
	"keyBool2": true
}
```
## Run
```bash
# Run test with the created file

./test conf.json
# keyString: secret123
# keyDouble: 123.34
# keyObj->key1: 1
# keyObj->key2: string
# keyObj->key3: 0.151213
# keyBool1: 0
# keyBool2: 1
```
