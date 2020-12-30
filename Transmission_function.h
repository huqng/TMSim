#include<set>
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Transmission_function{
    string oldQ, newQ;
    string oldS, newS;
    vector<string> direction;                 // l r *
public:
    Transmission_function(  string oldQ, string newQ, string oldS, string newS, vector<string>& direction
                            ):oldQ(oldQ), newQ(newQ), oldS(oldS), newS(newS), direction(direction){}
                            
    void print_info(){
        cout << "<" << this->oldQ << "> <" << this->oldS << "> <" << this->newQ << "> <"; 
        for(int i = 0; i < this->direction.size(); i++) 
            cout << this->direction[i];
        cout << "> <" << this->newS << ">" << endl;
    }
    string getOldState(){ return this->oldQ; }
    string getOldSymbol(){ return this->oldS; }
    string getNewState(){ return this->newQ; }
    string getNewSymbol(){ return this->newS; }
    vector<string> getDirection(){ return this->direction; }
};