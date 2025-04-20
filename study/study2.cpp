#include <iostream>
using namespace std;
/*
ユーザーから整数を3つ入力として受け取り、以下を出力してください。

3つの合計

平均値（整数として小数点以下切り捨て）P
*/

int main(){
    int a;
    int b;
    int c;

    std::cin >> a >> b >> c;

    std::cout << "sum="s << a+b+c;

    std::cout << ",ave="s << (a+b+c)/3.0;
}