TC=
CC=@echo "CC $@";$(TC)gcc
CXX=@echo "CC $@";$(TC)gcc
AR=@echo "AR $@";$(TC)ar

LIBDIR=-I.
# LIDLIBS=-lstd
CPPFLAGS=$(LIBDIR)
CPPFLAGS+=-std=c99
CPPFLAGS+=-w

TARG = $(subst .c,.o,$(wildcard *.c))

# LIBDIR+=-I../recast/

all:main
	./main

main:$(TARG)

.PHONY: clean
clean:
	$(RM) -r *.o *.a