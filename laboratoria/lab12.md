# Wprowadzenie do biblioteki STL (Standard Template Library)  
  
STL to skrót od Standard Template Library, czyli Standardowej Biblioteki Szablonów języka C++. Jest to bogata biblioteka gotowych klas i funkcji szablonowych, pozwalających na realizację róznych zadań.  
Biblioteka STL zawiera gotowe struktury danych i algorytmy, które są dobrze zoptymalizowane i bezpieczne, jak i elastyczne - poniewaz oparte są na szablonach, współpracują z wieloma typami danych. Jej znajomość przyspiesza pisanie kodu, eliminując konieczność samodzielnego implementowania wielu podstawowych struktur danych i algorytmów.  
Zawartość biblioteki mozna ogólnie podzielić na kategorie:
- kontenery - klasy tworzące kolekcje danych,
- algorytmy - funkcje przetwarzające dane w kontenerach (np. sortowanie, przeszukiwanie itp.),
- iteratory - specjalnie obiekty pośredniczące między kontenerami a algorytmami, pozwalające na iterowanie elementów kontenera w odpowiedni sposób,
- funktory/predykaty.

# Kontenery
Wyrózniamy kontenery:
- sekwencyjne: `array`, `vector`
- asocjacyjne (sortowane po kluczu): `set`, `map`
- adaptery na kontenery - interfejsy na pozostałe kontenery z ograniczonymi mozliwosciami dostępu do elementów, np. `stack` lub `queue`

## Kontenery sekwencyjne
`std::array<T, N>` czyli kontener o **stałym rozmiarze** zdefiniowany w nagłówku <array> - najbardziej przypomina w działaniu wbudowane tablice danych, ale jest bezpieczniejszy i łatwiejszy w uzyciu od nich.
```cpp
#include <iostream>
#include <array>

int main() {
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    std::cout << "Rozmiar tablicy: " << arr.size() << "\n";
    std::cout << "Pierwszy element: " << arr.front() << "\n";
    std::cout << "Ostatni element: " << arr.back() << "\n";

    arr[1] = 99;
    std::cout << "Element o indeksie 1: " << arr.at(1) << "\n";

    arr.fill(7);
    for (int el : arr)  // petle for-each - wygodna iteracja po wszystkich elementach
        std::cout << el << " ";
    std::cout << "\n";

    std::array<int, 5> other = {1, 2, 3, 4, 5};
    arr.swap(other);
    std::cout << "Po zamianie: ";
    for (int el : arr) 
        std::cout << el << " ";
    std::cout << "\n";

    return 0;
}
```
  
Z kolei najbardziej popularnym i prawdopodobnie najczęściej uzywanym jest kontener `std::vector<T>`. Charakteryzuje się **dynamiczną liczbą przechowywanych elementów**, co oczywiście sprawia, ze jest bardziej elastyczny i uzyteczny w wielu sytuacjach niz `std::array<T, N>`.
Ogólna zasada, wspomniana nawet w standardzie C++: jeśli w programie potrzebujemy uzyć jakiegoś kontenera do przechowywania danych, powinniśmy sięgnąć po `vector`, o ile nie mamy dobrego powodu, by zrobić inaczej.
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {10, 20, 30};

    vec.push_back(40);
    vec.insert(vec.begin() + 1, 15); // dodawanie elementu w miejscu innym niz koniec - tu indeks 1

    std::cout << "Aktualny rozmiar: " << vec.size() << "\n"; // aktualna liczba elementow
    std::cout << "Calkowita pojemnosc: " << vec.capacity() << "\n";
    std::cout << "Element o indeksie 2: " << vec.at(2) << "\n";
    std::cout << "Pierwszy element: " << vec.front() << ", ostatni element: " << vec.back() << "\n";

    vec.pop_back();
    vec.erase(vec.begin() + 1); // usun element o indeksie 1
    vec.resize(6, 100); // zmien rozmiar do 6, wypelnij wartoscia 100 nowe elementy

    std::cout << "Zawartosc: ";
    for (int x : vec) 
        std::cout << x << " ";
    std::cout << "\n";

    vec.clear();  // usuwa wszystkie elementy
    std::cout << "Czy pusty? " << (vec.empty() ? "Tak" : "Nie") << "\n";

    return 0;
}
```
Uwaga: metody `insert()` praz `operator[]` nie sprawdzają poprawności uzytych w parametrach indeksów, a podanie niepoprawnego indeksu nie wywołuje błędu (kończy się tzw. UB - undefined behaviour). Dostęp do elementu z dodatkowym zabezpieczeniem przed odczytem nieprawidłowego indeksu umozliwia metoda `at()`.
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {10, 20, 30};

    vec[1] = 99; // poprawny indeks operatora[]
    std::cout << "vec[1] = " << vec[1] << "\n";
    // vec[10] = 42; // UB
    try {
        vec.at(2) = 77; // poprawny indeks
        std::cout << "vec.at(2) = " << vec.at(2) << "\n";
        vec.at(10) = 42; // rzuca wyjatek
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << "\n";
    }

    vec.insert(vec.begin() + 1, 55);
    for (int val : vec) 
        std::cout << val << " ";
    std::cout << "\n";
    // vec.insert(vec.begin() + 100, 123); // UB

    return 0;
}
```

## Zadania
Ponizsze zadania zrealizuj z uzyciem poznanych kontenerów STL.
1. Napisz program, w którym uzytkownik wpisuje 5 liczb z klawiatury, a program oblicza i wypisuje ich średnią.
2. Napisz program, w którym uzytkownik wpisuje liczby dodatnie, kończąc proces wprowadzania danych przez wpisanie wartości ujemnej. Program ma wypisać najmniejszą i największą z wpisanych wartości oraz ich średnią.
3. Napisz program, który odwraca cyfry we wpisanej przez uzytkownika liczbie (np. `12345` -> `54321`).
4. Napisz program, który pozwala na edycję listy studentów (dla uproszczenia wystarczy imię i nazwisko jako pojedynczy `std::string`). Menu programu pozwala uzytkownikowi wyświetlić listę, dopisać nowego studenta do listy i usunąć wybranego studenta z listy (podając jego indeks).
5. Zmień klasę `MarksArray` z poprzednich laboratoriów tak, aby uzywała konteneru STL do przechowywania elementów.
6. Zmień klasę `Matrix` z poprzednich laboratoriów tak, aby uzywała konteneru STL do przechowywania elementów. Uwaga: prostokątną dwuwymiarową macierz mozna przechowywać w jednowymiarowym kontenerze, umozliwiając dostęp do elementu [i][j] w indeksie [i*liczba_kolumn + j].
  
# Iteratory
Do przechodzenia po kontenerach uzywamy specjalnych obiektów - iteratorów. Tworzą one uniwersalny interfejs dostępu do elementów kontenerów róznych klas. Iterator traktujemy jak wskaźnik na daną pozycję w kontenerze.  
Rodzaje iteratorów:
- `begin()` — iterator wskazujący na pierwszy element
- `end()` — iterator umieszczony **za ostatnim elementem** (nie mozna z jego pomocą odczytać wartości)
- `cbegin()`, `cend()` — stałe iteratory (pozwalające tylko na **odczyt** elementów)
- `rbegin()`, `rend()` — iteratory od końca do początku kontenera (ang. *reverse*).  
Iteratory "współpracują" z algorytmami biblioteki STL i są potrzebne do wskazania zakresu pracy np. funkcji sortującej, znajdującej zadany element i wielu innych.

```cpp
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main() {
    // uzyte w programie iteratory dzialaja tak samo dla obiektu vector i array
    // std::vector<int> container = {10, 20, 30, 40, 50};
    // std::array<int, 5> container = {10, 20, 30, 40, 50};

    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';

    int value = 30;
    auto found = std::find(container.begin(), container.end(), value);  // find zwraca iterator na znaleziony element, a nie sam element
    if (found != container.end()) {
        std::cout << "Wartosc " << value << " na pozycji [" << (found - container.begin()) << "]\n";
    } else {
        std::cout << "Nie znaleziono wartosci " << value << '\n';
    }

    return 0;
}
```
### Iteratory a pętla for-each
Do przejścia po wszystkich elementach kontenera od jego początku do końca w celu odczytania wartości (bez usuwanialub dodawania elementów) najwygodniej zastosować jest pętlę `for-each`. Dodawanie lub usuwanie elementów w trakcie pętli `for-each` jest niedozwolone. W takim scenariuszu nalezy uzyć iteratora.

# Algorytmy
W nagłówku `<algorithm>` znajdziemy ponad sto przydatnych algorytmów stworzonych do pracy z kontenerami STL. Mozna z ich pomocą zrealizować bardzo wiele zadań w sposób czytelny i bardzo efektywny, poniewaz implementacje są często napisane w sposób znacznie bardziej wydajny niz "naiwne" implementacje.  
Kilka często stosowanych algorytmów to np.: `std::find`, `std::count`, `std::sort`, `std::reverse`, `std::copy`, `std::remove`.
### Przewodnik po algorytmach STL
[Youtube: Prelekcja z konferencji CppCon o algorytmach STL](https://www.youtube.com/watch?v=2olsGf6JIkU)
  
## Zadania
1. Zmień rozwiązanie z.2 z poprzedniej listy tak, aby do znalezienia wartości minimalnej i maksymalnej uzyć algorytmu sortowania. Pogram ma tez wypisać ile razy we wprowadzonych danych wystąpiła wartość min i maksymalna.
2. Dodaj do rozwiązania z.4 mozliwość usunięcia z listy osoby przez wpisanie jej nazwiska zamiast jej indeksu na liście. Stwórz kopię listy osób i posortuj ją.
