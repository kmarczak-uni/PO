# Przeciązanie operatorów

Dotychczas uzywaliśmy operatorów (na przykład: `+, -, *, /, =, (), >/<, ==, <<` itd.) na typach wbudowanych lub gotowych klasach bibliotecznych. Język C++ udostępnia mozliwość implementacji operatorów dla własnych klas. Przeciązenie operatorów w klasie pozwala posługiwać się obiektami tej klasy podobnie, jak robi się to z typami wbudowanymi:
  
```cpp
Point p1(1, 1), p2(2, 3);
Point p3 = p1 + p2;  // punkt (3, 4)
bool b = p2 > p1;
b = p2 == p1;
std::cout << "Punkt 1: " << p1 << '\n';
```
  
Teoretycznie mozna zaimplementować te same operacje jako zwykłe metody w klasie, jednak jest to mniej wygodne i czytelne od standardowych operatorów - porównaj ponizszy przykład do tego powyzej:
```cpp
Point p1(1, 1), p2(2, 3);
Point p3 = p1.add(p2);
bool b = p2.biggerThan(p2);
b = p2.isEqual(p1);
std::cout << "Punkt 1: ";
p1.print();
std::cout << '\n';
```
  
Przeciązanie operatorów polega na zaimplementowaniu specjalnie nazwanej metody lub funkcji: `operator_` (w miejscu `_` wstawiamy konkretny operator). Niektóre operatory mozna zaimplementować zarówno jako metodę klasy, jak i funkcję zewnętrzną; niektóre tylko jako funkcję. Więcej szczegółów na ten temat zawierają komentarze do przykładów `przeciazanie_operatorow_*.cpp` w plikach zespołu MS Teams.
Ponizej krótki przeglądowy przykład implementacji kilku operatorów dla klasy `Point`. Przykład wykorzystuje nowe pojęcie **przyjaźni** w C++. Funkcja zaprzyjaźniona z klasą (oznaczona w samej klasie przez `friend`) ma dostęp do składowych klasy tak, *jakby była* metodą tej klasy.

```cpp
#include <iostream>

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // przeciazenie operatora +
    Point operator+(const Point & other) const {
        return Point(x + other.x, y + other.y);
    }

    // przyjazn dla operatora ==
    friend bool operator==(const Point& a, const Point& b);
};

bool operator==(const Point& a, const Point& b) {
    // chociaz ta funkcja nie jest metoda klasy, 
    // to dzieki zaprzyjaznieniu ma dostep do prywatnych pol x, y
    return a.x == b.x && a.y == b.y;
}

int main() {
    Point a(2, 3), b(4, 1);
    Point c = a + b;

    if (a == Point(2, 3)) {
        std::cout << "punkt a jest równy (2, 3)\n";
    }

    return 0;
}

```
  
Szczegółowe przykłady implementacji większej liczby operatorów zarówno jako metody, jak i funkcje zewnętrzne zawarte są w plikach `przeciazanie_operatorow_*.cpp`.

### Zadania
1. Napisz klasę Fraction, która reprezentuje wartości ułamkowe. Zaimplementuj w tej klasie operatory umozliwiające działania z ponizszej funkcji `main()`. Zwróć uwagę na mozliwość wykorzystania w implementacji danego operatora juz istniejących operatorów (np. dzielenie przez ulamek to mnozenie przez jego odwrotność itd.).
```cpp
Fraction f1(1, 2);
Fraction f2(1, 3);

Fraction result;
result = f1 + f2;
result = f1 - f2;
result = f1 * f2;
result = f1 / f2;
result = f1 * 2;
f1[0] = 4;  // zmiana licznika
std::cout << f1;

bool b;
b = f1 > f2;  // oraz  f1 < f2
b = f1 == f2;  // oraz f1 != f2
```
  
2. Rozbuduj klasę `MyString` (własną implementację klasy string z poprzednich zadań) o następujące operatory: `+` (jako konkatenacja czyli łączenie napisów), `==/!=` (porównywanie napisów), `[]` (mozliwosc pobrania lub zmiany znaku o danym indeksie) oraz `>>/<<` (wypisywanie na strumień i pobieranie danych ze strumienia do napisu).
3. Dla dowolnej klasy zaimplementuj operator przypisania `operator=`. W funkcji `main()` pokaz i porównaj przykład wywołania konstruktora kopiującego z uzyciem `=` oraz wywołanie przed chwilą zaimplementowanego `operator=`.
