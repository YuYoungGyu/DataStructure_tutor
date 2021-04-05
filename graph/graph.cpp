#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct node{
    int val;
    node* left;
    node* right;
};

class Graph{
    private:
        node* root;
        int n;        
    public:
        Graph(){
            root = new node;
            root->val = 0;
            root->left = nullptr;
            root->right = nullptr;
        }
        ~Graph(){};
        void make_graph_bfs(int n);
        node* push_left(node* p_node, int v);
        node* push_right(node* p_node, int v);
        void display_bfs();
        void display_dfs();
};

void Graph::make_graph_bfs(int n){
    this->n = n;
    if(n > 0){
        int i = 1;
        bool run = true;
        queue<node*> q;
        q.push(root);
        while(!q.empty() && run){
            node* tmp = q.front();
            q.pop();
            while(1){
                if(i >= n){
                    run = false;
                    break;
                }
                if(tmp->left == nullptr){
                    q.push(push_left(tmp, i));
                    i++;
                }
                else if(tmp->right == nullptr){
                    q.push(push_right(tmp, i));
                    i++;
                }
                else break;
            }
        }
    }
}
node* Graph::push_left(node* p_node, int v){
    node* new_node = new node;
    new_node->val = v;
    new_node->left = nullptr;
    new_node->right = nullptr;
    p_node->left = new_node;
    return new_node;
}
node* Graph::push_right(node* p_node, int v){
    node* new_node = new node;
    new_node->val = v;
    new_node->left = nullptr;
    new_node->right = nullptr;
    p_node->right = new_node;
    return new_node;
}

void Graph::display_bfs(){
    cout << "display graph with bfs search: ";
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* tmp = q.front();
        q.pop();
        cout << tmp->val << "->";
        if(tmp->left != nullptr) q.push(tmp->left);
        if(tmp->right != nullptr) q.push(tmp->right);
    }
    cout << "end" << endl;
}
void Graph::display_dfs(){
    cout << "display graph with dfs search: ";
    stack<node*> s;
    s.push(root);
    while(!s.empty()){
        node* tmp = s.top();
        s.pop();
        cout << tmp->val << "->";
        if(tmp->right != nullptr) s.push(tmp->right);
        if(tmp->left != nullptr) s.push(tmp->left);
    }
    cout << "end" << endl;
}

int main(){
    Graph g;
    g.make_graph_bfs(10);
    g.display_bfs();
    g.display_dfs();

    return 0;
}