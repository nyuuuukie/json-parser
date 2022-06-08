#pragma once

#include <iostream>
#include <stdio.h>

using std::string;

class Utils
{
	private:
	public:
		static void skipWhitespaces(const string &s, size_t &i);
		static std::string to_string(double val);
		
		static bool isEscChar(const std::string &s, size_t i, char c);

		static void trim(std::string &s, const char *t);

};
