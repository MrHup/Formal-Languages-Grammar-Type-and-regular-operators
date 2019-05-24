#include <iostream>
#include <cstring>
#include "../include/GrammarTest.h"
#include "../include/Nodes.h"
#include "../include/UsefulFunc.h"
#include "../include/Combine.h"

void copyTerminals(Grammar *A, Grammar *B, Grammar *G){
    renameCopies(A,B);
    // add terminals for A and B
    Terminal *pars = A->first_terminal;
    while(pars!=NULL){
        G->append_terminal(pars->label);
        pars = pars->next;
    }
    pars = B->first_terminal;
    while(pars!=NULL){
        G->append_terminal(pars->label);
        pars = pars->next;
    }

    // add non-terminals for A and B
    pars = A->first_non_terminal;
    while(pars!=NULL){
        G->append_non_terminal(pars->label);
        pars = pars->next;
    }
    pars = B->first_non_terminal;
    while(pars!=NULL){
        G->append_non_terminal(pars->label);
        pars = pars->next;
    }
    // create new starting point
    G->append_start("NewS");
}

void copyTerminals(Grammar *A, Grammar *G){
    // add terminals for
    Terminal *pars = A->first_terminal;
    while(pars!=NULL){
        G->append_terminal(pars->label);
        pars = pars->next;
    }

    // add non-terminals for A
    pars = A->first_non_terminal;
    while(pars!=NULL){
        G->append_non_terminal(pars->label);
        pars = pars->next;
    }
    // create new starting point
    G->append_start("NewS");
    // copy rules
    ProdRule *pars2 = A->first_rule;
    while(pars2!=NULL){
        G->append_prodRule(pars2->LHS,pars2->RHS);
        pars2 = pars2->next;
    }
}

Grammar Union(Grammar *A, Grammar *B){ // deals with the Union of 2 grammars
    Grammar G;
    copyTerminals(A,B,&G);
    // make NewS point to all the starts
    Terminal *pars = A->first_start;
    while(pars!=NULL){
        char *rule = new char[6+strlen(pars->label)];
        strcpy(rule,"NewS-");
        strcat(rule,pars->label);
        G.createRule(rule);
        pars = pars->next;
    }
    pars = B->first_start;
    while(pars!=NULL){
        char *rule = new char[6+strlen(pars->label)];
        strcpy(rule,"NewS-");
        strcat(rule,pars->label);
        G.createRule(rule);
        pars = pars->next;
    }
    // copy rules from A
    ProdRule *pars2 = A->first_rule;
    while(pars2!=NULL){
        char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)];
        strcpy(rule,pars2->LHS);
        strcat(rule,"-");
        strcat(rule,pars2->RHS);
        G.createRule(rule);
        pars2 = pars2->next;
    }
    // copy rules from B
    pars2 = B->first_rule;
    while(pars2!=NULL){
        char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)];
        strcpy(rule,pars2->LHS);
        strcat(rule,"-");
        strcat(rule,pars2->RHS);
        G.createRule(rule);
        pars2 = pars2->next;
    }
    return G;
}

//-------

// if there are more than 1 starting points. Debug that
Grammar Product(Grammar *A, Grammar *B){
    if(A->get_type()==3 && B->get_type()==3){
        renameCopies(A,B);
        Grammar G;
        // add terminals for A and B
        Terminal *pars = A->first_terminal;
        while(pars!=NULL){
            G.append_terminal(pars->label);
            pars = pars->next;
        }
        pars = B->first_terminal;
        while(pars!=NULL){
            G.append_terminal(pars->label);
            pars = pars->next;
        }

        // add non-terminals for A and B
        pars = A->first_non_terminal;
        while(pars!=NULL){
            G.append_non_terminal(pars->label);
            pars = pars->next;
        }
        pars = B->first_non_terminal;
        while(pars!=NULL){
            G.append_non_terminal(pars->label);
            pars = pars->next;
        }
        // create starting points from A
        pars = A->first_start;
        while(pars!=NULL){
            G.append_start(pars->label);
            pars = pars->next;
        }

        //---
        // copy rules from A
        ProdRule *pars2 = A->first_rule;
        while(pars2!=NULL){
            char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)+strlen(B->first_start->label)];
            strcpy(rule,pars2->LHS);
            strcat(rule,"-");
            strcat(rule,pars2->RHS);


            char *cuv2= new char[strlen(pars2->RHS)+1];
            strcpy(cuv2, A->replaceWithSymb(pars2->RHS));

            //std::cout<<cuv2<<"\n";

            int n = strlen(cuv2);
            for(int i=0;i<n-1;i++){
                if(cuv2[i]==cuv2[i+1] && cuv2[i]!='A') { //dont touch the non-terminals as A-aAB is not type 3
                        strcpy(cuv2+i,cuv2+i+1);
                        i--;n--;
                }
            }
            // check to see if it is mixed, left or right sided
            if(strcmp(cuv2,"b")==0 ){
                // change rule from A-p to A-pS2
                //std::cout<<"SCHIMBAT\n";
                strcat(rule,B->first_start->label);
            }

            //G.append_prodRule(pars2->LHS,pars2->RHS);
            G.createRule(rule);
            pars2 = pars2->next;
        }
        // copy rules from B
        pars2 = B->first_rule;
        while(pars2!=NULL){
            char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)];
            strcpy(rule,pars2->LHS);
            strcat(rule,"-");
            strcat(rule,pars2->RHS);
            G.createRule(rule);
            pars2 = pars2->next;
        }
        return G;
    }else{
        Grammar G;
        copyTerminals(A,B,&G);
        // make NewS point to all the starts
        char *rule2 = new char[6+strlen(A->first_start->label)+strlen(B->first_start->label)];
        strcpy(rule2,"NewS-");
        strcat(rule2,A->first_start->label);
        strcat(rule2,B->first_start->label);
        G.createRule(rule2);
        // copy rules from A
        ProdRule *pars2 = A->first_rule;
        while(pars2!=NULL){
            char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)];
            strcpy(rule,pars2->LHS);
            strcat(rule,"-");
            strcat(rule,pars2->RHS);
            G.createRule(rule);
            pars2 = pars2->next;
        }
        // copy rules from B
        pars2 = B->first_rule;
        while(pars2!=NULL){
            char *rule = new char[1+strlen(pars2->LHS)+strlen(pars2->RHS)];
            strcpy(rule,pars2->LHS);
            strcat(rule,"-");
            strcat(rule,pars2->RHS);
            G.createRule(rule);
            pars2 = pars2->next;
        }
        return G;
    }
}

//----Kleene closure

void Kleene_3(Grammar *A, Grammar *G){
    copyTerminals(A,G);
    // add S* - S|#
    G->append_prodRule("NewS",A->first_start->label);
    G->append_prodRule("NewS","#");

    // add P'
    ProdRule *pars2 = A->first_rule;
    while(pars2!=NULL){
        char *cuv2= new char[strlen(pars2->RHS)+1];
        strcpy(cuv2, A->replaceWithSymb(pars2->RHS));

        std::cout<<cuv2<<"\n";

        int n = strlen(cuv2);
        for(int i=0;i<n-1;i++){
            if(cuv2[i]==cuv2[i+1] && cuv2[i]!='A') { //dont touch the non-terminals as A-aAB is not type 3
                    strcpy(cuv2+i,cuv2+i+1);
                    i--;n--;
            }
        }
        // check to see if it is mixed, left or right sided
        if(strcmp(cuv2,"b")==0 ){
            // change rule from A-p to A-pS2
            char *cuv3= new char[strlen(pars2->RHS)+strlen(A->first_start->label)+1];
            strcpy(cuv3,pars2->RHS);
            strcat(cuv3,A->first_start->label);
            G->append_prodRule(pars2->LHS,cuv3);
        }
        pars2 = pars2->next;
    }

}

void Kleene_2(Grammar *A, Grammar *G){
    copyTerminals(A,G);
    // add prodrule NewS-NewSS
    char *concat = new char[strlen(A->first_start->label)+5];
    strcpy(concat,"NewS");
    strcat(concat,A->first_start->label);
    G->append_prodRule("NewS",concat);
    G->append_prodRule("NewS","#");
}

void Kleene_01(Grammar *A, Grammar *G){
    copyTerminals(A,G);
    // add [X] to nonterminals
    G->append_non_terminal("[X]");
    // make new start point to landa
    G->append_prodRule("NewS","#");
    // make new start point to old start and [X]oldStart
    G->append_prodRule("NewS",A->first_start->label);
    char *concat = new char[strlen(A->first_start->label)+5];
    strcpy(concat,"[X]");
    strcat(concat,A->first_start->label);
    G->append_prodRule("NewS",concat);

    //make the rule Xi - Si|XSi for all terminals
    Terminal *pars = A->first_terminal;
    while(pars!=NULL){
        char *concat1=new char[strlen(A->first_start->label)+20];
        char *concat2=new char[strlen(A->first_start->label)+20];
        char *concat3=new char[strlen(A->first_start->label)+20];

        strcpy(concat1,"[X]");
        strcat(concat1,pars->label);

        strcpy(concat2,A->first_start->label);
        strcat(concat2,pars->label);

        strcpy(concat3,"[X]");
        strcat(concat3,A->first_start->label);
        strcat(concat3,pars->label);

        G->append_prodRule(concat1,concat2);
        G->append_prodRule(concat1,concat3);

        pars = pars->next;
    }
}

Grammar Kleene(Grammar *A){
    Grammar G;
    if(A->get_type()==3)
        Kleene_3(A,&G);
    else if(A->get_type()==2)
        Kleene_2(A,&G);
    else
        Kleene_01(A,&G);
    return G;
}
