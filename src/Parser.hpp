#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>

#include <map>
#include <algorithm>

#include "Null.hpp"
#include "Array.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "Number.hpp"
#include "Boolean.hpp"

using std::string;
using std::ifstream;

namespace JSON {

bool isCorrectExt(const std::string &filename);
bool fileExists(const std::string &filename);

Object *parseFile(const std::string &filename);
Object *parseRaw(std::string &raw);

}
