#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/stat.h>

#include <map>
#include <algorithm>

#include "Null.hpp"
#include "Array.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "Number.hpp"
#include "Boolean.hpp"

using std::string;
using std::ifstream;

namespace JSON {

class Parser
{
	private:
		string	_filename;
		string	_raw;
		bool	_rawLoaded;

	public:
		Parser(void);
		Parser(const string &filename);
		~Parser();

		Parser(const Parser &other);
		Parser &operator=(const Parser &other);

		// Methods
		void loadFile(void);
		Object *parse(void);

		//Setters
		void setRaw(const std::string &);
		void setFilename(const string &filename);
		
		//Getters
		const string &getFilename(void) const;

		//Checkers
		bool isCorrectExt( void ) const;
		bool fileExists( void ) const;
		bool isValidJSON( void ) const;
		bool isValidJSON( const string &raw ) const;

		class FileException : public std::exception {
			private:
				string _message;
			public:
				FileException(std::string message);
				virtual ~FileException() throw();
				virtual const char *what(void) const throw();
		};

};

}
