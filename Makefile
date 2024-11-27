# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./ -I$(shell pkg-config --cflags sdl2) -Iimgui -Iimgui/backends
LDFLAGS = $(shell pkg-config --libs sdl2) -framework OpenGL -lGLEW

# Directories
SRC_DIR = src
BUILD_DIR = build
IMGUI_DIR = imgui

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
IMGUI_SRCS = $(IMGUI_DIR)/imgui.cpp \
             $(IMGUI_DIR)/imgui_draw.cpp \
             $(IMGUI_DIR)/imgui_tables.cpp \
             $(IMGUI_DIR)/imgui_widgets.cpp \
             $(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp \
             $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS) $(IMGUI_SRCS))

# Target executable
EXEC = $(BUILD_DIR)/firesim

# Default target
all: $(EXEC)

# Build the final executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
