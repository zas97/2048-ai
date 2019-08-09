#include <iostream>
#include "2048.h"
#include "pure_monte_carlo.h"
#include "mcts.h"

using namespace std;


int main(){
    cout<< "ok3"<<endl;
    init_tables();
    board_t board = initial_board();
    cout<<greedy_rollout(board)<<endl;
    cout<<rollout(board)<<endl;
    evaluate_multiple_games(get_best_move_mcts, 100);
}