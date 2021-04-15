#pragma once
#include <iostream>
#include <time.h>
using namespace std;
struct avltree {
	int key;
	int deleted;
	char* value;
	int height;
	struct avltree* left;
	struct avltree* right;
};

void avltree_free(struct avltree* tree);
struct avltree* avltree_lookup(struct avltree* tree, int key);
struct avltree* avltree_create(int key, char* value);
int avltree_height(struct avltree* tree);
int avltree_balance(struct avltree* tree);
struct avltree* avltree_add(struct avltree* tree, int key, char* value, int& count);
struct avltree* avltree_right_rotate(struct avltree* tree);
struct avltree* avltree_left_rotate(struct avltree* tree);
struct avltree* avltree_leftright_rotate(struct avltree* tree);
struct avltree* avltree_rightleft_rotate(struct avltree* tree);
int imax2(int first, int second);
struct avltree* avltree_min(struct avltree* tree);
struct avltree* avltree_max(struct avltree* tree);
void avltree_lazy_deleted(struct avltree* tree, int key, int& count);
struct avltree* search_avltree(struct avltree* tree, int key);
void dfsprint(struct avltree* tree);
struct avltree* find_parent(struct avltree* tree, int key);
void getarr(struct avltree* tree, int* arr, int& i);
struct avltree* new_avl_tree(struct avltree* tree, struct avltree* newtree, int* arr, int &i, int& count);
void printarray(int* arr, int j);
void looklvl(struct avltree* tree, int& count);