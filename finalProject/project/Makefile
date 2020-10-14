CC=g++
CFLAGS=-g -O0 -std=c++14
OFILES= ECComp.o ECCompose.o ECProj.o ECCommand.o ECChain.o ECTextViewImp.o ECEditorTest.o 

all:  ECEditorTest

ECEditorTest: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $@

.o:.cpp
	$(CC) -c $(CFLAGS) $< 

clean:
	@echo "Cleanup..." 
	rm -rf *.o *~ ECEditorTest


