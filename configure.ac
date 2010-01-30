AC_PREREQ(2.59)

sinclude(../eggmod.m4)

AC_INIT([Eggdrop Lua Module],[1.0.0],[toni.spets@iki.fi])

# add possible lua header locations
LUAINC="-I/usr/include -I/usr/include/lua -I/usr/include/lua5.1 -I/usr/local/include"
CFLAGS="$CFLAGS $LUAINC"
CPPFLAGS="$CPPFLAGS $LUAINC"

AC_CONFIG_SRCDIR(egglua.c)
AC_CONFIG_AUX_DIR(../../../misc)

AC_COPYRIGHT([Copyright (C) 2010 Toni Spets])

AC_CHECK_LIB(lua5.1, luaL_newstate, [LIBLUA="-llua5.1"], [])
AC_CHECK_HEADER(lua.h)
AC_CHECK_HEADER(lualib.h)
AC_CHECK_HEADER(lauxlib.h)

# Disable the module if either the header file or the library are missing.
if test "x${LIBLUA}" = "x"; then
  cat >&2 <<EOF
configure: warning:

  Your system does not provide a working Lua 5.1 library. The Lua
  scripting module will therefore be disabled.

EOF
  EGG_REMOVE_MOD(egglua)
else
  if [ test "${ac_cv_header_lua_h}" != "yes" ] || [ test "${ac_cv_header_lualib_h}" != "yes" ] || [ test "${ac_cv_header_lauxlib_h}" != "yes" ]; then
    cat >&2 <<EOF
configure: warning:

  Your system does not provide the necessary Lua 5.1 header files.
  The Lua scripting module will therefore be disabled.

EOF
    EGG_REMOVE_MOD(egglua)
  fi
fi

AC_SUBST(LIBLUA)
AC_SUBST(LUAINC)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
