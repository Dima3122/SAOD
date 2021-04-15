#include "foo.h"

int main()
{
    setlocale(LC_ALL, "ru");
    struct node* root = newNode(0);
    printf("Создаем дерево \n");
    preOrder(root);
    root = insert(root, 1);
    printf("\nДобавили 1 \n");
    preOrder(root);
    root = insert(root, 3);
    printf("\nДобавили 3\n");
    preOrder(root);
    root = insert(root, 2);
    printf("\nДобавили 2\n");
    preOrder(root);
    root = insert(root, 42);
    printf("\nДобавили 42\n");
    preOrder(root);
    root = insert(root, 213);
    printf("\nДобавили 213\n");
    preOrder(root);
    root = insert(root, 215);
    printf("\nДобавили 215\n");
    preOrder(root);
    root = insert(root, 66);
    printf("\nДобавили 66\n");
    preOrder(root);
    root = insert(root, 5);
    printf("\nДобавили 5\n");
    preOrder(root);
    root = delete_key(root, 42);
    printf("\nУдалили 42\n");
    preOrder(root);
    root = max_root(root);
    printf("\nМаксимальный эллемент\n");
    preOrder(root);
    root = search_root(root, 5);
    printf("\nНашли 5 эллемент\n");
    preOrder(root);
    return 0;
}