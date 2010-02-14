#include "../module.h"
#include "../irc.mod/irc.h"
#include "../server.mod/server.h"

#define MODULE_NAME "egglua"

#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static lua_State *L = NULL;

#undef global
static Function *global = NULL, *irc_funcs = NULL, *server_funcs = NULL;

#include "commands.c"
#include "exports.c"
#include "plugman.c"

EXPORT_SCOPE char *egglua_start();
static char *egglua_close();
static int egglua_expmem();
static void egglua_report(int idx, int details);

static cmd_t lua_dcc[] = {
    {"luaload",     "",     cmd_lua_load,   NULL},
    {"luaunload",   "",     cmd_lua_unload, NULL},
    {"luareload",   "",     cmd_lua_reload, NULL},
    {"lua",         "",     cmd_lua,        NULL},
    {NULL,          NULL,   NULL,           NULL}
};

static cmd_t lua_pubm[] = {
    {"*",           "",     lua_msg_pub,    NULL},
    {NULL,          NULL,   NULL,           NULL}
};

static cmd_t lua_msg[] = {
    {"*",           "",     lua_msg_priv,   NULL},
    {NULL,          NULL,   NULL,           NULL}
};
static cmd_t lua_kick[] = {
    {"*",           "",     lua_hook_kick,  NULL},
    {NULL,          NULL,   NULL,           NULL}
};
static cmd_t lua_nick[] = {
    {"*",           "",     lua_hook_nick,  NULL},
    {NULL,          NULL,   NULL,           NULL}
};
static cmd_t lua_join[] = {
    {"*",           "",     lua_hook_join,  NULL},
    {NULL,          NULL,   NULL,           NULL}
};
static cmd_t lua_part[] = {
    {"*",           "",     lua_hook_part,  NULL},
    {NULL,          NULL,   NULL,           NULL}
};
static cmd_t lua_sign[] = {
    {"*",           "",     lua_hook_sign,  NULL},
    {NULL,          NULL,   NULL,           NULL}
};
