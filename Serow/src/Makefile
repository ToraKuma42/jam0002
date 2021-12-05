SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
CFLAGS = -g -Wall -O2 -std=gnu17 -mstackrealign -mretpoline
LFLAGS = -Wl,--gc-sections
LLFLAGS = -I../include
CC = clang
TARGET = serow

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LLFLAGS) -o $(TARGET) $(LFLAGS)

clean:
	rm -f serow.exe *.o *.i *.s *.gch *~ serow


