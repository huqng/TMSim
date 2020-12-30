#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
using  namespace std;

class Tape{
    vector<string> t0, t1;
    string blank;
    int __head;
    
    void resize(int position){
        if(position >= 0){
            int i = position;
            if(i >= t0.size()){
                int i0 = t0.size();
                t0.resize(i + 1);
                for(int j = i0; j < i + 1; j++){
                    t0[j] = this->blank;
                }
            }
        }
        else{
            int i = -1 - position;
            if(i >= t1.size()){
                int i1 = t1.size();
                t1.resize(i + 1);
                for(int j = i1; j < i + 1; j++){
                    t1[j] = this->blank;
                }
            }
        }
    }
    void get_nonblank_index(int* plow, int* phigh){
        int low = -1 - this->t1.size();
        int high = this->t0.size() - 1;
        while((this->get(low) == this->blank) && (low < high))
            low++;
        while((this->get(high) == this->blank) && (high > low)) 
            high--;
        if(high == low && this->get(high) == this->blank){
            *plow = this->__head;
            *phigh = this->__head;
            return;
        }
        *plow = low;
        *phigh = high;
    }
public:
    Tape(){}
    Tape(int head = 0, string blank = "_"): __head(head), blank(blank){
        this->resize(this->__head);
        for(int i = 0; i < t0.size(); i++)
            t0[i] = blank;
        for(int i = 0; i < t1.size(); i++)
            t1[i] = blank;
        
    }
    int head(){ return this->__head; }

    string get(){
        int i = this->__head;
        if(i >= 0)
            return this->t0[i];
        else
            return this->t1[-1 - i];   
    }

    string get(int i){
        this->resize(i);
        if(i >= 0)
            return this->t0[i];
        else
            return this->t1[-1 - i];   
    }

    void set(string c){
        resize(this->__head);
        if(this->__head >= 0)
            t0[this->__head] = c;
        else
            t1[-1 - this->__head] = c;
    }

    void set(string c, int i){
        if(i >= 0 && i >= t0.size() || i < 0 && (-1 - i) >= t1.size())
            this->resize(i);

        if(i >= 0)
            t0[i] = c;
        else
            t1[-1 - i] = c;
    }
        
    void set_head(string s){
        int i = this->__head;
        if(s == "l")
            i--;
        else if(s == "r")
            i++;
        else if(s == "*")
            ;// do nothing
        else
            exit(-1000);
        this->resize(i);
        this->__head = i;
    }

    string get_tape_string(){
        string s;
        int low, high;
        this->get_nonblank_index(&low, &high);
        for(int i = low; i <= high; i++){
            s.append(this->get(i));
        }
        if(s.empty())
            return "_";
        return s;
    }

    void print(){
        cout<< this->get_tape_string();
        cout << endl;
    }

    void print_detailed(int j){
        int low, high;
        this->get_nonblank_index(&low, &high);
        if(this->__head < low)
            low = this->__head;
        else if(this->__head > high)
            high = this->__head;
        // print index:
        cout << left << setw(8) << "Index" + to_string(j) << ": ";
        for(int i = low; i <= high; i++)
            cout << abs(i) << " ";
        cout << endl;
        // print tape symbols
        cout << left << setw(8) << "Tape" + to_string(j) << ": ";
        int i = low;
        while(i <= high){
            cout << this->get(i);
            for(int j = 0; j <= to_string(abs(i)).size() - this->get(i).size(); j++)
                cout << " ";
            i++;
        }
        cout << endl;
        // print head ^
        cout << left << setw(8) << "Head" + to_string(j) << ": ";
        i = low;
        while(i < this->__head){
            for(int j = 0; j <= to_string(abs(i)).size(); j++)
                cout << " ";
            i++;
        }
        cout << "^" << endl;
    }
};