#include <iostream>

/*
ユーザーから整数 n（1 ≤ n ≤ 100）を1つ入力として受け取り、
その後 n 個の整数を入力として受け取ってください。

その配列の中から

最大値

最小値

をそれぞれ出力してください。
出力形式は以下のとおりです：

max=最大値
min=最小値
*/

int main(){
    int num;
    int inputs[100];
    int max;
    int min;

    std::cin >> num;
    for(int i=0;i<num;i++){
        std::cin >> inputs[i];
    }

    max=inputs[0];
    min=inputs[0];

    for(int i=0;i<num;i++){
        if(inputs[i] > max) max = inputs[i];
        if(inputs[i] < min) min = inputs[i];
    }

    std::cout << "max=" << max << "\n";
    std::cout << "min=" << min << "\n";
}