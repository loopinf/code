.PHONY: all clean

#CC = arm-linux-gnueabihf-gcc
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))
CFLAGS = -Werror -pthread 

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< -lrt

clean:
	rm -f $(PROGS)
