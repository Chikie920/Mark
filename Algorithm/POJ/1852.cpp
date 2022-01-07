#include <iostream>
using namespace std;

const int MAX_SIZE = 10000;

void ants(int *dis, int n, int l)
{
    int max_v=0;
    int min_v=0;
    for(int i=0; i<n; ++i){
        max_v=max(max_v, max(dis[i], l-dis[i]));
    }

    for(int j=0; j<n; ++j){
        min_v=max(min_v, min(dis[j], l-dis[j]));
    }
    cout<<max_v<<" "<<min_v<<endl;
}

int main()
{
    int n;
    int l;
    int dis[MAX_SIZE]={0};
    cin>>n>>l;
    for(int i=0; i<n; ++i){
        cin>>dis[i];
    }
    ants(dis, n, l);
    return 0;
}