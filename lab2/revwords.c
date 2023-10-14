#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "revwords.h"


int is_alpha(char c){
  if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
  else return 0;
}

void reverse_substring(char str[], int start, int end) { 
  for(int i = start, j = end; i < j; i++, j--){
      char temp = str[i];
      str[i] = str[j];
      str[j] = temp;
  }
}


int find_next_start(char str[], int len, int i) { 
  while(i < len){
    if(! is_alpha(str[i])){
      i++;
      continue;
    }else{
      return i;
    }
  }
  return -1;
}

//Confused by what this does
int find_next_end(char str[], int len, int i) {
  while(i < len && is_alpha(str[i])){
    i++;
  }
  return i;
}

void reverse_words(char s[]) { 
  int i = 0;
  int len = strlen(s);
  while(i < len){
    int i = find_next_start(s, len, i);
    if(i == -1){return;}
    int e = find_next_end(s, len, i) - 1;
    reverse_substring(s, i, e);
    i = e + 1;
  }
}
