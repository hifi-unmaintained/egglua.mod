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
    return 0;
}

static int cmd_lua_unload(struct userrec *u, int idx, char *par)
{
    Context;
    return 0;
}

static int cmd_lua_pubm(char *nick, char *uhost, char *hand, char *channel, char *rest)
{
    Context;
    return 0;
}

static int cmd_lua_msg(char *nick, char *uhost, char *hand, char *channel, char *rest)
{
    Context;
    return 0;
}
