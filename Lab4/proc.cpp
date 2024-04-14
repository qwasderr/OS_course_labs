#include <iostream>
#include <unistd.h> 
using namespace std;
int main(){
    int a;
    cout<<getpid()<<endl;
    cout<<&a<<endl;
    while(1){
    cin>>a;
    }
}