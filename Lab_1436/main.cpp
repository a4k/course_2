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
#include <sstream>
#include <iomanip>
using namespace std;



const int n = 6;
int i, j;
bool *visited = new bool[n];
string WAY = "";

//������� ��������� �����
int graph[n][n] =
{
	{0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0},
	{0, 1, 0, 0, 1, 1},
	{0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 1},
	{0, 0, 0, 0, 0, 0}
};

template <typename T>
string NumberToString(T pNumber)
{
 ostringstream oOStrStream;
 oOStrStream << pNumber;
 return oOStrStream.str();
}

int countView() {
	int count = 0;
	for(int i = 0; i < n; i++) {
		if(visited[i]) {
			count++;
		}
	}
	return count;
}

//����� � �������
bool viewGraph(int st)
{


	int r, currentWayPoint = st + 1;
	string cWay = NumberToString(currentWayPoint);

	cout << " " << st+1 << " -> ";
	WAY = WAY + " " + cWay;

	visited[st] = true;
	bool isFound = false;

	
	if(n == countView()) {
		return true;
	}

	for (r = 0; r <= n; r++) {
		if ( (graph[st][r] != 0) && (!visited[r]) ) {
			cout << r+1 << " -> ";
			isFound = viewGraph(r);
			if(!isFound) {
				visited[r] = false;
			} else {
				return true;
			}
		}
	}

	cout << " end view " << st+1 << endl;

	if(!isFound) {
		return false;
	} else {
		if(n == countView()) {
			return true;
		} else {
			return false;
		}
	}
}

void printArray() {
	for (i=0; i<n; i++)
	{
		visited[i] = false;

		for (j=0; j<n; j++)
			cout << " " << graph[i][j];

		cout<<endl;
	}

	return;
}

//������� �������
void main()
{
	setlocale(LC_ALL, "Rus");

	int start;

	cout<<"������� ��������� �����: "<<endl;

	printArray();

	cout << endl;

	cout << "��������� ������� >> ";
	cin >> start;

	//������ ���������� ������
	bool *visited = new bool[n];

	cout << "������� ������: ";

	bool isFound = viewGraph(start-1);

	if(!isFound) {
		cout << "���� �� ���������������" << endl;
	} else {
		cout << "���� ���������������" << endl;
	}

	cout << "����:" << endl;
	cout << WAY << endl;
	delete []visited;

	system("pause");
}


