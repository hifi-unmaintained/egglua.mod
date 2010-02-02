/* management commands (dcc) */
static int cmd_lua(struct userrec *u, int idx, char *par)
{
    Context;
    dprintf(idx, "egglua module commands:\n", par);
    dprintf(idx, " luaload <script>\n", par);
    dprintf(idx, " luaunload <script>\n", par);
    dprintf(idx, " luareload <script>\n", par);
    return 0;
}

static int cmd_lua_load(struct userrec *u, int idx, char *par)
{
    Context;
    char buf[256];
    char *tmp = strstr(par, " ");
    if(tmp) *tmp = 0;
    snprintf(buf, 255, "scripts/%s.lua", par);
    dprintf(DP_LOG, "egglua: loading file %s", buf);
    lua_getglobal(L, "pm_load");
    lua_pushstring(L, buf);
    lua_pcall(L, 1, 0, 0);
    return 0;
}

static int cmd_lua_unload(struct userrec *u, int idx, char *par)
{
    Context;
    char buf[256];
    char *tmp = strstr(par, " ");
    if(tmp) *tmp = 0;
    snprintf(buf, 255, "scripts/%s.lua", par);
    dprintf(DP_LOG, "egglua: unloading file %s", buf);
    lua_getglobal(L, "pm_unload");
    lua_pushstring(L, buf);
    lua_pcall(L, 1, 0, 0);
    return 0;
}

static int cmd_lua_reload(struct userrec *u, int idx, char *par)
{
    Context;
    char buf[256];
    char *tmp = strstr(par, " ");
    if(tmp) *tmp = 0;
    snprintf(buf, 255, "scripts/%s.lua", par);
    dprintf(DP_LOG, "egglua: reloading file %s", buf);
    lua_getglobal(L, "pm_reload");
    lua_pushstring(L, buf);
    lua_pcall(L, 1, 0, 0);
    return 0;
}

/* hooks */
static void lua_hook_secondly()
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "hook_secondly");
    lua_pcall(L, 1, 0, 0);
}
static void lua_hook_minutely()
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "hook_minutely");
    lua_pcall(L, 1, 0, 0);
}
static void lua_hook_5minutely()
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "hook_5minutely");
    lua_pcall(L, 1, 0, 0);
}
static void lua_hook_hourly()
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "hook_hourly");
    lua_pcall(L, 1, 0, 0);
}
static void lua_hook_daily()
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "hook_daily");
    lua_pcall(L, 1, 0, 0);
}

/* irc messages */
static int lua_msg_pub(char *nick, char *host, char *hand, char *channel, char *msg)
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "msg_pub");
    lua_pushstring(L, nick);
    lua_pushstring(L, host);
    lua_pushstring(L, hand);
    lua_pushstring(L, channel);
    lua_pushstring(L, msg);

    if(lua_pcall(L, 6, 1, 0) == 0) {
        /* do we need the return value? */
        (void)lua_toboolean(L, -1);
    } else {
        dprintf(DP_LOG, "egglua: call failed: %s", (char *)lua_tostring(L, -1));
    }
    return 0;
}

static int lua_msg_priv(const char *nick, const char *host, const struct userrec *u, char *msg)
{
    Context;
    lua_getglobal(L, "pm_call");
    lua_pushstring(L, "msg_priv");
    lua_pushstring(L, nick);
    lua_pushstring(L, host);
    lua_pushstring(L, msg);

    if(lua_pcall(L, 4, 1, 0) == 0) {
        /* do we need the return value? */
        (void)lua_toboolean(L, -1);
    } else {
        dprintf(DP_LOG, "egglua: call failed: %s", (char *)lua_tostring(L, -1));
    }
    return 0;
}
