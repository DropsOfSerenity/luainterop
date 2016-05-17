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

  if (luaL_loadfile(L, "test.lua"))
    error(L, "failed to loadfile");

  /* priming a file in this way exposes the globals and functions to our C
   * program
   */
  if(lua_pcall(L, 0, 0, 0)) // priming must happen before you can pcall a global
    error(L, "lua_pcall() failed");
  lua_getglobal(L, "saysomething"); // pushes function onto stack.
  if(lua_pcall(L, 0, 0, 0)) // run it
    error(L, "lua_pcall() failed");

  lua_getglobal(L, "square");
  lua_pushnumber(L, 6);
  /* call with nargs=1 and nreturns=1 signifying that we should take an arg off
   * the args stack and pass it to lua, and take a return value from the return
   * stack
   */
  if(lua_pcall(L, 1, 1, 0)) // call with nargs=1 and nreturns=1
    error(L, "lua_pcall() failed");

  int SquareReturn = lua_tonumber(L, -1);
  printf("Return number=%d\n", SquareReturn);

  lua_getglobal(L, "ChangeTable");
  lua_newtable(L);
  lua_pushliteral(L, "fname");
  lua_pushliteral(L, "Justin");
  lua_settable(L, -3);
  lua_pushliteral(L, "lname");
  lua_pushliteral(L, "Schiff");
  lua_settable(L, -3);

  if(lua_pcall(L, 1, 1, 0))
    error(L, "lua_pcall() failed");

  lua_pushnil(L);
  const char *k, *v;
  while(lua_next(L, -2))
  {
    v = lua_tostring(L, -1);
    lua_pop(L, 1);
    k = lua_tostring(L, -1);

    printf("From C k=>%s, v=>%s\n", k, v);
  }


  lua_close(L);

  return(0);
}
