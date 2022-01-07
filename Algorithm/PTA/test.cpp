#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    vector<int> power;
    cin>>n;
    for(int i=0; i<n; ++i){
        int temp;
        cin>>temp;
        power.push_back(temp);
    }
    sort(power.begin(), power.end());
    int min = power[0];
    int max = power[n-1];
    int min_counts = 1;
    int max_counts = 1;
    for(int j=1; power[j]==min; ++j){
        min_counts++;
    }
    for(int k=n-2; power[k]==max; --k){
        max_counts++;
    }
    cout<<min<<" "<<min_counts<<endl;
    cout<<max<<" "<<max_counts<<endl;

    return 0;
}