#define DBG_H_DEF_ONCE
#ifndef DBG_H_c49aa87c_54eb_46d2_8d72_a51f5efce1ac
#define DBG_H_c49aa87c_54eb_46d2_8d72_a51f5efce1ac

#ifndef DBG_H_NO_WARNING
#pragma message("WARNING: the \"dbg.h\" header is included in your code base")
#endif

#include <assert.h>
#include <stdio.h>

#ifdef DBG_H_DEF_ONCE
#include <string.h>


/**
 * basename(3) have inconsistent implementation across UNIX-like systems.
 * Besides, Windows doesn't have such API.
 */
const char *bname_b49cf5f693ad(const char *path){
  const char *p;

#ifdef _WIN32
  p = strrchr(path, '\\');
#else
  p = strrchr(path, '/');
#endif
  return(p != NULL ? p + 1 : path);
}
#endif      /* DBG_DEF_ONCE */

/**
 * Taken from https://github.com/sharkdp/dbg-macro
 */
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#define DBG_H_IS_UNIX
#endif

#define COL_NONE    ""
#define COL_RST     "\x1b[0m"
#define COL_DBG     "\x1b[02m"
#define COL_EXPR    "\x1b[36m"
#define COL_VAL     "\x1b[01m"
#define COL_TYPE    "\x1b[32m"

#ifdef DBG_H_IS_UNIX
#include <unistd.h>
#define DBG_H_COL(out, col)    (isatty(fileno(out)) ? (col) : COL_NONE)
#else
/* XXX: Assume it's colorized output */
#define DBG_H_COL(out, col)    (col)
#endif

/*
 * Taken from https://stackoverflow.com/a/2653351/13600780
 * see: linux/include/linux/stringify.h
 */
#ifndef xstr
#define xstr0(x)    #x
#define xstr(x)     xstr0(x)
#endif

#ifdef _WIN32
#define DBG_H_FILE    __FILE__
#else
#define DBG_H_FILE    __BASE_FILE__
#endif

#ifndef DBG_H_DISABLE
#define x_dbg_ac3a285c(out, x, fs)    ({                            \
    typeof(x) _x0 = (x);                                            \
    int _n0 = fprintf(                                              \
      out, "%s[%s:%d (%s)]%s %s%s%s = %s" xstr(fs) "%s (%s%s%s)\n", \
      DBG_H_COL(out, COL_DBG),                                      \
      bname_b49cf5f693ad(DBG_H_FILE), __LINE__, __func__,           \
      DBG_H_COL(out, COL_RST),                                      \
      DBG_H_COL(out, COL_EXPR), #x, DBG_H_COL(out, COL_RST),        \
      DBG_H_COL(out, COL_VAL), _x0, DBG_H_COL(out, COL_RST),        \
      DBG_H_COL(out, COL_TYPE), #fs, DBG_H_COL(out, COL_RST)        \
      );                                                            \
    assert(_n0 > 0);                                                \
    _x0;                                                            \
  })
#else
#define x_dbg_ac3a285c(out, x, fs)    ((void)(out), (void)(#fs), (x))
#endif

#define dbg(x, fs)                    x_dbg_ac3a285c(stdout, x, fs)
#define dbge(x, fs)                   x_dbg_ac3a285c(stderr, x, fs)

#endif
