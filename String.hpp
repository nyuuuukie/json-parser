#pragma once

#include "AType.hpp"

namespace JSON {
	
	class String : public AType
	{
		private:
			string _value;

		public:	
			String(void);
			String(const string &rawjson);
			~String();
			String(const String & other);
			String & operator=(const String & other);

			const string &getValue(void) const;
		
			virtual void parse(void);
	};

}
