/*
Описание задачи: Граф называется полугамильтоновым, если существует
простая цепь, проходящая через все вершины графа. Дан
орграф. Проверить, является ли он полугамильтоновым.

Разработчик: Бровкович Никита
2 курс ПИ в дизайне
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
	status_value status; // статус
	int			 a; // первая точка
	int			 b; // вторая точка
};

// Data
const int SIZE		= 24;
int currentNode		= 0;
int countNodes		= 0; // количество вершин
Graph				  graphData[SIZE];


// Prototypes

	// Graph
	void create(); // создание графа
	void insert(int a, int b); // добавление вершины
	void print(); // вывод графа на экран
	void changeStatus(int i, status_value status); // изменение статуса дуги
	void clearStatus(); // очищение статуса всех вершин

	// Graph walking
	void read(); // обход по графу
	int view(int g); // просмотр вершины

	int countArc(); // количество текущих пройденных дуг
	int countPending(); // количество дуг помеченых
	int countViewedNodes(); // количество пройденных вершин


	// File
	string getFileName();
	bool getFile();
	void transform(string buffer);

	int charToInt(char s);


int main ()
{
	setlocale(LC_ALL, "Russian");

	if(getFile()) {
		cout << "Введенный граф:" << endl;
		print();

		read();
	}
	/*
	Graph* root=NULL;
	create();

	cout << "Введенный граф:" << endl;
	//print();

	walk();
	//print();

	clearStatus();
	*/

	system("pause");
	return 0;
}

// название файла
string getFileName() {
	return "graph.txt";
};

// создание графа
void create() {
	bool isCanNext = true;

	while(isCanNext)
	{
		cout<<"Введите точку A" << endl;
		int buffer = 0, position = 0, result = 0, a = 0, b = 0;

		do {
			cin >> buffer;
			position++;
			if(position == 1) {
				a = buffer;
				cout<<"Введите точку B" << endl;
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

// вставка вершины
void insert(int a, int b) {
	graphData[currentNode].status = CREATED;
	graphData[currentNode].a = a;
	graphData[currentNode].b = b;
	currentNode++;
}

// вывод на экран
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

// обход по графу
void read() {
	int g = view(0);
	if(g == -1) {
		cout << "Граф не полугамильнов" << endl;
	} else {
		cout << "Граф полугамильнов" << endl;
	}

	return;
}

// обход по графу
int view(int i) {
	int a = 0, b = 0,
		k = -1; // вершина найденная, куда перейдем
	status_value status;

	a = graphData[i].a;
	b = graphData[i].b;
	status = graphData[i].status;


	if(status != PENDING) {
		// не помечена

		int a2, b2;
		status_value status2;

		for(int j = 0; j < SIZE; j++) {
			a2 = graphData[j].a;
			b2 = graphData[j].b;
			status2 = graphData[j].status;
			if(a2 == 0) break;

			if(j != i && status2 != PENDING) {
				// не текущая вершина и не помечена
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
			// не найдено вершин для перехода
			if(countArc() - 1 == countPending()) {
				changeStatus(i, PENDING);
				if(countViewedNodes() == countNodes) {
				// граф полугамильнов
					return 1;
				}
			}

			// граф не полугамильнтонов
			return -1;
		} else {
			cout << "coutArc :: " << countArc() << endl;
			cout << "countPending :: " << countPending() << endl;

			if(countArc() - 1 == countPending()) {
				// это последняя вершина
				// граф полугамильнов
				changeStatus(i, PENDING);
			cout << "countViewedNodes :: " << countViewedNodes() << endl;
			cout << "countNodes :: " << countNodes << endl;
				if(countViewedNodes() == countNodes) {
					return 1;
				}
				return -1;
			}
		}
		// проход дальше по цепочке
		changeStatus(i, PENDING);
		return view(k);
	}
	return -1;
}

// количество дуг
int countArc() {
	int k = 0, a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		k++;
	}
	return k;
}
// количество в обработке дуг
int countPending() {
	int k = 0, a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		if(graphData[i].status == PENDING) k++;
	}
	return k;
}
// количество просмотренных вершин
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

// изменение статуса
void changeStatus(int j, status_value status1) {
	int a;

	for(int i = 0; i < SIZE; i++) {
		a = graphData[i].a;
		if(a == 0) break;

		if(i == j) graphData[i].status = status1;
	}
	return;
}

// очистить статусы всех вершин
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


// получение файла
bool getFile() {
	ifstream file(getFileName());
 
	 if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			// перевод в граф
			transform(line.c_str());
		}
		file.close();
		 return true;
	}
		 return false;
}

// трансформер
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

// Перевод
int charToInt(char s) {
	if(s) {
		return (s - '0') % 48;
	}
	return 0;
}