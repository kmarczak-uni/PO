# Tworzenie własnych klas

Przykład
```cpp
#include <iostream>

class MyClass
{
	public:
		int a;
		int b;
		
	MyClass()
	{
		a = 1;
		b = 2;
		std::cout << "Konstruktor domyslny (bezparametrowy)\n";
	};
	
	~MyClass()
	{
		std::cout << "Destruktor\n";	
	};
};

int main()
{
	MyClass object;
	
	std::cout << "a= " << object.a << '\n';
	std::cout << "b= " << object.b << '\n';
	
	return 0;
}
```

## Konstruktor domyślny i argumentowy
  
### Pytania
1. W którym miejscu ma miejsce wywołanie konstruktora klasy `MyClass`, a w który destruktora?
2. Co się stanie, jeśli deklaracje pól `int a` oraz `int b` znajdą się przed deklaracją public? Co się dzieje, jeśli w ogóle usuniemy deklarację `public` z klasy?
3. Sprawdź, czy konstruktor i destruktor może nazywać się inaczej niż klasa, do której należy. Czy w obrębie klasy może istnieć więcej niż jeden konstruktor? Jeśli tak, to pod jakim warunkiem?
4. Przeczytaj najpierw poniższe przykłady konstruktorów i zastanów się, czym różnią się od pierwszego przykładu i jakie zmiany w funkcji `main` należy wprowadzić, by wywołać te konstruktory. Na ile różnych sposobów można wywołać dany typ konstruktora? Następnie sprawdź uruchamiając kod, czy Twoje przewidywania się sprawdziły.  
  
```cpp
MyClass(int ap, int bp)
{
	a = ap;
	b = bp;
	std::cout << "Konstruktor wieloargumentowy\n";
};
```
```cpp
MyClass(int ap = 3, int bp = 5)
{
	a = ap;
	b = bp;
	std::cout << "Konstruktor domyslny (bezparametrowy)\n";
};
```
```cpp
MyClass(int ap = 3)
{
	a = ap;
	b = 2;
	std::cout << "Konstruktor domyslny (bezparametrowy)\n";
};
```
## Konstruktor z listą inicjalizacyjną

```cpp  
MyClass(int ap, int bp): a(ap), b(bp)
{
	std::cout << "a: " << a << ", b: " << b << '\n';
	std::cout << "Konstruktor z lista inicjalizacyjna\n";
};

MyClass(int ap): a(ap+5), b(7)
{
	std::cout << "a: " << a << ", b: " << b << '\n';
	std::cout << "Konstruktor z lista inicjalizacyjna\n";
};
```  
  
Na podstawie działania powyższych konstruktorów wyjaśnij, na czym polega działanie listy inicjalizacyjnej.  

## Zadania
1. Napisz klasę reprezentującą koło, z polami dlugość promienia i współrzędnymi środka `x` oraz `y`. Klasa ma posiadać jeden konstruktor domyślny (np. środek w punkcie `[0, 0]` i długość promienia `1`) oraz wieloargumentowy. Uwzględnij fakt, że poprawny zakres wartości dla promienia to `r > 0`. Użyj listy inicjalizacyjnej w obydwu konstruktorach. Stwórz po jednym obiekcie z użyciem każdego konstruktora.
2. Napisz klasę reprezentującą prostokąt, z polami przewchowującymi dlugości boków `a` i `b`. Klasa ma pozwalać na tworzenie obiektów przez podanie dwóch argumentów (długości boków) lub bez podania argumentów (domyślny obiekt: kwadrat 1x1). Uwzględnij fakt, że poprawny zakres wartości dla boków to `a > 0, b > 0`.
3. Napisz klasę reprezentującą datę, z polami przewchowującymi rok, miesiąc i dzień. Klasa ma pozwalać na tworzenie obiektów przez podanie trzech argumentów lub bez podania argumentów (domyślna data: 1. stycznia 1970). Na razie klasa ma sprawdzać tylko poprawność zakresów poszczególnych składowych: dzień `1-31`, miesiąc `1-12`, rok `1-9999`, nie weryfikując poprawności całej daty (np. czy możliwa jest data 31. lutego).  

# Metody - funkcje w klasie
  
```cpp
#include <iostream>

class MyClass
{
private:
	int a;
	int b;

public:	
	MyClass(int ap, int bp): a(ap), b(bp) { };
	
	MyClass(): a(0), b(0) { };

	void print()
	{
		std::cout << "Obiekt klasy MyClass, atrybut a = " << a << ", atrybut b: " << b << std::endl;
	}

	int product()
	{
		return a * b;
	}

	void set_ab(int ap, int bp)
	{
		a = ap;
		b = bp;
	}
	
	~MyClass() { };
};

int main()
{
	MyClass object(2, 5);
	object.print();
	int value = object.product()
	std::cout << "Zmienna value = " << value << ", wywołanie metody product(): " << object.product() << std::endl;
	object.set_ab(1, 4);
	object.print(); 
	
	return 0;
}
```
  
Metody to funkcje szczególnego rodzaju, zdefiniowane w obrębie danej klasy, które wywołujemy __na rzecz obiektu klasy__. Metoda ma dostęp do wszystkich składowych klasy, ponieważ sama jest jedną z nich - w ciele metody możemy odczytywać i manipulować wartością zarówno publicznych, jak i prywatnych atrybutów.  
  
Domyślną konwencją programowania w paradygmacie obiektowym jest zastosowanie hermetyzacji - ukrywanie części atrybutów klasy i udostępnianie publicznego interfejsu, który określa, w jaki sposób "wolno nam" manipulować obiektem. Pozwala to na lepszą kontrolę nad stanem obiektu, np. metody umożliwiające zmianę wartości atrybutów mogą dodatkowo zawierać logikę walidującą wartości, które chce ustawić użytkownik.  
  
## Zadania
4. Zmień klasę `Circle` z zadania powyżej (dobre praktyki programistyczne!) tak, aby jej pola były prywatne. Dopisz 2 publiczne metody pozwalające odpowiednio na zmianę wartości promienia oraz współrzędnych środka (promień musi być wartością dodatnią). Następnie napisz metody do obliczania pola i obwodu oraz wypisania obiektu. Wartość `pi` pobierz z biblioteki `<cmath>` lub zdefiniuj samodzielnie w programie jako stałą.
5. Zmień klasę `Rectangle` z poprzedniego zadania tak, aby jej pola były prywatne. Dopisz publiczne metody pozwalające odpowiednio na: 
- zmianę wartości długości boków,
- obliczanie pola, obwodu i długości przekątnej,
- wypisania obiektu.
6. Zmień klasę `Date` tak, aby jej pola były prywatne. Dopisz metodę pozwalającą na zmianę daty utworzonej w konstruktorze (wymaga podania wszystkich 3 wartości).  
  
# Zarządzanie pamięcią - new & delete
W języku C++ dynamiczne zarządzanie pamięcią pozwala na alokację i dealokację pamięci w trakcie działania programu. Odbywa się to za pomocą operatorów `new` i `delete`, które zastępują funkcje `malloc()` i `free()` znane z języka C.  
W języku C dynamiczna pamięć jest alokowana funkcją `malloc()`, która zwraca wskaźnik typu `void*`, wymagając rzutowania do odpowiedniego typu:
```c
int* ptr = (int*)malloc(sizeof(int));
free(ptr);
```
  
W C++ operator `new` upraszcza ten proces, automatycznie zwracając wskaźnik do odpowiedniego typu:
```cpp
int* ptr = new int;
delete ptr;

int* ptr_5 = new int(5);
delete ptr_5;
```
Dla tablic wygląda to analogicznie, ale **uwaga na prawidłowe zwalnianie pamięci** (pominięcie `[]` przy `delete` prowadzi do wycieku pamięci!):  
```cpp
int* arr = new int[10];
delete[] arr; // uwaga: latwo tutaj o blad niewykrywalny przy kompilacji  
```
  
Przykład alokacji obiektów klasy:
```cpp
MyClass * ptr = new MyClass;
delete ptr;

MyClass * tabPtr = new MyClass[10];
delete[] ptr;
```
  
Wywoływanie metod obiektu za pomocą wskaźnika:
```cpp
MyClass * ptr = new MyClass;
(*ptr).print();
// lub czesciej stosowane:
ptr->print();
delete ptr;
```
  
### Pytania
1. Dlaczego musimy uważać na prawidłowe zwalnianie pamięci? Uruchom powyższy fragment programu z dynamiczną alokacją pojedynczego obiektu oraz tablicy obiektów MyClass. Co zaobserwowałeś na wyjściu programu? Jaki płynie z tego wniosek nt. konstruktorów i destruktorów?  
Uwaga: w standardzie C++11 do jeszcze lepszego i wygodniejszego zarządzania pamięcią służą tzw. smart pointers. Na razie jednak do dynamicznej alokacji pamięci będziemy używać tylko `new` oraz `delete`.

### Zadania  
7. Napisz program, który tworzy dwuwymiarową tablicę `int`ów o rozmiarze `m` x `n` wprowadzonym przez użytkownika z klawiatury. Tablica ma być wypełniona zerami i wypisana na ekran.
2. Przeanalizuj poniższy program i zlicz, ile razy zostanie wywołany konstruktor i destruktor klasy `Circle`. Spróbuj poprawić program tak, by zminimalizować liczbę tych wywołań.
```cpp
int main()
{
    int numCircles;

    std::cout << "Wprowadz liczbe obiektow (kol) w tablicy: ";
    std::cin >> numCircles;

    Circle* circles = new Circle[numCircles];
    
    for (int i = 0; i < numCircles; i++) {
        double r;
        std::cout << "Wprowadź wartość promienia: ";
        std::cin >> r;
        circles[i] = Circle(r);
    }

    std::cout << "\nPola kol:\n";
    for (int i = 0; i < numCircles; i++) {
        std::cout << "Kolo nr " << i + 1 << " Pole = " << circles[i].area() << "\n";
    }
    
    delete[] circles;

    return 0;
}
```
  
# Zadanie domowe
1. Napisz klasę `Triangle`, która zamodeluje obiekty trójkątów. Klasa ma zawierać wszystkie wymiary trójkąta, które są potrzebne do policzenia jego pola oraz obwodu, jak również metody do obliczenia tych cech.  
2. Zmodyfikuj program z poprzedniego zadania domowego tak, aby to użytkownik sam mógł wprowadzić z klawiatury liczbę `tasków`, które chce zapisać na swojej liście. Następnie zaprojektuj klasę, która będzie służyć do tworzenia `tasku` (tj. zadania do wykonania), która zastąpi wcześniej użytą do tego klasę `std::string`. `Task` posiada dwa pola: treść typu `std::string` (np. `"odrobic zadanie domowe"`) oraz wartość logiczną `bool` określającą, czy `task` został już wykonany. Napisz w klasie metody niezbędne do dotychczasowego działania programu (tj. wprowadzanie listy zadań przez użytkownika z klawiatury i wypisanie jej na ekran).
3. Napisz klasę, która będzie przechowywać dwuwymiarową tablicę (macierz) liczb typu `float` o wymiarach `m x n` podanych przez użytkownika. Macierz ma być domyślnie wypełniona zerami przy jej konstrukcji. Napisz metodę pozwalającą zmieniać wartość poszczególnych elementów tablicy, podając współrzędne elementu do zmiany i wartość do wpisania w argumentach metody. Napisz również metodę wypisującą macierz na ekran z określoną w argumencie metody precyzją tj. liczbą cyfr po przecinku.
