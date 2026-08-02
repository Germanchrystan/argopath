CC = clang
CFLAGS = # -Wall -Wextra -Werror -MMD -MP
LDFLAGS = -lraylib

CSOURCES = $(wildcard *.c)
MSOURCES = $(wildcard *.m)

MOBJS = $(patsubst %.m, %.o, $(MSOURCES))
COBJS = $(patsubst %.c, %.o, $(CSOURCES))

# This allows macos_presentation.m to be compiled on macOS, but not on other platforms.
# It also links the Cocoa framework on macOS.
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
LDFLAGS += -framework Cocoa
endif

all: argopath

argopath: $(COBJS) $(MOBJS)
	$(CC) -o argopath $(COBJS) $(MOBJS) $(LDFLAGS)
	rm -f $(COBJS) $(MOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.m
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COBJS) $(MOBJS)

run:
	./argopath