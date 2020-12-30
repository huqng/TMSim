#include "Transmission_function.h"
#include "Tape.h"

#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#define isStateSymbol(c) (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '_')
#define isInputSymbol(c) (c != ' ' && c != ',' && c != ';' && c != '{' && c != '}' && c != '*' && c != '_')
#define isTapeSymbol(c) (c != ' ' && c != ',' && c != ';' && c != '{' && c != '}' && c != '*')
#define isDirectionSymbol(c) (c == 'l' || c == 'r' || c == '*')

class TM{    
    // verbose flag:
    bool verbose;
    // 7-tuple: 
    set<string> Q, S, G;         // 状态集、输入符号集、纸带符号集
    string q0, B;                   // 初始状态、空格符号
    set<string> F;                 // 终结状态集
    set<Transmission_function*> Transmission_functions;
    // number of tape(s):

    int N;                          
    // tapes
    vector<Tape*> tape;            
    // head is in class Tape
    // ucurrent state
    string curState;

    void fail(string msg){
        cerr << "syntax error" << endl;
#ifdef DEBUG   
        cerr << msg << endl;
#endif
        exit(-1);
    }
public:
    TM(){}
    TM(string filename, bool verbose):verbose(verbose){
        //this->Q = new set<string>;
        //this->S = new set<string>;
        //this->G = new set<string>;
        q0 = "";
        B = "";                     // 初始状态、空格符号
        //this->F = new set<string>;
        //this->delta = new set<Transmission_function*>;
        
        // open file
        ifstream fin(filename, ios::in);
        if(!fin.is_open()){
            cerr << "Failed to open file " << filename << "!" << endl;
            exit(-1);
        }
        string s;
        int cnt = 0;
        
        while(getline(fin, s) && cnt < 8){

            if(s[0] == ';' || s[0] == ' ' || s[0] == '\n' || s[0] == '\t')
                continue;
                        
            if(s[0] == '#') {
                switch(cnt){
                    case 0: {   // Q 状态集
                        if(s.length() < 7 && s.substr(2, 4) != " = {") {
                            fail(s + "Q1");
                        }
                        int i = 6;
                        while(1){
                            int j = i;
                            while(j < s.length() && isStateSymbol(s[j]))
                                j++;
                            if(j >= s.length())
                                fail("Q2");
                            
                            this->Q.insert(s.substr(i, j - i));
                            if(s[j] == ',')
                                i = j + 1;
                            else if(s[j] == '}')
                                break;
                        }
                        cnt++;
                        // print what it read:
#ifdef DEBUG                        
                        cout<<"Q:\t";
                        auto it = this->Q.begin();
                        cout << *(it++);
                        while(it != this->Q.end()){
                            cout<<", " << *it;
                            it++;
                        }
                        cout << endl;
# endif

                        break;
                    }
                    case 1: {   // S 输入符号集
                        if(s.substr(0, 6) != "#S = {"){
                            fail(s + "S1");
                        }
                        int i = 6;
                        while(i < s.length()){
                            if(isInputSymbol(s[i]))
                                this->S.insert(string(1, s[i]));
                            i++;
                        }
#ifdef DEBUG   
                        cout<<"S:\t";
                        auto it = this->S.begin();
                        cout << *(it++);
                        while(it != this->S.end()){
                            cout<<", " << *it;
                            it++;
                        }
                        cout << endl;
# endif

                        cnt++;
                        break;
                    }
                    case 2: {   // G 纸带符号集
                        if(s.substr(0, 6) != "#G = {"){
                            fail(s + "G1");
                        }
                        int i = 6;
                        while(i < s.length()){
                            if(isTapeSymbol(s[i]))
                                this->G.insert(string(1, s[i]));
                            i++;
                        }
#ifdef DEBUG   
                        cout<<"G:\t";
                        auto it = this->G.begin();
                        cout << *(it++);
                        while(it != this->G.end()){
                            cout<<", " << *it;
                            it++;
                        }
                        cout << endl;
#endif
                        cnt++;
                        break;
                    }
                    case 3: {   // q0 初始状态
                        if(s.substr(0, 6) != "#q0 = "){
                            fail(s + "q0");
                        }
                        int i = 6;
                        int j = i;
                        while(j < s.length() && isStateSymbol(s[j]))
                            j++;
                        this->q0 = s.substr(i, j - i);
                        this->curState = this->q0;
#ifdef DEBUG   
                        cout << "q0:\t" << this->q0 << endl;
#endif         
                        cnt++;
                        break;
                    }
                    case 4: {   // B 空白符
                        if(s.substr(0, 5) != "#B = "){
                            fail(s + "B1");
                        }
                        int i = 5;
                        if(i < s.length())
                            this->B = s[i];
                        else
                            fail("B2");
#ifdef DEBUG   
                        cout << "B:\t" << this->B << endl;
#endif         
                        cnt++;
                        break;
                    }
                    case 5: {   // F 终结状态集
                        if(s.length() < 7 && s.substr(2, 4) != " = {") {
                            fail(s + "F1");
                        }
                        int i = 6;
                        while(1){
                            int j = i;
                            while(j < s.length() && isStateSymbol(s[j]))
                                j++;
                            if(j >= s.length())
                                fail("F2");
                            
                            this->F.insert(s.substr(i, j - i));
                            if(s[j] == ',')
                                i = j + 1;
                            else if(s[j] == '}')
                                break;
                        }
                        cnt++;
#ifdef DEBUG   
                        // print what it read:
                        cout<<"F:\t";
                        auto it = this->F.begin();
                        cout << *(it++);
                        while(it != this->F.end()){
                            cout<<", " << *it;
                            it++;
                        }
                        cout << endl;
#endif

                        break;
                    }
                    case 6: {   // N 纸带数
                        if(s.substr(0, 5) != "#N = "){
                            fail(s + "N1");
                        }
                        int i = 5;
                        int j = i;
                        while(j < s.length() && isdigit(s[j]))
                            j++;
                        this->N = atoi(s.substr(i, j - i).c_str());

                        //this->tape.resize(N);
                        for(int j = 0; j < this->N; j++)
                            this->tape.push_back(new Tape(0, this->B));
#ifdef DEBUG   
                        cout << "N:\t" << this->N << endl;
#endif

                        cnt++;
                        break;
                    }
                    default:
                        break;
                }
            } // end of #...
            // deal with transmission functions:
            else if(cnt == 7 && s.length() >= 9){  
                string oldState, oldSymbol, newState, newSymbol;
                string d;
                vector<string> direction(this->N);
                int i = 0;
                int j = i;
                while(j < s.length() && isStateSymbol(s[j]))
                    j++;
                if(j >= s.length()){
                    cout << s.length() << endl;
                    fail("D1");
                }
                oldState = s.substr(i, j - i);

                i = ++j;
                while(j < s.length() && isTapeSymbol(s[j]))
                    j++;
                if(j >= s.length())
                    fail("D2");
                oldSymbol = s.substr(i, j - i);


                i = ++j;
                while(j < s.length() && isStateSymbol(s[j]))
                    j++;
                if(j >= s.length())
                    fail("D3");
                newSymbol = s.substr(i, j - i);


                i = ++j;
                while(j < s.length() && isDirectionSymbol(s[j]))
                    j++;
                if(j >= s.length())
                    fail("D4");
                d = s.substr(i, j - i);


                i = ++j;
                while(j < s.length() && isTapeSymbol(s[j]))
                    j++;
                newState = s.substr(i, j - i);
                
                for(int i = 0; i < this->N; i++){
                    direction[i] = d.substr(i, 1);
                }

                this->Transmission_functions.insert(new Transmission_function(oldState, newState, oldSymbol, newSymbol, direction));
            } // end of A delta ...
        } // end of while getline
        if(cnt != 7){
            fail("Failed before Delta");
        }
#ifdef DEBUG   
        cout << "Delta:" << endl;
        auto it = this->Transmission_functions.begin();
        while(it != this->Transmission_functions.end()){
            cout << "\t";
            (*it)->print_info();
            it++;
        }
# endif
    }// end of constructor TM(...)
    
    bool run(string input, bool verbose){
        // check ilegality:
        for(int i = 0; i < input.length(); i++){
            if(this->S.find(string(1, input[i])) == this->S.end()){
                if(!this->verbose)
                    cerr << "illegal input" << endl;
                else{
                    cerr << "Input: " << input << endl;
                    cerr << "==================== ERR ====================" << endl;
                    cerr << "error: \'" << input[i] << "\' was not declared in the set of input symbols" << endl;
                    cerr << "Input: " << input << endl;
                    for(int j = 0; j < 7 + i; j++)
                        cerr << " ";
                    cerr << "^" << endl;
                    cerr << "==================== END ====================" << endl;
                }
                exit(-2);
            }
        }
        if(this->verbose){
            cout << "Input: " << input << endl;
            cout << "==================== RUN ====================" << endl;
        }
        // write input to tape[0]
        for(int j = 0; j < input.length(); j++){
            this->tape[0]->set(string(1, input[j]), j);
        }
        // really run:
        int step = 0;
        while(1){
            string cur_tape_symbols;
            for(int j = 0; j < this->N; j++){
                string tmp = this->tape[j]->get();
                cur_tape_symbols.append(tmp);
            }
            // find a delta
            set<Transmission_function*>::iterator delta = this->Transmission_functions.end();
            for(auto it = this->Transmission_functions.begin(); it != this->Transmission_functions.end(); it++){
                bool matchingS = ((*it)->getOldState() == this->curState);
                bool matchingQ = (cur_tape_symbols == (*it)->getOldSymbol());
                if(matchingQ && matchingS){
                    delta = it;
                    break;
                }
            }
            // print info
            if(this->verbose){
                cout << left << setw(8) << "Step" << ": " << step++ << endl;
                for(int j = 0; j < this->N; j++){
                    this->tape[j]->print_detailed(j);
                }
                cout << left << setw(8) << "State" << ": " << this->curState << endl;
                cout << "---------------------------------------------" << endl;
            }
            
            if(delta == this->Transmission_functions.end()){
                // halted:
                if(this->verbose)
                    cout << "Result: ";
                this->tape[0]->print();
                if(this->verbose)
                    cout << "==================== END ====================" << endl;
                exit(-1000);
            }
            else{   

                // if not halted:
                string newState = (*delta)->getNewState();
                string newSymbol = (*delta)->getNewSymbol();
                vector<string> curDirection = (*delta)->getDirection();
                // update state:
                this->curState = newState;
                // for each tape, update symbol(s) & head(s):
                for(int j = 0; j < this->N; j++){
                    this->tape[j]->set(string(1, newSymbol[j]));
                    this->tape[j]->set_head(curDirection[j]);
                }
            }
        } // end of while input
        return false;
    }// end of run()
};// end of class TM