#include <iostream>
#include <string.h>


using namespace std;

const int MAX_SIZE = 20;
int route[MAX_SIZE][MAX_SIZE];

/*


注意：
    输入矩阵时，当不存在边时，用-1代替


*/

int main()
{
    memset(route, 1, sizeof(route));
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

    for(int i=0; i<N; ++i){ // 遍历次数或遍历各点或当前点
        for(int j=0; j<N; ++j){ // 其他各点到当前点
            for(int k=0; k<N; ++k){ // 当前点到其他各点
                if(i==j || j==k || i==k){
                    continue;
                } // 优化
                if(route[j][i]+route[i][k] < route[j][k]){
                    route[j][k] = route[j][i]+route[i][k];
                }
            }
        }
    }

    cout<<"结果为"<<endl;
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            cout<<route[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}

/*
测试矩阵：
0 3 8 -1 -4
-1 0 -1 1 7
-1 4 0 -1 -1
2 -1 -5 0 -1
-1 -1 -1 6 0
*/
