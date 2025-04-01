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
delete[] tabPtr;
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
1. Napisz program, który pozwala uzytkownikowi wpisać z klawiatury wybraną przez niego liczbę ocen (poprawne wartości oceny: `[2.0, 2.5, ..., 5.0]`) i policzy ich średnią. Wykorzystaj dynamiczną alokację pamięci (operator `new`) oraz pętle.
2. Napisz program, który tworzy dwuwymiarową tablicę `int`ów o rozmiarze `m` x `n` wprowadzonym przez użytkownika z klawiatury. Tablica ma być wypełniona zerami i wypisana na ekran.
3. Do zadania 1. i 2. dopisz funkcje, które pozwalają na stworzenie niezaleznej kopii tablicy utworzonej w programie.
4. Przeanalizuj poniższy program i zlicz, ile razy zostanie wywołany konstruktor i destruktor klasy `Circle`. Spróbuj poprawić program tak, by zminimalizować liczbę tych wywołań.
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
1. Zmodyfikuj program z poprzedniego zadania domowego tak, aby to użytkownik sam mógł wprowadzić z klawiatury liczbę `tasków`, które chce zapisać na swojej liście. Następnie zaprojektuj klasę, która będzie służyć do tworzenia `tasku` (tj. zadania do wykonania), która zastąpi wcześniej użytą do tego klasę `std::string`. `Task` posiada dwa pola: treść typu `std::string` (np. `"odrobic zadanie domowe"`) oraz wartość logiczną `bool` określającą, czy `task` został już wykonany. Napisz w klasie metody niezbędne do dotychczasowego działania programu (tj. wprowadzanie listy zadań przez użytkownika z klawiatury i wypisanie jej na ekran).
2. Napisz klasę, która będzie przechowywać dwuwymiarową tablicę (macierz) liczb typu `float` o wymiarach `m x n` podanych przez użytkownika. Macierz ma być domyślnie wypełniona zerami przy jej konstrukcji. Napisz metody pozwalające:
- odczytać wartość poszczególnych elementów tablicy, podając współrzędne elementu do odczytu
- zmieniać wartość poszczególnych elementów tablicy, podając współrzędne elementu do zmiany i wartość do wpisania w argumentach metody
- wypełnić całą macierz wybraną wartością
- mnozyć macierz przez skalar (tj. pomnozyć wszystkie elementy macierzy przez argument metody)
- dodać do siebie dwie macierze (pod warunkiem, ze mają te same wymiary)
- wypisać macierz na ekran.
