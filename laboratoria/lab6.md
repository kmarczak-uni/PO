# Dziedziczenie cd. - metody wirtualne

W zalinkowanym w zeszłym tygodniu [artykule](https://www.programiz.com/cpp-programming/function-overriding) poruszony był problem przesłaniania nazw metod z klasy bazowej w klasie pochodnej.

```cpp
#include <iostream>

class Base {
   public:
    void print() const {
        std::cout << "Base Function" << std::endl;
    }
};

class Derived : public Base {
   public:
    void print() const {
        std::cout << "Derived Function" << std::endl;
        // w razie potrzeby, mozemy odwolac sie bezposrednio do wersji print() z klasy bazowej
        // Base::print();
    }
};

int main() {
    Base base1;
    base1.print();

    Derived derived1;
    derived1.print();  // wykona kod metody klasy pochodnej
    // istnieje mozliwosc odwolania sie do metody bazowej przez klase Derived rowniez za posrednictwem obiektu:
    derived1.Base::print();  // wykona kod metody klasy bazowej

    return 0;
}
```
  
Co się stanie, jeśli zamiast statycznie utworzonych obiektów, posłuzymy się wskaźnikami na obiekt? 
  
```cpp
int main() {
    Derived derived1;

    Base * basePtr = &derived1;
    Derived * derivedPtr = &derived1;

    basePtr->print();
    derivedPtr->print();

    return 0;
}
```
  
Chociaz istnieje mozliwość utworzenia dwóch typów wskaźnika, który wskazuje na obiekt klasy `Derived` (czyli zarówno wskaźnika typu `Base *`, jak i `Derived *`), to wywołanie pozornie tej samej metody przez te wskaźniki ma inny efekt. Wywołanie `basePtr->print()` wykonuje metodę z klasy bazowejm pomimo ze wskazywany obiekt jest instancją klasy `Derived`.  
Jezeli chcemy móc odwoływać się za pomocą wskaźników klasy bazowej do metody właściwej dla faktycznego typu wskazywanego obiektu, musimy w klasie bazowej zdefiniować metodę `print()` jako **wirtualną**.  
  
```cpp
#include <iostream>

class Base {
public:
   // definicja metody wirtualnej - slowo kluczowe virtual
    virtual void print() const {
        std::cout << "Base Function" << std::endl;
    }
};

class Derived : public Base {
public:
    void print() const {
        std::cout << "Derived Function" << std::endl;
    }
};

int main() {
    Derived derived1;

    Base * basePtr = &derived1;
    Derived * derivedPtr = &derived1;

    basePtr->print();
    derivedPtr->print();

    return 0;
}
```
  
Dzięki metodzie wirtualnej, wywołanie metody `print()` za pomocą wskaźnika typu `Base` poprawnie wywołuje wersję metody zgodną z faktycznym typem wskazywanego obiektu, czyli `Derived`.

### Destruktory wirtualne

Aby zapewnić poprawne usuwanie obiektów klasy pochodnej, kazda klasa bazowa, która zezwala na dziedziczenie po sobie, powinna  deklarować swój destruktor jako wirtualny. Brak takiej deklaracji w przypadku klasy skutkuje brakiem wywołania wszystkich koniecznych destruktorów. Porównaj ponizsze przykłady:

Przykład 1 - błędny
```cpp
class Base {
public:
    ~Base() {
        std::cout << "Destruktor Base\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Destruktor Derived\n";
    }
};

int main() {
    Base* b = new Derived();
    delete b; // uwaga - tylko wywolanie destruktora Base, czyli niepoprawne zwolnienie pamieci!
}
```
  
Przykład 2 - poprawny
```cpp
class Base {
public:
    virtual ~Base() {
        std::cout << "Destruktor Base\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Destruktor Derived\n";
    }
};

int main() {
    Base* b = new Derived();
    delete b;
}
```
  
Uwaga: deklaracja destruktora wirtualnego nie jest potrzebna, jeśli klasa jest zadeklarowana jako `final` - ten zapis oznacza, ze nie mozna z takiej klasy dziedziczyć.
```cpp
#include <iostream>

class Base final {
   public:
    void print() const {
        std::cout << "Base Function" << std::endl;
    }
};

class Derived : public Base {  // blad kompilacji
```
  
### Słowo kluczowe override
  
Przy nadpisywaniu metody z klasy bazowej wskazane jest (tzn. zalecane, choć nie wymagane przez składnię języka) uzycie słowa `override`. Taka deklaracja pomaga nam w prawidłowy sposób nadpisać metodę. Nadpisanie wymaga od nas, aby sygnatury metody nadpisywanej były zgodne, to znaczy w klasie bazowej i pochodnej nadpisana metoda ma ten sam zwracany typ, te same argumenty i te same modyfikatory (np. jeśli nadpisujemy metodę `const`, to musimy równiez uzyc `const` w klasie pochodnej). Dodanie deklaracji `override` sprawia, ze kompilator "przypilnuje nas" i w razie przeoczenia zgłosi niezgodność sygnatur. Porównaj ponizsze przykłady:
  
Przykład 1 - błędny
```cpp
// brak deklaracji override - bledne nadpisanie metody print() przez pominiecie slowa const
class Base {
public:
    virtual void print() const {
        std::cout << "Base Function" << std::endl;
    }
    
    virtual ~Base() { }
};

class Derived : public Base {
public:
    void print() {
        std::cout << "Derived Function" << std::endl;
    }
};

int main() {
    Derived derived1;

    Base * basePtr = &derived1;
    Derived * derivedPtr = &derived1;

    basePtr->print();
    derivedPtr->print();

    return 0;
}
```
  
Przykład 2 - poprawny
```cpp
// deklaracja override - kompilator zglasza przeoczenie (niezgodnosc sygnatur)
class Base {
   public:
    virtual void print() const {
        std::cout << "Base Function" << std::endl;
    }
};

class Derived : public Base {
   public:
    void print() override {
        std::cout << "Derived Function" << std::endl;
    }
};

int main() {
    Derived derived1;

    Base * basePtr = &derived1;
    Derived * derivedPtr = &derived1;

    basePtr->print();
    derivedPtr->print();

    return 0;
}
```
  
Uzycie `override`, podobnie jak `const` w przypadku metod niemodyfikujących obiektów, nie jest konieczne aby program zadziałał, ale zdecydowanie zalecane jako lepszy styl programowania. W kolejnych rozwiązaniach zadań proszę stosować obydwie deklaracje wszędzie tam, gdzie powinny się znaleźć. **Szczególnie wskazane jest uzycie `override` wtedy, gdy metoda jest wirtualna**.
  
  
### Zadanie
1. Popraw poprzednie zadanie z klasami symulującymi konta bankowe tak, aby uzyć deklaracji `virtual` i `override` wszędzie tam, gdzie powinny być uzyte. Przetestuj zmiany, tworząc wskaźnik do klasy bazowej oraz po 1 obiekcie kazdej z klas, następnie wykonaj kilka działań na kazdym koncie (wpłata, wypłata, wypisanie informacji) **za pomocą wskaźnika na klasę bazową**.
2. Do dotychczas napisanych 3 klas figur geometrycznych (`Circle`, `Rectangle` i `Triangle`) napisz klasę bazową (np. `Shape`), z której mają dziedziczyć te klasy. Wskazówka: Klasa bazowa powinna posiadać składowe, które są wspólne dla klas pochodnych (mogą to być same metody) i być napisana tak, by wskaźnik typu `Shape` na obiekt klasy pochodnej wywoływał odpowiednie metody z klasy pochodnej.  
  
Przykład uzycia prawidłowo napisanych klas figur:
```cpp
int main() {
    Triangle t1(3, 4, 5);
    Circle c1;
    Rectangle r1(2, 3);

    Shape * shapes[3];
    shape[0] = &t1;
    shape[1] = &c1;
    shape[2] = &r1;

    for (int i=0; i < 3; i++) {
        std::cout << "Pole = " << shapes[i]->area() << '\n';
        std::cout << "Obwod = " << shapes[i]->perimeter() << '\n';
    }

    return 0;
}
```

### Zadanie domowe
1. Utwórz 3 klasy, które będą w uproszczony sposób reprezentować pracowników w firmie. Stwórz klasę `Employee` z polami `name`, `id` i `baseSalary`. Dodaj do niej metody `calculateSalary()` oraz `printDetails()`. Następnie utwórz klasy:
   - `Manager` z polem `bonus`, które zwiększa pensję
   - `Intern` z pensją zależną od liczby godzin (`hoursWorked`)
W funkcji `main()` utwórz kilka obiektów powyzszych klas oraz tablicę wskaźników na typ `Employee`. Wyświetl szczegóły i pensje wszystkich pracowników za pomocą wskaźników.
