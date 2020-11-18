#include <iostream>
int main(void)
{
    int a, b, max, min;
    std::cout << "input two numbers:" << std::endl;
    std::cin >> a >> b;
    if(a<b){
        max = b;
        min = a+1;
    } else {
        max = a;
        min = b+1;
    }
    for(;min < max;++min){
        std::cout << min << std::endl;
    }
    return 0;
}