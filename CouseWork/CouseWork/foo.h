#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>

struct node //структура хранения данных
{
    int key;//ключ
    struct node* left;//указатель налево
    struct node* right;//указатель направо
};

struct node* newNode(int key);
struct node* rightRotate(struct node* x);
struct node* leftRotate(struct node* x);
struct node* splay(struct node* root, int key);
struct node* delete_key(struct node* root, int key);
struct node* insert(struct node* root, int k);
struct node* min_root(struct node* root);
struct node* max_root(struct node* root);
struct node* search_root(node* root, int key);
void preOrder(struct node* root);