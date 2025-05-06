#include <iostream>

// Nie mozna przeladowywac operatorow dla typow wbudowanych (int, char, float).

// Operator mozna przeladowac jako:
// - niestatyczna funkcja skladowa tj. metoda (takimi funkcjami musza byc operatory: =, [], (), ->)
// - funkcja zaprzyjazniona z klasa lub zwykla funkcja globalna (jesli
//   operator nie musi miec dostepu do prywatnych skladnikow klasy)

// Jesli operator zmienia w jakis sposob obiekt, na ktorym pracuje, to
// powinien byc funkcja skladowa klasy (=, ++, --, +=, *= itp.).
// W przeciwnym razie stosuje sie raczej zwykla funkcje globalna
// ze wzgledu na wygode zapisu:
// x + 5
// 5 + x (tak nie da sie napisac jesli operator + jest funkcja skladowa
// bo wtedy pierwszym argumentem musi byc ukryty wskaznik this do obiektu,
// na rzecz ktorego wywolano funkcje skladowa realizujaca operator.
// Przy czym aby byla mozliwa taka przemiennosc, trzeba operator
// zdefiniowac jako 2 funkcje globalne np.:
// operator+(X, int)
// operator+(int, X)

class X
{
private:
  int a;

public:
  X(int ap = 0) : a(ap) { };

  friend X operator-(const X &x); // -x (operator jednoargumentowy)
  friend X operator+(const X &x1, const X &x2);
  friend X operator-(const X &x1, const X &x2);
  friend X operator*(const X &x, const int c);  // x*5
  friend X operator*(const int c, const X &x);  // 5*x
  friend X operator*(const X &x1, const X &x2); // x1*x2

  friend bool operator==(const X &x1, const X &x2);
  friend bool operator<=(const X &x1, const X &x2);
  friend bool operator<(const X &x1, const X &x2);
  friend bool operator>=(const X &x1, const X &x2);
  friend bool operator>(const X &x1, const X &x2);
  friend bool operator!=(const X &x1, const X &x2);
};

X operator-(const X &x)
{
  X s;
  s.a = -x.a;
  return s;
}

X operator+(const X &x1, const X &x2)
{
  X s;
  s.a = x1.a + x2.a;
  return s;
}

X operator-(const X &x1, const X &x2)
{
  X s;
  s.a = x1.a - x2.a;
  return s;
}

X operator*(const X &x, const int c)
{
  X s;
  s.a = x.a * c;
  return s;
}

X operator*(const int c, const X &x)
{
  X s;
  s.a = c * x.a;
  return s;
}

X operator*(const X &x1, const X &x2)
{
  X s;
  s.a = x1.a * x2.a;
  return s;
}

bool operator==(const X &x1, const X &x2)
{
  return x1.a == x2.a;
}

bool operator<=(const X &x1, const X &x2)
{
  return x1.a <= x2.a;
}

bool operator<(const X &x1, const X &x2)
{
  if (x1.a < x2.a)
    return true;
  else
    return false;
}

bool operator>=(const X &x1, const X &x2)
{
  return x1.a >= x2.a;
}

bool operator>(const X &x1, const X &x2)
{
  if (x1.a > x2.a)
    return true;
  else
    return false;
}

bool operator!=(const X &x1, const X &x2)
{
  return x1.a != x2.a;
}

int main()
{
  X x1(2), x2(1);  
  X x3;

  x3 = -x2;

  if (x1 == x2)
    std::cout << "x1==x2" << std::endl;
  else if (x1 < x2)
    std::cout << "x1<x2" << std::endl;
  else if (x1 > x2)
    std::cout << "x1>x2" << std::endl;

  return 0;
}
