#include "../include/Nodes.h"
#include <iostream>
#include <strings.h>

ProdRule::ProdRule(){
    LHS = NULL;
    RHS = NULL;
    next = NULL;
    passed = false;
    type = 0;
}

ProdRule::ProdRule(const char *left_side,const char *right_side){
    LHS = new char[strlen(left_side)+3];
    RHS = new char[strlen(right_side)+3];
    strcpy(LHS, left_side);
    strcpy(RHS, right_side);
    next = NULL;
    type = 0;
    passed = false;
}

void ProdRule::updateType(){
 // update the type of the prod rule
}

Terminal::Terminal(const char *lb){
    label = new char[strlen(lb)+2];
    strcpy(label,lb);
    next = NULL;
}
