#include "src/mod/module.h"

#define MODULE_NAME "egglua"

#include <stdlib.h>

#include <lua5.1/lua.h>
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>

#undef global

Function *global = NULL;

static int cmd_lua(struct userrec *u, int idx, char *par);
static int cmd_lua_load(struct userrec *u, int idx, char *par);
static int cmd_lua_unload(struct userrec *u, int idx, char *par);

static int cmd_lua_pubm(char *nick, char *uhost, char *hand, char *channel, char *rest);
static int cmd_lua_msg(char *nick, char *uhost, char *hand, char *channel, char *rest);

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
