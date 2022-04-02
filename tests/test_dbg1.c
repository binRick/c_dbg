/********************************/
#include <stdio.h>
/********************************/
//#define DBG_H_DISABLE
/********************************/
#include "dbg.h"
#include "include/debug_print.h"
/********************************/
#include "src/dbg.c"
/********************************/
#define RED_GROUP           1
#define EXTRA_INFO_GROUP    2
/********************************/
debug_print_options o = (struct debug_print_options){ .colorscheme = FORE_BLUE };


/********************************/
static int factorial(int n) {
  if (dbg(n <= 1, % d)) {
    return(dbg(1, % d));
  }
  return(dbg(n * factorial(n - 1), % d));
}


/********************************/
void debug_print_demo(){
  int  i  = 5;
  char *s = "yo";
  FILE *a = fopen("/tmp/a", "w");

  strncpy(debug_print_group_options_list[RED_GROUP].colorscheme, FORE_MAGENTA, DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE - 1);
  debug_print_group_options_list[EXTRA_INFO_GROUP].disabled = true;

  DBG(factorial(10));
  DBG(7, .group = 1);
  DBG(i);
  DBG('A');
  DBG(s);
  DBG("yo", FORE_GREEN);
  DBG("yo message", FORE_YELLOW);
  DBG(0 + 22);
  DBG(0 == 1);
  DBG(1 == 1);
  DBG(2 > 1);
  DBG(s, .group                                         = EXTRA_INFO_GROUP);
  DBG(o, .colorscheme                                   = FORE_GREEN, .group = RED_GROUP);
  DBG(debug_print_group_options_list[RED_GROUP], .group = RED_GROUP);
}


/********************************/
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

  debug_print_demo();
  DBG(env_get_or("USER", "UNKNOWN"), FORE_GREEN);
  DBG(env_get_or("USER1", "UNKNOWN"), FORE_YELLOW);

  char *ss = "xxxxxxxxxxxxxxxxx";
  int dd = 1024;
  print("s:", ss, dd);
  print(env_get_or("USER1", "UNKNOWN"));
  print("d:", dd);

  return(0);
}
/********************************/
/*
enum
{
    plain = 0,
    bold = 1,
    italic = 2
};


void PrintString(const char* message = NULL, int size = 0, int style = 0)
{
}

void vvvx(){

#define PRINT_STRING(...) PrintString(__VA_ARGS__)


    PRINT_STRING("Hello, World!");
    PRINT_STRING("Hello, World!", 18);
    PRINT_STRING("Hello, World!", 18, bold);

    return 0;
}*/
