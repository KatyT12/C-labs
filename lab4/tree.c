#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

Tree *empty = NULL;

/* BASE EXERCISE */

int tree_member(int x, Tree *tree) { 
  // Will use dfs
  if(tree == NULL)return 0;

  if (tree->value == x) return 1;
  if(x  < tree->value) return tree_member(x, tree->left);
  else return tree_member(x,tree->right); 
}

Tree *tree_insert(int x, Tree *tree) { 
  if(tree == NULL){
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->value = x;
    t->left = NULL;
    t->right = NULL;
    return t;
  }
  if(x < tree->value){
    tree->left = tree_insert(x, tree->left);
  }else{
    tree->right = tree_insert(x, tree->right);
  }
  return tree;
}

void tree_free(Tree *tree) { 
  if(tree == NULL) return;
  tree_free(tree->left);
  tree_free(tree->right);
  free(tree);
}

/* CHALLENGE EXERCISE */ 

void pop_minimum(Tree *tree, int *min, Tree **new_tree) { 
  
  if(tree->left == NULL){
    *min = tree->value;
    if(tree->right == NULL){
      *new_tree = NULL;
    }else{
      *new_tree = tree->right;
    }
    
  }else{
    Tree* new_left;
    pop_minimum(tree->left, min, &new_left);
    tree->left = new_left;
    *new_tree = tree;
  }
}

void pop_maximum(Tree *tree, int *max, Tree **new_tree) { 
  if(tree->right == NULL){
    *max = tree->value;
    if(tree->left == NULL){
      *new_tree = NULL;
    }else{
      *new_tree = tree->left;
    }
  }else{
    Tree* new_right;
    pop_minimum(tree->right, max, &new_right);
    tree->right = new_right;
    *new_tree = tree;
  }
}


Tree *tree_remove(int x, Tree *tree) { 
  if(x == tree->value){
    if(tree->left == NULL && tree->right == NULL){
      return NULL;
    }
    int min; //Replacement
    Tree* new_tree;
    if(tree->right != NULL){ 
      pop_minimum(tree->right, &min, &new_tree);
      tree->right = new_tree;
    }else{
      pop_maximum(tree->left, &min, &new_tree);
      tree->left = new_tree;
    }
    tree->value = min;
    return tree;
  }else{
    if(x < tree->value){
      tree->left = tree_remove(x, tree->left);
    }else{
      tree->right = tree_remove(x, tree->right);
    }
    return tree;
  }
  
}
