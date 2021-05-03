#include <iostream>
#include <vector>

using namespace std;

enum statement{
    Recovered,
    Suspected,
    Infected,
};

class Person{
    private:
        static int suspected_person;
        statement state;
    public:
        Person(){
            state = Suspected;
            suspected_person++;
        }
        int get_suspected_person(){
            return suspected_person;
        }
        void infect(){
            state = Infected;
        }
};

int Person::suspected_person = 0;

int main(){
    
    vector<Person*> all_person;
    for(int i = 0; i < 88; i++){
        Person *tmp = new Person();
        all_person.push_back(tmp);
    }

    cout << all_person[0]->get_suspected_person() << endl;

    cout << all_person[70]->get_suspected_person() << endl;

    return 0;
}