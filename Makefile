CC := gcc
CFLAGS := -O0 -std=gnu99 -g3 -Wall -Werror -Wno-error=cpp

JCC_DEBUG := JCC_DEBUG

LEX_DIR          := ./lexical
CORE_DIR         := ./core
SRC_DIR          := src
INCLUDE_DIR      := include
DEMO_DIR         := demo

LEX_INCLUDES_DIR := $(LEX_DIR)/$(INCLUDE_DIR)
LEX_SRC_DIR      := $(LEX_DIR)/$(SRC_DIR)
CORE_INCLUDES_DIR:= $(CORE_DIR)/$(INCLUDE_DIR)
CORE_SRC_DIR     := $(CORE_DIR)/$(SRC_DIR)


TARGET := JCC
LEX_SOURCE  :=$(wildcard $(LEX_SRC_DIR)/*.c)
CORE_SOURCE :=$(wildcard $(CORE_SRC_DIR)/*.c)


all:$(TARGET)


#Open the debug output in JCC
#CFLAGS += -D$(JCC_DEBUG)

$(TARGET):$(CORE_SOURCE) $(LEX_SOURCE)
	$(CC) $(CFLAGS) $(addprefix -I,$(LEX_INCLUDES_DIR)) $(addprefix -I,$(CORE_INCLUDES_DIR)) \
          $^ -o $@

demo:$(TARGET)
	./JCC $(DEMO_DIR)/ex_Indent.c

demo_gdb:$(TARGET)
	gdb --args ./$(TARGET) $(DEMO_DIR)/ex_Indent.c


clean:
	rm $(TARGET)


cscope:
	cscope -Rbqf ./cscope.out

astyle:
	@echo "More details please see: coding-style.txt"
	astyle --style=linux --indent=tab -p -U -K -H --suffix=none --exclude=$(DEMO_DIR) --recursive ./*.c
	astyle --style=linux --indent=tab -p -U -K -H --suffix=none --exclude=$(DEMO_DIR) --recursive ./*.h
