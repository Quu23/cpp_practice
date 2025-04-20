#include <iostream>

/*
ユーザーから整数 n（1 ≤ n ≤ 100）を1つ入力として受け取り、その後 n 個の整数を入力として受け取ってください。
それらの整数を 配列に格納し、逆順 に出力してください。
*/

int main(){
    int num;
    std::cin >> num;
    int inputs[100];
    for(int i=0;i<num;i++){
        std::cin >> inputs[i];
    }

    for(int i=0;i<num/2;i++){
        int tmp = inputs[i];
        inputs[i] = inputs[num-i-1];
        inputs[num-i-1] = tmp;
    }

    // 表示用
    for(int i=0;i<num;i++){
        std::cout << inputs[i] <<" ";
    }
}