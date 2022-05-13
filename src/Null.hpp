#pragma once

#include "AType.hpp"

namespace JSON {
	
	class Null : public AType
	{
		private:
			AType *_value;

		public:	
			Null(void);
			Null(const string &rawjson);
			~Null();
			Null(const Null & other);
			Null & operator=(const Null & other);

			virtual void parse(void);
	};
}
