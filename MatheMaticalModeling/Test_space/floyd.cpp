////// 注意: 本算法可能写的有问题 //////

#include <iostream>
#include <vector>

using namespace std;

const int INF = 999; //设置最大值
const int MAXSIZE = 4; //设置矩阵大小

void init_weight(vector<vector<int>> &, vector<vector<int>> &); //初始化原始的带权邻接矩阵，和用于后续修改的矩阵
void floyd(vector<vector<int>> &, int);
void result(const vector<vector<int>> &);

int main()
{
    cout << "Floyd弗洛伊德算法求任意两结点与其他结点的最短路径实现" << endl;
    vector<vector<int>> P;
    vector<vector<int>> S;
    init_weight(P, S);
    for (int i = 0; i < MAXSIZE; ++i)
    {
        floyd(S, i);
    }
    result(S);
    return 0;
}

void init_weight(vector<vector<int>> &P, vector<vector<int>> &S)
{
    P = {
        {0, 2, 6, 4},
        {INF, 0, 3, INF},
        {7, INF, 0, 1},
        {5, INF, 12, 0}
        };
    S = P;
}

void floyd(vector<vector<int>> &S, int sub)
{
    for (int i = 0; i < MAXSIZE; ++i)
    {
        if (i == sub)
        {
            continue;
        }
        for (int j = 0; j < MAXSIZE; ++j)
        {
            if (j == sub || i == j)
            {
                continue;
            }
            S[i][j] = S[i][sub] + S[sub][j] < S[i][j] ? S[i][sub] + S[sub][j] : S[i][j];
        }
    }
}

void result(const vector<vector<int>> &S)
{
    for (int i = 0; i < MAXSIZE; ++i)
    {
        for (int j = 0; j < MAXSIZE; ++j)
        {
            cout << S[i][j] << " ";
        }
        cout << endl;
    }
}