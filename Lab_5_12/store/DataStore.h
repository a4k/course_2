// declaration
// ”правление данными

#pragma once
#include <iostream>
using namespace std;


template <class T = int, int SIZE = 32>
class DataStore {

  private:
    T db[SIZE];
	int lastId;
    T *dbPtr; // указатель на стек

  public:

	DataStore() {
		dbPtr = new T[SIZE];
		lastId = -1;
	}

	~DataStore() {
		delete [] dbPtr;

	}

	int test() {
		return 125;
	}

	int Create(T value) {
		if (lastId == SIZE - 1)
			return false;
 
		lastId++;
		dbPtr[lastId] = value;
		
		return lastId;
	}

	int Update(int id, T value) {
		if(id > -1) {
			dbPtr[id] = value;
			return id;
		}
		return 0;
	}

	T Get(int id) {
		return dbPtr[id];
	}

	T GetLast() {
		return dbPtr[lastId];
	}

	int Remove(int id) {
		if(id > -1) {
			dbPtr[id] = 0;
			return 1;
		}
		
		return 0;
	}


};