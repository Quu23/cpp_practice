#include <iostream>

/*
内容：
ユーザーから整数 n（1 ≤ n ≤ 100）を入力として受け取り、
続いて n 個の整数を配列として受け取ってください。

その配列を 昇順（小さい順）にソートし、
1行にすべての要素を空白区切りで出力してください。
*/

void printArray(int array[100],int len);

void swap(int array[100],int firstIndex,int secondIndex);

int findMinIndex(int array[100],int startIndex,int endIndex);

void bubbleSort(int array[100],int len);

void selectionSort(int array[100],int len);

void insertSort(int array[100],int len);

int main(){
    int num;
    int inputs[100];
    int sum=0;
    int sumSquare=0;

    std::cin >> num;
    for(int i=0;i<num;i++){
        std::cin >> inputs[i];
    }

    //sort
    // bubbleSort(inputs,num);
    // selectionSort(inputs,num);
    insertSort(inputs,num);

    printArray(inputs,num);

}

void printArray(int array[100],int len){
    for(int i=0;i<len;i++){
        std::cout << array[i] << " ";
    }
}

void swap(int array[100],int firstIndex,int secondIndex){
    int tmp = array[firstIndex];
    array[firstIndex] = array[secondIndex];
    array[secondIndex] = tmp;
}

int findMinIndex(int array[100],int startIndex,int endIndex){
    int minIndex = startIndex;

    for(int i=startIndex;i<=endIndex;i++){
        minIndex = array[i] < array[minIndex] ? i : minIndex;
    }
    return minIndex;
}

void bubbleSort(int array[100],int len){
    for(int i=0;i<len-1;i++){
        for(int j=i+1;j<len;j++){
            if(array[j] < array[i]){
                swap(array,i,j);
            }
        }
    }
}

void selectionSort(int array[100],int len){
    for(int i=0;i<len-1;i++){
        int minIndex = findMinIndex(array,i,len-1);
        swap(array,i,minIndex);
    }
}

void insertSort(int array[100],int len){
    for(int i=1;i<len;i++){
        // int startShiftIndex=-1;
        // int target = array[i];
        
        // for(int j=0;j<i;j++){
        //     if(array[j] > array[i]){
        //         startShiftIndex = j;
        //         break;
        //     }
        // }
        // if(startShiftIndex==-1) continue; //-1だから挿入もシフトしない.

        // for(int j=i-1;j>=startShiftIndex;j--){
        //     array[j+1] = array[j];
        // }
        // array[startShiftIndex] = target;


        // 一般的な方法
        int target = array[i];
        int j = i-1;
        while(j>=0 && array[j] > target){
            array[j+1] = array[j];
            j--;
        }
        array[j+1]=target;
    }
}