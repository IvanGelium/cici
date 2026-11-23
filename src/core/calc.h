#pragma once

#include "base.h"

i32 add(i32, i32);
i32 sub(i32, i32);
i32 mul(i32, i32);
i32 dva(i32, i32);
void calc_cli(void);
typedef i32 (*op_cb)(i32, i32);
typedef enum { ADD, SUB, MUL, DVA } CALC_OPS;
