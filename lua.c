/*
 * lua.c -- part of lua.mod
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

#define MODULE_NAME "lua"
#define MAKING_WOOBIE

#include "src/mod/module.h"
#include <stdlib.h>

#undef global
/* Pointer to the eggdrop core function table. Gets initialized in
 * lua_start().
 */
static Function *global = NULL;

/* Calculate the memory we keep allocated.
 */
static int lua_expmem()
{
  int size = 0;

  Context;
  return size;
}

static int cmd_lua(struct userrec *u, int idx, char *par)
{
  /* Define a context.
   *
   * If the bot crashes after the context, it will be  the last mentioned
   * in the resulting DEBUG file. This helps you debugging.
   */
  Context;

  /* Log the command as soon as you're sure all parameters are valid. */
  putlog(LOG_CMDS, "*", "#%s# lua", dcc[idx].nick);

  dprintf(idx, "WOOBIE!\n");
  return 0;
}

/* A report on the module status.
 *
 * details is either 0 or 1:
 *    0 - `.status'
 *    1 - `.status all'  or  `.module lua'
 */
static void lua_report(int idx, int details)
{
  if (details) {
    int size = lua_expmem();

    dprintf(idx, "    Using %d byte%s of memory\n", size,
            (size != 1) ? "s" : "");
  }
}

/* Note: The tcl-name is automatically created if you set it to NULL. In
 *       the example below it would be just "*dcc:lua". If you specify
 *       "lua:lua" it would be "*dcc:lua:lua" instead.
 *               ^----- command name   ^--- table name
 *        ^------------ module name
 *
 *       This is only useful for stackable binding tables (and H_dcc isn't
 *       stackable).
 */
static cmd_t mydcc[] = {
  /* command  flags  function     tcl-name */
  {".",  "",    cmd_lua,  NULL},
  {NULL,      NULL,  NULL,        NULL}  /* Mark end. */
};

static char *lua_close()
{
  Context;
  rem_builtins(H_dcc, mydcc);
  module_undepend(MODULE_NAME);
  return NULL;
}

/* Define the prototype here, to avoid warning messages in the
 * lua_table.
 */
EXPORT_SCOPE char *lua_start();

/* This function table is exported and may be used by other modules and
 * the core.
 *
 * The first four have to be defined (you may define them as NULL), as
 * they are checked by eggdrop core.
 */
static Function lua_table[] = {
  (Function) lua_start,
  (Function) lua_close,
  (Function) lua_expmem,
  (Function) lua_report,
};

char *lua_start(Function *global_funcs)
{
  /* Assign the core function table. After this point you use all normal
   * functions defined in src/mod/modules.h
   */
  global = global_funcs;

  Context;
  /* Register the module. */
  module_register(MODULE_NAME, lua_table, 2, 0);
  /*                                            ^--- minor module version
   *                                         ^------ major module version
   *                           ^-------------------- module function table
   *              ^--------------------------------- module name
   */

  if (!module_depend(MODULE_NAME, "eggdrop", 106, 0)) {
    module_undepend(MODULE_NAME);
    return "This module requires Eggdrop 1.6.0 or later.";
  }

  /* Add command table to bind list H_dcc, responsible for dcc commands.
   * Currently we only add one command, `lua'.
   */
  add_builtins(H_dcc, mydcc);
  return NULL;
}
