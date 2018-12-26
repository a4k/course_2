// definition 

#include "Polynom.h"
using namespace std;



// Многочлен
Polynom::Polynom() 
{
	lenPolynoms = 0;

	lPolynom = &ePolynom;
	lPolynom->id = -1;
	lPolynom->pow = 0;

	DataStore<int, 32> polynoms;


	return;
}
Polynom::Polynom(int pow) 
{

	lPolynom = &ePolynom;
	lPolynom->id = -1;
	lPolynom->pow = pow;

	DataStore<int, 32> polynoms;

	return;
}

// Деструктор
Polynom::~Polynom()
{
	delete lPolynom;
}


void Polynom::setPow(int pow) 
{
	lPolynom->pow = pow;
	return;
}
void Polynom::setId(int id) 
{
	lPolynom->id = id;
	return;
}

int Polynom::getId() 
{
	return lPolynom->id;
}
int Polynom::getPow() 
{
	return lPolynom->pow;
}



Polynom Polynom::operator+(Polynom & second) {
	cout << "test" << endl;
	Polynom Z;
	cout << "test2" << endl;
	return Z;
}

/*
Polynom Polynom::operator+(const Polynom &t) // оператор сложения A+B
{

	return *this;
    int i, coef = 0;
    if (getPow() >= t.getPow()) // A > B
    {
        Polynom Z = *this;
		for (i = 0; i <= getPow(); i++) {

			Z.Element::set(i);
			t.Element::set(i);
			Element::set(i);
			
			coef = getCoef();
			coef += t.getCoef();

			Z.Element::setCoef(coef);
			Z.Element::setPow(i);
			Z.Element::update();
		}
        return Z;
    } else // A < B
    {
        Polynom Z = t;
		for (i = 0; i <= getPow(); i++) {

			Z.Element::set(i);
			t.Element::set(i);
			Element::set(i);
			
			coef = getCoef();
			coef += t.getCoef();

			Z.Element::setCoef(coef);
			Z.Element::setPow(i);
			Z.Element::update();
		}
        return Z;
    }
}
	*/

const Polynom& Polynom::operator = (Polynom &t) 
{
    if(this != &t)
    {
        setPow(t.getPow());

		int i, coef = 0;
		for (i = 0; i <= getPow(); i++) {


			t.Element::set(i);
			
			coef = t.getCoef();

			cout << coef << endl;


			Element::setCoef(coef);
			Element::setPow(i);
			Element::create();
		}

    }
    return *this;
}

istream &operator >> (istream &s, Polynom &c)// перегруженный оператор ввода
{
	
    int coef = 0, pow = 0;

	while(c.getPow() < 1) {
		if(c.getPow() == 0) {
			cout << "Введите степень многочлена " << '\n';
			s >> pow;
			c.setPow(pow);
		}
	}

	
	cout << "Введите коэфициенты многочлена " << '\n';

    int i;
    for (i = 0; i <= c.getPow(); i++)
    {
		if(i == 0) {
			cout << "Коэффициент " << endl;
		
		} else {
			if(i == 1) {
				cout << "Коэффициент x" << endl;

			} else {
				cout << "Коэффициент x^" << i << endl;

			}
		}

        s >> coef;

		c.Element::setCoef(coef);
		c.Element::setPow(i);
		c.Element::create();

    }

	cout << endl;
	cout << endl;


    return s;
}


ostream &operator<<(ostream &s, Polynom &c)
{
	int i, n = 0, coef = 0, cpow = 0;

	int pow = c.getPow();

	if(pow > 0) {

		c.Element::print();

		
	s << '\n';

	} else
	{
		s << 0;
	}

	return s;
}


/*


Polynom Polynom::operator-(const Polynom &t) //оператор вычитания А-В
{
    int i;
    if (n >= t.n)//А>B
    {
        Polynom Z = *this;
        for (i = 0; i <= t.n; i++)
            Z.koef[i] = koef[i] - t.koef[i];
        return Z;
    }
    else//B>A
    {
        Polynom Z(t.n);
        for (i = 0; i <= n; i++)
            Z.koef[i] = -t.koef[i] + koef[i];
        for (i = n + 1; i <= t.n; i++)
            Z.koef[i] = -t.koef[i];
        return Z;
    }
}
Polynom Polynom::operator+(const Polynom &t)//оператор сложения A+B
{
    int i;
    if (n >= t.n)//A>B
    {
        Polynom Z=*this;
        for (i = 0; i <= n; i++)
            Z.koef[i] = koef[i] + t.koef[i];
        return Z;
    }
    else//A<B
    {
        Polynom Z=t;
        for (i = 0; i <= n; i++)
            Z.koef[i] = t.koef[i] + koef[i];
        return Z;
    }
}
Polynom Polynom::operator*(const Polynom &t)//оператор умножения А*В
{
    int i,j, s=0;
    Polynom Y(n+t.n);
    for (i = 0; i <= n; i++)
        for (j = 0; j <= t.n; j++)
            Y.koef[i + j] += koef[i]*t.koef[j];
    return Y;
}
Polynom Polynom::operator = (const Polynom &t) 
{
    if(this!=&t)
    {
        delete[] koef;
        n = t.n;
        koef = new double[n + 1];
        for (int i = 0; i <= n; i++)
            koef[i] = t.koef[i];
    }
    return *this;
}
istream &operator>>(istream &s, Polynom &c)// перегруженный оператор ввода
{
    int i;
    for (i = 0; i <= c.n; i++)
    {
        s >> c.koef[i];
    }
    return s;
}
ostream &operator<<(ostream &s, const Polynom &c)
{
int i, n=0;
for (i = 0; i <= c.n; i++)
{
    if (c.koef[i] != 0)
        n++;
}
if (n != 0)
{
    if (c.koef[0] != 0)
    {
        s << c.koef[0];
    }
    for (i = 1; i <= c.n; i++)
    {
        if (c.koef[i] < 0)
        { 
            if(c.koef[i]!=-1)
                s << c.koef[i] << "X^" << i; 
            else
                s << "-" << "X^" << i;
        }
        else
        {
            if (c.koef[i] != 0)
            {
                if(c.koef[i] != 1)
                    s << "+" << c.koef[i] << "X^" << i;
                else
                    s<< "+" << "X^" << i;
            }
        }
    }
s << '\n';
}
else
{
    s << 0;
}
return s;
}
Polynom Polynom::derivative()//производная от А
{
    int i;
    Polynom Z(n - 1);
    for (i = 0; i <=n-1; i++)
    {
        Z.koef[i] =(i+1)*koef[i +1];
    }
    return Z;
}
Polynom Polynom::integral()//интеграл от А
{
    int i;
    Polynom Z(n+ 1);
    for (i = 1; i <= n+1; i++)
    {
        Z.koef[i] = (koef[i-1])/(i);
    }
    Z.koef[0] = 0;
    return Z;
}
*/