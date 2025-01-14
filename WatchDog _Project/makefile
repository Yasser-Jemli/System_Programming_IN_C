CFLAGS = -Wall -pedantic -std=gnu99 $(shell pkg-config --cflags libnotify)
LIBS = $(shell pkg-config --libs libnotify)

all: Watchdogd

Watchdogd:
	gcc $(CFLAGS) Watchdogd.c -o build/Watchdogdd $(LIBS)
