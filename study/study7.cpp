#include <iostream>

/*
ユーザーから整数 n（1 ≤ n ≤ 100）を入力として受け取り、
続いて n 個の整数を配列として入力してください。

その後、整数 x を1つ入力として受け取り、
配列の中に x が含まれているかどうかを判定してください。

含まれていれば：
Found at index: インデックス番号（最初に見つかった位置）

含まれていなければ：
Not found

を出力してください。
（インデックス番号は 0 から始まるとします）
*/

int main(){
    int num;
    int inputs[100];
    int x;

    std::cin >> num;
    for(int i=0;i<num;i++){
        std::cin >> inputs[i];
    }

    std::cout << "Search for ";
    std::cin >> x;

    for(int i=0;i<num;i++){
        if(inputs[i]==x){
            std::cout << "Found at index:" << i;
            break;
        }else if(i==num-1){
            std::cout << "Not found ";
        }
    }
}