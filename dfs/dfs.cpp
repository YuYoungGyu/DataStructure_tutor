#include <iostream>
#include <vector>
#include <stack>

using namespace std;

char miro[5][5] = {{'O','O','O','O','X'},
                {'O','X','X','O','O'},
                {'O','X','X','X','O'},
                {'O','O','O','O','X'},
                {'O','X','X','O','O'}};

bool check[5][5] = {false,};

bool check_boundary(int pos_x, int pos_y){
    if(pos_x >= 0 && pos_x < 5 && pos_y >= 0 && pos_y < 5) return true;
    else return false;
}

int main(){
    cout << "===miro===\n";
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << miro[i][j] << " ";
        }
        cout << endl;
    }

    /*find path with bfs 
      start point: (0,0)
      end point: (4,4)
      get shortest move form s_point to e_point*/
    stack<vector<int>> dfs; // (좌표, depth) 를 한번에 queue에 저장

    dfs.push({0,0,'0'}); // input starting point and depth
    check[0][0] = true;    // masking(지나온 곳을 표시) -> 다시 방문하지 않기 위해
    miro[0][0] = '0';  // depth 넣어줌
    int find_direction_x[4] = {1,0,-1,0};
    int find_direction_y[4] = {0,1,0,-1};

    while(!dfs.empty()){
        int pos_x = dfs.top()[0];  //x좌표
        int pos_y = dfs.top()[1];  //y좌표
        int depth = dfs.top()[2];  //depth
        dfs.pop();
        for(int i = 0; i < 4; i++){
            int new_x = pos_x + find_direction_x[i];  // 확인해야할 곳의 x좌표
            int new_y = pos_y + find_direction_y[i];  // 확인해야할 곳의 y좌표
            if(check_boundary(new_x, new_y) && miro[new_x][new_y] == 'O' && !check[new_x][new_y]){
                check[new_x][new_y] = true;
                miro[new_x][new_y] = depth+1;
                dfs.push({new_x,new_y,depth+1});
            }
        }
    }

    cout << "=miro_with_depth=\n";
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << miro[i][j] << " ";
        }
        cout << endl;
    }
    cout << "shortest move is: " << miro[4][4] << endl;


    return 0;
}