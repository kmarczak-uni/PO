# Dziedziczenie
  
Dziedziczenie to jeden z kluczowych mechanizmów programowania obiektowego, umożliwiający tworzenie nowych klas na podstawie już istniejących. Pozwala to na ponowne wykorzystanie kodu oraz tworzenie logicznych hierarchii klas.  
Klasa, która udostępnia swoje właściwości i metody, nazywana jest klasą bazową (ang. *base class*), natomiast klasa dziedzicząca z klasy bazowej – klasą pochodną (ang. *derived class*). Klasa pochodna może rozszerzać lub modyfikować zachowanie klasy bazowej, dodając własne pola i metody lub przesłaniając te odziedziczone.  
W języku C++ dziedziczenie jest domyślnie prywatne, jednak najczęściej stosuje się dziedziczenie publiczne, aby elementy publiczne i chronione klasy bazowej były dostępne również w klasie pochodnej.  

Pomocny artykuł: [link 1](https://www.programiz.com/cpp-programming/inheritance) oraz [link 2](https://www.programiz.com/cpp-programming/function-overriding)

Przykład
```cpp
#include <iostream>

class X
{
public:
	int a;
	int b;
		
	X(int ap = 0, int bp = 0): a(ap), b(bp)
	{
		std::cout << "Konstruktor X \n";
	};
	
	X(const X& X1)
	{
		a = X1.a;
		b = X1.b;
		std::cout << "Konstruktor kopiujacy X\n";
	};
	
	void wypisz()
	{
		std::cout << "a= " << a << "\n";
		std::cout << "b= " << b << "\n";
	};
	
	~X() { std::cout << "Destruktor X\n"; };
};

class Y : public X  // zapis ": public X" oznacza, ze klasa Y dziedziczy publicznie z klasy X
{
public:
	int c;
		
	Y(int ap = 0, int bp = 0, int cp = 0) : X(ap, bp), c(cp)
	{
		std::cout << "Konstruktor Y \n";
	};
	
	Y(const Y& Y1) : X(Y1)
	{
		c = Y1.c;
		std::cout << "Konstruktor kopiujacy Y\n";
	};
	
	void wypisz_c()
	{
		std::cout << "c= " << c << "\n";
	};
	
	void wypisz()
	{
		X::wypisz();
		wypisz_c();
	};
	
	~Y() { std::cout << "Destruktor Y\n"; };
};

int main()
{
	{
		std::cout << "X:\n";
		X x(1,2);
		x.wypisz();
	}

	std::cout << "\n";

	{
		std::cout << "Y:\n";
		Y y(3, 4, 5);
		y.wypisz();

		std::cout << "Y2:\n";
		Y y2(y);
		y.wypisz();
	}

	return 0;
}
```
  
### Pytania
1. Zwróc uwagę na wypisane komunikaty przy tworzeniu obiektu klasy `Y`. Ile i jakich konstruktorów oraz destruktorów zostaje wywołanych?  
2. W jaki sposób zaimplementowane zostało wypisanie wszystkich pól w metodzie `wypisz()` w klasie `Y`? Spróbuj wprowadzić następujące zmiany:
- zamiast wywołania `X::wypisz()` odwołać się bezpośrednio do pól `a` i `b`
- zmienić klasę `X` tak, by pola były prywatne. Czy bezpośrednie odwołanie wprowadzone powyzej nadal działa? Zmień deklarację pól z prywatnej na **chronioną** (zastosuj deklarację **`protected` zamiast `private`**). Jaki jest efekt tego działania?

### Zadania
1. Utwórz 3 klasy, które będą w uproszczony sposób reprezentować konto w banku. Stwórz klasę bazową `Account` z polami `ownerName`, `balance` i `accountNumber`. Dodaj metody: `deposit(double amount)`, `withdraw(double amount)` oraz `printStatement()`.  
Następnie utwórz klasę `SavingsAccount`, która ma symulować konto oszczędnościowe. Metody tej klasy: nadpisanie `withdraw()` i `printStatement()` oraz nowa metoda `addInterest()`, pola: `interestRate`.  
Na koniec utwórz klasę `CheckingAccount`, która dodaje limit debetu `overdraftLimit` i nadpisuje `withdraw()` tak, by można było przekroczyć saldo do limitu.  
Klasy powinny być powiązane odpowiednią hierarchią dziedziczenia.

