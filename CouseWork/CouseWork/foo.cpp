#include "foo.h"

struct node* newNode(int key)//�������� ������ ����
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

struct node* rightRotate(struct node* x)//������ �������
{
    struct node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct node* leftRotate(struct node* x)//����� �������
{
    struct node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

//��� ������� �������� ���� � ������, ���� ���� ������������ � ������.
//���� ���� �����������, �� ��������� ��������� ��������� ������� � ������
struct node* splay(struct node* root, int key)
{ 
    if (root == NULL || root->key == key)//������ ����� NULL ��� ���� � �����
    {
        return root;//���������� ������
    }
    if (root->key > key)//���� ���� � ����� ���������
    {
        if (root->left == NULL)//���� ������ ��������� ���
        {
            return root;//���������� ������
        }
        if (root->left->key > key)//������� Zig-Zig (Left Left) 
        {
            root->left->left = splay(root->left->left, key);//���������� �������� �������� splay
            root = rightRotate(root);//������ ������ �������
        }
        else if (root->left->key < key) // Zig-Zag (Left Right) 
        {
            root->left->right = splay(root->left->right, key);//���������� �������� �������� splay
            if (root->left->right != NULL)//���� ��������� �� ����� ����
            {
                root->left = leftRotate(root->left);//������ ����� �������
            }
        }
        //���� ����� ��������� ����� NULL �� ������ ������ ������� 
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else //���� ���� ����� � ������ ���������
    {
        if (root->right == NULL)//���� ������ ��������� ����� ����
        {
            return root;//�� ���������� ������
        } 
        if (root->right->key > key)// Zag-Zig (Right Left)
        {
            // ��������� ���� ��� ������ ������-����� 
            root->right->left = splay(root->right->left, key);//���������� �������� �������� splay

            if (root->right->left != NULL)//���� ��������� �� ����� ����
            {
                root->right = rightRotate(root->right);//�� ������ ������ �������
            }
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            root->right->right = splay(root->right->right, key);//���������� �������� �������� splay
            root = leftRotate(root);//������ ����� �������
        }
        //���� ������ ��������� ����� NULL �� ������ ����� �������
        return (root->right == NULL) ? root : leftRotate(root);
    }
}
 
struct node* delete_key(struct node* root, int key)//������� ��� �������� ���� �� ������
{
    struct node* temp;//������� ��������� ����������
    if (!root)//���� ����� ���, ��
    {
        return NULL;//���������� NULL
    }
    root = splay(root, key);//��������� ���� ������

    if (key != root->key)//���� ���� �� ������
    {
        return root;//���������� ������
    }
    if (!root->left)//���� ����� ��������� ����� NULL
    {
        temp = root;//temp = ������
        root = root->right;//� ������ ����������� ������ ����� ������
    }   
    else // �����, ���� ����� ������� ����������
    {
        temp = root;//temp = ������
        root = splay(root->left, key);//� ��������� ���� ������
        root->right = temp->right;//���������� �� ������� ����
    }
    free(temp);//����������� ��������� ����������
    return root;//���������� ������ ������ ������
}
  
void preOrder(struct node* root)//������� ��� ������ � ������ ������
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// ������� ��� ������� ������ �����
struct node* insert(struct node* root, int k)
{
    if (root == NULL)//���� �������� ������ ������, ��
    {
        return newNode(k);//������� �������� ��������
    }
    root = splay(root, k);//�������� ��������� �������� ���� � �����

    if (root->key == k) // ���� ���� ����, �� 
    {
        return root;//�� ���������� ������
    } 
    struct node* newnode = newNode(k);//���� ��� �� ����� �� �������, ������ �������� ������ 
    //��� ����� ����
    if (root->key > k)//���� ���� ������ ������ �����, �� ������ root
    {                 //������ ��������
        newnode->right = root;//������� ��������� ����������� ������
        newnode->left = root->left;//������ ��������� ����������� ��������� ������ ������
        root->left = NULL;//����� ��������� ������ ��������
    }
    // of newnode � ���������� ������ �������� ������� root � newnode 
    else//���� ���� root ������, �������� root ����� �������� 
    {
        newnode->left = root;//� ����� ���� ��������� ������
        newnode->right = root->right;//� ����� ���� ��������� ������ ��������� � ������
        root->right = NULL;//������ ��������� ������ ��������
    }
    return newnode; // newnode ���������� ����� ������ 
}

struct node* min_root(node* root)//����� ������������ ���������
{
    if (root == NULL)//���� �������� �������
    {
        return NULL;//���������� NULL
    }
    struct node* temp = root;//������� ��������� �����
    while (root->left != NULL)//���� ������ ����� �� ����� ����
    {
        root = root->left;//���� ������
    }
    root = splay(temp, root->key);//��� ������������ �������� ��������� splay
    return root;//� ���������� ������
}

struct node* max_root(node* root)//����� ������������� ���������
{
    if (root == NULL)//���� �������� �������
    {
        return NULL;//���������� NULL
    }
    struct node* temp = root;//������� ��������� �����
    while (root->right != NULL)//���� ������ ������ �� ����� ����
    {
        root = root->right;//���� ������
    }
    root = splay(temp, root->key);//��� ������������� �������� ��������� splay
    return root;//� ���������� ������
}

struct node* search_root(node* root, int key)//����� ���������
{
    if (root == NULL)//���� ���� ����
    {
        return NULL;//���������� NULL
    }
    struct node* temp = root;//������� ��������� ����������
    while (root != NULL)//���� ���� �� ����� ����� ����
    {
        if (key == root->key)//���� ���� ����� ����� � ���������
        {
            root = splay(temp, root->key);//�� ��� ����� �������� ��������� �������� splay
            return root;//� ���������� ����
        }
        else if (key < root->key)//���� ���� ������ ����� ����
        {
            root = root->left;//�� ���� �����
        }
        else if (key > root->key)//���� ���� ������ ����� ����
        {
            root = root->right;//�� ���� ������
        }
        else//����� ���������� NULL
        {
            return NULL;
        }
    }
    return root;
}