# Operatory - cd.

### Zadania
1. Zaimplementuj wszystkie operatory wykorzystane w funkcji main().

```cpp
#include <iostream>
#include <cmath>

class Point2D {
    double x, y;

public:
    Point2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    /*
      implementacja operatorow
    */
};

int main() {
    Point2D a(3, 4);
    Point2D b;

    std::cout << "Wpisz wspolrzedne punktu b (format: x y): ";
    std::cin >> b;

    std::cout << "\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";

    Point2D c = a + 2.0;
    Point2D d = a - 1.0;
    Point2D e = a * 3.0;
    Point2D f = a / 2.0;

    std::cout << "\n";
    std::cout << "a + 2.0 = " << c << "\n";
    std::cout << "a - 1.0 = " << d << "\n";
    std::cout << "a * 3.0 = " << e << "\n";
    std::cout << "a / 2.0 = " << f << "\n";

    std::cout << "\n";
    std::cout << "2.0 + b = " << 2.0 + b << "\n";
    std::cout << "5.0 - b = " << 5.0 - b << "\n";
    std::cout << "3.0 * b = " << 3.0 * b << "\n";
    std::cout << "10.0 / b = " << 10.0 / b << "\n";

    Point2D g(1, 1);
    std::cout << "g = " << g << "\n";
    g += 5;
    std::cout << "g += 5 -> " << g << "\n";
    g -= 2;
    std::cout << "g -= 2 -> " << g << "\n";
    g *= 3;
    std::cout << "g *= 3 -> " << g << "\n";
    g /= 2;
    std::cout << "g /= 2 -> " << g << "\n";

    std::cout << "\nPorownanie >/< w oparciu o odleglosc od punktu (0, 0):\n";
    std::cout << "a = " << a << ", odleglosc = " << a.distance() << "\n";
    std::cout << "b = " << b << ", odleglosc = " << b.distance() << "\n";

    std::cout << "a <  b: " << (a < b) << "\n";
    std::cout << "a <= b: " << (a <= b) << "\n";
    std::cout << "a >  b: " << (a > b) << "\n";
    std::cout << "a >= b: " << (a >= b) << "\n";

    std::cout << "\nRownosc punktow:\n";
    std::cout << "a == b: " << (a == b) << "\n";
    std::cout << "a != b: " << (a != b) << "\n";

    return 0;
}
```

