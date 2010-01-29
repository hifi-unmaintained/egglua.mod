int egglua_dprintf(lua_State *L)
{
    int idx = (int)lua_tointeger(L, 1);
    char *str = (char *)lua_tostring(L, 2);

    dprintf(idx, str);

    return 0;
}
