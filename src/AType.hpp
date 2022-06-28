#pragma once

#include <iostream>
#include <exception>

#include "Utils.hpp"

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
			string _key;
			string _name;
			string _rawjson;

		public:
			AType(void);
			AType(const string &name, string rawjson);
			virtual	~AType();
		
			AType(const AType &other);
			AType &operator=(const AType &other);

			void setRaw(const string &);
			string &getRaw(void);

			void setKey(const string &);
			const string &getKey(void);

			const string &getRawRef(void) const;
			const string &getType(void) const;

			//Convert
			double toNum(void);
			const string toStr(void);
			bool toBool(void);
			Object *toObj(void);
			Array *toArr(void);
			
			bool isStr(void);
			bool isNum(void);
			bool isNull(void);
			bool isBool(void);
			bool isObj(void);
			bool isArr(void);

			//Getters for object and array types
			Null *getNull(void) const;
			AType *get(const string &key);
			AType *get(const size_t index);

			virtual void parse(void) = 0;

			//Exceptions
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
