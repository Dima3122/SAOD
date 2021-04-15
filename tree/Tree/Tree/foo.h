#pragma once
#include <iostream>
#include <string>
using namespace std;

struct trie {
	char* value; 
	char ch;
	struct trie* sibling; /* Родственный узел */
	struct trie* child; /* Первый ребенок */
};

struct trie* trie_create();
char* trie_lookup(struct trie* root, char* key);
struct trie* trie_insert(struct trie* root, char* key, char* value);
struct trie* trie_delete(struct trie* root, char* key);
struct trie* trie_delete_dfs(struct trie* root, struct trie* parent, char* key, int* found);