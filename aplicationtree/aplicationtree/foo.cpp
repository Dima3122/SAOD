#include "foo.h"

void avltree_free(struct avltree* tree)
{
	if (tree == NULL)
	{ 
		return;
	}
	avltree_free(tree->left);
	avltree_free(tree->right);
	free(tree);
}

struct avltree* avltree_lookup(struct avltree* tree, int key)
{
	while (tree != NULL)
	{
		if (key == tree->key)
		{
			if (tree->deleted == 0)
			{
				return tree;
			}
			else
			{
				return NULL;
			}
		}
		else if (key < tree->key)
		{
			tree = tree->left;
		}
		else if (key > tree->key)
		{
			tree = tree->right;
		}
		else
		{
			return NULL;
		}
	}
	return tree;
}

struct avltree* search_avltree(struct avltree* tree, int key)
{
	while (tree != NULL)
	{
		if (key == tree->key)
		{
			return tree;
		}
		else if (key < tree->key)
		{
			tree = tree->left;
		}
		else if (key > tree->key)
		{
			tree = tree->right;
		}
		else
		{
			return NULL;
		}
	}
	return tree;
}
struct avltree* avltree_create(int key, char* value)
{
	struct avltree* node;
	node = new avltree;
	if (node != NULL) 
	{
		node->key = key;
		node->value = value;
		node->left = NULL;
		node->right = NULL;
		node->height = 0;
		node->deleted = 0;
	}
	return node;
}

int avltree_height(struct avltree* tree)
{
	if (tree != NULL && tree->deleted == 0)
	{
		return tree->height;
	}
	else
	{
		return -1;
	}
}

int avltree_balance(struct avltree* tree)
{
	return avltree_height(tree->left) - avltree_height(tree->right);
}

struct avltree* avltree_add(struct avltree* tree, int key, char* value, int &count)
{
	if (tree == NULL) 
	{
		return avltree_create(key, value);
	}
	struct avltree* node = search_avltree(tree, key);
	if (node != NULL)
	{
		node->deleted = 0;
		count--;
		return tree;
	}
	else if (key < tree->key) 
	{
		/* �������� � ����� ��������� */
		tree->left = avltree_add(tree->left, key, value, count);
		if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
		{
			/* ��������� ������������������ */
			if (key < tree->left->key)
			{
				/* Left left case */
				tree = avltree_right_rotate(tree);
			}
			else
			{
				/* Left right case */
				tree = avltree_leftright_rotate(tree);
			}
		}
	}
	else if (key > tree->key) 
	{
		/* �������� � ������ ��������� */
		tree->right = avltree_add(tree->right, key, value, count);
		if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
		{
			/* ������ ������������������ */
			if (key > tree->right->key)
			{
				/* Right right case */
				tree = avltree_left_rotate(tree);
			}
			else
			{
				/* Right left case */
				tree = avltree_rightleft_rotate(tree);
			}
		}
	}
	tree->height = imax2(avltree_height(tree->left),avltree_height(tree->right)) + 1;
	tree->deleted = 0;
	return tree;
}

struct avltree* avltree_right_rotate(struct avltree* tree)
{
	struct avltree* left;
	left = tree->left;
	tree->left = left->right;
	left->right = tree;
	tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
	left->height = imax2(avltree_height(left->left), tree->height) + 1;
	return left;
}

struct avltree* avltree_left_rotate(struct avltree* tree)
{
	struct avltree* right;
	right = tree->right;
	tree->right = right->left;
	right->left = tree;
	tree->height = imax2(avltree_height(tree->left), avltree_height(tree->right)) + 1;
	right->height = imax2(avltree_height(right->right), tree->height) + 1;
	return right;
}

struct avltree* avltree_leftright_rotate(struct avltree* tree)
{
	tree->left = avltree_left_rotate(tree->left);
	return avltree_right_rotate(tree);
}

struct avltree* avltree_rightleft_rotate(struct avltree* tree)
{
	tree->right = avltree_right_rotate(tree->right);
	return avltree_left_rotate(tree);
}

int imax2(int first, int second)
{
	if (first >= second)
	{
		return first;
	}
	else
	{
		return second;
	}
}

struct avltree* avltree_min(struct avltree* tree)
{
	if (tree == NULL)
	{
		return NULL;
	}

	while (tree->left != NULL)
	{
		tree = tree->left;
	}
	return tree;
}

struct avltree* avltree_max(struct avltree* tree)
{
	if (tree == NULL)
	{
		return NULL;
	}

	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	return tree;
}

void avltree_lazy_deleted(struct avltree* tree, int key, int &count)
{
	struct avltree* node;
	node = search_avltree(tree, key);
	if (node != NULL)
	{
		if (tree->deleted == 0)
		{
			node->deleted = 1;
			count++;
			cout << "Удаление прошло успешно" << endl;
		}
		else
		{
			cout << "Ошибка удаления" << endl;
		}
	}
	else
	{
		cout << "������ �������" << endl;
	}
	
}

void printarray(int* arr, int j)
{
	for (size_t i = 0; i < j; i++)
	{
		cout << arr[i] << endl;
	}
}

struct avltree* new_avl_tree(struct avltree* tree, struct avltree* newtree, int *arr, int &i, int &count)
{
	getarr(tree, arr, i);
	struct avltree* node = new avltree;
	node = search_avltree(tree, arr[0]);
	newtree = avltree_create(arr[0], node->value);
	for (int j = 1; j < i; j++)
	{
		node = search_avltree(tree, arr[j]);
		newtree = avltree_add(newtree, arr[j], node->value, count);
	}
	return newtree;
}

void getarr(struct avltree* tree, int *arr, int &i)
{
	if (tree == NULL || tree->deleted == 1)
	{
		return;
	}
	arr[i] = tree->key;
	i++;
	getarr(tree->right, arr, i);
	getarr(tree->left, arr, i);
}

void dfsprint(struct avltree* tree)
{
	if (tree == NULL || tree->deleted == 1)
	{
		return;
	}
	cout << tree->value << endl;
	dfsprint(tree->right);
	dfsprint(tree->left);
}

struct avltree* find_parent(struct avltree* tree, int key)
{
	while (tree != NULL)
	{
		if ((tree->right != NULL) && (key == tree->right->key))
		{
			return tree;
		}
		else if ((tree->left != NULL) && (key == tree->left->key))
		{
			return tree;
		}
		if (key < tree->key)
		{
			tree = tree->left;
		}
		else if (key > tree->key)
		{
			tree = tree->right;
		}
		else
		{
			return NULL;
		}
	}
	return tree;
}

void looklvl(struct avltree* tree, int &count)
{
	if (tree == NULL)
	{
		return;
	}
	count++;
	looklvl(tree->right, count);
}