#include <iostream>

int main(void)
{
    int a, b;
    std::cin >> a >> b;
    std::cout << a;
    std::cout << "*";
    std::cout << b;
    std::cout << " = ";
    std::cout << a*b;
    return 0;
}