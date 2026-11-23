#include "base.h"
#include "core/calc.c"
#include "core/file.c"
#include "core/file.h"
#include "core/linked_list.c"
#include "core/linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  UNUSED(argc);
  UNUSED(argv);
  usize size = 0;
  const char *path = "./README.md";
  u8 *fp = read_entire_file(path, &size);
  if (fp != NULL) {
    printf("READ %zu bytes:\n%s\n", size, (char *)fp);
    free(fp);
  }
  return 0;
}
