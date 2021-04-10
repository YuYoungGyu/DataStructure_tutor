#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

struct dir{
    string name;                // directory name
    dir* parent_dir = nullptr;  // parent directory
    vector<dir*> child_dir;     // child directory
};

class FileSystem{
    private:
        dir* root = nullptr;
        dir* current_dir = nullptr;
    public:
        FileSystem(){
            root = new dir;
            root->name = "root";
            current_dir = root;
        }
        ~FileSystem(){};
        void print_current_path();
        void mkdir(string name);
        void ls();
        void cd(string name);
        void rmdir(string name);
        void rmdir_recursive(string name, dir* tmp);
        void print_error_message();
};

void FileSystem::print_current_path(){
    vector<string> path;
    dir* temp_dir = current_dir;
    while(1){
        path.push_back(temp_dir->name);
        if(temp_dir == root) break;
        temp_dir = temp_dir->parent_dir;
    }

    while(!path.empty()){
        cout << "\\" << path.back();
        path.pop_back();
    }
    cout << ">";
}

void FileSystem::mkdir(string name){
    dir* new_dir = new dir;
    new_dir->name = name;
    new_dir->parent_dir = current_dir;
    current_dir->child_dir.push_back(new_dir);
}

void FileSystem::ls(){
    for(dir* child: current_dir->child_dir)
        cout << child->name << endl;
}

void FileSystem::print_error_message(){
    cout << "올바르지 않은 명령어 입니다.\n";
}

void FileSystem::cd(string name){
    if(name.compare("..") == 0){
        current_dir = current_dir->parent_dir;
        return;
    }
    else if(name.compare("~") == 0){
        current_dir = root;
        return;
    }
    for(dir* c: current_dir->child_dir){
        if(c->name.compare(name) == 0){
            current_dir = c;
            break;
        }
    }
}

void FileSystem::rmdir(string name){
    for(int idx = 0; idx < current_dir->child_dir.size(); idx++){
        if(current_dir->child_dir[idx]->name.compare(name) == 0){
            dir* tmp = current_dir->child_dir[idx];
            tmp->parent_dir = nullptr;
            current_dir->child_dir.erase(current_dir->child_dir.begin() + idx);
            stack<dir*> nodes;
            queue<dir*> q;
            q.push(tmp);
            while(!q.empty()){
                dir* t = q.front();
                q.pop();
                nodes.push(t);
                for(dir* c : t->child_dir){
                    q.push(c);
                }
            }
            while(!nodes.empty()){
                dir* t = nodes.top();
                nodes.pop();
                cout << t->name << '\n';
                t = nullptr;
                delete t;
            }
            break;
        }
    }
}

void FileSystem::rmdir_recursive(string name, dir* tmp){
    if(tmp != nullptr){
        for(dir* c: tmp->child_dir){
            c->parent_dir = nullptr;
            rmdir_recursive(name,c);
        }
        tmp->child_dir.clear();
        cout << tmp->name << endl;
        delete tmp;
        return;
    }
    for(int idx = 0; idx < current_dir->child_dir.size(); idx++){
        if(current_dir->child_dir[idx]->name.compare(name) == 0){
            tmp = current_dir->child_dir[idx];
            tmp->parent_dir = nullptr;
            current_dir->child_dir.erase(current_dir->child_dir.begin() + idx);
            rmdir_recursive(name,tmp);
            break;
        }
    }
}

vector<string> command_spliter(){
    vector<string> result;
    string sub_command;

    char c;
    int i = 0;
    while((c = getchar()) != '\n'){
        if(c != ' '){ 
            sub_command[i] = c;
            i++;
        }
        else{
            result.push_back(sub_command);
            cout << sub_command << "\n";
            sub_command.clear();
            i = 0;
        }
    }
    result.push_back(sub_command);
    cout << sub_command << "\n";
    return result;
}

int main(){
    FileSystem f;
    string command;
    vector<string> command_set;

    while(1){
        f.print_current_path();
        while(1){
            cin >> command;
            command_set.push_back(command);
            if(getchar() == '\n') break;
        }
        if(command_set[0].compare("ls") == 0) f.ls();
        else if(command_set[0].compare("mkdir") == 0) f.mkdir(command_set[1]);
        else if(command_set[0].compare("cd") == 0) f.cd(command_set[1]);
        else if(command_set[0].compare("rmdir") == 0) f.rmdir(command_set[1]);
        else if(command_set[0].compare("rmdir_recursive") == 0) f.rmdir_recursive(command_set[1],nullptr);
        else if(command_set[0].compare("exit") == 0) break;
        command_set.clear();
    }

    return 0;
}