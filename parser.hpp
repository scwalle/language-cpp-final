#pragma once
#include <iostream>
#include <lua5.1/lua.hpp>
/* #include <lua5.1/lauxlib.h> */

class Parser {
	private:
		std::istream input;
		lua_State *L;
	public:	
		Parser(lua_State *L, std::istream &input); 

		char c;

		// methods from Crafting interpreters
		char peek(); // basically a stub since we're not indexing a string

		bool next();

		bool match(char expected);

		bool parseWord();

		bool whitespace();
};
