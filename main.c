#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdlib.h>
#include <stdio.h>

void
error(lua_State *L, char *msg)
{
  fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
      msg, lua_tostring(L, -1));
  exit(1);
}

int
main()
{
  lua_State *L;
  L = luaL_newstate();

  luaL_openlibs(L);

  if ( luaL_loadfile(L, "test.lua") )
    error(L, "failed to loadfile");

  if(lua_pcall(L, 0, 0, 0)) // priming must happen before you can pcall a global
    error(L, "lua_pcall() failed");
  lua_getglobal(L, "saysomething");

  if(lua_pcall(L, 0, 0, 0))
    error(L, "lua_pcall() failed");

  printf("Successfully called lua from C! :)\n");

  lua_close(L);

  return(0);
}
