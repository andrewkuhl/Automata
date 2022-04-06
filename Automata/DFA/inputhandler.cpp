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
    
    args = argv; //copy args
    ms = nullptr; //set ptr to null for check
    ms = freopen(args[2], "r", stdin); //open file to ptr
    if (ms == nullptr) //if file not opened
    {
        cout << "[InputHandler][ERROR]: couldn't open specifications"
        << endl;//bad path
        exit(1);
    }
    else //else file opened?
    {
        cout << "[InputHandler]: opened specifications" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
}
InputHandler::~InputHandler()
{
    delete ms;
    delete inf;
}
vector<string> InputHandler::getQ()
{
    vector<string> Qlist;//list of states
    char c;
    for(int j = 0; j < 2; j ++){
        c = getc(ms);// burn Q and {
    }
    string ch = "";
    do{ // while char isnt }
        c = getc(ms); //get char
        switch(c){
            case '\n':
                break;
            case ' ':
            case '}':
            {
                if(ch != ""){
                    Qlist.push_back(ch); //if delimiter app to vec
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c); //if char app to string
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
        c = getc(ms);// burn \n E and {
    }
    string ch = "";
    do{ //while char isnt }
        c = getc(ms); //get char
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                if(ch != ""){
                    Elist.push_back(ch); //if delim add to vec
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c); //if char add to str
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
        c = getc(ms);// burn \n d and { \n
    }
    string ch = "";
    vector<string> tmp;
    do{ //while char not }
        c = getc(ms); //get char
        switch(c){
            case '\n':
                break;
            case ',':
            case '}':
            {
                tmp.push_back(ch); //if delim load vec to obj
                ch = "";
                if(tmp.size() > 2){
                    Transition t;
                    t.Qs = tmp.at(0);
                    t.e = tmp.at(1);
                    t.Qf = tmp.at(2);
                    T_.push_back(t); //push obj to transvec
                    tmp.clear();
                }
                else
                {
                    cout << "[InputHandler][ERROR]: invalid transition" << endl;
                    exit(1); //exit if transition bad
                }
                break;
            }
            case ' ':
            {
                tmp.push_back(ch);
                ch = ""; //if delim push str to stringvec
                break;
            }
            default:
            {
                ch.push_back(c); //if char push to string
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
        c = getc(ms);// burn \n q 0 and {
    }
    string q0_ = "";//start state
    do{ //while char not }
        c = getc(ms); //get char
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                break;
            }
            default:
            {
                q0_.push_back(c); //if char push
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
        c = getc(ms);// burn \n F and {
    }
    string ch = "";
    do{ //while char not }
        c = getc(ms); //get char
        switch(c){
            case '\n':
                break;
            case '}':
            case ' ':
            {
                if(ch != ""){
                    Flist.push_back(ch); //if delim push to vec
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c); //if char push to str
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
    inf = freopen(args[3], "r", stdin); //open file to ptr
    if (inf == nullptr) //if file not load
    {
        cout << "[InputHandler][ERROR]: couldn't open input"
        << endl;//bad path
        exit(1); //exit
    }
    else //file loaded
    {
        cout << "[InputHandler]: opened input" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
    char c;
    string ch = "";
    do{ //while char not ;
        c = getc(inf); //get char
        switch(c){
            case '\n':
                break;
            case ';':
            case ' ':
            {
                if(ch != ""){ //if space or ; push to input vec
                    input.push_back(ch);
                    ch = "";
                }
                break;
            }
            default:
            {
                ch.push_back(c); //if char push to string
                break;
            }
        }
    }while(c != ';');
}
string InputHandler::getInput()
{
    if(input.empty()) //if no more input
    {
        return "";
    }
    else
    {
        string a = input.front(); //pop first string off and return it
        input.erase(input.begin());
        return a;
    }
}
