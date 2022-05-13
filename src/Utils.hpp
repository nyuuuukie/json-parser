#pragma once

#include <iostream>

using std::string;

class Utils
{
	private:
	public:
		static bool skipWhitespaces(const string &s, size_t &i);
		static bool checkColon(const string &s, size_t &i);
		static bool checkComma(const string &s, size_t &i);
		static std::string to_string(double val);
};
