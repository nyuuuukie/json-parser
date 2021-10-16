#pragma once

#include <iostream>
#include <exception>

using std::string;

namespace JSON {

	class Null;
	class Array;
	class Number;
	class Object;
	class String;
	class Boolean;

	class AType
	{
		private:
			string _name;
			string _rawjson;

			//AType *_value;

		public:
			AType(void);
			AType(const string &name, const string &rawjson);
			virtual	~AType();
		
			AType(const AType &other);
			AType &operator=(const AType &other);

			void setRaw(const string &);
			const string &getRaw(void) const;
			
			const string &getType(void) const;

			Number *toNum(void);
			Object *toObj(void);
			String *toStr(void);
			Null  *toNull(void);
			Array *toArray(void);
			Boolean *toBool(void);

			virtual void parse(void) = 0;

			class ParseException : public std::exception {
				private:
					string _message;
				public:
					ParseException(std::string message);
					virtual ~ParseException() throw();
					virtual const char *what(void) const throw();
			};
	};
}

#include "Null.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "Number.hpp"
#include "Object.hpp"
#include "Boolean.hpp"
