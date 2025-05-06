#include <iostream>

// Nie mo�na prze�adowywa� operator�w dla typ�w wbudowanych (int, char, float).

// Operator mo�na prze�adowa� jako:
// - niestatyczn� funkcj� sk�adow� (takimi funkcjami musz� by� operatory: =, [], (), ->)
// - funkcj� zaprzyja�nion� z klas� lub zwyk�� funkcj� globaln� (je�li 
//   operator nie musi mie� dost�pu do prywatnych sk�adnik�w klasy)

// Je�li operator zmienia w jaki� spos�b obiekt, na k�rym pracuje, to 
// powinien by� funkcj� sk�adow� klasy (=, ++, --, +=, *= itp.).
// W przeciwnym razie stosuje si� raczej zwyk�� funkcj� globaln�
// ze wzgl�du na wygod� zapisu:
// x + 5
// 5 + x (tak nie da sie napisa� je�li operator + jest funkcj� sk�adow�
// bo wtedy pierwszym argumentem musi by� ukryty wska�nik this do obiektu, 
// na rzecz kt�rego wywo�ano funkcj� sk�adow� realizuj�c� operator.
// Przy czym aby by�a mo�liwa taka przemienno��, trzeba operator 
// zdefiniowa� jako 2 funkcje globalne np.:
// operator+(X, int)
// operator+(int, X)

class X
{
  private:
    int a,b;
 	
  public:
    X(int ap=0, int bp=0) : a(ap), b(bp) { };
	
    friend X operator-(const X& x); // -x (operator jednoargumentowy)
    friend X operator+(const X& x1,const X& x2);
    friend X operator-(const X& x1,const X& x2);
    friend X operator*(const X& x,const int c); // x*5
    friend X operator*(const int c,const X& x); // 5*x
    friend X operator*(const X& x1,const X& x2); // x1*x2
    
    // Operator indeksowania musi by� niestatyczn� funkcj� sk�adow� klasy.
    // Operator ten zwraca referencje do elementu pod indeksem i,
    // dzi�ki czemu mo�emy napisa� np.: x[0]=7;
    int& operator[](int i);
    
    // Operator przypisania musi by� niestatyczn� funkcj� sk�adow� klasy.
    // Podobnie jak w przypadku konstruktora kopiuj�cego
    // - je�li w danej klasie nie zdefiniowano operatora przypisania, 
    // kompilator stara si� wygenerowa� go sam jako "sk�adnik po sk�adniku"
    // (b�dzie to �r�d�em b��d�w je�li np. w klasie pami�� przydzielana
    // dynamicznie itp.).
    // Operator przypisania likwiduje star� wersj� obiektu i tworzy now�
    // przez kopiowanie (to samo co w konstruktorze kopiuj�cym).
    // U�ycie = przy definiowaniu obiektu (np. X x=y;) wywo�uje wyj�tkowo
    // konstruktor kopiuj�cy, nie operator przypisania.
    // Operator = powinien by� zabezpieczony przed 
    // przypisywaniem obiektu do samego siebie ( &x != this )
    // Operator = zwraca referencje do obiektu dzi�ki czemu b�d� dzia�a� 
    // wielokrotne przypisania: x=y=z, kt�re w rzeczywisto�ci nale�y
    // rozumie� jako: x=(y=z).
    // Uwaga !: operatora przypisania si� nie dziedziczy, podobnie jak
    // konstruktor�w i destruktor�w.
    X& operator=(const X& x);
	
    friend bool operator==(const X& x1,const X& x2);
    friend bool operator<=(const X& x1,const X& x2);
    friend bool operator<(const X& x1,const X& x2);
    friend bool operator>=(const X& x1,const X& x2);
    friend bool operator>(const X& x1,const X& x2);
    friend bool operator!=(const X& x1,const X& x2);
    
    // Operator wypisania obiektu do strumienia << powinien by� funkcj� zaprzyja�nion� z klas�
    // bo jego pierwszym argumentem musi by� argument klasy ostream
	  // i zazwyczaj operator ten potrzebuje dost�pu do sk�adnik�w prywatnych klasy.
    // Gdyby by� funkcj� sk�adow� to jego pierwszym argumentem by�by ukryty
    // wska�nik this do obiektu, a wi�c mo�na by�oby pisa� tylko tak:
    // x << cout;
    // Je�li by�by zwyk�� funkcj� globaln� to nie mia�by dost�pu 
    // do sk�adowych prywatnych klasy.
    // Operator << zwraca referencje do obiektu dzi�ki czemu b�d� dzia�a� 
    // nast�puj�ce konstrukcje: cout << x << y, kt�re w rzeczywisto�ci
    // nale�y rozumie� jako: ( (cout << x) << y ).
    friend std::ostream& operator<<(std::ostream& out,const X& x);
};

X operator-(const X& x)
{
  X s;
  s.a=-x.a;
  s.b=-x.b;
  return s;
}
X operator+(const X& x1,const X& x2)
{
  X s;
  s.a=x1.a+x2.a;
  s.b=x1.b+x2.b;
  return s;
}
X operator-(const X& x1,const X& x2)
{
  X s;
  s.a=x1.a-x2.a;
  s.b=x1.b-x2.b;
  return s;
}
X operator*(const X& x,const int c)
{
  X s;
  s.a=x.a*c;
  s.b=x.b*c;
  return s;
}
X operator*(const int c,const X& x)
{
  X s;
  s.a=c*x.a;
  s.b=c*x.b;
  return s;
}
X operator*(const X& x1,const X& x2)
{
  X s;
  s.a=x1.a*x2.a;
  s.b=x1.b*x2.b;
  return s;
}
int& X::operator[](int i)
{
  if(i<0 || i>1)
  {
    std::cout << "Wrong index: " << i << "\n";
    throw(1);
  }
  if(i==0)
    return a;
  else
    return b;
}
bool operator==(const X& x1,const X& x2)
{
  return x1.a==x2.a && x1.b==x2.b;
}
bool operator<=(const X& x1,const X& x2)
{
  return x1.a<=x2.a;	
}
bool operator<(const X& x1,const X& x2)
{
  if((x1.a<x2.a) || (x1.a==x2.a && x1.b<x2.b))
    return true;
  else
    return false;	
}
bool operator>=(const X& x1,const X& x2)
{
  return x1.a>=x2.a;	
}
bool operator>(const X& x1,const X& x2)
{
  if((x1.a>x2.a) || (x1.a==x2.a && x1.b>x2.b))
    return true;
  else
    return false;	
}
bool operator!=(const X& x1,const X& x2)
{
  return x1.a!=x2.a || x1.b!=x2.b;
}
X& X::operator=(const X& x)
{
  if(&x != this)	
  {
    a=x.a;
    b=x.b;
  }
  return *this;
}
std::ostream& operator<<(std::ostream& out,const X& x)
{
  out << "(" << x.a << "," << x.b << ")";
  return out;
}


int main()
{
  X i(0,1);
  X x1(2,3),x2(1,-1);
  X x3;
  x3=-x2;
  x3[0]=2; 
  
  std::cout << "x1=" << x1 << std::endl;
  std::cout << "x2=" << x2 << std::endl;
  std::cout << "x3=" << x3 << std::endl;
  std::cout << "x1[0]=" << x1[0] << std::endl;
  std::cout << "x2[1]=" << x1[1] << std::endl;
  std::cout << "x1+x2=" << x1+x2 << std::endl;
  std::cout << "x1-x2=" << x1-x2 << std::endl;
  std::cout << "2*x1=" << 2*x1 << std::endl;
  std::cout << "x2*3=" << x2*3 << std::endl;
  std::cout << "x1*x2=" << x1*x2 << std::endl;
  
  if(x1==x2)
    std::cout << "x1==x2" << std::endl;
  else
  if(x1<x2)
    std::cout << "x1<x2" << std::endl;
  else
  if(x1>x2)
    std::cout << "x1>x2" << std::endl;

  
  return 0;
}


