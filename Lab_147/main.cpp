/*
Описание задачи: 
Дано целое неотрицательное n. 
Построить бинарное дерево глубины n, корень которого имеет значение 0, а каждая
вершина  значение, совпадающее с ее уровнем.
*/


#include <iostream>
#include <iomanip>
#include <locale.h>
using namespace std;

struct tree
{
  int info;
  tree* left, *right;
};

// Prototypes
tree* MakeTree(int level, int maxlevel);
void PrintTree(tree * &root, const int level=0);

void main ()
{
	setlocale(LC_ALL,"Russian");

	int n = -1; // Начальное значение глубины
	cout << "Введите глубину n" << endl;
	while(n < 0) {
		cin >> n;
	}
	tree* root= MakeTree(0, n);

	cout<<"Введенное дерево:"<<endl;
	PrintTree(root);

	system("pause");
	return;
}


// Рекурсивная функция создания дерева глубины MAXLEVEL
tree* MakeTree(int level, int maxlevel)
{
	if(level > -1 && maxlevel > -1) {

		tree *p = new tree;
		p->info = level;
		if(level <= maxlevel) {
			p->left = MakeTree(level + 1, maxlevel);
			p->right = MakeTree(level + 1, maxlevel);
			return p;
		}
	}
	return NULL;

}

// Вывод дерева
void PrintTree(tree * &root, const int level)
{
  if (root)
  {
    PrintTree(root->left,level+1);
    cout<<setw(4*level)<< "" << root->info<<endl;
    PrintTree(root->right,level+1);
  }
  return;
}