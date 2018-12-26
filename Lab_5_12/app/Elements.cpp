// definition 

#include "Elements.h"
using namespace std;



Elements::Elements() 
{
	count = 0;

	lElement = &eElement;
	lElement->id = -1;
	lElement->coef = 1;
	
	DataStore<int, 32> elements;
	return;
}
Elements::~Elements() {
	delete lElement;
}



void Elements::set(int id) 
{
	Struct::modelElement newElement = elements.Get(id);
	lElement = &newElement;
	return;
}

void Elements::setPow(int pow) 
{
	lElement->pow = pow;
	return;
}
void Elements::setId(int id) 
{
	lElement->id = id;
	return;
}
void Elements::setCoef(int coef) 
{
	lElement->coef = coef;
	return;
}


Struct::modelElement Elements::get(int id) 
{
	return elements.Get(id);
}

int Elements::getId() 
{
	return lElement->id;
}

int Elements::getPow() 
{
	return lElement->pow;
}

int Elements::getCoef() 
{
	return lElement->coef;
}


void Elements::create() 
{
	int id = getId();
	id++;
	setId(id);

	elements.Create(*lElement);
	count++;
	return;
}
void Elements::update() 
{
	elements.Update(getId(), *lElement);
	return;
}


void Elements::print() {
	Struct::modelElement f[32];
	for(int i = 0; i < count; i++) {
		f[i] = elements.Get(i);

		int coef, pow, id, pid2;

		coef = f[i].coef;
		pow = f[i].pow;


		if(coef == 0) break;
		

			if(pow == 0) {
				cout << coef;
			} else {

				if (coef < 0) { 
					if(coef != -1) {
						cout << coef << "X^" << pow; 
					} else {
						cout << "-" << "X^" << pow;
					}

				} else if(coef > 0) {
					if(coef != 1) {
						cout << "+" << coef << "X^" << pow; 
					} else {
						cout << "+" << "X^" << pow;
					}
				}

			}





	}

}


int Elements::getCount() {
	return Element::count;
};