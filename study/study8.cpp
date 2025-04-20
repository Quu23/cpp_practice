#include <iostream>

// ユーザーから整数 n（1 ≤ n ≤ 100）を1つ入力として受け取り、
// その後 n 個の整数を配列に入力してください。

// その配列の 平均値（整数で出力） と
// 分散（整数で出力、小数点以下切り捨て） を計算し、以下の形式で出力してください。

// 出力形式：
// mean=平均値
// variance=分散

int main(){
    int num;
    int inputs[100];
    int sum=0;
    int sumSquare=0;

    std::cin >> num;
    for(int i=0;i<num;i++){
        std::cin >> inputs[i];
    }

    for(int i=0;i<num;i++){
        sum += inputs[i];
        sumSquare += inputs[i]*inputs[i];
    }

    std::cout << "mean=" << sum/num;
    std::cout << "\nvariance=" << (int)((sumSquare - sum * sum /(double)num)/num); //intキャストは最後に行わないと, 情報が失われる.
}