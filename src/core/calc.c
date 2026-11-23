#include "core/calc.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

i32 add(i32 x, i32 y) { return x + y; }
i32 sub(i32 x, i32 y) { return x - y; }
i32 mul(i32 x, i32 y) { return x * y; }
i32 dva(i32 x, i32 y) { return x / y; }

void calc_cli(void) {

  op_cb ops_dict[256] = {0};
  ops_dict['+'] = add;
  ops_dict['-'] = sub;
  ops_dict['*'] = mul;
  ops_dict['/'] = dva;

  char buf[64] = {0};
  printf("Введите первое число: ");
  fgets(buf, sizeof(buf), stdin);
  char *endptr = NULL;
  i32 num1 = (i32)strtol(buf, &endptr, 10);
  printf("Введите операцию (+,-,*,/): ");
  fgets(buf, sizeof(buf), stdin);
  u8 op = (u8)buf[0];
  bool isOpExist = op == '+' || op == '-' || op == '*' || op == '/';

  if (!isOpExist) {
    printf("Вы ввелите некорректную операцию.\n");
    printf("Выход из программы.\n");
    return;
  }
  printf("Введите второе число: ");
  fgets(buf, sizeof(buf), stdin);
  i32 num2 = (i32)strtol(buf, &endptr, 10);
  i32 res = ops_dict[op](num1, num2);
  printf("Результат: %d%c%d: %d\n", num1, op, num2, res);
}
