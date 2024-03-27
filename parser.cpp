#include <iostream>
#include <lua5.1/lua.hpp>
#include "parser.hpp"
/* #include <lua5.1/lauxlib.h> */

Parser::Parser(lua_State *L, std::istream &input) : input(input.rdbuf()) {
	// stream magic to initialize Parser.input
	// input.rdbuf(newinput.rdbuf()); to change input
	this->L = L;
	next();
}

char Parser::peek() { // basically a stub since we're not indexing a string
	return input.peek();	
};

bool Parser::next() {
	input.get(c);
	return input.fail();
};

bool Parser::match(char expected) {
	if (input.eof()) {
		return false;
	}
	if (c == expected) {
		next();
		return true;
	}
	return false;
};

/* bool Parser::parseWord() { */
/* 	std::string word; */
/* 	if (input >> word) { */
/* 		// success */
/* 		lua_pushstring(L, word.c_str()); */
/* 		return true; */
/* 	} else { */
/* 		// fail */
/* 		return false; */
/* 	} */
/* } */

bool Parser::parseWord() {

	// eat whitespace
	while (whitespace() && !input.eof()) {
		next();
	}
	if (input.eof()) {
		return false;
	}

	luaL_Buffer b;
	luaL_buffinit(L, &b);

	while (!whitespace()) {
		luaL_addchar(&b, c);
		next();
		if (input.fail()) {
			break;
		}
	}

	luaL_pushresult(&b);
	return true;
}

bool Parser::whitespace() {
	switch (c) {
		case ' ':
		case '\n':
		case '\t':
		case EOF:
			return true;
			break;
		default:
			return false;
	}	
}
