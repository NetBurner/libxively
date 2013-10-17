LIBXIVELY := $(shell git rev-parse --show-toplevel)

include $(LIBXIVELY)/Makefile.include

XI_SOURCES = $(wildcard *.c) ../libxively/xi_err.c

XI_EXTRA_CFLAGS += -I./ -I../libxively/

#XI_EXPERIMENTAL = $(XI_BINDIR)/experimental

all: $(XI_BINDIR)/experimental

objs: $(XI_OBJS)
deps: $(XI_DEPS)

$(XI_BINDIR)/experimental: $(XI) $(XI_OBJS)
	@-mkdir -p $(dir $@)
	$(CC) $(XI_CFLAGS) $^ -o $@

$(XI):
	$(MAKE) -C .. libxively

include $(LIBXIVELY)/Makefile.rules

ifneq ($(MAKECMDGOALS),clean)
  -include $(XI_DEPS)
endif
