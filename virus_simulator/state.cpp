#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

enum statement{
    Recovered,
    Suspected,
    Infected,
    Removed
};

/*
1. Suspected - -> Infected
2. Recovered -/-> Infected
3. Recovered per = input value(0)
4. Infected per = input value(0)
5. Removed - -> Recovered try > 3
6. spread - -> nearby
7. start node - -> ???
*/


class Person{
    private:
        static int time;
        int recover_try;

        vector<Person*> near_node;
        static int recovered_person;
        static int suspected_person;
        static int infected_person;
        static int removed_person;
        statement state;
    public:
        Person(){
            state = Suspected;
            suspected_person++;
            recover_try = 0;
        }
        statement get_state(){
            return state;
        }
        int get_suspected_person(){
            return suspected_person;
        }
        int get_recovered_person(){
            return recovered_person;
        }
        int get_infected_person(){
            return infected_person;
        }
        int get_recover_try(){
            return recover_try;
        }
        void connect(Person* p){
            this->near_node.push_back(p);
            p->near_node.push_back(this);
        }
        bool infect(int infected_per){
            int random = rand()%100;

            if(random < infected_per) { 
                state = Infected;
                suspected_person--;
                infected_person++;
                return true;
            }
            else return false;
        }
        bool recover(int recovered_per){
            int random = rand()%100;
            recover_try++;
            if(random < recovered_per) { 
                state = Recovered;
                infected_person--;
                recovered_person++;
                return true;
            }
            else return false;
        }
        void remove(){
            state = Removed;
            infected_person--;
            removed_person++;
        }
        void display_near_node(){
            int result = near_node.size();
            cout << result << endl;
            
        }
        void time_increment(){
            time++;
        }
        vector<Person*> get_near_node(){
            return near_node;
        }
        void simulation_display(){
            cout << "TIME: " << time << endl;
            cout << "Suspected_person: " << suspected_person << "명 입니다." << endl;
            cout << "Infected_person : " << infected_person  << "명 입니다." << endl;
            cout << "Recovered_person: " << recovered_person << "명 입니다." << endl;
            cout << "removed_person  : " << removed_person   << "명 입니다." << endl;
            cout << "----------------------------------------" << endl;
        }
};

int Person::time = 0;
int Person::recovered_person = 0;
int Person::suspected_person = 0;
int Person::infected_person = 0;
int Person::removed_person = 0;

pair<int,int> select_connect_node(vector<int> pool){
    int s = pool.size();
    int idx1 = rand()%s;
    int idx2 = rand()%s;
    
    while(1){
        if(pool[idx1] == pool[idx2]) idx2 = rand()%s;
        else break;
    }

    return make_pair(idx1,idx2);
}

int main(){
    srand((unsigned int)time(NULL));

    vector<Person*> network;
    vector<int> pool;
    pair<int,int> selected_idx;

    int recovered_per;
    int infected_per;

    cin >> recovered_per >> infected_per;
    if((recovered_per < 0 && recovered_per > 100) || (infected_per < 0 && infected_per > 100)) return 0;

    Person *tmp1 = new Person();
    network.push_back(tmp1);
    Person *tmp2 = new Person();
    network.push_back(tmp2);
    network[0]->connect(network[1]);
    pool.push_back(0);
    pool.push_back(1);

    for(int i = 2; i < 1000; i++){
        Person *tmp = new Person();
        network.push_back(tmp);
        int s = network.size();

        selected_idx = select_connect_node(pool);
        int idx1 = selected_idx.first;
        int idx2 = selected_idx.second;

        Person* c1 = network[pool[idx1]];
        Person* c2 = network[pool[idx2]];

        network[s-1]->connect(c1);
        network[s-1]->connect(c2);
        
        pool.push_back(pool[idx1]);
        pool.push_back(pool[idx2]);
        pool.push_back(s-1);
        pool.push_back(s-1);   
    }

    Person* start;
    int tmp_idx = 0;
    for(Person* node: network){
        int size = node->get_near_node().size();
        if(tmp_idx < size){
            start = node;
            tmp_idx = size;
        }
    }

    // 바이러스 숙주 한명 선택
    start->infect(100);
    start->time_increment();

    vector<Person*> infected_vector;
    vector<Person*> newly_infected;
    
    infected_vector.push_back(start);

    while(!infected_vector.empty()){
        infected_vector.back()->simulation_display();
        infected_vector.back()->time_increment();
        for(Person* infected_person: infected_vector){
            for(Person* near_person: infected_person->get_near_node()){
                if(near_person->get_state() == Suspected && near_person->infect(infected_per)) {
                    newly_infected.push_back(near_person);
                }
                
            }
            // 회복 시도한다.
            infected_person->recover(recovered_per);
            // 일정 시도를 넘기면 죽는다.
            
        }
    }

    return 0;
}