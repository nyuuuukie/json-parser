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
	"keyBool": true,
	"keyString": "secret123"
}
```
## Run
```bash
# Run test with the created file

./test conf.json    
# 1
# secret123
```
