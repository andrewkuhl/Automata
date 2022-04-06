//
//  inputhandler.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/5/22.
//

#include "inputhandler.hpp"

using namespace std;

InputHandler::InputHandler(const char * argv[])
{
    cout << "[InputHandler]: initialized" << endl;
    cout << "[InputHandler]: opening machine specifications.." << endl;
    args = argv;
    ms = nullptr; //null ptr for check
    ms = freopen(args[2], "r", stdin);
    if (ms == nullptr)
    {
        cout << "[InputHandler][ERROR]: couldn't open specifications"
        << endl;//bad path
        exit(1);
    }
    else
    {
        cout << "[InputHandler]: opened specifications" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
}
InputHandler::~InputHandler()
{
    delete ms;
}
vector<string> InputHandler::getQ()
{
    vector<string> Qlist;//list of states
    char c;
    for(int j = 0; j < 2; j ++){
        c = getc(ms);// burn Q and {
    }
    string ch = "";
    do{
        c = getc(ms);
        switch(c){
            case '\n':
                break;
            case ' ':
            case '}':
            {
                if(ch != ""){
                    Qlist.push_back(ch);
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c);
                break;
            }
        }
    }while(c != '}');
    cout << "[InputHandler]: sending Q" << endl;
    return Qlist;
}

vector<string> InputHandler::getE()
{
    vector<string> Elist;//list of states
    char c;
    for(int j = 0; j < 3; j ++){
        c = getc(ms);// burn E and {
    }
    string ch = "";
    do{
        c = getc(ms);
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                if(ch != ""){
                    Elist.push_back(ch);
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c);
                break;
            }
        }
    }while(c != '}');
    cout << "[InputHandler]: sending E" << endl;
    return Elist;
}
vector<Transition> InputHandler::getd()
{
    vector<Transition> T_;//list of states
    char c;
    for(int j = 0; j < 4; j ++){
        c = getc(ms);// burn \n E and { \n
    }
    string ch = "";
    vector<string> tmp;
    do{
        c = getc(ms);
        switch(c){
            case '\n':
                break;
            case ',':
            case '}':
            {
                tmp.push_back(ch);
                ch = "";
                if(tmp.size() > 2){
                    Transition t;
                    t.Qs = tmp.at(0);
                    t.e = tmp.at(1);
                    t.Qf = tmp.at(2);
                    T_.push_back(t);
                    tmp.clear();
                }
                else
                {
                    cout << "[InputHandler][ERROR]: invalid transition" << endl;
                    exit(1);
                }
                break;
            }
            case ' ':
            {
                tmp.push_back(ch);
                ch = "";
                break;
            }
            default:
            {
                ch.push_back(c);
                break;
            }
        }
    }while(c != '}');
    
    
    cout << "[InputHandler]: sending d" << endl;
    return T_;
}
string InputHandler::getq0()
{
    char c;
    for(int j = 0; j < 4; j ++){
        c = getc(ms);// burn \n E and {
    }
    string q0_ = "";//start state
    do{
        c = getc(ms);
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                if(q0_ != ""){
                  
                }
                break;
            }
            default:
            {
                q0_.push_back(c);
                break;
            }
        }
    }while(c != '}');
    cout << "[InputHandler]: sending q0" << endl;
    return q0_;
}
vector<string> InputHandler::getF()
{
    vector<string> Flist;//list of states
    char c;
    for(int j = 0; j < 3; j ++){
        c = getc(ms);// burn E and {
    }
    string ch = "";
    do{
        c = getc(ms);
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                if(ch != ""){
                    Flist.push_back(ch);
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c);
                break;
            }
        }
    }while(c != '}');
    cout << "[InputHandler]: sending F" << endl;
    return Flist;
}
void InputHandler::getINF()
{
    cout << "[InputHandler]: opening input.." << endl;
    inf = nullptr; //null ptr for check
    inf = freopen(args[3], "r", stdin);
    if (inf == nullptr)
    {
        cout << "[InputHandler][ERROR]: couldn't open input"
        << endl;//bad path
        exit(1);
    }
    else
    {
        cout << "[InputHandler]: opened input" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
    char c;
    string ch = "";
    do{
        c = getc(inf);
        switch(c){
            case '\n':
                break;
            case ';':
            case ' ':
            {
                if(ch != ""){
                    input.push_back(ch);
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c);
                break;
            }
        }
    }while(c != ';');
}
string InputHandler::getInput()
{
    if(input.empty())
    {
        return "";
    }
    else
    {
        string a = input.front();
        input.erase(input.begin());
        return a;
    }
}
