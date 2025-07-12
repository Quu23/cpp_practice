#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <array>

using namespace std;
using Matrix = std::vector<std::vector<int>>;

void make_random(int board[4][4]);

void print_array(int board[4][4]);

void solve_first(int board[4][4]);

void solve_second(int board[4][4]);

void solve_third(int board[4][4]);

void solve_forth(int board[4][4]);

//start_i, start_j は領域の左上隅の添え字
void solve(int board[4][4]);

void rotate(int board[4][4], int start_i, int start_j, int radius);

std::array<int, 2> rotate(std::array<int, 2> indexes, int start_i, int start_j, int radius);

std::array<int, 2> rotate(int i, int j, int start_i, int start_j, int radius);

std::array<int, 2> search_pair(int board[4][4], int color, int color_i, int color_j);

int get_side_index(int i, int j, int direction);

int get_side_index(std::array<int, 2> indexes, int direction);

int rotate_count = 0;

int main(){
    /*
        {0,0,1,1,},
        {2,2,3,3,},
        {4,4,5,5,},
        {6,6,7,7,},
    */
    int board[4][4] = {
{1,5,6,2,},
{0,1,0,4,},
{6,2,7,4,},
{7,3,3,5,},
    };
    std::cout << "\n" << "count = " << rotate_count << "\n\n";

    print_array(board);
    std::cout << "\n" << "count = " << rotate_count << "\n\n";

    make_random(board);
    // print_array(board);
    // rotate(board, 1, 1, 3);

    print_array(board);
    std::cout << "\n" << "count = " << rotate_count << "\n\n";

    solve(board);

    print_array(board);
    std::cout << "\n" << "count = " << rotate_count << "\n\n";
}

void make_random(int board[4][4]){
    int color_num = 4 * 4 / 2; //マスの和/2

    std::vector<int> temp_vec;

    for (int i=0;i<color_num;i++){
        temp_vec.push_back(i);
        temp_vec.push_back(i);
    }

    std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
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
            board[i + start_i][j + start_j] = temp_mini_board[radius - j - 1][i];
        }
    }

    rotate_count++;

    std::cout << "=====\n";
    print_array(board);
    std::cout << "\n" << "count = " << rotate_count << "\n\n";
}

// memo : 多分回転1のやつも(Do Nothingとして)実装しておくと, プログラムの分がよりエレガントに書けそう.
std::array<int, 2> rotate(std::array<int, 2> indexes, int start_i, int start_j, int radius){
    int i_rel = indexes[0] - start_i;
    int j_rel = indexes[1] - start_j;

    indexes[0] = j_rel + start_i;
    indexes[1] = radius - 1 - i_rel + start_j;

    return indexes;
}

std::array<int, 2> rotate(int i, int j, int start_i, int start_j, int radius){
    std::array<int, 2> indexes = {-1, -1};
    int i_rel = i - start_i;
    int j_rel = j - start_j;

    indexes[0] = j_rel + start_i;
    indexes[1] = radius - 1 - i_rel + start_j;
    return indexes;
}

std::array<int, 2> search_pair(int board[4][4], int color, int color_i, int color_j){
    // [0] ... i, [1] ... j
    std::array<int, 2> pair_indexes = {-1,-1};
    
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(i == color_i && j == color_j) continue;
            if(board[i][j] == color){
                pair_indexes[0] = i;
                pair_indexes[1] = j;
                return pair_indexes;
            }
        }
    }

    throw std::runtime_error("Probably, the board does not have pair.");    
}

void solve(int board[4][4]){
    solve_first(board);
    solve_second(board);
    solve_third(board);
    solve_forth(board);
    std::cout << "===end===\n";
}

void solve_first(int board[4][4]){
    std::array<int, 2> first_pair_indexes = search_pair(board, board[3][3], 3 , 3);

    if(first_pair_indexes[1] == 3){
        if(first_pair_indexes[0] == 2) return; // すでにそろっている.
        rotate(board, first_pair_indexes[0], first_pair_indexes[0] + 1, 3 - first_pair_indexes[0]);
        return;
    }

    // (3,3)の上辺とpairの左辺が含まれる領域を探す.
    for(int r = 2; r <= 3; r++){
        if(first_pair_indexes[1] == 3 - (r - 1) && first_pair_indexes[0] < 3 && first_pair_indexes[0] >= 3 - r){
            rotate(board, 3 - r, 3 - (r - 1), r);

            // 領域上の左上隅以外なら二回回転.
            if(first_pair_indexes[0] != 3 - r) {
                rotate(board, 3 - r, 3 - (r - 1), r);
                first_pair_indexes = rotate(first_pair_indexes, 3 - r, 3 - (r - 1), r);
            }
            first_pair_indexes = rotate(first_pair_indexes, 3 - r, 3 - (r - 1), r);

            // この時点でfirst_pairは3列目にあるはず.
            if (first_pair_indexes[0] != 3 - 1) rotate(board, first_pair_indexes[0], first_pair_indexes[0] + 1, 3 - first_pair_indexes[0]);
            // この時点で, 一つ揃った.
            return;
        }
    }

    // 以下は, 4x4の左辺下辺か, (0,2)のどちらか.
    if (first_pair_indexes[0] == 0 && first_pair_indexes[1] == 2){
        rotate(board, first_pair_indexes[0], first_pair_indexes[1], 2);
        rotate(board, 0, 1, 3);
        return;
    }

    // 4x4の左辺下辺
    // i = 3にあるものは回転させることで, j = 0の三つ(i = 0,1,2)に帰着できる.
    if (first_pair_indexes[0] == 3){
        rotate(board, 1, 0, 3);
        first_pair_indexes = rotate(first_pair_indexes, 1, 0, 3);
        if (first_pair_indexes[0] == 3){
            rotate(board, 1, 0, 3);
            first_pair_indexes = rotate(first_pair_indexes, 1, 0, 3);
        }
    }
    // j = 0の三つ.
    if (first_pair_indexes[1] == 0 && first_pair_indexes[0] < 2){
        rotate(board, 0, 0, 3);
        first_pair_indexes = rotate(first_pair_indexes, 0, 0, 3);
        rotate(board, 0, 1, 3);
        first_pair_indexes = rotate(first_pair_indexes, 0, 1, 3);
        // 多分これで場合分けを計算に落とし込んだ.
        rotate(board, first_pair_indexes[0], 1 + first_pair_indexes[0], 3 - first_pair_indexes[0]);
        return;
    }
    if (first_pair_indexes[1] == 0 && first_pair_indexes[0] == 2){
        rotate(board, 1, 0, 3);
        rotate(board, 1, 1, 2);
        rotate(board, 1, 2, 2);
        rotate(board, 1, 2, 2); //二回でそろう.
        return;
    }
}

void solve_second(int board[4][4]){
    std::array<int, 2> second_pair_indexes = search_pair(board, board[0][3], 0 , 3);

    if(second_pair_indexes[0] == 1 && second_pair_indexes[1] == 3) return;

    std::cout << second_pair_indexes[0] << ", " << second_pair_indexes[1] << "\n";

    // i = 1　に帰着させる.
    if(second_pair_indexes[0] == 3){
        if(second_pair_indexes[1] != 0) rotate(board, 1, 0, 3);
        rotate(board, 1, 0, 3);

        if(second_pair_indexes[1] != 0) second_pair_indexes = rotate(second_pair_indexes, 1, 0, 3);
        second_pair_indexes = rotate(second_pair_indexes, 1, 0, 3);
    }

    // i = 0に帰着させる.
    if(second_pair_indexes[0] == 2){
        if(second_pair_indexes[1] == 0) rotate(board, 0, 0, 3);
        rotate(board, 0, 0, 3);

        if(second_pair_indexes[1] == 0) second_pair_indexes = rotate(second_pair_indexes, 0, 0, 3);
        second_pair_indexes = rotate(second_pair_indexes, 0, 0, 3);
    }

    // i = 0に帰着させる.
    if(second_pair_indexes[0] == 1){
        if(second_pair_indexes[1] == 0){
            rotate(board, 0, 0, 3);
            second_pair_indexes = rotate(second_pair_indexes, 0, 0, 3);
        }else if(second_pair_indexes[1] == 1){
            rotate(board, 0, 1, 2);
            second_pair_indexes = rotate(second_pair_indexes, 0, 1, 2);
        }else if(second_pair_indexes[2] == 2){
            rotate(board, 0, 1, 2);
            second_pair_indexes = rotate(second_pair_indexes, 0, 1, 2);
            rotate(board, 0, 1, 2);
            second_pair_indexes = rotate(second_pair_indexes, 0, 1, 2);
        }
    }

    // ここで, そろえてみる.
    if(second_pair_indexes[0] == 0){
        if (second_pair_indexes[1] < 2){
            rotate(board, 0, second_pair_indexes[1], 3 - second_pair_indexes[1]);
        }
        rotate(board, 0, 2, 2);
    }
}


// memo: なんとなくだけど, 添え字の和を使うとうまく条件かけるのか？
// memo: 仮に, 与えられた二つのマスの距離を評価するときには, 回転に対称性がないことを留意して評価しないといけなさそう.

/*
方針: すでにj=3列はそろっているから, i=0,1,j=2に揃えたい. 基準色をi=0,j=2としておく.
凡例 (i,j)
(0,1)に揃える場合(pattern 1)と, (1,2)に揃える場合(pattern 2)
pattern 1: i=0が対象. (0,1)に揃え, (0,1)で2マス回転.
pattern 2: (1,2)に揃える.
*/ 
void solve_third(int board[4][4]){
    std::array<int, 2> third_pair_indexes = search_pair(board, board[0][2], 0, 2);
    
    // pattern 1
    if(third_pair_indexes[0] == 0){
        if(third_pair_indexes[1] == 0) rotate(board, 0, 0, 2);
        rotate(board, 0, 1, 2);
        return;
    }

    // pattern 2
    // まずは外側L字型から
    if(third_pair_indexes[0] == 3 || third_pair_indexes[1] == 0){
        // いったん, (2,0), (3,1)は別の場所に帰着させる.
        if(third_pair_indexes[0] == 2 && third_pair_indexes[1] == 0){
            rotate(board, 1, 0, 2);
            third_pair_indexes = rotate(third_pair_indexes, 1, 0, 2);   
        }else if(third_pair_indexes[0] == 3 && third_pair_indexes[1] == 1){
            rotate(board, 2, 0, 2);
            third_pair_indexes = rotate(third_pair_indexes, 2, 0, 2);   
        }
        for(int i = 0; i < (third_pair_indexes[0]+third_pair_indexes[1] + 1)/2; i++)rotate(board, 1, 0, 3); //i+jは1,3,5しかないから, +1して2で割った分がちょうど回転数.
        return;
    }

    // 内側
    for(int i = 0; i < third_pair_indexes[0]+third_pair_indexes[1] - 1; i++)rotate(board, 1, 1, 2); //i+jは2,3,4しかないから, -1した分がちょうど回転数.
}

/*
方針: i = 0のときは, 2 - j回(0,0)で半径2回転させ, i = 1に帰着させる.
i > 0のときは, i=1のときは(1,0)で, それ以外は(2,0)で適当な回数回転させる.
=> (2,1)に集めたら, それを(2,1)で2マス回転.
*/ 
void solve_forth(int board[4][4]){
    std::array<int, 2> forth_pair_indexes = search_pair(board, board[2][2], 2, 2);

    if(forth_pair_indexes[0] == 3 && forth_pair_indexes[1] == 2)return; // すでにそろっている.

    // i = 1に帰着.
    if(forth_pair_indexes[0] == 0){
        {
            int count = 2 - forth_pair_indexes[1]; // forth_pair_indexes[1]に依存するから保存しておく.
            for(int i = 0; i < count; i++){
                rotate(board, 0, 0, 2);
                forth_pair_indexes = rotate(forth_pair_indexes, 0, 0, 2);
            }
        }
    }

    if(forth_pair_indexes[0] == 1){
        for(int i = 0; i < 2 - forth_pair_indexes[1]; i++){
                rotate(board, 1, 0, 2);
        }
    }

    // i = 2,3のとき.
    for(int i = 0; i < forth_pair_indexes[0] + forth_pair_indexes[1] - 1; i++)rotate(board, 2, 0, 2); //i+jは2,3,4しかないから, -1したら回転数.

    rotate(board, 2, 1, 2); // これでそろう.
}

void print_array(int board[4][4]) {
    for (int i = 0; i < 4; i++){
        std::cout << "{";
        for (int j = 0; j < 4; j++){
            std::cout << board[i][j] << ",";
        }
        std::cout << "},\n";
    }
}

/** direction : Left 0 / Above 1 / Right 2 / Below 3*/
int get_side_index(int i, int j, int direction){
    if(direction > 3 || direction < 0) throw std::runtime_error("direction must be between 0 and 3!!");

    if(direction % 2 == 0){
        return direction == 0 ? 5 - j : 5 - j - 1;
    }else{
        return direction == 1 ? 5 - i : 5 - i - 1;
    }
}

/** direction : Left 0 / Above 1 / Right 2 / Below 3*/
int get_side_index(std::array<int, 2> indexes, int direction){
    return get_side_index(indexes[0], indexes[1], direction);
}
