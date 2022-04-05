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
    std::cout << "[InputHandler]: initialized" << std::endl;
    std::cout << "[InputHandler]: opening input file" << std::endl;
    fp = freopen(argv[2], "r", stdin);
    if (fp == nullptr)
    {
        std::cout << "[InputHandler][ERROR]: couldn't open input file" << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "[InputHandler]: opened input file" << std::endl;
    }
    
}
InputHandler::~InputHandler()
{
    delete fp;
}
char* InputHandler::getQ()
{
    return nullptr;
}

char* InputHandler::getE()
{
    return nullptr;
}
Transition* InputHandler::getd()
{
    return nullptr;
}
char InputHandler::getq0()
{
    return ' ';
}
char* InputHandler::getF()
{
    return nullptr;
}
