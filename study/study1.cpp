#include <iostream>
using namespace std;
/*
ユーザーから2つの整数を入力として受け取り、大きい方の値を出力するプログラムを作成してください。
ただし、2つの値が同じ場合には「Equal」と出力してください。
*/

int main(){
    int a;
    int b;
    // std::cin >> a;
    // std::cin >> b;
    std::cin >> a >> b;

    if (a > b){
        std::cout << a;
    }else if(a < b){
        std::cout << b;
    }else{  
        std::cout << "Equal"s;
    }
}