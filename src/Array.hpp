#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <vector>
#include <algorithm>

#include "AType.hpp"

using std::string;

namespace JSON {

	class Array : public AType
	{
		public:
			typedef std::vector<AType *>::iterator iterator;
			typedef std::vector<AType *>::const_iterator const_iterator;

		private:
			std::vector<AType *> _arr;

		public:
			Array(void);
			Array(const string &rawjson);
			~Array(void);

			Array(const Array &other);
			Array &operator=(const Array &other);

			iterator begin(void);
			iterator end(void);
			const_iterator begin(void) const;
			const_iterator end(void) const;

			size_t countValues(int depth = 1) const;
			AType *identify(const string &rawvalue);
			
			void cutBraces(void);

			AType *getValue(const size_t index) const;

			string getRawKey(const string &s, size_t &i);
			string getRawValue(const string &s, size_t &i);

			virtual void parse(void);
	};

}
