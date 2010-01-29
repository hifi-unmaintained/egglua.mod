LIBLUA = -llua5.1
srcdir = .


doofus:
	@echo ""
	@echo "Let's try this from the right directory..."
	@echo ""
	@cd ../../../ && make

static: ../egglua.o
	@echo "$(LIBLUA)" >> ../mod.xlibs

modules: ../../../egglua.$(MOD_EXT)

../egglua.o: egglua.h commands.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DMAKING_MODS -c $(srcdir)/egglua.c
	@rm -f ../egglua.o
	mv egglua.o ../

../../../egglua.$(MOD_EXT): ../egglua.o
	$(LD) -o ../../../egglua.$(MOD_EXT) ../egglua.o $(LIBLUA) $(XLIBS) $(MODULE_XLIBS)
	$(STRIP) ../../../egglua.$(MOD_EXT)

depend:
	$(CC) $(CFLAGS) -MM $(srcdir)/egglua.c -MT ../egglua.o > .depend

clean:
	@rm -f .depend *.o *.$(MOD_EXT) *~

distclean: clean

#safety hash
../egglua.o: ./egglua.c ./commands.c ../../../src/mod/module.h ../../../src/main.h \
  ../../../config.h ../../../lush.h ../../../src/lang.h \
  ../../../src/eggdrop.h ../../../src/flags.h ../../../src/cmdt.h \
  ../../../src/tclegg.h ../../../src/tclhash.h ../../../src/chan.h \
  ../../../src/users.h ../../../src/compat/compat.h \
  ../../../src/compat/inet_aton.h ../../../src/main.h \
  ../../../src/compat/snprintf.h ../../../src/compat/memset.h \
  ../../../src/compat/memcpy.h ../../../src/compat/strcasecmp.h \
  ../../../src/compat/strftime.h ../../../src/mod/modvals.h \
  ../../../src/tandem.h
