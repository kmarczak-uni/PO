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
  

# Składowe statyczne

Czasami chcemy, aby pewne dane lub funkcje były wspólne dla wszystkich obiektów danej klasy, a nie unikalne dla każdego z nich.  
Załózmy, ze chcemy policzyć, ile razy utworzono obiekty pewnej klasy. Nie jest to mozliwe za pomocą zwykłych atrybutów w klasie, poniewaz kazda instancja (utworzony obiekt) klasy ma  własne, niezalezne kopie atrybutów. Do realizacji tego zadania musimy uzyc atrybutów  statycznych deklarowanych za pomocą słowa kluczowego `static`.
Statyczne atrybuty (zmienne statyczne):
- są deklarowane wewnątrz definicji klasy z uzyciem słowa kluczowego static
- nie nalezą do żadnego konkretnego obiektu klasy i istnieją niezaleznie od tego, czy utworzono jakiekolwiek obiekty tej klasy
- istnieje tylko jedna kopia statycznego atrybutu dla całej klasy. Wszystkie obiekty tej klasy współdzielą tę samą wartość tego atrybutu
- muszą być zdefiniowane (inicjalizowane) w szczególny sposób - **poza definicją klasy** (C++11/14)
- statyczne metody mogą być wywołane bez tworzenia instancji klasy.

Przykład:
```cpp
#include <iostream>

class MyClass {
private:
    int a;
    int b;
    static int x;

public:
    MyClass(int ap, int bp) : a(ap), b(bp) { 
        x += 10;
        std::cout << "Konstruktor MyClass\n";
    }

    MyClass() : a(0), b(0) { }

    void print() const {
        std::cout << "Adres statycznej zmiennej x: " << &x << '\n';
        std::cout << "Adres zmiennej a: " << &a << ", zmienna b: " << &b << "\n\n";
    }

    void set_ab(int ap, int bp) {
        a = ap;
        b = bp;
    }

    static int get_x() {
        // uwaga: statyczna metoda !nie ma dostepu! do niestatycznych atrybutow. Np. zabronione sa:
        // std::cout << a;  
        // set_ab(0, 0);
        x += 1;
        return x;
    }
};

// definicja (inicjalizacja) statycznego atrybutu poza klasa (C++11/14)
int MyClass::x = 0;

int main() {
    std::cout << "MyClass::get_x() przed utworzeniem jakiegokolwiek obiektu: " << MyClass::get_x() << '\n';

    MyClass obj1(10, 20);
    obj1.print();

    std::cout << "MyClass::get_x() po utworzeniu jednego obiektu: " << MyClass::get_x() << '\n';
    obj1.get_x();

    MyClass obj2(10, 20);
    obj2.print();

    std::cout << "MyClass::get_x() po utworzeniu dwoch obiektow: " << MyClass::get_x() << '\n';

    return 0;
}
```

## Zadania
1. Zmień powyzszy przykład tak, aby klasa zawierała statyczny atrybut `objectCount`, który zawsze przechowuje aktualną liczbę istniejących instancji (obiektów) klasy.
2. Zmień program uzywajacy klasy `Circle` tak, aby wartość `pi` była **stałym statycznym** atrybutem klasy i była uzywana do stosownych obliczen w metodach.
  
## Zadanie domowe
1. ⚠️ Zapoznaj się z działaniem ponizszej klasy, symulującej w uproszczony sposób działanie loggera (narzędzia zapisującego jakieś zdarzenia np. do pliku). Następnie zmień ją tak, aby nie dało się utworzyć więcej niz jednej instancji obiektu tej klasy. Taka klasa realizuje tzw. wzorzec projektowy nazywany `singleton`. Podpowiedź: do rozwiązania przydadzą się wskaźniki oraz ukrywanie pewnych funkcjonalności klasy przez umieszczenie ich w części prywatnej.  
  
```cpp
#include <iostream>
#include <string>

class Logger {
private:
    std::string logFilename;

public:
    Logger(const std::string& filename = "app.log") : logFilename(filename) {
        log("Logger zainicjalizowany.");
    }

    ~Logger() {
        log("Logger zamykany.");
    }

    void log(const std::string& message) const {
        std::cout << "[INFO] " << message << " (zapis do: " << logFilename << ")" << std::endl;
    }

    void logError(const std::string& message) const {
        std::cerr << "[ERROR] " << message << " (zapis do: " << logFilename << ")" << std::endl;
    }
};

int main() {
    Logger logger1;
    logger1.log("Wiadomosc z pierwszego loggera\n");

    Logger logger2("debug.log");
    logger2.logError("Blad z drugiego loggera\n");

    return 0;
}
```
