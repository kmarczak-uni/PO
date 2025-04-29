# Dziedziczenie cd. - klasy abstrakcyjne

Na poprzednich zajęciach pisaliśmy klasę bazową `Shape`, z której dziedziczyły pozostałe klasy figur. Problem definicji metod `area()` i `perimeter()` w klasie `Shape` mozna chwilowo rozwiązać (a raczej obejść), np. zwracając wartość `0`, gdyz konkretne obliczenia delegowane są do klas pochodnych. Klasa `Shape` właściwie słuzy tylko do tego, by móc utworzyć wskaźniki tego typu, ale konkretne instancje obiektów zawsze są klas pochodnych, np. `Circle` lub `Triangle`. Czy w takim razie jest sens tworzyć instancje klasy `Shape` i "udawać" implementacje metod liczących pole i obwód?  
Rozwiązaniem tego problemu są metody czysto wirtualne oraz klasy abstrakcyjne. Metoda czysto wirtualna to metoda, która nie podaje zadnej definicji - nie określa nic poza typem zwracanym, nazwą i argumentami, pozostawiając decyzję nt. implementacji klasie pochodnej. Aby zadeklarować taką metodę, stosujemy następującą składnię:  

```cpp
class Shape {
    public:
      virtual void calculateArea() = 0;  // uwaga: brak ciala metody { }, nawet pustego!
};
```

Kazda klasa, która posiada chociaz jedną czysto wirtualną metodę zadeklarowaną w powyzszy sposób, staje się **klasą abstrakcyjną**. Nie jest mozliwe utworzenie instancji klasy abstrakcyjnej - jest ona zdefiniowana tylko po to, by umozliwiać tworzenie wskaźników na swój typ (bo deklaracja wskaźnika np. klasy `Shape` nie tworzy obiektu tej klasy).

### Zadania
1. Zmień klasę `Shape` tak, aby metody tej klasy były czysto wirtualne, następnie przetestuj ponownie funkcję `main()`. Czy program działa tak samo? Spróbuj utworzyć instancję klasy `Shape`.
2. Dopisz abstrakcyjną klasę bazową `PaymentMethod` dla ponizszych klas i wprowadź odpowiednie dziedziczenie. Następnie napisz program, który pozwala uzytkownikowi wprowadzić z klawiatury wybraną opcję płatności i ją wywołuje.

```cpp
class CreditCardPayment {
private:
    std::string cardNumber;
    double balance;
public:
    CreditCardPayment(const std::string& number, double bal)
        : cardNumber(number), balance(bal) {}

    bool authorize(double amount) override {
        return balance >= amount;
    }

    void pay(double amount) override {
        balance -= amount;
        std::cout << "Zaplacono " << amount << " z uzyciem karty kredytowej o numerze " << cardNumber << "\n";
    }
};

class PaypalPayment {
private:
    std::string email;
    double balance;
public:
    PaypalPayment(const std::string & email, double balance)
        : email(email), balance(balance) {}

    bool authorize(double amount) override {
        return balance >= amount;
    }

    void pay(double amount) override {
        balance -= amount;
        std::cout << "Zaplacono " << amount << " przez konto PayPal (" << email << ")\n";
    }
};

class CashPayment {
public:
    bool authorize(double) override {
        return true;
    }

    void pay(double amount) override {
        std::cout << "Zaplacono " << amount << " gotowka\n";
    }
};


```
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
