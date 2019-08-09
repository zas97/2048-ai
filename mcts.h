#pragma once
#include "2048.h"
#include "pure_monte_carlo.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

const double TIME_LIMIT = 0.1;

class NodeAfterRandom;
class NodeAfterMove;

class Node{
    public:
        Node(board_t b);

        virtual float expand() = 0;

        virtual void build_childs() = 0;

        board_t get_board(){
            return board;
        }
    protected:
        board_t board;
        float sum_scores;
        int nb_visits;
};

class NodeAfterRandom : public Node{
    public:
        NodeAfterRandom(board_t b);

        float expand();

        void build_childs();

        void update_score(float new_score);

        ~NodeAfterRandom(){
            #ifdef DEBUG
            cout<<"afterRandom I dont want to die"<<endl;
            #endif
        }

        vector<NodeAfterMove*> get_childs(){
            return childs;
        }

    protected:
        vector<NodeAfterMove*> childs;
};

class NodeAfterMove : public Node{
    public:
        NodeAfterMove(board_t b);

        float expand();

        void build_childs();

        void update_score(float new_score);

        float get_score();

        ~NodeAfterMove(){
            #ifdef DEBUG
            cout<<"afterMove I dont want to die"<<endl;
            #endif
        }

    private:
        vector<NodeAfterRandom*> childs;
};

int get_best_move_mcts(board_t board);


void clear_news();

int get_best_move_mcts(board_t board);

void clear_news();