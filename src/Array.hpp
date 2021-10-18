#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <vector>
#include <algorithm>

#include "Object.hpp"

using std::string;
using std::map;

namespace JSON {

	class Array : public AType
	{
		typedef std::vector<AType *>::iterator iterator;

		private:
			std::vector<AType *> _arr;
			Null *nullobj;

		public:
			Array(void);
			Array(const string &rawjson);
			~Array(void);

			Array(const Array &other);
			Array &operator=(const Array &other);

			size_t countValues(int depth = 1) const;
			AType *identify(const string &rawvalue);
			
			void cutBraces(void);

			AType *getValue(const size_t index) const;

			string getRawKey(const string &s, size_t &i);
			string getRawValue(const string &s, size_t &i);

			virtual void parse(void);
	};

}
