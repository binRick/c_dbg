/********************************/
#include <stdio.h>
/********************************/
#define DBG_H_DEF_ONCE
/********************************/
//#define DBG_H_DISABLE
/********************************/
#include "dbg.h"
/********************************/
#include "src/dbg.c"
/********************************/


static int factorial(int n) {
  if (dbg(n <= 1, % d)) {
    return(dbg(1, % d));
  }
  return(dbg(n * factorial(n - 1), % d));
}


int main(void) {
  int x = 1;

  dbg(x > 0, % d);
  factorial(4);
  const char *s = "hello world";

  dbg(s, % s);
  dbge(sizeof(double), % zu);
  dbg(&main, % p);
  dbg(main == &main, % d);
  dbg("this line is executed", % s);

  dbg(env_get_or("USER", "UNKNOWN"), % s);
  dbg(env_get_or("USER1", "UNKNOWN"), % s);
  dbge(env_get_or("USER1", "UNKNOWN"), % s);


  return(0);
}
