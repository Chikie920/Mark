#include <iostream>
#include <vector>

using namespace std;

const int INF = 999; //定义最大值
const int MAXSIZE = 7; //矩阵大小
const int origin_sub = 3; //初始结点下标

class Node {
public:
    Node():use(false), weight(INF){}
    Node(int weight_update):weight(weight_update), use(false){}
    //构造函数，初始化数据成员
public:
    bool use;
    int weight;
};

void init_weight(vector<vector<int>> &, vector<Node> &); //初始化目标矩阵，与初始点关于其他点的矩阵
int min_weight(const vector<vector<int>> &, const vector<Node> &);
void update(const vector<vector<int>> &, vector<Node> &);
void dijkstra(const vector<vector<int>> &, vector<Node> &);

int main()
{
    vector<Node> S;
    vector<vector<int>> matrix_weight;
    init_weight(matrix_weight, S);
    S[3].use = true; //设置初始点
    printf("Dijkstra算法求最短路实现\n");
    dijkstra(matrix_weight, S);

    return 0;
}

void init_weight(vector<vector<int>> &matrix_weight, vector<Node> &S)
{
    matrix_weight = {{0, 12, INF, INF, INF, 16, 14}, 
                    {12, 0, 10, INF, INF, 7, INF},
                    {INF, 10, 0, 3, 5, 6, INF},
                    {INF, INF, 3, 0, 4, INF, INF},
                    {INF, INF, 5, 4, 0, 2, 8},
                    {16, 7, 6, INF, 2, 0, 9},
                    {14, INF, INF, INF, 8, 9, 0}
                    }; //带权邻接矩阵

    for(int i = 0; i < MAXSIZE; ++i){
        Node temp(matrix_weight[origin_sub][i]);
        S.push_back(temp);
    } //初始化与初始结点的路径权值、使用情况矩阵
}

int min_weight(const vector<vector<int>> &matrix_weight, const vector<Node> &S)
{
    int min = INF;
    int sub;
    for(int i = 0; i < MAXSIZE; ++i){
        if(!S[i].use){
            if(min > S[i].weight){
                min = S[i].weight;
                sub = i;
            }
        }
    }

    return sub;
} //返回最小权值点下标

void update(const vector<vector<int>> &matrix_weight, vector<Node> &S)
{
    int min_sub = min_weight(matrix_weight, S); //得到最小权值下标
    S[min_sub].use = true;
    for(int i = 0; i < MAXSIZE; ++i){
        if(matrix_weight[min_sub][i] != 0 && matrix_weight[min_sub][i] != INF && !S[i].use){
            S[i].weight = S[min_sub].weight + matrix_weight[min_sub][i] < S[i].weight ? S[min_sub].weight + matrix_weight[min_sub][i] : S[i].weight;
            //更新S矩阵的权
        }
    }
}

void dijkstra(const vector<vector<int>> &matrix_weight, vector<Node> &S)
{
    for(int i = 0; i < MAXSIZE-1; ++i){
        update(matrix_weight, S);
    }

    for(int i = 0; i < MAXSIZE; ++i){
        printf("距初始点的最短路径权值分别为%d\n", S[i].weight);
    }
}