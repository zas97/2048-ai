#include "mcts.h"

using namespace std;

#define PROFILE

unordered_map<board_t, NodeAfterRandom*> mem_after_random;
unordered_map<board_t, NodeAfterMove*> mem_after_move;

NodeAfterMove * get_or_create(board_t board){
    unordered_map<board_t, NodeAfterMove*>::iterator it;
    it = mem_after_move.find(board);
    if(it == mem_after_move.end()){
        NodeAfterMove * new_node = new NodeAfterMove(board);
        mem_after_move[board] = new_node;
        return new_node; 
    }
    return mem_after_move[board];
}

Node::Node(board_t b){
    board = b;
    sum_scores = 0;
    nb_visits = 0;
}


NodeAfterRandom::NodeAfterRandom(board_t b) : Node(b){}

float NodeAfterRandom::expand(){
    if(nb_visits == 0){
        float new_score = rollout(board);
        update_score(new_score);
        return new_score;
    }
    if(nb_visits == 1){
        build_childs();
    }
    float new_score;
    if(childs.size() == 0){
        new_score = score_board(board);
    }

    else{
        int rand_index = rand() % childs.size();
        new_score = childs[rand_index]->expand();
    }
    update_score(new_score);
    return new_score;

}

void NodeAfterRandom::update_score(float new_score){
    sum_scores += new_score;
    nb_visits++;
}

void NodeAfterRandom::build_childs(){
    for(int mv=0; mv<4; mv++){
        board_t moved = execute_move(mv, board);
        if(moved != board){
            NodeAfterMove * new_child = get_or_create(moved);
            childs.push_back(new_child);
        }
    }
}

NodeAfterMove::NodeAfterMove(board_t b) : Node(b){}

void NodeAfterMove::update_score(float new_score){
    sum_scores += new_score;
    nb_visits++;
}

float NodeAfterMove::expand(){
    board_t tile = draw_tile();
    board_t inserted = insert_tile_rand(board, tile);
    float new_score = rollout(inserted);
    update_score(new_score);
    return new_score;
}

float NodeAfterMove::get_score(){
    return sum_scores / nb_visits;
}

void NodeAfterMove::build_childs(){
}

int reverse_engineer_move(board_t from, board_t to){
    for(int mv=0;mv<4;mv++){
        if(execute_move(mv, from)==to){
            return mv;
        }
    }
    return 0;
}

int get_best_move(NodeAfterRandom node){
    vector<NodeAfterMove*> childs = node.get_childs();
    if(childs.size()== 0){
        return 0;
    }
    float best_score = 0;
    NodeAfterMove* best_child;
    for(int it=0; it < childs.size();it++){
        float score = childs[it]->get_score();
        if(score > best_score){
            best_score = score;
            best_child = childs[it];
        }
    }
    int best_mv = reverse_engineer_move(node.get_board(), best_child->get_board());
    return best_mv;
}

int get_best_move_mcts(board_t board){
    NodeAfterRandom root(board);
    int nb_runs = 0;
    auto start_chrono = std::chrono::high_resolution_clock::now();
    auto now_chrono = std::chrono::high_resolution_clock::now();
    double elapsed_d = chrono::duration<double>(now_chrono - start_chrono).count();
    while(elapsed_d<TIME_LIMIT){
        root.expand();
        now_chrono = std::chrono::high_resolution_clock::now();
        nb_runs++;
        elapsed_d = chrono::duration<double>(now_chrono - start_chrono).count();
    }
    #ifdef PROFILE
        cout<<"nb runs:"<<nb_runs<<endl;
        cout<<"nb runs per move:"<<nb_runs / root.get_childs().size()<<endl;
    #endif

    int best_mv = get_best_move(root);
    clear_news();
    return best_mv;
}


void clear_news(){
    #ifdef DEBUG
    cout<<"clearing mems"<<endl;
    #endif
    for(auto it = mem_after_move.begin(); it!=mem_after_move.end(); it++){
        delete it->second;
    }

    for(auto it = mem_after_random.begin(); it!=mem_after_random.end(); it++){
        delete it->second;
    }

    mem_after_random.clear();
    mem_after_move.clear();
}