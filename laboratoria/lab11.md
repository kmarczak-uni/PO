# Szablony

Szablony to mechanizm C++, który pozwala pisać funkcje i klasy, gdzie typ danych jest parametrem. Dzięki temu zamiast pisać osobne wersje dla `int`, `float`, `char`, itd., można napisać jeden uniwersalny kod, który zadziała z dowolnym typem.  
Szablony umożliwiają programowanie uogólnione (ang. *generic programming*) — pisanie kodu, który działa dla wielu typów danych.
Mozemy tworzyć: 
- funkcje szablonowe - uniwersalne funkcje dla różnych typów,
- klasy szablonowe - uniwersalne struktury danych.
  
## Funkcje szablonowe
Przykład 1 - uniwersalna funkcja `swap`
```cpp
template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swapValues(x, y);
    std::cout << "After swap: x = "<< x << ", y = " << y << std::endl;

    char a = 'A', b = 'B';
    swapValues(a, b);
    std::cout << "After swap: a = "<< a << ", b = " << b << std::endl;

    return 0;
}
```
Szablony nie są "gotowymi" funkcjami ani klasami. Kompilator generuje właściwą wersję dopiero w przypadku uzycia szablonu z konkretnymi typami (w przykładzie powyzej, wygenerowane zostaną dwie funkcje -jedna dla typu`int`, druga dla tpu `char`).
Uwaga - przy pisaniu szablonów łatwo jest o błędy. Jeśli operacje uzyte w szablonie nie mają sensu dla jakiegoś typu (np. operator `>` dla obiektów, które nie mają przeciązonego tego operatora), błąd pojawi się dopiero przy próbie użycia szablonu z tym typem.
Szablony są elastyczne, ale trzeba uważać, by używać w nich tylko operacji dostępnych dla przewidzianych typów danych.

### Zadanie - funkcje szablonowe
1. Napisz funkcję szablonową `max`, która przyjmie dwa argumenty i zwróci większy z nich na wyjściu. Przetestuj jej działanie na wybranym typie wbudowanym i na klasie np. std::string. Następnie spróbuj wywołać ją z obiektami jednej z klas, których nie da się porównać (`Circle`, `BankAccount` lub inna) i zaobserwuj zwrócone przez kompilator błędy.

## Klasy szablonowe
Analogicznie do funkcji szablonowych, mozemy tworzyć tez klasy szablonowe. Podobnie jak funkcje, są one parametryzowane typem danych, który przyjmują.  
Prosty przykład klasy szablonowej `Box` przechowującej dowolny typ danych:
```cpp
template <typename T>
class Box {
private:
    T value;

public:
    void set(const T & val) {
        value = val;
    }

    T get() const {
        return value;
    }
};

int main() {
    Box<int> intBox;
    intBox.set(42);

    Box<char> charBox;
    charBox.set('Z');
    char z = charBox.get();

    return 0;
}
```
  
### Zadania - klasy szablonowe
1. Zaimplementuj szablonową klasę `Stack`, która będzie reprezentować strukturę danych stosu. Klasa posiada następujące metody: `push` do umieszczania danych na stosie, `pop` do usuwania i zwracania ostatniego elementu i `isEmpty` do sprawdzenia, czy stos jest pusty. Oprócz tablicy danych, stos ma przechowywać swoją maksymalną pojemność określaną atrybutem `capacity` oraz atrybut `topIndex` do przechowywania indeksu ostatnio umieszczonego elementu.
  
  
# Zadanie domowe
1. Napisz funkcję szablonową, która sortuje otrzymaną w argumencie tablicę danych. Mozna wykorzystać dowolny algorytm sortowania (jednym z prostszych jest np. sortowanie bąbelkowe). Przetestuj jej działanie na tablicach obiektów wybranej przez siebie klasy. Jakie operacje musi implementować dana klasa, by mozna było posortować tablicę jej obiektów?
2. Zaimplementuj uproszczoną szablonową klasę `Map`, która będzie reprezentować strukturę danych zwaną mapą lub słownikiem (przykładem takiej struktury jest typ `dict` z języka Python). Klasa ta jest parametryzowana dwoma typami i posiada następujące metody: `get(T1 &  key)` do pobrania wartości pod kluczem `key`, metodę `put(const T1 & key, const T2 & value)` do zapisania w mapie pary klucz-wartość oraz `contains(const T1 & key)` do sprawdzenia, czy mapa zawiera dany klucz (zwraca prawda/fałsz). Do realizacji zadania podobnie jak w przypadku stosu klasa powinna przechowywać swoją maksymalną pojemność określoną w konstruktorze oraz liczbę zapisanych w danym momencie rekordów.
3. Ulepsz klasy `Stack` i `Map` tak, aby zezwalały na zwiększenie swojej maksymalnej pojemności w momencie próby dodania nowego rekordu do wypełnionej struktury danych (np. stos z 10 elementami i limitem = 10 powiększa się dynamicznie przy próbie dodania 11. elementu.)
