/*
 * egglua.c -- part of egglua.mod
 *   Lua scripting support for eggdrop 1.6
 *
 * Written by Toni Spets
 *
 */
/*
 * Copyright (C) 1999 - 2008 Eggheads Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#define MAKING_EGGLUA

#include "egglua.h"

static Function egglua_table[] = {
    (Function) egglua_start,
    (Function) egglua_close,
    (Function) egglua_expmem,
    (Function) egglua_report,
};

char *egglua_start(Function *global_funcs)
{
    global = global_funcs;

    Context;

    L = luaL_newstate();
    luaL_openlibs(L);
    
    /* register constants */
    lua_pushnumber(L, DP_STDOUT);
    lua_setglobal(L, "DP_STDOUT");
    lua_pushnumber(L, DP_LOG);
    lua_setglobal(L, "DP_LOG");
    lua_pushnumber(L, DP_SERVER);
    lua_setglobal(L, "DP_SERVER");
    lua_pushnumber(L, DP_HELP);
    lua_setglobal(L, "DP_HELP");
    lua_pushnumber(L, DP_STDERR);
    lua_setglobal(L, "DP_STDERR");
    lua_pushnumber(L, DP_MODE);
    lua_setglobal(L, "DP_MODE");

    /* export some C functions from eggdrop for Lua scripts */
    lua_pushcfunction(L, egglua_dprintf);
    lua_setglobal(L, "dprintf");

    /* load plugin manager */
    if(luaL_loadstring(L, lua_plugman) != 0) {
        dprintf(DP_LOG, "\nDUMPING PLUGMAN CODE\n---\n%s\n---", lua_plugman);
        return "Lua plugin manager code load failed";
    }

    if(lua_pcall(L, 0, 0, 0) != 0) {
        (char *)lua_tostring(L, -1);
        return "Lua plugin manager code execution failed";
    }

    lua_getglobal(L, "pm_init");
    if(lua_pcall(L, 0, 0, 0) != 0) {
        return "Lua plugin manager init failed";
    }

    module_register(MODULE_NAME, egglua_table, 0, 1);

    if (!module_depend(MODULE_NAME, "eggdrop", 106, 0)) {
        module_undepend(MODULE_NAME);
        return "This module requires Eggdrop 1.6.0 or later.";
    }

    if (!(irc_funcs = module_depend(MODULE_NAME, "irc", 1, 0)))
        return "You need the irc module to use the stats module.";
    if (!(server_funcs = module_depend(MODULE_NAME, "server", 1, 0)))
        return "You need the server module to use the stats module.";

    add_builtins(H_dcc, lua_dcc);
    add_builtins(H_pubm, lua_pubm);
    add_builtins(H_msgm, lua_msg);
    return NULL;
}

static char *egglua_close()
{
    Context;

    lua_getglobal(L, "pm_shutdown");
    if(lua_pcall(L, 0, 0, 0) != 0) {
        dprintf(DP_LOG, "Lua plugin manager shutdown failed, but unloading anyway");
    }

    lua_close(L);
    rem_builtins(H_dcc, lua_dcc);
    rem_builtins(H_pubm, lua_pubm);
    rem_builtins(H_msgm, lua_msg);
    module_undepend(MODULE_NAME);
    return NULL;
}

static int egglua_expmem()
{
    int size = 0;

    Context;
    return size;
}

static void egglua_report(int idx, int details)
{
    if (details) {
        int size = egglua_expmem();
        dprintf(idx, "    Using %d byte%s of memory\n", size, (size != 1) ? "s" : "");
    }
}

