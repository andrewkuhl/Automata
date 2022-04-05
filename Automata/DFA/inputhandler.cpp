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
    cout << "[InputHandler]: opening input file.." << endl;
    fp = nullptr; //null ptr for check
    fp = freopen(argv[2], "r", stdin);
    if (fp == nullptr)
    {
        cout << "[InputHandler][ERROR]: couldn't open input file"
        << endl;//bad path
        exit(1);
    }
    else
    {
        cout << "[InputHandler]: opened input file" << endl;
        cout << "[InputHandler]: ready.." << endl;
        //opened file
    }
    
}
InputHandler::~InputHandler()
{
    delete fp;
}
vector<string> InputHandler::getQ()
{
    vector<string> Qlist;//list of states
    char c;
    for(int j = 0; j < 2; j ++){
        c = getc(fp);// burn Q and {
    }
    string ch = "";
    do{
        c = getc(fp);
        switch(c){
            case ' ':
            case '\n':
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
        c = getc(fp);// burn E and {
    }
    string ch = "";
    do{
        c = getc(fp);
        switch(c){
            case ' ':
            case '\n':
            case '}':
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
Transition* InputHandler::getd()
{
    return nullptr;
}
string InputHandler::getq0()
{
    return "";
}
vector<string> InputHandler::getF()
{
    vector<string> a;
    return a;
}
