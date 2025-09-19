#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "devices/input.h"

#define MON_BUF_SZ 128

static void read_line(char *buf, size_t n) {
  size_t i = 0;
  for (;;) {
    int ch = input_getc();
    if (ch == '\r' || ch == '\n') { printf("\n"); buf[i] = '\0'; return; }
    if (i + 1 < n && isprint(ch)) { buf[i++] = (char)ch; putchar(ch); }
  }
}

void kernel_monitor(void) {
  char line[MON_BUF_SZ];
  for (;;) {
    printf("BUOS> ");
    memset(line, 0, sizeof line);
    read_line(line, sizeof line);

    if (!strcmp(line, "whoami")) {
      printf("Derek Lee\n");          // <- your name
    } else if (!strcmp(line, "exit")) {
      return;
    } else if (line[0] != '\0') {
      printf("invalid command\n");
    }
  }
}

