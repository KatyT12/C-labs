#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "re.h"

arena_t create_arena(int size) { 
  arena_t arena = malloc(sizeof(struct arena));
  arena->elements = malloc(sizeof(Regexp) * size);
  arena->size = size;
  arena->current = 0;
  return arena;
}

void arena_free(arena_t a) { 
  free(a->elements);
  free(a);
}

Regexp *re_alloc(arena_t a) { 
  if(a->current >= a->size){
    printf("No memory\n");
    return NULL; //No memory
  }
  Regexp* re = a->elements + a->current;
  a->current += 1;
  return re;
}

Regexp *re_chr(arena_t a, char c) { 
  Regexp* re = re_alloc(a);
  if(re == NULL){
    return NULL;
  }
  re->type = CHR;
  re->data.chr = c;
  return re;
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp* re = re_alloc(a);
  if(re == NULL){
    return NULL;
  }
  re->type = ALT;
  re->data.pair.fst = r1;
  re->data.pair.snd = r2;
  return re;
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp* re = re_alloc(a);
  if(re == NULL){
    return NULL;
  }
  re->type = SEQ;
  re->data.pair.fst = r1;
  re->data.pair.snd = r2;
  return re;
}

int re_match(Regexp *r, char *s, int i) { 
  if(i > strlen(s)-1 || r == NULL) return -1;
  if(r->type == CHR){
    if(s[i] == r->data.chr){
      return i + 1;
    }else{
      return -1;
    }
  }else if(r->type == SEQ){
    int k = re_match(r->data.pair.fst, s, i);
    if(k == -1) return -1;
    int j = re_match(r->data.pair.snd, s, k);
    return j;
  }
  else if(r->type == ALT){
    int k = re_match(r->data.pair.fst, s, i);
    int j = re_match(r->data.pair.snd, s, i);
    return (k == -1) ? j : k;
  }
  return -1;
}



void re_print(Regexp *r) { 
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) { 
	printf("(");
	re_print(r->data.pair.fst);
	printf(")");
      } else {
	re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) { 
	printf("(");
	re_print(r->data.pair.snd);
	printf(")");
      } else {
	re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else { 
    printf("NULL");
  }
}    


      
  
