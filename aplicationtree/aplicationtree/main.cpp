#include "foo.h"

int main()
{
	setlocale(LC_ALL, "ru");
	clock_t start;
	clock_t end;
	double seconds;
	char buf[20] = "Какие то данные";
	int count = 0, choice, elem;
	struct avltree* tree, *node;
	tree = avltree_create(20, buf);

	do
	{
		cout << "\n\t\t\t\tАВЛ Дерево" << endl;
		cout << "\t\t\t::::::::::::::::::::::::::::\n" << endl;
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::1 Заполнить АВЛ дерево::::::::::::::::::::::" << endl;
		cout << "\t\t::::2 Найти минимальный элемент:::::::::::::::::" << endl;
		cout << "\t\t::::3 Найти максимальный элемент::::::::::::::::" << endl;
		cout << "\t\t::::4 Поиск по значению:::::::::::::::::::::::::" << endl;
		cout << "\t\t::::5 Удалить элемент:::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::6 Обход DFC:::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::7 Посмотреть количество уровней:::::::::::::" << endl;
		cout << "\t\t::::8 Очистка дерева::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::0 Выход:::::::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

		cout << "\nВыберите нужное действие и нажмите Enter: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "\n\t\tЗаполнение АВЛ дерева" << endl;
			cout << "\t\t:::::::::::::\n" << endl;
			cout << "\nВведите количество эллементов в АВЛ дереве: ";
			cin >> elem;
			tree = avltree_create(20, buf);
			start = clock();
			for (size_t i = 0; i < elem; i++)
			{
				tree = avltree_add(tree, i, buf, count);
			}
			end = clock();
			seconds = (double)(end - start) / CLOCKS_PER_SEC;
			printf("The time: %f seconds\n", seconds);
			break;
		case 2:
			node = NULL;
			node = avltree_min(tree);
			if (node != NULL && node->deleted == 0)
			{
				cout << "\nМинимальный элемент в дереве: " << node->key << endl;
			}
			else
			{
				do 
				{
					node = find_parent(tree, node->key);

				} while (node->deleted == 1);
				cout << "\nМинимальный элемент в дереве: " << node->key << endl;
			}
			break;
		case 3:
			node = NULL;
			node = avltree_max(tree);
			if (node != NULL && node->deleted == 0)
			{
				cout << "\nМаксимальный элемент в дереве: " << node->key << endl;
			}
			else
			{
				do
				{
					node = find_parent(tree, node->key);

				} while (node->deleted == 1);
				cout << "\nМаксимальный элемент в дереве: " << node->key << endl;
			}
			break;
		case 4:
			cout << "\nВведите искомый элемент: ";
			node = NULL;
			cin >> elem;
			start = clock();
			node = avltree_lookup(tree, elem);
			end = clock();
			seconds = (double)(end - start) / CLOCKS_PER_SEC;
			printf("The time: %f seconds\n", seconds);
			if (node != NULL)
			{
				cout << node->value << endl;
			}
			else
			{
				cout << "Данного узла нет в дереве" << endl;
			}
			break;
		case 5:
			cout << "\nКакой узел удалить? : ";
			cin >> elem;
			avltree_lazy_deleted(tree, elem, count);
			if (count >= 5)
			{
				int arr[50000];
				int i = 0;
				struct avltree* newtree = new avltree;
				newtree = new_avl_tree(tree, newtree, arr, i, count);
				tree = newtree;
				count = 0;
			}
			break;
		case 6:
			cout << "\n\t\tОбход DFC" << endl;
			dfsprint(tree);
			cout << endl;
			break;
		case 7:
			cout << "\nВысота АВЛ дерева: " << tree->height << endl;
			break;
		case 8:
			cout << "\nОчистка дерева" << endl;
			avltree_free(tree);
			break;
		case 0:
			cout << "\n\tБлагодарим вас за использование програмы\n" << endl;
			avltree_free(tree);
			break;
		default:
			cout << "Некорректный ввод\n" << endl;
			break;
		}
		system("pause");
		system("cls");
	} while (choice != 0);
	return 0;
}