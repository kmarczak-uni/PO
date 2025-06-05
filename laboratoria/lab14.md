# Zapis i odczyt plików
  
Mozliwość pracy z plikami pozwala tworzyć znacznie bardziej uzyteczne programy, poniewaz efekty działania programu zostają zachowane po jego zakończeniu i mozna je łatwo udostępnić dalej. W C++ niezbędne do tego celu klasy i funkcje znajdują się w nagłówku `fstream`. Uzywamy: 
- `std::ifstream` – wejście (plik do odczytu)
- `std::ofstream` – wyjście (plik do zapisu)
- `std::fstream` – zarówno wejście, jak i wyjście
W przypadku plików, musimy dodatkowo zadbać o otworzenie i zamykanie strumienia w odpowiednim momencie (czego nie trzeba robić w przypadku pracy z konsolą, czyli strumieniami `std::cin` oraz `std::cout`), jak równiez obługę sytuacji, gdy pliku nie udało się otworzyć.
  
## Praca z plikami tekstowymi
Zapis do pliku tekstowego `.txt`:
```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream file("dane.txt");
    if (!file) {
        std::cerr << "Nie udalo sie otworzyc pliku\n";
        return 1;
    }

    file << "Hello world!\n";
    file << 101 << " " << 3.1417 << "\n" << 'a';
    file.close();

    return 0;
}
```
  
Odczyt z pliku tekstowego:
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("dane.txt");
    if (!file) {
        std::cerr << "Nie udalo sie otworzyc pliku\n";
        return 1;
    }

    std::string word;
    int number;
    double pi;

    file >> word >> number >> pi;

    std::cout << "Tekst: " << word << "\n";
    std::cout << "Liczba: " << number << "\n";
    std::cout << "Pi: " << pi << "\n";

    inFile.close();

    return 0;
}
```
Operator `>>` domyślnie dzieli dane wg białych znaków - spacji, znaku nowej linii lub tabulatora. Do oddzielania danych wg innego separatora nalezy uzyć funkcji `std::getline(file, line, separator)`.

## Praca z plikami binarnymi
Zapis do pliku wprzypadku trybu binarnego wymaga uzycia specjalnej funkcji `reinterpret_cast<char*>(&source)` do konwersji danych:
```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ofstream outFile("data.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Nie udalo sie otworzyc pliku\n";
        return 1;
    }

    int number = 1234;
    char p = 'p';

    outFile.write(reinterpret_cast<char*>(&number), sizeof(number));
    outFile.write(reinterpret_cast<char*>(&p), sizeof(p));
    outFile.close();

    return 0;
}
```
Podobnie w przypadku odczytu z pliku binarnego:
```cpp
#include <iostream>
#include <fstream>

int main() {
    std::ifstream inFile("data.bin", std::ios::binary);
    if (!inFile) {
        std::cerr << "Nie udalo sie otworzyc pliku\n";
        return 1;
    }

    int number;
    char p;

    inFile.read(reinterpret_cast<char*>(&number), sizeof(number));
    inFile.read(reinterpret_cast<char*>(&p), sizeof(p));

    std::cout << "Odczytana liczba: " << number << "\n";
    std::cout << "Odczytany znak: " << p << "\n";

    file.close();
    return 0;
}
```
  
Zapis binarny jest znacznie bardziej wydajny pamięciowo, dlatego jest preferowany, gdy chcemy zapisać instancje utworzonych w programie obiektówdo ich późniejszego odtworzenia. Zapis tekstowy wybieramy, gdy wyjściowy plik programu ma być czytelny i uzyteczny poza kontekstem programu (np. dać się otworzyć w edytorze tekstowym, arkuszu kalkulacyjnym itd.).

## Zapis binarny obiektów klasy
Aby zapisać i odczytać obiekty klas w trybie binarnym, najczęściej (wg konwencji, nie jest to obowiązek) zapisuje się rozmiar obiektu na początku pliku, a następnie jego dane, poniewaz w przeciwieństwie do trybu tekstowego, tryb binarny nie posiada oczywistych separatorów danych, takich jak spacje czy znak nowej linii. Dodatkowo trzeba uwazać na zapisanie istotnych danych, które dają się odtworzyć w nowym programie. Oznacza to np. ze zapisując obiekt typu `std::string`, zapisujemy sam przechowywany łańcuch znakowy, a nie cały obiekt (w tym wskaźnik na ten łańcuch przechowywany wewnętrznie przez tę klasę).  
Zapis do pliku
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string text = "Moj przykladowy tekst";

    std::ofstream outFile("textdata.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Nie udalo sie otworzyc pliku.\n";
        return 1;
    }

    size_t length = text.size();
    outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));  // zapis rozmiaru
    outFile.write(text.c_str(), length);  // zapis samych danych

    outFile.close();
    return 0;
}
```
Odczyt z pliku
```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inFile("textdata.bin", std::ios::binary);
    if (!inFile) {
        std::cerr << "Nie udalo sie otworzyc pliku.\n";
        return 1;
    }

    size_t length;
    inFile.read(reinterpret_cast<char*>(&length), sizeof(length));

    std::string text(length, '\0'); 
    inFile.read(&text[0], length);

    std::cout << "Odczytano tekst: " << text << "\n";

    inFile.close();
    return 0;
}
```
  
## Tryby otwarcia pliku
- `ios::in` - plik do odczytu (domyślnie przy `ostream`)
- `ios::out` - plik do zapisu (domyślnie przy `istream`)
- `ios::app` - dopisanie za końcem pliku (*append*)
- `ios::trunc` - nadpisanie zawartości
- `ios::binary` - tryb binarny
Tryby otwarcia funkcjonują jako bitowe flagi - łączymy np. tryb do zapisu na końcu pliku przez `ios::out | ios::app`
  
# Zadania
Rozwiązania zadań z laboratorium 12. i 13. zmień tak, aby pracowały na plikach tekstowych, zamiast danych wpisanych w kod programu (np. odczytwały liczby, słowa, nazwiska studentów, wyniki lotka itd. z pliku i zapisywały wyniki działania do pliku).

