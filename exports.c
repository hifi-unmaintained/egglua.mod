static int egglua_putserv(lua_State *L)
{
    char *str = (char *)luaL_checkstring(L, 1);
    int arg = (int)lua_toboolean(L, 2);
    if(arg)
        dprintf(DP_SERVER_NEXT, str);
    else
        dprintf(DP_SERVER, str);
    return 0;
}

static int egglua_puthelp(lua_State *L)
{
    char *str = (char *)luaL_checkstring(L, 1);
    int arg = (int)lua_toboolean(L, 2);
    if(arg)
        dprintf(DP_HELP_NEXT, str);
    else
        dprintf(DP_HELP, str);
    return 0;
}

static int egglua_putquick(lua_State *L)
{
    char *str = (char *)luaL_checkstring(L, 1);
    int arg = (int)lua_toboolean(L, 2);
    if(arg)
        dprintf(DP_MODE_NEXT, str);
    else
        dprintf(DP_MODE, str);
    return 0;
}

static int egglua_putlog(lua_State *L)
{
  char logtext[501];

  char *str = (char *)luaL_checkstring(L, 1);

  strncpyz(logtext, str, sizeof logtext);
  putlog(LOG_MISC, "*", "%s", logtext);
  return 0;
}

static int egglua_putcmdlog(lua_State *L)
{
  char logtext[501];

  char *str = (char *)luaL_checkstring(L, 1);

  strncpyz(logtext, str, sizeof logtext);
  putlog(LOG_CMDS, "*", "%s", logtext);
  return TCL_OK;
}

static int egglua_putxferlog(lua_State *L)
{
  char logtext[501];

  char *str = (char *)luaL_checkstring(L, 1);

  strncpyz(logtext, str, sizeof logtext);
  putlog(LOG_FILES, "*", "%s", logtext);
  return TCL_OK;
}
