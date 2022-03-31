# `dbg(...)`

`dbg.h` is a clumsy replica of [sharkdp/dbg-macro](https://github.com/sharkdp/dbg-macro), which mainly target for C89 and above.

This project provides [a single header file](dbg.h) with two macros `dbg(...)` and `dbge(...)` that can be used in all circumstances where you would typically write [`printf(...)`](https://www.man7.org/linux/man-pages/man3/printf.3.html) or [`fprintf(...)`](https://www.man7.org/linux/man-pages/man3/fprintf.3.html).

The `dbg(...)` will prints debugging output to the `stdout`, yet the `dbge(...)` will prints to the `stderr`.

`dbg*(...)` macro takes two arguments: the former is the expression itself, the latter is the format specifier (just as in [`printf(3)`](https://www.man7.org/linux/man-pages/man3/printf.3.html)).

# Example

```c
#include <stdio.h>

#define DBG_H_DEF_ONCE
#include "dbg.h"

static int factorial(int n) {
    if (dbg(n <= 1, %d)) return dbg(1, %d);
    return dbg(n * factorial(n - 1), %d);
}

int main(void) {
    int x = 1;
    dbg(x > 0, %d);
    factorial(4);
    const char *s = "hello world";
    dbg(s, %s);
    dbge(sizeof(double), %zu);
    dbg(&main, %p);
    dbg(main == &main, %d);
    dbg("this line is executed", %s);
    return 0;
}
```

You must `#define DBG_H_DEF_ONCE` only once before include the "dbg.h".

Note that the format specifier(the second argument) is **NOT** double-quoted.

Sample output of above code ([try it yourself](https://repl.it/@leiless/dbgh-demo)):

![dbg.h example output](https://user-images.githubusercontent.com/38041294/90304146-2e128a00-dee7-11ea-8462-2854dfdeac03.png)

# Feature

* Easy to read, colorized output (colors will be disable when the output is not an interactive terminal)

* Prints file name, line number, function name and the original expression

* Prints format specifier for the printed-out value (which far less powerful than [sharkdp/dbg-macro](https://github.com/sharkdp/dbg-macro))

* Can be used inside expressions (passing through the original value)

* The `dbg.h` header issues a compiler warning when included (so you don't forget to remove it)

* Compatible with C89, C99, C11.

# Configuration

* `#define DBG_H_NO_WARNING` to suppress output of the `WARNING: the "dbg.h" header is included in your code base`

* `#define DBG_H_DISABLE` to disable the debugging output, so `dbg(x, fs)` will be simply replaced by `x` itself.

# Stability

The exact output printed by this macro should not be relied upon and is subject to future changes.

# Panics

Panics if writing to [`fprintf(3)`](https://www.man7.org/linux/man-pages/man3/fprintf.3.html) fails (by calling [`assert(3)`](https://www.man7.org/linux/man-pages/man3/assert.3.html), so `#define NDEBUG` will disable this panic).

P.S. this is extreme unlikely to happen.

# Courtesy

This project mainly inspired by [sharkdp/dbg-macro](https://github.com/sharkdp/dbg-macro), this project cannot succeeded without his effort.

Part of this README inspired by [sharkdp/dbg-macro](https://github.com/sharkdp/dbg-macro) and Rust's [std::dbg!()](https://doc.rust-lang.org/std/macro.dbg.html).

# TODO

[`_Generic`](https://en.cppreference.com/w/c/language/generic) keyword introduced since C11, we may do better in debugging output.
