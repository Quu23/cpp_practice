#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
using Matrix = std::vector<std::vector<int>>;

void make_random(int board[4][4]);

void print_array(int board[4][4]);

void solve(int board[4][4]);

void rotate(int board[4][4], int start_i, int start_j, int radius);

int main(){
    int board[4][4] = {
        {0,1,2,3},
        {0,1,2,3},
        {4,5,6,7},
        {4,5,6,7},
    };
    std::cout << "\n";

    print_array(board);
    std::cout << "\n";

    // make_random(board);
    rotate(board, 0, 0, 4);

    print_array(board);
    std::cout << "\n";
}

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

void rotate(int board[4][4], int start_i, int start_j, int radius){

    if(start_i < 0 || start_i > 3 || start_j < 0 || start_j > 3 || radius < 2 || radius > 4){
        std::cout << "s_i=" << start_i << "/ s_j=" << start_j << "/ radius=" << radius << '\n';
        throw std::runtime_error("out of index OR out of radius");
    }
    if(start_i + radius > 4 || start_j + radius > 4){
        std::cout << "s_i+radius=" << start_i+radius << "/ s_j+radius=" << start_j+radius << '\n';
        throw std::runtime_error("out of sum of index");
    }

    Matrix temp_mini_board(radius,std::vector<int>(radius));
    for (int i = start_i; i < start_i+radius; i++){
        for (int j = start_j; j < start_j+radius; j++){
            temp_mini_board[i-start_i][j-start_j] = board[i][j];
        }
    }
    
    for (int i = 0; i < radius; i++) {
        for (int j = 0; j < radius; j++) {
            board[j + start_j][radius - i - 1 + start_i] = temp_mini_board[i][j];
        }
    }
}

void solve(int board[4][4]){

}

void print_array(int board[4][4]) {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}

