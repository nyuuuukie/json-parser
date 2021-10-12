#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

using std::string;

class JSON
{
	private:
		string _filename;

	public:
		JSON(void);
		JSON(const string &filename);
		~JSON(void);

		JSON(const JSON &other);
		JSON & operator=(const JSON &other);

		// Methods
		void serialize(const JSON &json);
		const JSON &parse(void);

		//Setters
		void setFilename(const string &filename);
		
		//Getters
		const string &getFilename(void) const;

		//Checkers
		bool isValidJSON( void ) const;
		bool isCorrectExt( void ) const;
		bool fileExists( void ) const;

};