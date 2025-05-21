CXX = g++
CXXFLAGS = -std=c++17 -Wall
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = UTGhalam

.SILENT: all $(TARGET) $(OBJS)

all: $(TARGET)
	@echo UTGhalam

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -f $(OBJS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TARGET)