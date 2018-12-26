#include <iostream>
#include <iomanip>
#include <locale.h>
#include <string>
#include <algorithm>
#include <set>
//#include "Polynomial.h"
using namespace std;
  
struct Term
{
    int coefficient;
	bool x;
    int exponent;
    Term(int coef, int exp, bool x) : coefficient(coef), exponent(exp), x(x) {}
};
struct TermComparator
{
    bool operator()(const Term& lhs, const Term& rhs) {
        return lhs.exponent < rhs.exponent;
    }
};
struct find_by_exponent {
	int exponent;
	find_by_exponent(int exponent) : exponent(exponent) {}
	
	bool operator()(const Term & lhs) {
        return lhs.exponent == exponent;
    }
};


class Polynomial
{
private:
	set<Term, TermComparator> terms;
	int maxLevel;
public:
	Polynomial() : maxLevel(0) {}
	Polynomial(int l) : maxLevel(l) {}
	~Polynomial() {}

	void init() {
		cout << "Вводите многочлен, чтобы закончить введите коэффициент = 0." << endl;
		int coef = 1;
		int exponent = 0;
		string isX = "N";
		bool x = false;
		bool isHaveMax = false;
		if(this->maxLevel > 0) isHaveMax = true;

		while(coef != 0) {
			
			if(isHaveMax) {
				this->maxLevel--;
				if(this->maxLevel < 1) {
					coef = 0;
					break;
				}
			}
			cout << "Коэффициент: ";
			cin >> coef;
			if(coef == 0) break;
			
			cout << "Есть x? y или n ";
			cin >> isX;

			if(isX == "Y" || isX == "y") {
				x = true;
				cout << "Степень: ";
				cin >> exponent;
			} else {
				x = false;
				exponent = 0;
			}
			
			auto my_term = Term(coef, exponent, x);
			terms.insert(my_term);
			cout << endl;

		}
		return;
	}
	void info() {
		cout << "" << endl;
		auto my_it = terms.begin();
		int i = 0;

		while (my_it != terms.end())
		{
			if(i > 0) {
				if(my_it->coefficient > 0) cout << " +";
				else cout << " ";
			}
			cout << my_it->coefficient;
			if(my_it->x) {
				cout << "x";
				if(my_it->exponent > 1) cout << "^" << my_it->exponent;
			}

			i++;
			++my_it;
		}
		cout << endl;
		return;
	}
	Polynomial operator+(Polynomial p)
	{
		return this->plus(p);
	}
	Polynomial operator*(Polynomial p)
	{
		return this->prod(p);
	}
	// Сумма
	Polynomial plus(Polynomial p) {
		Polynomial result;
		Polynomial copy;
		auto my_it = terms.begin();
		auto p_it = p.terms.begin();
		
		for (; p_it != p.terms.end(); ++p_it) copy.terms.insert(*p_it);
		auto c_it = copy.terms.begin();


		while(my_it != terms.end()) {

			auto resultFind = find_if(copy.terms.begin(), copy.terms.end(), find_by_exponent(my_it->exponent));

			int coef = my_it->coefficient;
			int exponent = my_it->exponent;
			bool isX = my_it->x;
			

			if(resultFind != copy.terms.end()) {
				coef += resultFind->coefficient;
				copy.terms.erase(*resultFind);
			}

			result.terms.insert(Term(coef, exponent, isX));
			++my_it;
		}

		c_it = copy.terms.begin();
		while(c_it != copy.terms.end()) {
			result.terms.insert(Term(c_it->coefficient, c_it->exponent, c_it->x));
			++c_it;
		}
		return result;
	}
	// Произведение
	Polynomial prod(Polynomial p) {
		Polynomial result;
		auto my_it = terms.begin();
		auto p_it = p.terms.begin();


		while(my_it != terms.end()) {

			auto p_it = p.terms.begin();
			while(p_it != p.terms.end()) {
				int coef = my_it->coefficient * p_it->coefficient;
				int exponent = my_it->exponent + p_it->exponent;
				bool isX = false;
				if(my_it->x|| p_it->x) isX = true;

				// проверка если есть такая степень
				auto resultFind = find_if(result.terms.begin(), result.terms.end(), find_by_exponent(exponent));
				if(resultFind != result.terms.end()) {
					coef += resultFind->coefficient;
					result.terms.erase(*resultFind);
				}
				result.terms.insert(Term(coef, exponent, isX));
				++p_it;
			}

			++my_it;
		}

		return result;
	}
	// Перегрузка ввода
	friend istream &operator >> (istream &s, Polynomial &c) {
		c.init();
		return s;
	}
	// Перегрузка вывода
	friend ostream &operator << (ostream &s, Polynomial &c) {
		c.info();
		return s;
	}
};
  
int main()
{        
	setlocale(LC_ALL,"Russian");

	Polynomial ra = Polynomial();
	
	cin >> ra;
	cout << ra;
	
	Polynomial rc = Polynomial();
	
	rc.init();
	rc.info();

	Polynomial rb = ra + rc;
	rb.info();
	Polynomial rf = ra * rc;
	rf.info();
	
	cout << endl;
	cout << endl;


	system("pause");
}