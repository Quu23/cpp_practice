#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
using Matrix = std::vector<std::vector<int>>;

void make_random(int board[4][4]){
    int color_num = 4 * 4 / 2; //マスの和/2

    std::vector<int> temp_vec;

    for (int i=0;i<color_num;i++){
        temp_vec.push_back(i);
        temp_vec.push_back(i);
    }

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(temp_vec.begin(), temp_vec.end(), engine);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = temp_vec[i * 4 + j];
        }
    }
}

void print_array(int board[4][4]) {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(){
    int board[4][4] = {
        {0,1,2,3},
        {0,1,2,3},
        {4,5,6,7},
        {4,5,6,7},
    };

    print_array(board);
    std::cout << "\n";

    make_random(board);

    print_array(board);
    std::cout << "\n";

}

