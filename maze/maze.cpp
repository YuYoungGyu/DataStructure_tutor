#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Maze{
    private:
        int n;
        vector<vector<char>> maze_array;
        vector<vector<char>> maze_masking;
        vector<pair<int,int>> exit_pos;
        vector<int> results;
    public:
        Maze(int n);
        ~Maze(){};

        bool b_check(int x, int y);
        bool p_check(int x, int y);
        bool s_check(int x, int y);
        void maze_initialize();
        void make_maze();
        void trip_maze();
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
}

bool Maze::b_check(int x, int y){
    if((x >= 0 && x < n) && (y >= 0 && y < n)) return true;
    else return false;
}

bool Maze::p_check(int x, int y){
    if(maze_array[x][y] == 'X') return true;
    else return false;
}

bool Maze::s_check(int x, int y){
    
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
    maze_array[e_x][e_y] = 'O';

    int m_x[4] = {0,1,0,-1};
    int m_y[4] = {1,0,-1,0};

    stack<pair<int,int>> maker;
    maker.push(make_pair(0,0));
    while(!maker.empty()){
        int x = maker.top().first;
        int y = maker.top().second;
        maker.pop();

        for(int i = 0; i < 4; i++){
            int n_x = x + m_x[i];
            int n_y = y + m_y[i];
            if(b_check(n_x,n_y) && p_check(n_x,n_y) && s_check(n_x,n_y)){
                maze_array[n_x][n_y] = 'O';
                maker.push(make_pair(n_x,n_y));
            }
        }
    }
    display_maze();
    maze_initialize();
    make_maze();
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