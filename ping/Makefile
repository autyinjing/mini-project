#begin Makefile

C_SOURCES = $(shell find ./ -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

C_FLAGS = -c -g -Wall
C_LINKFLAGS = -lpthread

TARGET = my_ping

CC = gcc

$(TARGET): $(C_OBJECTS)
	@echo 链接 ...
	@$(CC) -o $(TARGET) $(C_OBJECTS) $(C_LINKFLAGS)

$(C_OBJECTS): %.o: %.c
	@echo 编译 ...
	@$(CC) $(C_FLAGS) $< -o $@

.PHONY: clean

clean:
	@echo 删除中间文件
	@rm -f $(C_OBJECTS)

#end of Makefile
