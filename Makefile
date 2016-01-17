#SRC specifies which files to compile as part of the project
SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
HDR = $(wildcard $(SRC_DIR)/*.h)

#CC specifies which compiler we're using
CC = g++

#Compiler Flags
# -w suppresses all warnings
CC_FLAGS = -w -std=c++11

#Linker Flags
LD_FLAGS = -lSDL2 -lSDL2_image
INCLUDES = -Iinclude

#TARGET specifies the name of our exectuable
TARGET_NAME = breakout
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: clean distclean run

#This is the target that compiles our executable
all: dir $(TARGET)

dir:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo Linking $@
	@$(CC) $^ -o $@ $(LD_FLAGS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp $(BUILD_DIR)/%.d
	@echo Compiling $< to $@
	@$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@ -MT $@ -MMD -MP -MF $(@:.o=.d)

clean:
	@echo Cleaning
	@rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET)

distclean:
	@echo Removing Directory $(BUILD_DIR)
	@$(RM) -rf $(BUILD_DIR)

run: all	
	@echo Running $(TARGET)
	@./$(TARGET)

$(BUILD_DIR)/%.d: ;
.PRECIOUS: $(BUILD_DIR)/%.d

-include $(OBJS:.o=.d)
