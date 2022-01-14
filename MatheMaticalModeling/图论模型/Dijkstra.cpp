#include <iostream>
#include <string.h>

using namespace std;

const int MAX_SIZE = 20;
int route[MAX_SIZE][MAX_SIZE];
int visitd[MAX_SIZE];
int dis[MAX_SIZE];
int parent[MAX_SIZE];

/*


注意：
    输入矩阵时，当不存在边时，用-1代替


*/

int main()
{
    memset(route, 1, sizeof(route));
    memset(visitd, 0, sizeof(visitd));
    memset(dis, 1, sizeof(dis));
    memset(parent, -1, sizeof(parent));
    // 初始化集合

    int N;
    cout<<"输入节点个数:"<<endl;
    cin>>N;
    cout<<"输入图像矩阵:"<<endl;
    int temp;
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            cin>>temp;
            if(temp == -1){
                continue;
            }
            route[i][j] = temp;
        }
    }
    // 输入矩阵

    int start;
    cout<<"输入起始点:"; // 注意：点编号从0开始
    cin>>start;

    visitd[start] = 1;
    dis[start] = 0;
    // 初始化起始点

    int pre = start;
    for(int i=0; i<N-1; ++i){
        for(int j=0; j<N; ++j){
            if(j==pre || visitd[j]){
                continue;
            }
            if(dis[pre]+route[pre][j] < dis[j]){
                dis[j] = dis[pre]+route[pre][j];
                parent[j] = pre;
            }
        } // 更新操作

        int max_v = 0x7FFFFFFF;
        int index;
        for(int i=0; i<N; ++i){
            if(visitd[i]){
                continue;
            }
            if(max_v > dis[i]){
                max_v = dis[i];
                index = i;
            }
        } // 搜索操作

        visitd[index] = 1;
        pre = index;
        // 添加操作
    }

    cout<<"距离向量: ";
    for(int i=0; i<N; ++i){
        cout<<dis[i]<<" ";
    }
    cout<<endl;

    cout<<"父节点向量: ";
    for(int i=0; i<N; ++i){
        cout<<parent[i]<<" ";
    }
    cout<<endl;

    return 0;
}

/*
测试矩阵

0 4 -1 -1 -1 -1 -1 8 -1
4 0 8 -1 -1 -1 -1 3 -1
-1 8 0 7 -1 4 -1 -1 2
-1 -1 7 0 9 14 -1 -1 -1
-1 -1 -1 9 0 10 -1 -1 -1
-1 -1 4 14 10 0 2 -1 -1
-1 -1 -1 -1 -1 2 0 6 6
8 3 -1 -1 -1 -1 6 0 1
-1 -1 2 -1 -1 -1 6 1 0

*/