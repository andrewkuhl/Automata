//
//  dtm.hpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#ifndef dtm_hpp
#define dtm_hpp

#include "dtminputhandler.hpp"
#include <future>

class DTM {
    
    struct Tape {
        
        struct tapeSymbol{
        string e;
        tapeSymbol* left;
        tapeSymbol* right;
            tapeSymbol(){e = "blank"; left = nullptr; right = nullptr;}
        };
        
        tapeSymbol* head;
        tapeSymbol* last;
        tapeSymbol* curr;
        
        Tape(){cout<<"[Tape]: initialized"<<endl;head = nullptr; last = nullptr; curr = nullptr;}
        ~Tape(){deleteTape(head);}
        void deleteTape(tapeSymbol* headptr){
            if(headptr == nullptr)
                return;
            deleteTape(headptr->right);
            delete headptr;
        }
        void newSymbol(string a){
            if(last!=nullptr){
                tapeSymbol* newsym = new tapeSymbol();
                newsym->e = a;
                newsym->left = last;
                last->right = newsym;
                last = last->right;
            }
            else
            {
                tapeSymbol* newsym = new tapeSymbol();
                newsym->e = a;
                last = newsym;
                curr = newsym;
                head = newsym;
            }
        }
        string read(){return curr->e;}
        void write(string e_){curr->e = e_;}
        void move(string dir){
            if(dir == "L"){
                if(curr->left != nullptr)
                    curr = curr->left;
            }
            if(dir == "R"){
                if(curr->right == nullptr)
                    newSymbol("blank");
                curr = curr->right;
            }
        }
        void print(tapeSymbol* printing){
            if (printing==nullptr)
            {
                cout << "\n";
                return;
            }
            cout << printing->e << " ";
            print(printing->right);
        }

        
    }*tape;
    
    struct Controller{ //controller
        
        vector<string> Q; //set of states
        vector<string> E; //set of input characters
        vector<string> G; //set of stack characters
        vector<DTMTransition> d; //set of transitions
        string q0; //start state
        string qaccept; //accepting state
        string qreject; //rejecting state
        
        
        Controller(){cout<<"[Controller]: initialized" <<endl;}
    }*controller; //controller object
    
    DTMInputHandler* inhandler; //input handler obj
    
public:
    
    DTM(const char * argv[]);
    ~DTM();
    bool run(); //run function
    bool machine(string currState_,
                 vector<DTMTransition> transitions_, Tape* tape_);
};

#endif /* dtm_hpp */
