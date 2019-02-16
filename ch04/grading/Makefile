# Makefile for `grading` program

CC = g++

SRC = src
BUILD = build
BIN = bin
TARGET = $(BIN)/grading

SRCEXT = cpp
SOURCES = $(shell find $(SRC) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.cpp=.o))
INC = -I $(SRC)

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^

$(BUILD)/main.o : \
	$(SRC)/main.cpp \
	$(SRC)/grade.h \
	$(SRC)/Student_info.h

$(BUILD)/grade.o : \
	$(SRC)/grade.cpp \
	$(SRC)/grade.h \
	$(SRC)/Student_info.h \
	$(SRC)/median.h

$(BUILD)/median.o : $(SRC)/median.cpp

$(BUILD)/Student_info.o : \
	$(SRC)/Student_info.cpp \
	$(SRC)/Student_info.h

$(BUILD)/%.o : $(SRC)/%.cpp
	g++ $(INC) -g -o $@ -c $<

clean :
	rm -f $(BUILD)/* $(BIN)/*
