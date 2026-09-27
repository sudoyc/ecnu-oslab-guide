# Lab1 的观察用示例。stack 需要 RISC-V 交叉编译器（前缀不同就 make CROSS=riscv64-linux-gnu- stack），race 只需要 gcc
CROSS ?= riscv64-elf-
stack: stack.c
	$(CROSS)gcc -O1 -c stack.c -o stack.o
	$(CROSS)objdump -d stack.o

race: race.c
	gcc -O1 -pthread race.c -o race
	./race none; ./race fine; ./race coarse

clean:
	rm -f stack.o race

.PHONY: stack race clean
