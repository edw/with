/* WITH.H */

#ifndef __WITH_H__
#define __WITH_H__

#include <stdarg.h>

typedef void *(*acquirefn)(va_list args);
typedef int (*usefn)(void *resource, va_list args);
typedef void (*releasefn)(void *resource);

extern int with(acquirefn a, usefn u, releasefn r, ...);

#endif
