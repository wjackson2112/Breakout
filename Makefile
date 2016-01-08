#SRC specifies which files to compile as part of the project
SRC = $(wildcard src/*.cpp)

#CC specifies which compiler we're using
CC = g++

#Compiler Flags
# -w suppresses all warnings
CC_FLAGS = -w -std=c++11

#Linker Flags
LD_FLAGS = -lSDL2 -lSDL2_image

#TARGET specifies the name of our exectuable
TARGET = build/breakout

#This is the target that compiles our executable
all : $(SRC)
	@mkdir -p build
	@$(CC) $(SRC) $(CC_FLAGS) $(LD_FLAGS) -o $(TARGET)
clean : $(SRC)
	@rm -rf build
run : $(SRC)
	@$(CC) $(SRC) $(CC_FLAGS) $(LD_FLAGS) -o $(TARGET)	
	@./$(TARGET)