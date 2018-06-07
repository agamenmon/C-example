
CFLAGS=$(shell pkg-config --cflags sqlite3) -O0 -g
LDLIBS=$(shell pkg-config --libs sqlite3)

default : demo mem openclose

debug : 
	@echo CFLAGS = $(CFLAGS)
	@echo LDLIBS = $(LDLIBS)


