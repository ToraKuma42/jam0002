SRC = *.c
OBJS = $(SRC:.c=.o)
CFLAGS = -g -Wall -s -O2 -std=gnu17 -mstackrealign -mretpoline
LFLAGS = -Wl,--gc-sections
LDFLAGS = -lcunit
LLFLAGS = -I../include
CC = clang
TARGET = serow

all: $(TARGET)

clean:
	rm -f test-serow.exe *.o *.i *.s *.gch *~ test-serow

serow: 
	clang $(CFLAGS) $(SRC) $(LLFLAGS) $(LDFLAGS) -o test-serow $(LFLAGS)


