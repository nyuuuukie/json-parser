#include "Utils.hpp"

bool Utils::skipWhitespaces(const string &s, size_t &i) {

	const size_t len = s.length();
	for (; i < len; i++) {
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '\r' && s[i] != '\t')
			return false;
	}
	return true;
}

bool Utils::checkColon(const string &s, size_t &i) {
	if (s[i] != ':' || (s[i] == ':' && s[i - 1] == '\\'))
		return false;
	i++;
	return true;
}

bool Utils::checkComma(const string &s, size_t &i) {
	if (s[i] != ',' || (s[i] == ',' && s[i - 1] == '\\'))
		return false;
	i++;
	return true;
}
