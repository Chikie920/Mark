#include <iostream>
#include <vector>

using namespace std;

const int INF = 999;
const int SIZE = 7;

class Node {
public:
    Node():use(false), minWeight(INF), parent(-1){}
    Node(int sub):subScript(sub), use(false), minWeight(INF), parent(-1){}
public:
    int subScript;
    bool use;
    int minWeight;
    int parent;
};

void InitMatrix(vector<vector<int>> &P, vector<Node> &S);
void prim(vector<vector<int>> &P, vector<Node> &S);
void OutPut(const vector<Node> &S);

int main()
{
    vector<vector<int>> P;
    vector<Node> S;
    InitMatrix(P, S);
    S[0].use = true;
    S[0].minWeight = 0;
    for(int i = 0; i < SIZE; ++i){
        prim(P, S);
    }
    OutPut(S);

    return 0;
}

void InitMatrix(vector<vector<int>> &P, vector<Node> &S)
{
    P ={
        {0, 50, 60, INF, INF, INF, INF},
        {50, 0, INF, 65, 40, INF, INF},
        {60, INF, 0, 52, 40, INF, INF},
        {INF, 65, 52, 0, 50, 30, 42},
        {INF, 40, INF, 50, 0, 70, INF},
        {INF, INF, INF, 30, 70, 0, INF},
        {INF, INF, 45, 42, INF, INF, INF}
    };

    for(int n = 0; n < SIZE; ++n){
        S.push_back(n);
    }
    
}

void prim(vector<vector<int>> &P, vector<Node> &S)
{
    int sub, sub_next;
    for(int i = 0; i < SIZE; ++i){
        int min = INF;
        if(S[i].use){
            for(int j = 0; j < SIZE; ++j){
                if(!S[j].use && P[i][j] < min && P[i][j] != INF){
                    min = P[i][j];
                    sub = i;
                    sub_next = j;
                }
            }
        }
    S[sub_next].use = true;
    S[sub_next].minWeight = P[sub][sub_next];
    S[sub_next].parent = sub;
    }
}

void OutPut(const vector<Node> &S)
{
    for(int i = 0; i < SIZE; ++i){
        cout << "下标: " << S[i].subScript << " 权值: " << S[i].minWeight << " 父节点: " << S[i].parent << endl;
    }
}