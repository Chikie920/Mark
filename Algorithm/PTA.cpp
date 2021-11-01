#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    char ch;
    int i=0;
    int j=0;
    int results=0;
    vector<int> places;
    string place[] = {"yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    while((ch=cin.get())!='\n'){
        results+=ch-'0';
    }

    while(1){
        places.push_back(results%10);
        results/=10;
        if(!results){
            break;
        }
    }

    for(int i=places.size()-1; i>=0; --i){
        cout<<place[places[i]-1];
        if(i==0){
            break;
        }
        cout<<" ";
    }

    return 0;
}