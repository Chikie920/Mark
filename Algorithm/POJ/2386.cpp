#include <iostream>
using namespace std;

const int N = 12;
const int M = 6;

char yard[M][N] = {
    {"#**########"},
    {"##*###**###"},
    {"##*###**###"},
    {"###########"},   
    {"#*###**####"},
    {"#*####**###"},   
};

void DFS(int i, int j)
{
    yard[i][j]='#'; //更改积水处
    for(int x=-1; x<=1; ++x){
        for(int y=-1; y<=1; ++y){
            if(i+x>=0&&i+x<M&&j+y>=0&&j+y<N&&yard[i+x][j+y]=='*'){
                DFS(i+x, j+y);
            }
        }
    } //遍历积水处的四周，若有积水则继续递归调用DFS，四周位置需要满足在园子范围内
}

int main()
{
    int ans=0;
    for(int i=0; i<M; ++i){
        for(int j=0; j<N; ++j){
            if(yard[i][j]=='*'){
                DFS(i, j);
                ans++;
            }
        }
    } //遍历行与列，查找积水处，调用DFS函数
    cout<<ans<<endl;
    return 0;
}