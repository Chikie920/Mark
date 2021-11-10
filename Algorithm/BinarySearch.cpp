#include <iostream>
#include <algorithm>

using namespace std;

void BinarySearch(int x, int n, int *array)
{
    int l=0, r=n-1;
    while(l<=r){ //注意等号是必须的
        int mid=(l+r)/2;
        if(array[mid]==x){
            cout<<mid;
            return;
        } else if(array[mid]>x){
            r=mid-1;
        } else {
            l=mid+1;
        }
    }
}


int main()
{
    const int MAX_SIZE = 50;
    int array[MAX_SIZE] = {0};
    int n;
    int x;
    cin>>n>>x;
    for(int i=0; i<n; ++i){
        cin>>array[i];
    }
    sort(array, array+n-1); //使用二分搜索需要对数组排序，使用STL sort函数即可
    BinarySearch(x, n, array);
    return 0;
}