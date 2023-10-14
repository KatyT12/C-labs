#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *cons(int head, List *tail) { 
  /* malloc() will be explained in the next lecture! */
  List *cell = malloc(sizeof(List));
  cell->head = head;
  cell->tail = tail;
  return cell;
}

/* Functions for you to implement */

int sum(List *list) {
  int ret=0;
  while(list != NULL){
    ret+= list->head;
    list = list->tail;
  }
  return ret;
}

void iterate(int (*f)(int), List *list) {
  while(list != NULL){
    
    list->head = f(list->head);
    list = list->tail;
  }
}

void print_list(List *list) { 
  while(list != NULL){
    printf("[");
    while(list != NULL){
      printf("%d%s",list->head, (list->tail == NULL ? "" : ", "));
      list = list->tail;
    }
    printf("]\n");
  }
}

/**** CHALLENGE PROBLEMS ****/


  //test = cons(1, cons(3, cons(4, cons(12, cons(18, NULL)))));
  //List *test2 = cons(2, cons(7, cons(8, cons(9, cons(20, NULL)))));

List *merge(List *list1, List *list2){ 
  
  //ret will be the list with the smaller start
  List* ret = list1->head <= list2->head ? list1 : list2;
  //For when one list reaches the end before the other
  List* prev1;
  List* prev2;

  prev1=list1;prev2=list2;
  printf("Start\n");
  while(list1 != NULL && list2 != NULL){ 
    if(list1->head <= list2->head){
      //maybe should wrap this up in a function instead?
      while(list1->tail != NULL && list2->head > list1->tail->head){
        prev1=list1;
        list1 = list1->tail;
      }
      
      //Insert
      List* temp = list1->tail;
      list1->tail = list2;
      list1 = temp;
      if(list1 == NULL) return ret;
    }
    else{
      while(list2->tail != NULL && list1->head > list2->tail->head){
        prev2 = list2; 
        list2 = list2->tail;
      }
      List* temp = list2->tail;
      list2->tail = list1;
      list2 = temp;
      if(list2 == NULL) return ret; // is all merged
      
    }
    
  }
  
  //Add to tail
  if(list1 != NULL){
    prev2->tail = list1;
  }else if(list2 != NULL){
    prev1->tail = list2;
  }
  
  return ret;  
}

void split(List *list, List **list1, List **list2) { 
  *list1 = NULL;
  *list2 = NULL;
  int i = 0;
  while(list != NULL){
    if(i == 0) *list1 = cons(list->head, *list1);
    else *list2 = cons(list->head, *list2);
    i = 1-i;
    list = list->tail;
  }
}

/* You get the mergesort implementation for free. But it won't
   work unless you implement merge() and split() first! */

List *mergesort(List *list) { 
  if (list == NULL || list->tail == NULL) { 
    return list;
  } else { 
    List *list1;
    List *list2;
    split(list, &list1, &list2);
    list1 = mergesort(list1);
    list2 = mergesort(list2);
    List* l = merge(list1, list2);
    //print_list(l);
    return l;
  }
}
