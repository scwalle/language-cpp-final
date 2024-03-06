#include <iostream>
#include <lua5.1/lua.hpp>
/* #include <lua5.1/lauxlib.h> */
/* #include <lua5.1/lualib.h> */

const int LUA_OK = 0;

int main() {
    // Create a Lua state
    lua_State* L = luaL_newstate();

    // Load Lua standard libraries
    luaL_openlibs(L);

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

