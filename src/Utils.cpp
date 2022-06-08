#include "Utils.hpp"

void
Utils::skipWhitespaces(const std::string &s, size_t &i) {

	const size_t len = s.length();
	for (; i < len && std::isspace(s[i]); i++);
}

bool 
Utils::isEscChar(const std::string &s, size_t i, char c) {
	return !(s[i] == c && (i == 0 || s[i - 1] != '\\'));
}

std::string Utils::to_string(double val) {
    char buf[100];
    snprintf(buf, 100, "%f", val);
    return std::string(buf);
}

static inline std::string &
rtrim(std::string &s, const char *t) {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

static inline std::string &
ltrim(std::string &s, const char *t) {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

void
Utils::trim(std::string &s, const char *t) {
    ltrim(rtrim(s, t), t);
}
