#include "../module.h"
#include "../irc.mod/irc.h"
#include "../server.mod/server.h"

#define MODULE_NAME "egglua"

#include <stdlib.h>

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

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
    {"lua",         "",     cmd_lua,        NULL},
    {NULL,          NULL,   NULL,           NULL}
};

static cmd_t lua_pubm[] = {
    {"*",           "",     cmd_lua_pubm,   NULL},
    {NULL,          NULL,   NULL,           NULL}
};

static cmd_t lua_msg[] = {
    {"*",           "",     cmd_lua_msg,    NULL},
    {NULL,          NULL,   NULL,           NULL}
};
