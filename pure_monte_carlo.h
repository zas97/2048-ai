#pragma once
#include "2048.h"



int test_import();
float rollout(board_t board);
int pure_MC_time_constrained(board_t board);
board_t do_random_move(board_t board);
board_t do_greedy_move(board_t board);
float greedy_rollout(board_t board);
int greedy_pure_MC_time_constrained(board_t board);
