# Konfiguracja środowiska Visual Studio 20xx
Proszę uruchomić pierwszy przykładowy program w języku C++, zgodnie z poniższą instrukcją:  
[Tutorial](https://learn.microsoft.com/en-us/cpp/windows/walkthrough-creating-a-standard-cpp-program-cpp?view=msvc-160)  
Jako przykładowy program, można użyć poniższego fragmentu kodu:  
```cpp
#include <iostream>

int main()
{
    bool t = true;
    bool f = false;
    
    int a = 1, b = 2;
    auto c = a + b;

    std::cout << "Witaj!\n";

    return 0;
}
```
  
Więcej na temat typu auto w [tym artykule](https://learn.microsoft.com/en-us/cpp/cpp/auto-cpp?view=msvc-170), zwłaszcza sekcje Usefulness i Examples. (głównie dla osób znających już C++, wspomniane w nim zalety i ograniczenia takiej deklaracji będą w pełni zrozumiałe dopiero pod koniec semestru).  
  
# Referencje (aliasy)
Zmienna wskaźnikowa czyli wskaźnik do zmiennej:  
  
```cpp
int a = 1;
int * ptr_a;
ptr_a = &a;
```  

Referencja do zmiennej:  
```cpp
int a = 1;
int & ref_a = a;
```
  
Referencje pełnią podobną rolę, co wskaźniki - można o nich myśleć jak o stałych wskaźnikach (uwaga, nie wskaźnikach na stałą: jaka jest różnica?). Pozwalają one uprościć składnię programów.  
Najważniejsze różnice względem wskaźników:  
- Nie można tylko zadeklarować referencji, trzeba ją od razu zainicjalizować
- Raz zainicjalizowana referencja zawsze wskazuje na tę samą zmienną, nie może stać się aliasem innej zmiennej, niż ta wybrana przy inicjalizacji  
  
Czy w takim razie możemy całkowicie zastąpić wskaźniki referencjami? Jeśli nie, to dlaczego?

### Zadania
1. Przeanalizuj poniższy kod i wpisz w miejsce `?` wyjaśnienie, co zostaje wypisane w poszczególnych linijkach programu:
```cpp
int a = 1;
int & ref_a = a;
int * ptr_a = &a;

std::cout << "Wartosc zmiennej a: " << a << '\n';
std::cout << "Referencja do zmiennej a: " << ref_a << '\n';
std::cout << "Adres zmiennej a: " << &a << '\n';
std::cout << "?: " << &ref_a << '\n';
std::cout << "?: " << *ptr_a << '\n';
std::cout << "?: " << ptr_a << '\n';
std::cout << "?: " << &ptr_a << '\n';
``` 
  
2. Zmień poniższy program tak, by jego działanie było takie samo, ale z użyciem referencji zamiast wskaźników w argumentach funkcji `swap`:
  
```cpp
#include <iostream>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    std::cout << "Przed zamiana: x = " << x << ", y = " << y << std::endl;
    swap(&x, &y);
    std::cout << "Po zamianie: x = " << x << ", y = " << y << std::endl;
    return 0;
}
```
  
# Obsługa standardowego wejścia i wyjścia
Uwaga: chwilowo nie wnikamy, czym są elementy `std::cout` oraz `std::cin` (mały spoiler: obiektami) i dlaczego zamiast wywołania jakiejś funkcji, łączymy je z pozostałymi elementami programu za pomocą `<<` oraz `>>`. Wyjaśnimy to dokładniej za kilka tygodni.  
Jakie różnice względem języka C rzucają się w oczy? Czy operacje wejścia/wyjścia są bardziej czytelne?  
  
```cpp
#include <iostream>

int main()
{
    std::string studentName, instituteName;
    int studentAge;

    std::cout << "Podaj swoje imie: \n";
    std::cin >> studentName;
    std::cout << "Podaj swoj wiek: \n";
    std::cin >> studentAge;
    std::cout << "Podaj nazwe instytutu, w ktorym studiujesz: \n";
    std::getline(std::cin, instituteName);

    std::cout << "Witaj " << studentName << "!\n";
    std::cout << "Twoje imie ma " << studentName.length() << " liter.\n";
    std::cout << "Jego pierwsza litera to " << name[0] << std::endl;
    
    if (age >= 18) {
        std::cout << "Jestes pelnoletni.\n";
    }

    return 0;
}
```
  
### Zadania
1. Sprawdź w edytorze kodu, jakie jeszcze metody (czyli funkcje obiektu) są dostępne dla typu `std::string`, obok `length` w przykładzie powyżej. 
Spróbuj użyć metody `find`, by sprawdzić czy dany napis zawiera w sobie inny napis. Co oznacza widoczna w podpowiedzi edytora kodu informacja `+n overloads`? Co oznacza zwrócona z metody wartość? Do jakiego typu zmiennej możemy ją zapisać?  
Od czego należy zacząć rozwiązanie tego typu zadania?
2. Zabezpiecz powyższy program na wypadek podania przez użytkownika błędnego typu wartości przy pytaniu o wiek (prawidłowa wartość: typ int, zakres np. od 1 do 130). Następnie dodaj sprawdzenie, czy wprowadzone imię składa się tylko z liter alfabetu.  
Czy udało się znaleźć odpowiedź za pierwszym sformułowaniem zapytania do wyszukiwarki lub wybranego narzędzia AI? Jeśli nie, dlaczego? Czy proponowany kod jest czytelny (zrozumiały)? Czy udało się go po skopiowaniu skompilować i uruchomić, a jeśli nie, jaka może być tego przyczyna?  
3. Napisz program, który wypisze jakiś napis `std::string` (może być wprowadzony "na sztywno"/"hard-coded" w programie) od ostatniej litery do pierwszej, po jednej literze w linijce. Użyj do tego pętli `for` i odpowiednich metod napisu.  
4. Dowiedz się, czym różni się tworzenie nowej linii za pomocą `"\n"`oraz `std::endl`.  

# Dobre praktyki programistyczne
  
### Deklaracja przestrzeni nazw
Unikamy tego, co pojawia się w wielu przykładach online, tj. deklaracji na początku programu: `using namespace std;`  
Taka deklaracja początkowo trochę upraszcza składnię programów, pozwalając na używanie standardowej biblioteki bez przedrostka `std::`, ponieważ deklarujemy, że wszystkie napotkane w programie nazwy będą właśnie pochodzić z tej przestrzeni nazw:
```cpp
cout << "Hello world!";
string name;
cin >> name;
```  
Jest to jednak zły nawyk, który może sprawić kłopoty przy pisaniu większych, bardziej skomplikowanych programów, w których np. importujemy wiele bibliotek zawierających tak samo nazwane funkcje i/lub klasy.  
  
### Nazewnictwo zmiennych i funkcji
Standardem komercyjnym jest pisanie kodu w języku angielskim, również w komentarzach oraz wybierając nazwy tworzonych zmiennych i funkcji. Wszystkie przykłady na zajęciach będą się trzymać tej konwencji i jest to mile widziane (choć nie wymagane do zaliczenia) w rozwiązaniach przy odpowiedzi i na kolokwiach.  
Nazwy powinny być dobrane tak, by jednoznacznie wskazywały na to, do czego służy dana funkcja lub zmienna. Można wybrać konwencję camelCase lub snake_case (np. `accountNumber` lub `account_number`). Najważniejsze by trzymać się konsekwentnie wybranej konwencji w obrębie całego programu/projektu.  

# Zadanie domowe
1. Napisz program, który pozwoli użytkownikowi stworzyć swoją listę zadań (np. "zrobic zakupy", "odrobic zadanie domowe z programowania obiektowego" itd.) wpisując je z klawiatury. Przyjmij małą stałą liczbę zadań (np. 3) i użyj tablicy obiektów typu `std::string`. Na końcu program ma wypisać wszystkie podane zadania. Pamiętaj o stosowaniu dobrych praktyk wspomnianych powyżej.
