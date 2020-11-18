#include <iostream>
int main(void)
{
    int sum = 0;
    int n = 50;
    while(n<=100){
        sum+=n;
        ++n;
    }
    std::cout << "50-100的和为:" << sum << std::endl;
    return 0;
}