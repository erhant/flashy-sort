CC = g++
CCFLAGS = -O3 --std=c++11
BINDIR = bin
TARGET = ./$(BINDIR)/sort
INCLUDES = -Iinclude -Itemplates
SOURCES = src/main.cpp

# Make the target executable
$(TARGET): $(SOURCES)
	@mkdir -p $(BINDIR)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ $^ 
  
# Clean outputs
clean:
	rm $(BINDIR)/*

# Clean and make again
again:
	@make clean && make

.PHONY: clean again