#include <iostream>

/*
ユーザーから正の整数 n を1つ入力として受け取り、
1 から n までの整数のうち、以下の条件を満たす数を出力してください：

3の倍数だが5の倍数ではない数

出力は1行ずつ、昇順で表示してください。
*/

int main(){
    int input;

    std::cout << "入力:";
    std::cin  >> input;

    for(int i=1;i<=input;i++){
        if(i%3==0 && i%5!=0){
            std::cout << i << "\n";
        }
    }
}