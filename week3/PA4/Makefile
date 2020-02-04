CPPFILES = ECstropsmain.cpp\
 ECConcatenateStrings.cpp\
 ECGetDistinctSubstrings.cpp\
 ECIsSubString.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: stropsmain

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

stropsmain:$(OFILES)
	$(CC) -o strops $(OFILES)

clean: 
	rm *.o
	rm strops

