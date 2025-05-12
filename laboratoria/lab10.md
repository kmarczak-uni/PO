# Wyjątki

W rzeczywistych programach często dochodzi do błędów. Mogą to być na przykład:
- wykonanie niepoprawnej operacji, np. dzielenie przez zero
- nieprawidłowe dane wejściowe podane przez uzytkownika
- plik, który miał zostać otwarty, nie istnieje lub jest niedostępny
- brak miejsca na dysku lub pamięci RAM potrzebnej do działania

Do tej pory radziliśmy sobie z takimi sytuacjami, wypisując komunikaty o błędach lub zwracając kody błędów. Przykładowo, funkcja `main` zazwyczaj zwraca kod type `int`, który informuje, czy program zakończył się poprawnie. To podejście działa, ale nie jest wygodne - zwłaszcza gdy program staje się bardziej złożony. Lepszym rozwiązaniem jest wprowadzenie specjalnych obiektów reprezentujących błąd, czyli wyjątków.
  
Najprostsze, dotychczas stosowane podejście do obsługi błędów:
  
Przykład 1: Dzielenie przez zero z komunikatem błędu
```cpp
#include <iostream>

int main() {
    int a = 10; 
    int b = 0;

    if (b == 0) {
        std::cerr << "Error: Division by zero!" << std::endl;
        return 1;
    }

    std::cout << a / b << std::endl;
    return 0;
}
```
  
To wystarcza do działania programu, ale jego logika zostaje przerwana przez obsługę błędów, co nie jest zbyt czytelne ani wygodne.
Wyjątki pozwalają na lepsze oddzielenie logiki samego programu (zadania, które ma wykonać) od obsługi ewentualnych błędów.
  
Przykład 2: uzycie wyjątku
```cpp
#include <iostream>

int main() {
    int a = 10;
    int b = 0;

    if (b == 0) {
        throw "Division by zero!";
    }

    std::cout << a / b << std::endl;
    return 0;
}
```
Używamy słowa kluczowego `throw`, aby zasygnalizować, że coś poszło nie tak. Jak przechwycić taki wyjątek, tzn. gdzie i jak umieścić kod odpowiedzialny za obsługę tego błędu?
  
Aby obsłużyć wyjątek, otaczamy fragment programu, który może go zgłosić blokiem `try`, a następnie dodajemy jeden lub więcej bloków `catch` do obsługi konkretnych typów wyjątków.

```cpp
#include <iostream>

int main() {
    try {
        int a = 10;
        int b = 0;

        if (b == 0) {
            throw "Division by zero!";
        }

        std::cout << a / b << std::endl;
    }
    catch (const char* msg) {
        std::cerr << "Caught an exception: " << msg << std::endl;
    }

    return 0;
}
```
  
# Typy wyjątków
Można zgłaszać różne typy obiektów jako wyjątki, jednak najlepiej jest korzystać z gotowych typów wyjątków z biblioteki standardowej lub tworzyć własne klasy wyjątków, gdy potrzebujemy większej kontroli.  

## Typy biblioteczne

Jak już zostało pokazane powyzej, mozna rzucić wyjątek w postaci napisu `(const char*)`. To wystarcza w prostych przykładach, ale w złozonych programach warto stosować bardziej rozbudowane mechanizmy, np. klasy biblioteczne. Biblioteka standardowa zawiera wiele gotowych klas wyjątków (pochodzących od jednej wspólnej klasy bazowej `std::exception`).
  
```cpp
#include <iostream>
#include <stdexcept>

int getElement(int index) {
    if (index < 0 || index >= 5) {
        throw std::out_of_range("Index out of range");
    }
    return index;
}

int main() {
    try {
        std::cout << getElement(10) << std::endl;
    }
    catch (const std::out_of_range & e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}
```

## Własne typy wyjątków

Można również tworzyć własne klasy wyjątków, dziedzicząc po `std::exception` i nadpisując metodę `what()`:
```cpp
#include <iostream>
#include <exception>

class MyError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Something went wrong in MyError!";
    }
};

int main() {
    try {
        throw MyError();
    }
    catch (const MyError & e) {
        std::cerr << "Caught custom exception: " << e.what() << std::endl;
    }
}
```

## Bloki `catch`

Można używać wielu bloków `catch`, aby obsługiwać różne typy wyjątków. Uwaga: kolejność bloków ma znaczenie, poniewaz wykonany zostanie **pierwszy pasujący do przechwyconego wyjątku** blok `catch`.  
**Przykład 1 - błędny!**
```cpp
try {
    throw std::out_of_range("Index out of range");
}
catch (const std::exception & e) {
    std::cerr << "General exception: " << e.what() << std::endl;
}
catch (const std::out_of_range & e) { // ten blok nigdy nie zostanie wykonant
    std::cerr << "Out of range exception: " << e.what() << std::endl;
}
```
**Przykład 2 - poprawna kolejność bloków `catch`**
```cpp
try {
    throw std::out_of_range("Index out of range");
}
catch (const std::out_of_range & e) {
    std::cerr << "Out of range: " << e.what() << std::endl;
}
catch (const std::exception & e) {
    std::cerr << "General: " << e.what() << std::endl;
}
```
# Podsumowanie
1. Nalezy stosować wyjątki, aby oddzielić logikę programu od logiki obsługi błędów.
2. Nalezy przechwytywać wyjątki przez referencję `(const exception_type &)`, a nie przez wartość.
3. Najczęściej nalezy uzywać standardowych klas wyjątków (`std::runtime_error`, `std::logic_error`, itp.) a własne klasy tworzyć tylko wtedy, gdy potrzebujemy zawrzeć w obiekcie wyjątku dodatkowe dane.
4. Kolejność bloków `catch` ma bardzo duze znaczenie: najpierw typy szczegółowe (klas pochodnych), potem ogólne (klas bazowych).
5. Własne wyjątki nalezy tworzyć przez dziedziczenie po `std::exception` i nadpisanie metody `what()`.

# Zadania
Uwaga: w celu wybrania wyjątku bibliotecznego mozna wykorzystać listę wyjątków z (dokumentacji)[https://en.cppreference.com/w/cpp/error/exception].
1. Do klasy `Fraction` dopisz `operator[]`. W jego implementacji zastosuj odpowiedni wyjątek biblioteczny w przypadku wyjścia poza zakres `0-1`.
2. Wykonaj to samo zadanie dla klasy `MyString` (własnej implementacji typu `std::string` z poprzednich zajęć).
3. Do następującej klasy:
```cpp
class BankAccount {
private:
    double balance;
public:
    BankAccount(double balance);
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
};
```
- użyj odpowiedniego wyjątku w sytuacji próby wpłacenia ujemnej kwoty
- napisz własną klasę wyjątku `InsufficientFunds`, który będzie rzucany w przypadku próby pobrania większej kwoty, niż przechowywana na koncie.
4. Rozbuduj wyjątek `InsufficientFunds` tak, aby w treści komunikatu o błędzie wypisywał wartość, która spowodowała błąd: np. `"Insufficient fund, tried to withdraw amount = 99999"`.
5. Utwórz klasę bazową `AppException` oraz dwie klasy pochodne: `FileException` i `NetworkException`. Napisz funkcję, która losowo wyrzuca jeden z tych wyjątków. Obsłuż wyjątki za pomocą odpowiednich bloków `catch` tak, aby kazdy możliwy wyjątek został obsłużony.
