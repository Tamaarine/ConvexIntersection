CC = g++
SRC = src
CFLAGS := -Wall -Werror -Wno-unused-variable -Wno-unused-function -MMD
INC := -I include  
EXE := convexIntersect
BIND := bin
BUILD := build

srcs = $(shell find src/ -type f)
objs := $(patsubst src/%, $(BUILD)/%, $(srcs:.cpp=.o))

all: setup bin/$(EXE)
setup: $(BIND) $(BUILD)
$(BIND):
	echo $(objs)
	mkdir -p $(BIND)
$(BUILD):
	mkdir -p $(BUILD)

bin/$(EXE): $(objs)
	$(CC) $^ -o $@

build/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
.PHONY: clean 
clean: 
	rm -rf bin build