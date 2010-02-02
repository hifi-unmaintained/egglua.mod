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
  return 0;
}

static int egglua_putxferlog(lua_State *L)
{
  char logtext[501];

  char *str = (char *)luaL_checkstring(L, 1);

  strncpyz(logtext, str, sizeof logtext);
  putlog(LOG_FILES, "*", "%s", logtext);
  return 0;
}

int chan_sanity_check(int, int);
/* converted from tcl_attr(), all credits to the Eggdrop team */
static int egglua_chattr(lua_State *L)
{
  char *chan, *chg, work[100];
  struct flag_record pls, mns, user;
  struct userrec *u;

  /* argv -> invidual pointers */
  char *handle = (char *)luaL_checkstring(L, 1);
  char *changes  = (char *)lua_tostring(L, 2);
  char *channel = (char *)lua_tostring(L, 3);

  /* be compatible */
  int argc = 4;
  if(channel == NULL)
      argc = 3;
  if(changes == NULL)
      argc = 2;

  if ((handle[0] == '*') || !(u = get_user_by_handle(userlist, handle))) {
    lua_pushstring(L, "*");
    return 1;
  }
  if (argc == 4) {
    user.match = FR_GLOBAL | FR_CHAN;
    chan = channel;
    chg = changes;
  } else if (argc == 3 && changes[0]) {
    int ischan = (findchan_by_dname(changes) != NULL);

    if (strchr(CHANMETA, changes[0]) && !ischan && changes[0] != '+' &&
        changes[0] != '-') {
      lua_pushnil(L);
      lua_pushstring(L, "no such channel");
      return 2;
    } else if (ischan) {
      /* Channel exists */
      user.match = FR_GLOBAL | FR_CHAN;
      chan = changes;
      chg = NULL;
    } else {
      /* 3rd possibility... channel doesnt exist, does start with a +.
       * In this case we assume the string is flags.
       */
      user.match = FR_GLOBAL;
      chan = NULL;
      chg = changes;
    }
  } else {
    user.match = FR_GLOBAL;
    chan = NULL;
    chg = NULL;
  }
  if (chan && !findchan_by_dname(chan)) {
    lua_pushnil(L);
    lua_pushstring(L, "no such channel");
    return 2;
  }
  get_user_flagrec(u, &user, chan);
  /* Make changes */
  if (chg) {
    pls.match = user.match;
    break_down_flags(chg, &pls, &mns);
    /* No-one can change these flags on-the-fly */
    pls.global &=~(USER_BOT);
    mns.global &=~(USER_BOT);

    if (chan) {
      pls.chan &= ~(BOT_SHARE);
      mns.chan &= ~(BOT_SHARE);
    }
    user.global = sanity_check((user.global |pls.global) &~mns.global);

    user.udef_global = (user.udef_global | pls.udef_global)
                       & ~mns.udef_global;
    if (chan) {
      user.chan = chan_sanity_check((user.chan | pls.chan) & ~mns.chan,
                                    user.global);
      user.udef_chan = (user.udef_chan | pls.udef_chan) & ~mns.udef_chan;
    }
    set_user_flagrec(u, &user, chan);
  }
  /* Retrieve current flags and return them */
  build_flags(work, &user, NULL);
  lua_pushstring(L, work);
  return 1;
}

/* converted from tcl_attr(), all credits to the Eggdrop team */
static int egglua_matchattr(lua_State *L)
{
  struct userrec *u;
  struct flag_record plus, minus, user;
  int ok = 0, f;

  char *handle = (char *)luaL_checkstring(L, 1);
  char *flags = (char *)luaL_checkstring(L, 2);
  char *channel = (char *)lua_tostring(L, 3);

  /* be compatible */
  int argc = 4;
  if(channel == NULL)
      argc = 3;

  if ((u = get_user_by_handle(userlist, handle))) {
    user.match = FR_GLOBAL | (argc == 4 ? FR_CHAN : 0) | FR_BOT;
    get_user_flagrec(u, &user, channel);
    plus.match = user.match;
    break_down_flags(flags, &plus, &minus);
    f = (minus.global ||minus.udef_global || minus.chan || minus.udef_chan ||
         minus.bot);
    if (flagrec_eq(&plus, &user)) {
      if (!f)
        ok = 1;
      else {
        minus.match = plus.match ^ (FR_AND | FR_OR);
        if (!flagrec_eq(&minus, &user))
          ok = 1;
      }
    }
  }
  lua_pushboolean(L, ok);
  return 1;
}
