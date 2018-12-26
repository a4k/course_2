/*
 Реализовать основные операции с бинарным деревом поиска (БДП):
 1. Формирование деревыа вставкой новых вершин
 2. Вывод дерева на консольный экран
 3. Исключение вершин из дерева
 
 * Описание задачи 14.25: 
 Во входном текстовом файле задано синтаксически правильное 
 выражение; синтаксис выражения следующий:
	<выражение> ::= <цифра>|(<цифра><знак><выражение>)
	<знак> ::= +|-|*
	<цифра> ::= 0|1|2|3|4|5|6|7|8|9

* Задачи
	1. Построить по заданному выражению бинарное дерево выра-
	жения
	2. Вывести его на экран в виде дерева
	3. Найти значение выражения.

	
//  Можно вводить ар. выражения с операциями +-*,
//  использовать скобки.
//  Выход - ввод пустой строки

	Автор: Бровкович Никита
	2 курс ПИ в дизайне
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
//****************************************************************
// Глобальные определения и объявления
//****************************************************************
int no_of_errors = 0;           // счетчик ошибок

enum token_value                // внутреннее представление лексем
{ 
	NAME,
	NUMBER,
	END,
	PLUS='+',
	MINUS='-',
	MUL='*',
	LPK='(',
	RPK=')'
};

token_value curr_tok;   	// текущая лексема

double number_value;    	// значение текущей числовой лексемы


/////////////////////////////////////////////////////////////////////
//  Обработчик ошибок
//  Функция error выдает на экран сообщение об ошибке и
//  увеличивает счетчик ошибок
/////////////////////////////////////////////////////////////////////
void error(const char* s)
{
	cout << "Возникла ошибка: " << s << "\n";
	no_of_errors++;  
	//ExitProcess(0);
	return;
}

//****************************************************************
// Динамические структуры и их построение: двоичные деревья
//****************************************************************
struct node
{
	token_value type;
	double value;
	node *left;  // Левое поддерево
	node *right; // Правое поддерево
};

node* tnode;

/////////////////////////////////////////////////////////////////////
//   Перегруженная функция new_node создает новую вершину
//   двоичного дерева в зависимости от типа узла: число или имя.
/////////////////////////////////////////////////////////////////////
node *new_node(const token_value type)
{
	node * p = new node;
	p->type = type;
	p->left = p->right = NULL;
	return p;
}

//   Создание вершины дерева - числа
node *new_node(const token_value type, const double value)
{
	node * p = new_node(type);
	p->value = value;
	return p;
}

//Функция выводит двоичное дерево с корнем root на консольный экран
void print(node* p, int level)
{
	if (p) //Значит, что дерево не пустое
	{
		print(p -> left, level + 1);
		switch(p->type) {
		case NUMBER:
			cout << setw(level * 4) << p -> value << endl;
			break;
		case PLUS:
			cout << setw(level * 4) << "+" << endl;
			break;
		case MINUS:
			cout << setw(level * 4) << "-" << endl;
			break;
		case MUL:
			cout << setw(level * 4) << "*" << endl;
			break;
		case LPK:
			cout << setw(level * 4) << "(" << endl;
			break;
		case RPK:
			cout << setw(level * 4) << ")" << endl;
			break;
		default:
			break;
		}
		print(p -> right, level + 1);
	}
}



//****************************************************************
//  Сканер (лексический анализатор).
//  Функция производит ввод из входного потока и возвращает
//  очередную лексему во внутреннем представлении.
//****************************************************************
token_value get_token()
{

	char ch;
	do // игнорирует пропуски, за исключением \n
	{ 
		if (!cin.get(ch)) {
			return curr_tok = END;
		}
	} while (ch!='\n' && isspace(ch));
	
	switch (ch){

	case'\n':
		return curr_tok = END;

	case'*':
	case'+':
	case'-':
	case'(':
	case')':
		return curr_tok = token_value(ch);

		// Выделение числа
	case'0':    case'1':    case'2':    case'3':    case'4':
	case'5':    case'6':    case'7':    case'8':    case'9':
		//cin.putback(ch);
		number_value = ch - '0';
		return curr_tok = NUMBER;

		// Выделение имени или ошибка
	default:
		error("Плохая лексема");
		return curr_tok = END;
	}
}

//****************************************************************
//  Синтаксический анализатор
//  Функции expr(), prim(), term() производят синтанализ
//  соответствующих синтаксический конструкций и формируют
//  двоичные деревья выражений
//****************************************************************

node *expr (); // предварительное объявление

// Разбор prim. Функция возвращает указатель на дерево, построенное
// из разобранного prim
node *prim ()
{
	node *p;
	switch (curr_tok)
	{
	case NUMBER :  		// Число
		get_token();
		return new_node(NUMBER, number_value);

	case PLUS: case MINUS:     // Операция унарный плюс или минус
		p = new_node(curr_tok);
		get_token();
		p->left = new_node(NUMBER, 0.0);
		p->right = prim();
		return p;

	case LPK:                 	// Выражение в скобках
		get_token();
		p = expr();
		if (curr_tok != RPK) {
			error("Ожидается )");
			return NULL;
		}
		get_token();
		return p;

	default:
		{
			return NULL;
		}
	}
}

// Разбор term. Функция возвращает указатель на дерево, построенное
// из разобранного term
node *term ()
{
	node *p;
	node *left = prim();
	for (;;) {
		switch (curr_tok)
		{
			case MUL:
				p = new_node(curr_tok);
				get_token();
				p->left = left;
				p->right = prim();
				left = p;
				break;

			default:
				return left;
		}
	}
}

// Разбор expr. Функция возвращает указатель на дерево, построенное
// из разобранного expr
node *expr()
{
	node *p;
	node *left = term();
	for (;;) {
		switch (curr_tok)
		{
			case PLUS:
			case MINUS:
				p = new_node(curr_tok);
				p->left = left;
				get_token();
				p->right = term();
				left = p;
				tnode = p;
				break;

			default:
				tnode = left;
				return left;
		}
	}
}

/////////////////////////////////////////////////////////////////////
// Вычислитель
// На входе - дерево p, значение которого нужно вычислить
// На выходе - вычисленное вещественное значение
/////////////////////////////////////////////////////////////////////
double eval(node* p)
{
	if(p) {
		switch (p->type)
		{
		case NUMBER:
			return p->value;

		case PLUS:
			return eval(p->left) + eval(p->right);

		case MINUS:
			return eval(p->left) - eval(p->right);

		case MUL:
			return eval(p->left) * eval(p->right);

		}
	}
	return 1;
}

/////////////////////////////////////////////////////////////////////
// Драйвер
// Функция осуществляет ввод в режиме "командной строки",
// обращается к синтаксическому анализатору для разбора выражения
// и построения двоичного дерева выражения, и к вычислителю для
// вычисления значения постороенного двоичного дерева
/////////////////////////////////////////////////////////////////////
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите выражение:" << endl;
	while (cin)                      // Пока входной поток не пуст
	{ 
		cout << "calc>";
		get_token();                  // Берем первую лексему

			if (curr_tok == END) {
				no_of_errors = 0;
				//break;    // Если не конец
			} else {
				int n = eval(expr());


				if(no_of_errors > 0 || curr_tok != END) {
					error ("Лишние символы");
					break;
				} else {
					if(no_of_errors < 1) {
						cout << n << "\n";  // Строим дерево, вычисляем его и выводим
						cout << "Полученное дерево:" << endl;
						print(tnode, 0);
						delete tnode;
						node* tnode;
					}
				}

			}
		
	}

	system("pause");
	

	return no_of_errors;
}
