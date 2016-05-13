CC := gcc
CFLAGS := -O0 -std=gnu99 -g3 -Wall -Werror 


INCLUDES_DIR := ./include
SRC_DIR   := ./src

TARGET := JCC
CORE_SOURCE :=$(wildcard $(SRC_DIR)/*.c)


all:$(TARGET)

$(info $(TARGET))


$(TARGET):$(CORE_SOURCE)
	$(CC) $(CFLAGS) $(addprefix -I,$($(1)_INC_DIR)) \
          $^ -o $@

clean:
	rm $(TARGET)


cscope:
	cscope -Rbqf ./cscope.out

astyle:
	@echo "More details please see: coding-style.txt"
	astyle --style=linux --indent=tab -p -U -K -H --suffix=none --recursive ./*.c
	astyle --style=linux --indent=tab -p -U -K -H --suffix=none --recursive ./*.h
