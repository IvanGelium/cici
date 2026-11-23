#include "core/file.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

u8 *read_entire_file(const char *path, usize *out_size) {
  FILE *fc = fopen(path, "rb");
  if (fc == NULL) {
    printf("Couldn't access the file %s \n", path);
    return NULL;
  }

  if (fseek(fc, 0, SEEK_END) != 0) {
    fclose(fc);
    return NULL;
  }

  long raw_size = ftell(fc);
  if (raw_size < 0) {
    fclose(fc);
    return NULL;
  }

  rewind(fc);
  usize size = (usize)raw_size;

  u8 *buf = malloc(size + 1);
  if (buf == NULL) {
    fclose(fc);
    return NULL;
  }

  usize bytes_read = fread(buf, 1, size, fc);
  fclose(fc);

  if (bytes_read != size) {
    free(buf);
    return NULL;
  }
  buf[size] = '\0';
  if (out_size != NULL) {
    *out_size = size;
  }

  return buf;
}