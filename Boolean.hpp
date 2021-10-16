#pragma once

#include "AType.hpp"

namespace JSON {

	class Boolean : public AType
	{
		private:
			bool _value;

		public:	
			Boolean(void);
			Boolean(const string &rawjson);
			~Boolean();
			Boolean(const Boolean &other);
			Boolean &operator=(const Boolean &other);

			bool getValue(void) const;

			virtual void parse(void);
	};
}

