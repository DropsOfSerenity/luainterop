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
  {
    error(L, "failed to loadfile");
  }

  printf("Calling test.lua from C file...\n");

  if(lua_pcall(L, 0, 0, 0))
  {
    error(L, "failed to call lua file");
  }

  printf("Successfully called lua from C! :)\n");

  lua_close(L);

  return(0);
}
