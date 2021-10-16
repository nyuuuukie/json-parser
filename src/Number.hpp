#pragma once

#include "AType.hpp"

namespace JSON {
	
	class Number : public AType {
		private:
			double _value;

		public:	
			Number(void);
			Number(const string &rawjson);
			~Number();
			Number(const Number & other);
			Number & operator=(const Number & other);

			double getValue(void) const;

			virtual void parse(void);
	};

}
