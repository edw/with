#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "with.h"

#define FIRST_NAME "First name"
#define LAST_NAME "Last name"

#define MAX_NAME_SIZE 255

char* trimr(char* s) {
  size_t len=strlen(s);

  if(len && s[len-1]=='\n') {
    s[len-1]='\0';
  }

  return s;
}

char *get_name(FILE *in, FILE *out, char const *type) {
  char *s=NULL;
  size_t capp=0;

  fprintf(out, "%s: ", type);
  getline(&s, &capp, in);
  trimr(s);

  return s;
}

typedef struct person {
  char *first;
  char *last;
} person;

void *getperson(va_list ap) {
  person *p;
  FILE *in = va_arg(ap, FILE *);
  FILE *out = va_arg(ap, FILE *);

  p = malloc(sizeof(person));
  assert(p != NULL);
  p->first = get_name(in, out, FIRST_NAME);
  p->last = get_name(in, out, LAST_NAME);

  return p;
}

int greetperson(void *o, va_list ap) {
  person *p = o;
  FILE *out = va_arg(ap, FILE *);
  char *greeting = va_arg(ap, char *);

  fprintf(out, "%s, %s %s.\n", greeting, p->first, p->last);

  return 0;
}

void freeperson(void *o) {
  person *p = o;

  if(p != NULL) {
    free(p->first);
    free(p->last);
    free(p);
  }
}

int main(int argc, char **argv) {
  with(getperson, greetperson, freeperson,
       stdin, stdout,
       stdout, "Yo");
  return 0;
}
