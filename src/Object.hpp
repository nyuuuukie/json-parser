#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "AType.hpp"

using std::string;
using std::map;

namespace JSON {

	class Object : public AType
	{
		typedef map<string, AType *>::iterator iterator;

		private:
			map<string, AType *> _map;
			Null *nullobj;

		public:
			Object(void);
			Object(const string &rawjson);
			~Object(void);

			Object(const Object &other);
			Object &operator=(const Object &other);

			iterator getPair(const string &key);
			size_t countKeys(int depth = 1) const;
			size_t endOfScope(const std::string &text, size_t beg, char begScope, char endScope);
			AType *identify(const string &rawvalue);
			
			AType *getValue(const string &key) const;

			void cutBraces(void);

			string getRawKey(const string &s, size_t &i);
			string getRawValue(const string &s, size_t &i);

			virtual void parse(void);
	};

}
