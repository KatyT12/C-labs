#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

Node *empty = NULL;

Node *node(int value, Node *left, Node *right) { 
  Node *r = malloc(sizeof(Node));
  r->marked = false;
  r->value = value;
  r->left = left;
  r->right = right;
  return r;
}


/* Basic Problems */

int size(Node *node) {
  if(node == NULL || node->marked){
    return 0;
  } 
  node->marked = true;

  return size(node->left) + size(node->right) + 1;
}


void unmark(Node *node) { 
  if(node == NULL || !(node->marked)){
    return;
  }
  node->marked = false;
  unmark(node->left);
  unmark(node->right);
}

bool path_from(Node *node1, Node *node2) {
  /* TODO */
  if(node1 == NULL || node1->marked){
    return false;
  }
  if(node1 == node2){
    return true;
  }
  node1->marked = true;
  return path_from(node1->left,node2) || path_from(node1->right, node2);
}

bool cyclic(Node *node) { 
  node->marked = true;
  bool a = path_from(node->right, node);
  bool b = path_from(node->left, node);
  return a || b;
} 


/* Challenge problems */

Node**  get_nodes(Node *node, Node **dest) { 
  //Node** nodes = malloc(sizeof(Node*) * size(node));
  if(node == NULL || node->marked){
    return dest;
  }
  node->marked=true;
  *dest = node;
  dest++; //Go to next
  
  dest = get_nodes(node->left,dest);
  dest = get_nodes(node->right,dest);
  return dest;
}

void graph_free(Node *node) { 
  int s = size(node); //Why is size == 1
  unmark(node);
  Node** arr = malloc(sizeof(Node*)*s);
  get_nodes(node, arr);

  for(int i = 0; i < s; i++){
    free(*(arr + i));
  }
  free(arr);
}


