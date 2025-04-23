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
