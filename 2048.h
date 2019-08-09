#pragma once
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include <algorithm>
#include <iostream>
#include <array>        // std::array
#include <random>
#include <vector>
#include <numeric>
#include "config.h"
#include "platdefs.h"


/* The fundamental trick: the 4x4 board is represented as a 64-bit word,
 * with each board square packed into a single 4-bit nibble.
 * 
 * The maximum possible board value that can be supported is 32768 (2^15), but
 * this is a minor limitation as achieving 65536 is highly unlikely under normal circumstances.
 * 
 * The space and computation savings from using this representation should be significant.
 * 
 * The nibble shift can be computed as (r,c) -> shift (4*r + c). That is, (0,0) is the LSB.
 */

typedef uint64_t board_t;
typedef uint16_t row_t;

//store the depth at which the heuristic was recorded as well as the actual heuristic
struct trans_table_entry_t{
    uint8_t depth;
    float heuristic;
};

static const board_t ROW_MASK = 0xFFFFULL;
static const board_t COL_MASK = 0x000F000F000F000FULL;

void print_board(board_t board);

static inline board_t unpack_col(row_t row);

static inline row_t reverse_row(row_t row);

board_t insert_tile_rand(board_t board, board_t tile) ;
board_t draw_tile();

board_t do_random_move(board_t board);
static inline board_t transpose(board_t x);
static int count_empty(board_t x);
void init_tables();

static inline board_t execute_move_0(board_t board);
static inline board_t execute_move_1(board_t board);
static inline board_t execute_move_2(board_t board);
static inline board_t execute_move_3(board_t board);
board_t execute_move(int move, board_t board);

static inline int get_max_rank(board_t board);
static inline int count_distinct_tiles(board_t board);

float score_board(board_t board);

board_t initial_board();

typedef int (*get_move_func_t)(board_t);
void evaluate_multiple_games(get_move_func_t get_move, int nb_games);






/* Functions */
// #ifdef __cplusplus
// extern "C" {
// #endif

// DLL_PUBLIC void init_tables();

// DLL_PUBLIC float score_toplevel_move(board_t board, int move);
// DLL_PUBLIC int find_best_move(board_t board);
// DLL_PUBLIC int ask_for_move(board_t board);
// DLL_PUBLIC void play_game(get_move_func_t get_move);

// #ifdef __cplusplus
// }
// #endif
