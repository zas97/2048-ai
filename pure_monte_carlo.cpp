#include "pure_monte_carlo.h"

int shuffled_possible_moves[] = {0, 1, 2, 3};
const int POSSIBLE_MOVES[] = {0, 1, 2, 3};
static const float TIME_LIMIT_PER_MOVE = 0.0333;
static const bool PROFILE = true;

using namespace std;

int test_import(){
    return 42;
}

int pure_MC_time_constrained(board_t board){
    int best_move;
    float best_score = -1;
    for(int mv=0; mv < 4; mv++){
        board_t board_moved = execute_move(mv, board);
        float sum_scores = 0;
        int nb_runs = 0;
        if(board_moved != board){
            struct timeval start, finish;
            gettimeofday(&start, NULL);
            double elapsed = 0;
            while(elapsed < TIME_LIMIT_PER_MOVE){
                board_t tile = draw_tile();
                board_t new_board = insert_tile_rand(board_moved, tile);
                sum_scores += rollout(new_board);
                gettimeofday(&finish, NULL);
                elapsed = (finish.tv_sec - start.tv_sec);
                elapsed += (finish.tv_usec - start.tv_usec) / 1000000.0;
                nb_runs++;
            }
            if(PROFILE){
                cout<< "runs done:" << nb_runs <<endl;
            }
        }
        float score_move = sum_scores / nb_runs;
        if(score_move > best_score){
            best_score = score_move;
            best_move = mv;
        }
    }
    return best_move;
    
}

board_t do_random_move(board_t board){
    random_shuffle(shuffled_possible_moves, shuffled_possible_moves+4);
    for(int it = 0; it < 4; it++) {
        board_t new_board = execute_move(shuffled_possible_moves[it], board);
        if(new_board != board){
            return new_board;
        }
    }
    return board;
}

float rollout(board_t board){
    while(1){
        board_t board_moved = do_random_move(board);
        if(board_moved == board){
            break;
        }
        board_t tile = draw_tile();
        board = insert_tile_rand(board_moved, tile);
    }
    return score_board(board);
}

board_t do_greedy_move(board_t board){
    board_t best_board = board;
    float best_score = -1;
    random_shuffle(shuffled_possible_moves, shuffled_possible_moves+4);
    for(int mv=0; mv < 4; mv++){
        board_t moved = execute_move(shuffled_possible_moves[mv], board);
        float score = score_board(moved);
        if(score > best_score && moved != board){
            best_board = moved;
            best_score = score;
        }
    }
    return best_board;
}


float greedy_rollout(board_t board){
    while(1){
        board_t board_moved = do_greedy_move(board);
        if(board_moved == board){
            break;
        }
        board_t tile = draw_tile();
        board = insert_tile_rand(board_moved, tile);
    }
    return score_board(board);
}


int greedy_pure_MC_time_constrained(board_t board){
    int best_move;
    float best_score = -1;
    for(int mv=0; mv < 4; mv++){
        board_t board_moved = execute_move(mv, board);
        float sum_scores = 0;
        int nb_runs = 0;
        if(board_moved != board){
            struct timeval start, finish;
            gettimeofday(&start, NULL);
            double elapsed = 0;
            while(elapsed < TIME_LIMIT_PER_MOVE){
                board_t tile = draw_tile();
                board_t new_board = insert_tile_rand(board_moved, tile);
                sum_scores += greedy_rollout(new_board);
                gettimeofday(&finish, NULL);
                elapsed = (finish.tv_sec - start.tv_sec);
                elapsed += (finish.tv_usec - start.tv_usec) / 1000000.0;
                nb_runs++;
            }
            if(PROFILE){
                cout<< "runs done:" << nb_runs <<endl;
            }
        }
        float score_move = sum_scores / nb_runs;
        if(score_move > best_score){
            best_score = score_move;
            best_move = mv;
        }
    }
    return best_move;
    
}
