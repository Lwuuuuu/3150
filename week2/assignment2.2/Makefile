CC=c++
CFLAGS=-g -O0 -std=c++14
OFILES=wList.o main.o

all:  run

wlist2: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $@

.o:.cpp
	$(CC) -c $(CFLAGS) $< 

run : 	wlist2
		./wlist2

.PHONY: all run

clean:
	@echo "Cleanup..." 
	rm -rf *.o *~ wList


