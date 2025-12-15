#include <iostream>
#include "../include/Vector.hpp"

int main()
{
    pe::Vector a(3.0, 4.0);
    pe::Vector b(1.0, 2.0);
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    auto c = a.add(b);
    std::cout << "a + b = " << c << "\n";
    std::cout << "dot(a,b) = " << a.dotProduct(b) << "\n";
    std::cout << "length(a) = " << a.length() << "\n";
    std::cout << "angle(a) = " << a.getAngle() << " degrees\n";
    std::cout << "a * 2 = " << a.multiply(2.0) << "\n";
    return 0;
}
