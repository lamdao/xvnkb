ifeq (Makefile.cfg,$(wildcard Makefile.cfg))
include Makefile.cfg
endif

CC=gcc

ifeq "$(CFLAGS)" ""
CFLAGS=-O3 -s
endif

FPTR=-fomit-frame-pointer -D_REENTRANT
XLIB_INC=$(XLIB_DIR)/include
XLIB_PATH=$(XLIB_DIR)/lib
LIBS=-lX11 -ldl

.PHONY: config debug core core_debug tools uninstall

CORE=xvnkb.so.$(VERSION)
CORE_OBJS=xvnkb.o visckey.o property.o

GUI=xvnkb
GUI_OBJS=data.o flash.o main.o event.o mainwin.o menu.o hotkey.o \
		mode.o property.o session.o xconfig.o xresource.o label.o button.o


all: do-it-all

.c.o:
	$(CC) $(CFLAGS) $(FPTR) $(VK_OPT) -DVERSION=\"$(VERSION)\" -Wall -I$(XLIB_INC) -c $<

$(CORE): $(CORE_OBJS)
	$(CC) $(CFLAGS) -shared -fpic -Wl,-soname,$@ -o $@ $(CORE_OBJS) -L$(XLIB_PATH) $(LIBS)

$(GUI): $(GUI_OBJS)
	$(CC) $(CFLAGS) -o $@ $(GUI_OBJS) -L$(XLIB_PATH) $(LIBS) $(XFT_LIBS)

main: $(CORE) $(GUI)
	@echo >/dev/null

tools:
	@make -C tools

clean:
	@make -C tools clean
	rm -f *.o core

distclean:
	@make -C tools distclean
	rm -f *.o core
	rm -f $(CORE) $(GUI)
	rm -f Makefile.cfg
	rm -f .*.sw*

install: all
	@./install

uninstall:
	@./uninstall

debug: clean
	@$(MAKE) CFLAGS="-DDEBUG $(CFLAGS)"

core: clean
	@$(MAKE) CFLAGS="-DVK_CORE_ONLY $(CFLAGS)" $(CORE)

core_debug: clean
	@$(MAKE) CFLAGS="-DDEBUG $(CFLAGS)" core

config:
	@./configure

dep: Makefile.dep

Makefile.dep:
	@echo
	@echo -n "Create $@ ... "
	@gcc -I$(XLIB_INC) -MM *.c > $@
	@echo done
	@echo

ifneq (Makefile.cfg,$(wildcard Makefile.cfg))
do-it-all: config
	@make
else
ifeq (Makefile.dep,$(wildcard Makefile.dep))
include Makefile.dep
do-it-all: main tools
else
do-it-all: dep
	@make main tools
endif
endif
