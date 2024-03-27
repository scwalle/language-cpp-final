#include <lua5.1/lua.hpp>

#include <iostream>
#include <string>
#include <sstream>
/* #include <lua5.1/lauxlib.h> */
/* #include <lua5.1/lualib.h> */

#include "parser.hpp"

const int LUA_OK = 0;

static void lprint (lua_State *L, int index);
static void stackDump (lua_State *L);

void parseWord();
void lookupWord();
void executeWord();

/*
Main loop pseudocode
 
if stdin:
	input = stdin
else:
	input = file

while input is left:
	parseWord()
	executeWord()

*/

void lpush(lua_State *L, int idx) {
	int top = luaL_getn(L, idx);	
	lua_rawseti(L, luaL_getn(L, idx), -1);

}

int main(int argc, char *argv[]) {
    // Create a Lua state
    lua_State *L = luaL_newstate();

    // Load Lua standard libraries
    luaL_openlibs(L);

	lua_newtable(L);
	lua_setglobal(L, "words");
	const int words = lua_gettop(L);

	std::istringstream foo(argv[1]);
	std::istream input(std::cin.rdbuf());
	//
	// TODO fix segfault
	// 
	if(argc > 0)
	{
		input.rdbuf(foo.rdbuf());
	}
	Parser p (L, input);

	while (p.parseWord()) {
	/* std::string word; */
	/* while (std::cin >> word) { */
		/* lua_pushstring(L, word.c_str()); */
		std::cout << "word: " << lua_tostring(L, -1) << std::endl;
		/* luaL_dostring(L, "words = {}"); */
		lua_setglobal(L, "word");
		luaL_dostring(L, "table.insert(words, word)");
	}
	std::cout << std::endl;
	stackDump(L);
	/* luaL_dostring(L, "debug.debug()"); */
	

	/* bool status = p.parseWord(); */
	/* std::cout << "status: " << (status ? "true" : "false") << std::endl; */
	/* /1* std::cout << "word: " << lua_tostring(L, -1); *1/ */
	/* lua_pushstring(L, "word:"); */
	/* lua_getglobal(L, "print"); */
	/* lua_insert(L, -3); */
	/* lua_call(L, 2, -3); */



    // Lua code to be executed
    const char* luaCode = "print('Hello from Lua!')";

    // Run the Lua code
    if (luaL_dostring(L, luaCode) != LUA_OK) {
        std::cerr << "Error running Lua code: " << lua_tostring(L, -1) << std::endl;
        lua_close(L);
        return 1;
    }

    // Close the Lua state
    lua_close(L);

    return 0;
}

static void lprint (lua_State *L, int index) {
	int type = lua_type(L, index);
	switch (type) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, index));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, index) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, index));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, type));
			break;

	}
}

static void stackDump (lua_State *L) {
	int i;
	int top = lua_gettop(L);
	printf("<%i> ", top);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		lprint(L, i);
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

