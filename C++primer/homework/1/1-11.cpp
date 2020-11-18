#include <iostream>
int main(void)
{
    int a, b, max, min;

    std::cout << "input two number:" << std::endl;
    std::cin >> a >> b;

    if(a<b){
        max = b;
        min = a+1;
    } else {
        max = a;
        min = b+1;
    }

    while(min < max){
        std::cout << min << std::endl;
        ++min;
    }

    return 0;
}