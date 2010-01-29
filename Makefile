srcdir = .


doofus:
	@echo ""
	@echo "Let's try this from the right directory..."
	@echo ""
	@cd ../../../ && make

static: ../lua.o

modules: ../../../lua.$(MOD_EXT)

../lua.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -DMAKING_MODS -c $(srcdir)/lua.c
	@rm -f ../lua.o
	mv lua.o ../

../../../lua.$(MOD_EXT): ../lua.o
	$(LD) -o ../../../lua.$(MOD_EXT) ../lua.o $(XLIBS) $(MODULE_XLIBS)
	$(STRIP) ../../../lua.$(MOD_EXT)

depend:
	$(CC) $(CFLAGS) -MM $(srcdir)/lua.c -MT ../lua.o > .depend

clean:
	@rm -f .depend *.o *.$(MOD_EXT) *~

distclean: clean

#safety hash
../lua.o: ./lua.c ../../../src/mod/module.h ../../../src/main.h \
  ../../../config.h ../../../lush.h ../../../src/lang.h \
  ../../../src/eggdrop.h ../../../src/flags.h ../../../src/cmdt.h \
  ../../../src/tclegg.h ../../../src/tclhash.h ../../../src/chan.h \
  ../../../src/users.h ../../../src/compat/compat.h \
  ../../../src/compat/inet_aton.h ../../../src/main.h \
  ../../../src/compat/snprintf.h ../../../src/compat/memset.h \
  ../../../src/compat/memcpy.h ../../../src/compat/strcasecmp.h \
  ../../../src/compat/strftime.h ../../../src/mod/modvals.h \
  ../../../src/tandem.h
