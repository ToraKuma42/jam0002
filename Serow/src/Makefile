SUBDIRS = $(wildcard */)
SRC = $(wildcard $(addsuffix *.c,$(SUBDIRS))) $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRC))
CFLAGS = -g -Wall -O2 -std=gnu17 -mstackrealign -mretpoline
LFLAGS = -Wl,--gc-sections
LLFLAGS = -I../include
CC = clang
TARGET = serow

all: $(TARGET) test

test: $(TARGET)
	./serow ../test/resources/00/hello.slc

$(OBJS) : %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LLFLAGS) -o $(TARGET) $(LFLAGS)

clean:
	rm -f serow.exe *.o **/*.o *.i *.s *.gch *~ serow


