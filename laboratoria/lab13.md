# Wprowadzenie do biblioteki STL - cd.  

## Kontenery asocjacyjne
### `std::set` oraz `std::map`
Poprzednio omówione kontenery sekwencyjne - jak wskazuje ich nazwa - charakteryzują się sekwencyjnym przechowywaniem i udostępnianiem danych. W odróznieniu do nich, kontenery asocjacyjne przechowują elementy uporządkowane wg pewnego klucza i w oparciu o klucz wykonują operacje wyszukiwania, dodawania i usuwania elementów. Elementy tych kontenerów muszą być unikalne. Do najczęściej uzywanych kontenerów asocjacyjnych nalezą `std::set` oraz `std::map`, które są zawsze posortowane.  
  
#### Przykład uzycia `std::set`
```cpp
#include <iostream>
#include <vector>
#include <set>

int main() {
    std::set<int> s;

    s.insert(3);
    s.insert(1);
    s.insert(4);
    s.insert(2);
    s.insert(3);

    std::cout << "Elementy zbioru:\n";
    for (int x : s)
        std::cout << x << " ";
    std::cout << "\n";

    // dwa sposoby sprawdzenia, czy element istnieje w zbiorze
    // jeden zwraca inofmacje prawda-falsz, drugi daje dostep do znalezionego elementu
    if (s.count(2))
        std::cout << "Znaleziono element\n";

    auto it = s.find(3);
    if (it != s.end())
        std::cout << "Znaleziono: " << *it << "\n";

    s.erase(1);

    std::vector<int> vec = {10, 20, 10, 30};
    std::set<int> sFromVec(vec.begin(), vec.end());

    std::cout << "Elementy zbioru utworzonego z wektora:\n";
    for (int x : sFromVec)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
```
  
#### Przykład uzycia `std::map`
```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> marks;

    marks["Kowalski Jan"] = 5;
    marks["Nowak Iza"] = 5;
    marks["Iksinski Zygmunt"] = 3;

    // nadpisanie wartosci
    marks["Iksinski Zygmunt"] = 4;
    // dodanie rekordu przez insert - nie nadpisuje, jesli klucz juz istnieje
    scores.insert({"Tomek", 0});

    // iteracja - kolejnosc wg klucza
    std::cout << "Zawartosc mapy:\n";
    // poszczegolne rekordy sa typu std::pair, zlozonego ze skladowych first i second
    for (const auto & pair : marks)
        std::cout << pair.first << ": ocena " << pair.second << "\n";

    if (marks.count("Nowak Iza"))
        std::cout << "Nowak Iza jest zapisana w mapie\n";

    // usuwanie po kluczu
    marks.erase("Kowalski Jan");

    std::map<std::string, int> scores = {
        {"Tomek", 80},
        {"Ania", 95},
        {"Kasia", 90}
    };

    auto it = scores.find("Ania");
    if (it != scores.end())
        std::cout << "Wynik Ani: " << it->second << "\n";

    for (const auto & pair : scores)
        std::cout << pair.first << ": wynik = " << pair.second << "\n";

    return 0;
}
```

### Iteracja po kontenerach asocjacyjnych a sekwencyjnych
Poniewaz kontenery asocjacyjne nie zakładają przechowywania elementów w swoim "sąsiedztwie", nie udostępniają mozliwości odczytu elementów po dowolnym indeksie, mozna jedynie przesuwać iterator do przodu lub do tyłu (`++it` lub `--it`, ale nie `it+5, it[2]`).

## Algorytmy zbiorów
W nagłówku `<algorithm>` znajdziemy standardowe matematyczne operacje na zbiorach, czyli: część wspólna zbiorów `std::set_intersection` i wspólna bez powtórzeń `std::set_union`, róznica zbiorów `std::set_difference`, zawieranie zbiorów `std::includes`.
```cpp
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
    std::set<int> A = {1, 2, 3, 4, 5};
    std::set<int> B = {4, 5, 6, 7};
    std::vector<int> result;

    std::set_union(
        A.begin(), A.end(),
        B.begin(), B.end(),
        std::back_inserter(result)
    );
    std::cout << "Suma zbiorow: ";
    for (int x : result) std::cout << x << " ";
    std::cout << "\n";

    result.clear();
    std::set_intersection(
        A.begin(), A.end(),
        B.begin(), B.end(),
        std::back_inserter(result)
    );
    std::cout << "Czesc wspolna: ";
    for (int x : result) std::cout << x << " ";
    std::cout << "\n";

    result.clear();
    std::set_difference(
        A.begin(), A.end(),
        B.begin(), B.end(),
        std::back_inserter(result)
    );
    std::cout << "Roznica A - B: ";
    for (int x : result) std::cout << x << " ";
    std::cout << "\n";

    bool AincludesB = std::includes(
        A.begin(), A.end(),
        B.begin(), B.end()
    );
    std::cout << "Czy A zawiera B?: " << (AincludesB ? "tak" : "nie") << "\n";

    return 0;
}
```

# Zadania
1. Rozwiń ponizszy program o zliczenie wystąpień poszczególnych słów w tekście w oparciu o utworzony `std::vector<std::string>`:
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string input = "count the number of words and write the word count down as a number";
    std::vector<std::string> words;

    std::istringstream iss(input);
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return 0;
}
```
2. Napisz program, który grupuje listę słów wg pierwszej litery. Mozna wykorzystać przykładową listę: `"zebra", "orzel", "kangur", "koala", "owca", "pies", "kot", "wrobel", "lew", "pingwin", "orka"` lub stworzyć własną.
3. Napisz program symulujący obstawianie duzego lotka. Uzytkownik ma podać 6 unikalnych liczb całkowitych z zakresu `1-49`. Program losuje w taki sam sposób 6 liczb i podaje wynik (wg zasad gry w lotka, wygrana to trójka, czwórka, piątka lub szóstka pokrywających się liczb). Przyjmij przykładowe wygrane dla poszczególnych zwycięskich wyników i wyświetl je na końcu programu.
4. Napisz program symulujący system rejestrowania się uzytkownika w portalu. Uzytkownik musi stworzyć login, który nie jest juz zajęty przez innego uzytkownika oraz hasło złozone z min. 10 unikalnych znaków. Program wykonuje pętle az do podania poprawnych danych i zapisania ich do odpowiedniej struktury danych lub przerwania programu np. przez wpisanie `-1`.
