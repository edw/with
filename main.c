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

char *get_name(char const *type) {
  char *s=NULL;
  size_t capp=0;

  printf("%s: ", type);
  getline(&s, &capp, stdin);
  trimr(s);

  return s;
}

struct person {
  char *first;
  char *last;
};

void *getperson(va_list ap) {
  struct person *p;

  p = malloc(sizeof(struct person));
  assert(p != NULL);
  p->first = get_name(FIRST_NAME);
  p->last = get_name(LAST_NAME);
  return p;
}

int greetperson(void *o, va_list ap) {
  struct person *p = o;
  char *greeting = va_arg(ap, char *);
  printf("%s, %s %s.\n", greeting, p->first, p->last);
  return 0;
}

void freeperson(void *o) {
  struct person *p = o;
  if(p != NULL) {
    free(p->first);
    free(p->last);
    free(p);
  }
}

int main(int argc, char **argv) {
  with(getperson, greetperson, freeperson,
       "Yo");
  
  return 0;
}
