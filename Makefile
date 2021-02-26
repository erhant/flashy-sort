CC = g++
CCFLAGS = -O3  
TARGET = sort
INCLUDES = -Iinclude
SOURCES = src/main.cpp

$(TARGET): $(SOURCES)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $@ $^ 

clean:
	rm $(TARGET).exe
	rm $(TARGET).exp
	rm $(TARGET).lib