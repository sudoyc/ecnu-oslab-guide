#pragma once

// 输出一个字符。内核里对应 uart_putc_sync，这里由 test.c 提供。
void kputc(int c);

void kprintf(const char *fmt, ...);
