#include "foo.h"

struct node* newNode(int key)//создание нового узла
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

struct node* rightRotate(struct node* x)//правый поворот
{
    struct node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct node* leftRotate(struct node* x)//левый поворот
{
    struct node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

//Эта функция помещает ключ в корень, если ключ присутствует в дереве.
//Если ключ отсутствует, он переносит последний доступный элемент в корень
struct node* splay(struct node* root, int key)
{ 
    if (root == NULL || root->key == key)//корень равен NULL или ключ в корне
    {
        return root;//возвращает корень
    }
    if (root->key > key)//если ключ в левом поддереве
    {
        if (root->left == NULL)//если левого поддерева нет
        {
            return root;//возвращаем корень
        }
        if (root->left->key > key)//поворот Zig-Zig (Left Left) 
        {
            root->left->left = splay(root->left->left, key);//рекурсивно вызываем операцию splay
            root = rightRotate(root);//делаем правый поворот
        }
        else if (root->left->key < key) // Zig-Zag (Left Right) 
        {
            root->left->right = splay(root->left->right, key);//рекурсивно вызываем операцию splay
            if (root->left->right != NULL)//если указатель не равен нулю
            {
                root->left = leftRotate(root->left);//делаем левый поворот
            }
        }
        //если левое поддерево равно NULL то делаем правый поворот 
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else //если ключ лежит в правом поддереве
    {
        if (root->right == NULL)//если правое поддерево равно нулю
        {
            return root;//то возвращаем дерево
        } 
        if (root->right->key > key)// Zag-Zig (Right Left)
        {
            // Принесите ключ как корень справа-слева 
            root->right->left = splay(root->right->left, key);//рекурсивно вызываем операцию splay

            if (root->right->left != NULL)//если указатель не равен нулю
            {
                root->right = rightRotate(root->right);//то делаем правый поворот
            }
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            root->right->right = splay(root->right->right, key);//рекурсивно вызываем операцию splay
            root = leftRotate(root);//делаем левый поворот
        }
        //если правое поддерево равно NULL то делаем левый поворот
        return (root->right == NULL) ? root : leftRotate(root);
    }
}
 
struct node* delete_key(struct node* root, int key)//функция для удаления узла из дерева
{
    struct node* temp;//создаем временную переменную
    if (!root)//если корня нет, то
    {
        return NULL;//возвращаем NULL
    }
    root = splay(root, key);//поднимаем ключ наверх

    if (key != root->key)//если ключ не найден
    {
        return root;//возвращаем дерево
    }
    if (!root->left)//если левый указатель равен NULL
    {
        temp = root;//temp = дерево
        root = root->right;//а дереву присваиваем правую ветку дерева
    }   
    else // Иначе, если левый ребенок существует
    {
        temp = root;//temp = дерево
        root = splay(root->left, key);//и поднимаем ключ наверх
        root->right = temp->right;//спускаемся на уровень ниже
    }
    free(temp);//освобождаем временную переменную
    return root;//возвращаем корень нового дерева
}
  
void preOrder(struct node* root)//функция для обхода и печати дерева
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Функция для вставки нового ключа
struct node* insert(struct node* root, int k)
{
    if (root == NULL)//если передали пустое дерево, то
    {
        return newNode(k);//создаем корневой эллемент
    }
    root = splay(root, k);//Приводим ближайший листовой узел к корню

    if (root->key == k) // Если ключ есть, то 
    {
        return root;//то возвращаем дерево
    } 
    struct node* newnode = newNode(k);//если еще не вышли из функции, значит выделяем память 
    //под новый лист
    if (root->key > k)//если ключ дерева больше ключа, то делаем root
    {                 //правым потомком
        newnode->right = root;//правому указателю присваиваем дерево
        newnode->left = root->left;//левому указателю присваиваем указатель левого дерева
        root->left = NULL;//левый указатель дерева зануляем
    }
    // of newnode и скопируйте правый дочерний элемент root в newnode 
    else//Если ключ root меньше, сделайте root левым потомком 
    {
        newnode->left = root;//В новый узел вставляем дерево
        newnode->right = root->right;//в новый узел вставляем правый указатель в дерево
        root->right = NULL;//правый указатель дерева зануляем
    }
    return newnode; // newnode становится новым корнем 
}

struct node* min_root(node* root)//поиск минимального эллемента
{
    if (root == NULL)//Если передали пустоту
    {
        return NULL;//Возвращаем NULL
    }
    struct node* temp = root;//создаем временную копию
    while (root->left != NULL)//пока корень слева не равен нулю
    {
        root = root->left;//идем налево
    }
    root = splay(temp, root->key);//Для минимального значения выполняем splay
    return root;//И возвращаем дерево
}

struct node* max_root(node* root)//поиск максимального эллемента
{
    if (root == NULL)//если передали пустоту
    {
        return NULL;//возвращаем NULL
    }
    struct node* temp = root;//создаем временную копию
    while (root->right != NULL)//пока корень справа не равен нулю
    {
        root = root->right;//идем вправо
    }
    root = splay(temp, root->key);//Для максимального значения выполняем splay
    return root;//и возвращаем дерево
}

struct node* search_root(node* root, int key)//поиск эллемента
{
    if (root == NULL)//если узел пуст
    {
        return NULL;//возвращаем NULL
    }
    struct node* temp = root;//создаем временную переменную
    while (root != NULL)//пока узел не будет равен нулю
    {
        if (key == root->key)//если ключ равен ключу в структуре
        {
            root = splay(temp, root->key);//мы для этого значения выполняем операцию splay
            return root;//и возвращаем узел
        }
        else if (key < root->key)//если ключ меньше ключа узла
        {
            root = root->left;//то идем влево
        }
        else if (key > root->key)//если ключ больше ключа узла
        {
            root = root->right;//то идем вправо
        }
        else//иначе возвращаем NULL
        {
            return NULL;
        }
    }
    return root;
}