static int cmd_lua(struct userrec *u, int idx, char *par)
{
    Context;
    dprintf(idx, "Usage:\n", par);
    dprintf(idx, " luaload <script>\n", par);
    dprintf(idx, " luaunload <script>\n", par);
    return 0;
}

static int cmd_lua_load(struct userrec *u, int idx, char *par)
{
    Context;
    dprintf(DP_LOG, "Lua: loading file %s\n", par);
    return 0;
}

static int cmd_lua_unload(struct userrec *u, int idx, char *par)
{
    Context;
    dprintf(DP_LOG, "Lua: unloading file %s\n", par);
    return 0;
}

static int cmd_lua_pubm(char *nick, char *host, char *hand, char *channel, char *text)
{
    Context;
    dprintf(DP_LOG, "Lua: pubm %s,%s,%s,%s: %s", nick,host,hand,channel,text);
    return 0;
}

static int cmd_lua_msg(const char *nick, const char *host, const struct userrec *u, char *text)
{
    Context;
    dprintf(DP_LOG, "Lua: msg %s,%s: %s", nick,host,text);
    return 0;
}
