#include <iostream>
int main(void)
{
    int sum;
    for(int n = 50;n<=100;++n){
        sum += n;
    }
    std::cout << sum <<std::endl;
    return 0;
}