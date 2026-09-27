# 结构和课程框架的 Makefile 一样：先把每个 .c 编译成 .o，再链接成一个可执行文件
CC     = gcc
CFLAGS = -Wall -O1

OBJ = main.o greet.o

# 默认目标（第一个目标）：make 不带参数时执行它
demo: $(OBJ)
	$(CC) $(OBJ) -o $@

# 模式规则：任意 xxx.o 由 xxx.c 生成。$@ 是目标，$< 是第一个依赖
%.o: %.c greet.h
	$(CC) $(CFLAGS) -c $< -o $@

run: demo
	./demo

clean:
	rm -f demo *.o

.PHONY: run clean
