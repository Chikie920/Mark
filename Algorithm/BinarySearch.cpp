#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10;
const int MAX_SIZE = 50;
int a[MAX_SIZE] = {3, 5, 9, 2, 11, 23, 8, 45, 32, 43};

int BinarySearch(int *a, int b)
{
    int l = 0, r = N-1;
    while(l<r){
        int i = (l+r)/2;
        if(a[i]==b){
            return i;
        } else if(a[i]<b){
            l = i+1;
        } else {
            r = i;
        }
    }
    return -1;
}

int main()
{
    int b;
    cin>>b;
    sort(a, a+N);
    cout<<BinarySearch(a, b)<<endl;

    return 0;
}