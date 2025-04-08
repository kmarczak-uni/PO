# Słowo kluczowe const

## Zmienne
```cpp
const int x = 10;
x = 20;

const int* ptr_1 = &x;
*ptr_1 = 20;
ptr_1 = &y;

int* const ptr_2 = &x;
*ptr_2 = 20;
ptr_2 = &y;

const int* const ptr_3 = &x;
*ptr_3 = 20;
ptr_3 = &y;

const int& ref = x;
ref = 20;
```
## Zadanie
1. W powyzszym przykładzie wykomentuj te linijki, w których występuje niedozwolone (błędne) działanie na poszczególnych zmiennych.

## Funkcje
```cpp
void print(const std::string & text);  // uniemozliwia modyfikację obiektu text w funkcji print

const std::string getName();  // uniemozliwia dalszą modyfikację zwróconej przez funkcję wartości
```

## Zadanie
2. Napisz minimalny program z wykorzystaniem powyzszych funkcji, pokazujący konsekwencje wystąpienia słowa `const` w ich deklaracjach.
  
## Metody
```cpp
class Circle {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getRadius() const {  // metoda deklarująca brak modyfikacji obiektu, na którym jest wywołana
        return radius;
    }

    void setRadius(double r) {  // brak const oznacza, ze metoda moze (ale nie musi) zmienić stan obiektu na którym jest wywołana
        radius = r;
    }
};
```

## Podsumowanie

| **Zapis**                | **Znaczenie** |
|----------------------------|------------|
| `const int x = 10;` | `x` tylko do odczytu |
| `const int* ptr = &x;` | wskaźnik na stałą wartość (nie mozna zmienić wartości) |
| `int* const ptr = &x;` | stały wskaźnik (nie mozna ustawić wskaźnika na inny adres tj. inną zmienną niz x) |
| `const int* const ptr = &x;` | stały wskaźnik na stałą wartość |
| `const int& ref = x;` | referencja do stałej wartości |
| `void func(const int& x);` | referencja do stałej wartości (funkcja nie moze modyfikować wartości x) |
| `class Foo { void bar() const; };` | stała metoda (nie moze zmienić stanu obiektu) |


## Zadania
3. Utwórz stały obiekt jednej z samodzielnie napisanych klas (`Circle`, `Task` lub innej) a następnie spróbuj wywołać na rzecz tego obiektu jedną z jego metod , która z załozenia nie modyfikuje jego stanu (np. policzenie pola koła, wypisanie zadania na ekran itp.). Spróbuj poprawić klasę tak, aby program się skompilował.
4. Zmodyfikuj klasę `Task` tak, aby nie było możliwości zmiany treści zadania po utworzeniu obiektu.

# Konstruktor kopiujący
Przykład
```cpp
#include <iostream>

class MyClass
{
public:
    int a, b;

	MyClass(int pa, int pb)
	{
		a = pa;
		b = pb;
		std::cout << "Konstruktor parametrowy\n";
	};
    
    MyClass(const MyClass & other)
    {
        a = other.a;
        b = other.b;
		std::cout << "Konstruktor kopiujący\n";
    }

    void set(int pa, int pb) 
    { 
        a = pa; 
        b = pb;
    }
	
	~MyClass()
	{
		std::cout << "Destruktor\n";	
	};
};

void printByReference(MyClass & object)
{
    std::cout << "funkcja printByReference: " << object.a << ' ' << object.b << '\n';
}

void printByCopy(MyClass object)
{
    std::cout << "funkcja printByCopy: " << object.a << ' ' << object.b << '\n';
}

int main()
{
	MyClass object_1(1, 2);
    MyClass object_2(object_1);
    MyClass object_3 = object_2;
	
	printByReference(object_2);
    printByCopy(object_3);
	
	return 0;
}
```
  
## Pytania:  
1. Do czego słuzy konstruktor kopiujący?
2. Ile wywołań konstruktora kopiującego znajduje się w powyszym przykładzie? Ile jest łącznie wywołań destruktorów? 
3. Dlaczego konstruktor kopiujący deklaruje argument jako `const` i `&`? Która z tych dwóch deklaracji jest konieczna do poprawnego działania konstruktora, a która tylko zalecana (opcjonalna)?  
4. Co się stanie, jeśli usuniemy konstr. kopiujący w klasie? Czy program dalej będzie działał i miał ten sam efekt?  
  
  
## Zadania
1. Dopisac konstruktor kopiujący do klasy `Circle` i przetestować jego działanie.
2. Dopisac konstruktor kopiujący do klasy `Task` i przetestować jego działanie.  
3. Dopisać konstruktor kopiujący do klasy `Matrix` z zadania domowego.
4. Napisać klasę `MarksArray`, ktora pozwoli zrealizować zadania zgodnie z zad.1 z poprzedniego laboratorium (liczyć średnią ocen). Klasa ma przechowywać dowolną liczbę ocen (liczba ocen podana w konstruktorze), posiadać konstruktor kopiujący, metodę do wprowadzenia ocen oraz obliczenia średniej, wypisania ocen na ekran oraz zmiany oceny na wybranej pozycji.


## Zadanie domowe
1. Napisać własną klasę do manipulowania napisami, podobną do uzywanej dotychczas `std::string`. Klasa ma umozliwiać następujące operacje:
- tworzenie obiektów za pomocą konstruktora o następującej deklaracji: `MyString(const char* str = "")`
- kopiowanie istniejących obiektów (konstruktor kopiujący)
- wypisanie napisu na `std::cout` za pomocą metody `print()`
- zmianę przechowywanego napisu na nowy napis (równiez o innej długości), deklaracja metody: `void set(const char* newStr)`
Do kopiowania tablic znakowych i sprawdzenia ich długości mozna uzyc funkcji `std::strlen` praz `std::strcpy` z biblioteki `<cstring>`. Nie mozna uzywać w implementacji klasy `std::string`. 
