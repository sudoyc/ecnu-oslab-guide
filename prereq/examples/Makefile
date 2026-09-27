# 预备知识的示例。memory/pointer/bits 只需要 gcc；asm 需要 RISC-V 交叉编译器
# 前缀不同就 make CROSS=riscv64-linux-gnu- asm
CROSS ?= riscv64-elf-

memory pointer bits: %: %.c
	gcc -Wall -O0 $< -o $@
	./$@

asm: asm.c
	$(CROSS)gcc -O1 -c asm.c -o asm.o
	$(CROSS)objdump -d asm.o

clean:
	rm -f memory pointer bits asm.o

.PHONY: memory pointer bits asm clean
