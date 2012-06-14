CC=g++

GTEST_LIB=$(HOME)/local-gcc-trunk/gtest/lib

CFLAGSX:=$(CFLAGS)
LDFLAGSX:=$(LDFLAGS)

CFLAGSX+=-Wall -O3 -s -fpic -std=c++11 -Wno-strict-aliasing -Wextra -Werror -pedantic -DNDEBUG
CFLAGSX+=-Wno-unused-parameter

CFLAGSX+=-I include
CFLAGSX+=-I 3rdparty

LDFLAGSX+=-lstdc++ -lpthread -O3 -s


SRCS = $(wildcard test/*.cpp)

PROGS = $(patsubst %.cpp,%.out,$(SRCS))


all: $(PROGS) demo

%.out: %.cpp
	$(CC) $(LDFLAGSX) $(CFLAGSX) $(GTEST_LIB)/gtest_main.a -o $@ $<

test: all
	@for p in $(PROGS); do \
	  echo "running $$p"; \
	  ./$$p  --gtest_color=yes; \
	done;

demo: demo/demo.out

demo/demo.out: demo/demo.cpp
	$(CC) $(LDFLAGSX) $(CFLAGSX) -o $@ $<

clean:
	rm -f test/*.o $(PROGS) demo/*.out

.PHONY: clean test example

