#include <iostream>
#include <strings.h>
#include "../include/GrammarTest.h"
#include "../include/Nodes.h"

Grammar::Grammar(){
    first_rule = NULL;
    last_rule = NULL;
    first_non_terminal = NULL;
    first_terminal = last_non_terminal = last_terminal = first_start = last_start = NULL;
}

/*Grammar::Grammar(Grammar *G){
    first_rule = G->first_rule;
    last_rule = G->last_rule;
    first_non_terminal = G->first_non_terminal;
    first_terminal = G->first_terminal;
    last_non_terminal = G->last_non_terminal;
    last_terminal = G->last_terminal;
    first_start = G->first_start;
    last_start = G->last_start;
}*/

void Grammar::append_prodRule(const char *LHS, const char *RHS){
    ProdRule *n ;
    n= new ProdRule(LHS,RHS);
    if(first_rule == NULL){
        first_rule = n;
        last_rule = n;
    }else{
        last_rule->next = n;
        last_rule = n;
    }
}

void Grammar::append_terminal(const char *name){
    Terminal *n;
    n= new Terminal(name);
    if(first_terminal == NULL){
        first_terminal = n;
        last_terminal = n;
    }else{
        last_terminal->next = n;
        last_terminal = n;
    }
}

void Grammar::append_non_terminal(const char *name){
    Terminal *n;
    n= new Terminal(name);
    if(first_non_terminal == NULL){
        first_non_terminal = n;
        last_non_terminal = n;
    }else{
        last_non_terminal->next = n;
        last_non_terminal = n;
    }
}

void Grammar::append_start(const char *name){
    Terminal *n ;
    n= new Terminal(name);
    if(first_start == NULL){
        first_start = n;
        last_start = n;
    }else{
        last_start->next = n;
        last_start = n;
    }
}

void Grammar::parse_and_print(Terminal *pars_t){
    while(pars_t != NULL){
        std::cout<<pars_t->label;
        if(pars_t->next!=NULL) std::cout<<",";
        pars_t = pars_t->next;
    }
}

void Grammar::createRule(const char *text){
// creates production rule from text, also determines its type
// txt = "A - B|Ca"
    char *txt = new char[strlen(text)+2];
    strcpy(txt,text);
    char *left, *right;
    int n = strlen(txt),i;
    for(i=0;i<n;i++){
        if(txt[i]=='-') {
                txt[i]=NULL;
                left = txt;
                break;
        }
    }
    right = txt+i+1;
    for(i++;i<n;i++){
        if(txt[i]=='|'){
            txt[i]=NULL;
            append_prodRule(left,right);
            right = txt+i+1;
        }
    }
    append_prodRule(left,right);
}
char* Grammar::replaceWithSymb(const char *str){
    char *aux = new char[strlen(str)+2];
    strcpy(aux,str);
    Terminal *pars = first_non_terminal;
    // replace non-terminals with 'A'

    while(pars!=NULL){
        char *k = strstr(aux, pars->label);
        while(k!=NULL){

            // replace with A
            strcpy(k+1,k+strlen(pars->label));
            *k='A';
            k = strstr(k+1, pars->label);
        }
        pars = pars->next;
    }
    // replace terminals with 'a'
    pars = first_terminal;
    while(pars!=NULL){
        char *k = strstr(aux, pars->label);
        while(k!=NULL){
            // replace with A
            strcpy(k+1,k+strlen(pars->label));
            *k='b';
            k = strstr(k+1, pars->label);
        }
        pars = pars->next;
    }

    return aux;
}

void Grammar::updateRules(){
    ProdRule *pars=first_rule;
    char *cuv1, *cuv2;
    while(pars!=NULL){
        cuv1= new char[strlen(pars->LHS)+2];
        cuv2= new char[strlen(pars->RHS)+2];
        strcpy(cuv1, replaceWithSymb(pars->LHS));
        strcpy(cuv2, replaceWithSymb(pars->RHS));
        int l1 = strlen(cuv1), l2 = strlen(cuv2);
        if(l1==1){
            //compress the form
            int n = strlen(cuv2);
            for(int i=0;i<n-1;i++){
                if((cuv2[i]==cuv2[i+1] && cuv2[i]!='A') || cuv2[i]=='#') { //dont touch the non-terminals as A-aAB is not type 3
                        strcpy(cuv2+i,cuv2+i+1);
                        i--;n--;
                }
            }
            //std::cout<<cuv2<<"\n";
            // check to see if it is mixed, left or right sided
            if(strcmp(cuv2,"Ab")==0) pars->type = 4; // left linear production rule
            else if(strcmp(cuv2,"bA")==0) pars->type = 3; // right linear production rule
            else if(strcmp(cuv2,"b")==0 || strcmp(cuv2,"A")==0 || strcmp(cuv2,"#")==0) pars->type = 5;
            else pars->type = 2;
        }
        else{
            if(l1>l2) pars->type = 0;
            else pars->type = 1;
        }
        pars = pars->next;
    }
}

int Grammar::get_type(){
     updateRules();
     ProdRule *pars = first_rule;
     int minimum = 5;
     while(pars!=NULL){
        //std::cout<<pars->LHS<<" & "<<pars->RHS<<" "<<pars->type<<"\n";
        if(pars->type == 4 && minimum == 3) minimum = 2;
        else if(pars->type == 3 && minimum == 4) minimum = 2;
        else if(pars->type<minimum) minimum = pars->type;
        pars = pars->next;
     }
     if(minimum > 3) minimum = 3;
     return minimum;
}

void Grammar::show_grammar(){
    std::cout<<"Vn={";
    parse_and_print(first_non_terminal);
    std::cout<<"}\nVt={";
    parse_and_print(first_terminal);
    std::cout<<"}\nS={";
    parse_and_print(first_start);
    std::cout<<"}\nP={";
    ProdRule *pars=first_rule;

    while(pars!=NULL){
        if(pars->passed==false){
           std::cout<<pars->LHS<<"->"<<pars->RHS;
            pars->passed = true;
            ProdRule *pars2 = pars->next;
            while(pars2!=NULL){
                if(strcmp(pars->LHS,pars2->LHS)==0 && pars2->passed==false){ // first time iterated
                    pars2->passed = true;
                    std::cout<<"|"<<pars2->RHS;
                }
                pars2=pars2->next;
            }
            //check for other rules
            std::cout<<",";
        }
        pars->passed = false;
        pars = pars->next;
    }
    std::cout<<"\b}\n";
}
