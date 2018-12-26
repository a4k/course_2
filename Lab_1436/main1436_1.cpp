/*
�������� ������: ���� ���������� �����������������, ���� ����������
������� ����, ���������� ����� ��� ������� �����. ���
������. ���������, �������� �� �� �����������������.

�����������: ��������� ������
2 ���� �� � �������
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


enum status_value
{ 
	CREATED,
	PENDING
};

// Struct
struct Graph
{
	status_value status; // ������
	int			 a; // ������ �����
	int			 b; // ������ �����
};

// Data
const int SIZE		= 24;
int currentNode		= 0;
int countNodes		= 0; // ���������� ������
Graph				  graphData[SIZE];


// Prototypes

	// Graph
	void create(); // �������� �����
	void insert(int a, int b); // ���������� �������
	void print(); // ����� ����� �� �����
	void changeStatus(int i, status_value status); // ��������� ������� ����
	void clearStatus(); // �������� ������� ���� ������

	// Graph walking
	void read(); // ����� �� �����
	int view(int g); // �������� �������

	int countArc(); // ���������� ������� ���������� ���
	int countPending(); // ���������� ��� ���������
	int countViewedNodes(); // ���������� ���������� ������


	// File
	string getFileName();
	bool getFile();
	void transform(string buffer);

	int charToInt(char s);


int main ()
{
	setlocale(LC_ALL, "Russian");

	if(getFile()) {
		cout << "��������� ����:" << endl;
		print();

		read();
	}
	/*
	Graph* root=NULL;
	create();

	cout << "��������� ����:" << endl;
	//print();

	walk();
	//print();

	clearStatus();
	*/

	system("pause");
	return 0;
}

// �������� �����
string getFileName() {
	return "graph.txt";
};

// �������� �����
void create() {
	bool isCanNext = true;

	while(isCanNext)
	{
		cout<<"������� ����� A" << endl;
		int buffer = 0, position = 0, result = 0, a = 0, b = 0;

		do {
			cin >> buffer;
			position++;
			if(position == 1) {
				a = buffer;
				cout<<"������� ����� B" << endl;
			} else {
				b = buffer;
				position = 3;
			}
		} while (buffer != 0 && position != 3);

		if( a == 0 || b == 0 || buffer == 0 ) {
			// end
			isCanNext = false;
		} else {
			// next
			insert(a, b);
			isCanNext = true;
		}
	}
	return;

}

// ������� �������
void insert(int a, int b) {
	graphData[currentNode].status = CREATED;
	graphData[currentNode].a = a;
	graphData[currentNode].b = b;
	currentNode++;
}

// ����� �� �����
void print() {
	int a = 0, b = 0;
	status_value status;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		b = graphData[i].b;
		status = graphData[i].status;
		if(a == 0) break;


		cout << "status :: " << status << " a :: " << a << " b :: " << b << endl;
	}

	return;
}

// ����� �� �����
void read() {
	int g = view(0);
	if(g == -1) {
		cout << "���� �� �������������" << endl;
	} else {
		cout << "���� �������������" << endl;
	}

	return;
}

// ����� �� �����
int view(int i) {
	int a = 0, b = 0,
		k = -1; // ������� ���������, ���� ��������
	status_value status;

	a = graphData[i].a;
	b = graphData[i].b;
	status = graphData[i].status;


	if(status != PENDING) {
		// �� ��������

		int a2, b2;
		status_value status2;

		for(int j = 0; j < SIZE; j++) {
			a2 = graphData[j].a;
			b2 = graphData[j].b;
			status2 = graphData[j].status;
			if(a2 == 0) break;

			if(j != i && status2 != PENDING) {
				// �� ������� ������� � �� ��������
				if(a == a2 || a == b2) {
					k = j;
					break;
				} else if(b == b2 || b == a2) {
					k = j;
					break;
				}

			}
		}
			cout << "k :: " << k << endl;
			cout << "a :: " << a << endl;

		

		if(k == -1) {
			cout << "coutArc :: " << countArc() << endl;
			cout << "countPending :: " << countPending() << endl;
			cout << "countViewedNodes :: " << countViewedNodes() << endl;
			cout << "countNodes :: " << countNodes << endl;
			// �� ������� ������ ��� ��������
			if(countArc() - 1 == countPending()) {
				changeStatus(i, PENDING);
				if(countViewedNodes() == countNodes) {
				// ���� �������������
					return 1;
				}
			}

			// ���� �� ����������������
			return -1;
		} else {
			cout << "coutArc :: " << countArc() << endl;
			cout << "countPending :: " << countPending() << endl;

			if(countArc() - 1 == countPending()) {
				// ��� ��������� �������
				// ���� �������������
				changeStatus(i, PENDING);
			cout << "countViewedNodes :: " << countViewedNodes() << endl;
			cout << "countNodes :: " << countNodes << endl;
				if(countViewedNodes() == countNodes) {
					return 1;
				}
				return -1;
			}
		}
		// ������ ������ �� �������
		changeStatus(i, PENDING);
		return view(k);
	}
	return -1;
}

// ���������� ���
int countArc() {
	int k = 0, a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		k++;
	}
	return k;
}
// ���������� � ��������� ���
int countPending() {
	int k = 0, a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		if(graphData[i].status == PENDING) k++;
	}
	return k;
}
// ���������� ������������� ������
int countViewedNodes() {
	int k = 0, a = 0, b = 0, n = 0;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		b = graphData[i].b;
		if(a == 0) break;

		if(graphData[i].status == PENDING) {
			k = (a > b) ? a : b;
			if(k > n) {
				n = k;
			}
			
		}
	}
	return n;
}

// ��������� �������
void changeStatus(int j, status_value status1) {
	int a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		if(i == j) graphData[i].status = status1;
	}
	return;
}

// �������� ������� ���� ������
void clearStatus() {
	int a = 0;
	status_value status;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		status = graphData[i].status;
		if(a == 0) break;
		graphData[i].status = CREATED;
	}

	return;

}


// ��������� �����
bool getFile() {
	ifstream file(getFileName());
 
	 if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			// ������� � ����
			transform(line.c_str());
		}
		file.close();
		 return true;
	}
		 return false;
}

// �����������
void transform(string buffer) {
	int l = buffer.length();
	if(l == 1) {
		countNodes = charToInt(buffer[0]);
	} else if(l == 3) {

		int a = charToInt(buffer[0]);
		int b = charToInt(buffer[2]);
		insert(a, b);
	}
	return;
}

// �������
int charToInt(char s) {
	if(s) {
		return (s - '0') % 48;
	}
	return 0;
}