//
//  cfginputhandler.cpp
//  Automata
//
//  Created by Andrew Kuhl on 4/7/22.
//

#include "cfginputhandler.hpp"

using namespace std;

CFGInputHandler::CFGInputHandler(const char * argv[])
{
    cout << "[InputHandler]: initialized" << endl;
    cout << "[InputHandler]: opening machine specifications.." << endl;
    
    args = argv; //copy args
}
CFGInputHandler::~CFGInputHandler()
{
}
void CFGInputHandler::getMS()
{
    ms.open(args[1]);//open file to ptr
    
    if (!ms) //if file not opened
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
