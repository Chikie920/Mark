#include <iostream>
int main(void)
{
    int sum = 0, n;
    std::cout << "input numbers(q to quit):";
    while(std::cin >> n){
        sum += n;
    }
    std::cout << sum << std::endl;
    return 0;
}