#include "with.h"

extern int with(acquirefn a, usefn u, releasefn r, ...) {
  va_list ap;
  void *resource;
  int ret;

  va_start(ap, r);

  resource = a(ap);
  ret = u(resource, ap);
  r(resource);

  va_end(ap);

  return ret;
}
