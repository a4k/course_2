/*
 ����������� �������� �������� � �������� ������� ������ (���):
 1. ������������ ������� �������� ����� ������
 2. ����� ������ �� ���������� �����
 3. ���������� ������ �� ������
 
 * �������� ������ 14.25: 
 �� ������� ��������� ����� ������ ������������� ���������� 
 ���������; ��������� ��������� ���������:
	<���������> ::= <�����>|(<�����><����><���������>)
	<����> ::= +|-|*
	<�����> ::= 0|1|2|3|4|5|6|7|8|9

* ������
	1. ��������� �� ��������� ��������� �������� ������ ����-
	�����
	2. ������� ��� �� ����� � ���� ������
	3. ����� �������� ���������.

	
//  ����� ������� ��. ��������� � ���������� +-*,
//  ������������ ������.
//  ����� - ���� ������ ������

	�����: ��������� ������
	2 ���� �� � �������
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
//****************************************************************
// ���������� ����������� � ����������
//****************************************************************
int no_of_errors = 0;           // ������� ������

enum token_value                // ���������� ������������� ������
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

token_value curr_tok;   	// ������� �������

double number_value;    	// �������� ������� �������� �������


/////////////////////////////////////////////////////////////////////
//  ���������� ������
//  ������� error ������ �� ����� ��������� �� ������ �
//  ����������� ������� ������
/////////////////////////////////////////////////////////////////////
void error(const char* s)
{
	cout << "�������� ������: " << s << "\n";
	no_of_errors++;  
	//ExitProcess(0);
	return;
}

//****************************************************************
// ������������ ��������� � �� ����������: �������� �������
//****************************************************************
struct node
{
	token_value type;
	double value;
	node *left;  // ����� ���������
	node *right; // ������ ���������
};

node* tnode;

/////////////////////////////////////////////////////////////////////
//   ������������� ������� new_node ������� ����� �������
//   ��������� ������ � ����������� �� ���� ����: ����� ��� ���.
/////////////////////////////////////////////////////////////////////
node *new_node(const token_value type)
{
	node * p = new node;
	p->type = type;
	p->left = p->right = NULL;
	return p;
}

//   �������� ������� ������ - �����
node *new_node(const token_value type, const double value)
{
	node * p = new_node(type);
	p->value = value;
	return p;
}

//������� ������� �������� ������ � ������ root �� ���������� �����
void print(node* p, int level)
{
	if (p) //������, ��� ������ �� ������
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
//  ������ (����������� ����������).
//  ������� ���������� ���� �� �������� ������ � ����������
//  ��������� ������� �� ���������� �������������.
//****************************************************************
token_value get_token()
{

	char ch;
	do // ���������� ��������, �� ����������� \n
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

		// ��������� �����
	case'0':    case'1':    case'2':    case'3':    case'4':
	case'5':    case'6':    case'7':    case'8':    case'9':
		//cin.putback(ch);
		number_value = ch - '0';
		return curr_tok = NUMBER;

		// ��������� ����� ��� ������
	default:
		error("������ �������");
		return curr_tok = END;
	}
}

//****************************************************************
//  �������������� ����������
//  ������� expr(), prim(), term() ���������� ����������
//  ��������������� �������������� ����������� � ���������
//  �������� ������� ���������
//****************************************************************

node *expr (); // ��������������� ����������

// ������ prim. ������� ���������� ��������� �� ������, �����������
// �� ������������ prim
node *prim ()
{
	node *p;
	switch (curr_tok)
	{
	case NUMBER :  		// �����
		get_token();
		return new_node(NUMBER, number_value);

	case PLUS: case MINUS:     // �������� ������� ���� ��� �����
		p = new_node(curr_tok);
		get_token();
		p->left = new_node(NUMBER, 0.0);
		p->right = prim();
		return p;

	case LPK:                 	// ��������� � �������
		get_token();
		p = expr();
		if (curr_tok != RPK) {
			error("��������� )");
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

// ������ term. ������� ���������� ��������� �� ������, �����������
// �� ������������ term
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

// ������ expr. ������� ���������� ��������� �� ������, �����������
// �� ������������ expr
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
// �����������
// �� ����� - ������ p, �������� �������� ����� ���������
// �� ������ - ����������� ������������ ��������
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
// �������
// ������� ������������ ���� � ������ "��������� ������",
// ���������� � ��������������� ����������� ��� ������� ���������
// � ���������� ��������� ������ ���������, � � ����������� ���
// ���������� �������� ������������� ��������� ������
/////////////////////////////////////////////////////////////////////
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������� ���������:" << endl;
	while (cin)                      // ���� ������� ����� �� ����
	{ 
		cout << "calc>";
		get_token();                  // ����� ������ �������

			if (curr_tok == END) {
				no_of_errors = 0;
				//break;    // ���� �� �����
			} else {
				int n = eval(expr());


				if(no_of_errors > 0 || curr_tok != END) {
					error ("������ �������");
					break;
				} else {
					if(no_of_errors < 1) {
						cout << n << "\n";  // ������ ������, ��������� ��� � �������
						cout << "���������� ������:" << endl;
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
