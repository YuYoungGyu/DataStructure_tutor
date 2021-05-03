#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <random>
//#include <time.h>
//#include <stdlib.h>

using namespace std;

class Maze{
    private:
        int n;
        vector<vector<char>> maze_array;
        vector<vector<char>> maze_masking;
        vector<pair<int,int>> exit_pos;
        vector<vector<int>> m_pool;
        vector<int> results;
        vector<vector<pair<int,int>>> all_path;
    public:
        Maze(int n);
        ~Maze(){};

        bool b_check(int x, int y); // 경계체크
        bool p_check(int x, int y); // 현위치
        bool s_check(int x, int y); // 스퀘어체크
        bool four_check(int x, int y);
        void make_m_pool();
        void maze_initialize();
        void make_maze();
        void b_trip_maze(int e_x, int e_y);
        void d_trip_maze(int e_x, int e_y);
        void display_maze();
};

Maze::Maze(int n){
    this->n = n;

    maze_initialize();

    for(int i = 0; i < n; i++){
        exit_pos.push_back(make_pair(i,n-1));
        exit_pos.push_back(make_pair(n-1,i));
    }
    exit_pos.pop_back();

    make_m_pool();
}

void Maze::make_m_pool(){
    vector<int> v{ 0, 1, 2, 3};
 
    sort(v.begin(), v.end());
 
    do {
        vector<int> a;
        for (auto it = v.begin(); it != v.end(); ++it)
            a.push_back(*it);
        m_pool.push_back(a);
    } while (next_permutation(v.begin(), v.end()));
}

bool Maze::b_check(int x, int y){
    if((x >= 0 && x < n) && (y >= 0 && y < n)) return true;
    else return false;
}

bool Maze::p_check(int x, int y){
    if(maze_array[x][y] == 'X') return true;
    else return false;
}

bool Maze::four_check(int x, int y){
    int many = 0;

    int m_x[8] = {0,1,0,-1,-1,1,-1,1};
    int m_y[8] = {1,0,-1,0,-1,-1,1,1};

    for(int i=0; i < 8; i++){
        int n_x = x + m_x[i];
        int n_y = y + m_y[i];
        if(b_check(n_x,n_y) && (maze_array[n_x][n_y] == 'X')) many++;
        else if(!b_check(n_x,n_y)) many++;
    }

    if(many >= 4) return true;
    else return false;
}

bool Maze::s_check(int x, int y){
    int m_x[4][3] = {{-1,-1,0},{0,1,1},{1,1,0},{0,-1,-1}};
    int m_y[4][3] = {{-1,0,-1},{-1,-1,0},{0,1,1},{1,1,0}};

    for (int j = 0; j < 4; j++){
        int many = 0;
        for(int i=0; i < 3; i++){
            int n_x = x + m_x[j][i];
            int n_y = y + m_y[j][i];
            if(b_check(n_x,n_y) && maze_array[n_x][n_y] == 'O') many++;
        }
        if(many == 3) return false;
    }
    return true;
}

void Maze::maze_initialize(){
    maze_array.clear();
    maze_masking.clear();
    for(int i = 0; i < n; i++){
        vector<char> array1;
        vector<char> array2;
        for(int j = 0; j < n; j++){
            array1.push_back('X');
            array2.push_back('0');
        }
        maze_array.push_back(array1);
        maze_masking.push_back(array2);
    }
    maze_array[0][0] = 'O';
}

void Maze::make_maze(){
    if(exit_pos.empty()) return;
    int e_x = exit_pos.back().first;
    int e_y = exit_pos.back().second;
    exit_pos.pop_back();

    cout << e_x << "," << e_y << endl;

    int m_x[4] = {0,1,0,-1};
    int m_y[4] = {1,0,-1,0};

    bool run = true;

    //srand(time(NULL));

    do{
        maze_initialize();
        
        maze_array[e_x][e_y] = 'O';

        stack<pair<int,int>> maker;
        maker.push(make_pair(0,0));
        while(!maker.empty()){
            int x = maker.top().first;
            int y = maker.top().second;
            maker.pop();

            if(!(four_check(x,y) && s_check(x,y)) && maze_array[x][y] != 'O'){ continue;}
            
            maze_array[x][y] = 'O';
            int r = rand()%24;
            for(int i : m_pool[r]){
                int n_x = x + m_x[i];
                int n_y = y + m_y[i];
                if(b_check(n_x,n_y) && p_check(n_x,n_y) && four_check(n_x,n_y) && s_check(n_x,n_y)){ 
                    maker.push(make_pair(n_x,n_y));
                }
            }
        }
        for(int i=0; i<4; i++){
            int n_x = e_x + m_x[i];
            int n_y = e_y + m_y[i];
            if(b_check(n_x,n_y) && !p_check(n_x,n_y)){ 
                run = false;
                break;
            }
        }
    }while(run);

    display_maze();
    d_trip_maze(e_x,e_y);
    maze_initialize();
    make_maze();
}

void Maze::b_trip_maze(int e_x, int e_y){
    maze_array;
    maze_masking;
}



void Maze::d_trip_maze(int e_x, int e_y){
    vector<pair<int,int>> path;

    int m_x[4] = {0,1,0,-1};
    int m_y[4] = {1,0,-1,0};

    stack<pair<int,int>> d_trip;
    d_trip.push(make_pair(0,0));
    maze_masking[0][0] = '1';
    while(!d_trip.empty()){
        int t_x = d_trip.top().first;
        int t_y = d_trip.top().second;
        d_trip.pop();
        
        path.push_back(make_pair(t_x,t_y));
        if(t_x == e_x && t_y == e_y) break;

        for(int i = 0; i < 4; i++){
            int n_x = t_x + m_x[i];
            int n_y = t_y + m_y[i];

            if(b_check(n_x,n_y) && maze_array[n_x][n_y] == 'O' && maze_masking[n_x][n_y] != '1'){
                d_trip.push(make_pair(n_x,n_y));
                maze_masking[t_x][t_y] = '1';
            }
        }
    }

    for(pair<int,int> a: path){
        cout << '(' << a.first << ',' << a.second << ')' << "->";
    }
    cout << endl;
    int size = path.size();
    cout << size <<"\n----------------\n";
    results.push_back(size);
    all_path.push_back(path);
}

void Maze::display_maze(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << maze_array[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;

    Maze m(n);
    m.make_maze();

    return 0;
}