#include "foo.h"

int main()
{
	setlocale(LC_ALL, "rus");
	char buf[20] = "Какие то данные";
	char buf3[20] = "Пони";
	char buf4[20] = "СЛон"; 
	char buf5[20] = "Как";
	char buf6[20] = "данные";
	char *buf2;
	struct trie* trie;
	trie = trie_create();
	trie = trie_insert(trie, buf, buf);
	trie = trie_insert(trie, buf3, buf3);
	trie = trie_insert(trie, buf4, buf4);
	trie = trie_insert(trie, buf5, buf5);
	buf2 = trie_lookup(trie, buf5);
	cout << buf2 << endl;
	trie = trie_delete(trie, buf4);
	buf2 = trie_lookup(trie, buf4);
	if (buf2 == NULL)
	{
		cout << "Данного узла нет в дереве" << endl;
	}
	else
	{
		cout << buf2 << endl;
	}
}