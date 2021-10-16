#pragma once

#include <vector>

#include "Null.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "Number.hpp"
#include "Boolean.hpp"

namespace JSON {

	class Array : public AType
	{
		private:
			std::vector<AType *> _arr;

		public:	
			Array(void);
			Array(const string &rawjson);
			~Array();
			Array(const Array &other);
			Array & operator=(const Array &other);

			AType *operator[](int index);

			virtual void parse(void);
	};

}
