#include <iostream>
#include <strings.h>
#include "../include/GrammarTest.h"
#include "../include/Nodes.h"
#include "../include/UsefulFunc.h"

// error handling

bool check_unique(Grammar *A){
    Terminal *pars = A->first_non_terminal;
    while(pars!=NULL){
        Terminal *pars2 = A->first_terminal;
        while(pars2!=NULL){
            if(strcmp(pars->label,pars2->label)==0){
                std::cout<<"ERROR\\\\::The Terminals should be unique in regards to the non-terminals.\n";
                std::cout<<pars2->label<<" is repeating, you should maybe get that checked.\n";
                return false;
            }
            pars2 = pars2 -> next;
        }
        pars = pars->next;
    }
    return true;
}

bool check_pattern(char *txt){
    bool ok = false;
    int c=0;
    for(int i=0;i<strlen(txt);i++){
        if(txt[i]=='{') {
            if(ok==false) ok = true;
            else return false;
            c++;
        }else if(txt[i]=='}'){
            if(ok==true) ok = false;
            else return false;
            c++;
        }
    }
    if(c==8) return true;
    else return false;
}

int getWhatsInsideBrackets(char *a){
    // crops out the first substring contained between curly brackets
    // returns the value after the cropped string
    int n = strlen(a),i;
    int finish, ok=0;
    for(i=0;i<n;i++){
        if(a[i]=='{' && ok==0){
            strcpy(a+i,a+i+1);
            i--;
            ok++;
        }else if(a[i]=='}' && ok==1){
            a[i]=NULL;
            finish = i+1;
            break;
        }
    }
    return finish;

}

void removeSpecialChars(char *txt){
    //removes unwanted characters from the given string
    int n=strlen(txt);
    for(int i=0;i<n;i++){
        if(txt[i]==' ' || txt[i]=='>' || txt[i]=='(' || txt[i]==')'){
            strcpy(txt+i,txt+i+1);
            n--;i--;
        }
    }
}

void makeUnique(Grammar *A, const char *dup){
    // changes duplicate to duplicate'
    //changes in terminals
    Terminal *pars = A->first_non_terminal;
    while(pars!=NULL){
        if(strcmp(pars->label,dup)==0){
            pars->label = new char[strlen(dup)+2];
            strcpy(pars->label,dup);
            strcat(pars->label,"'");
            break;
        }
        pars = pars->next;
    }
    //changes in terminals
    pars = A->first_terminal;
    while(pars!=NULL){
        if(strcmp(pars->label,dup)==0){
            pars->label = new char[strlen(dup)+2];
            strcpy(pars->label,dup);
            strcat(pars->label,"'");
            break;
        }
        pars = pars->next;
    }
    //changes in start
    pars = A->first_start;
    while(pars!=NULL){
        if(strcmp(pars->label,dup)==0){
            pars->label = new char[strlen(dup)+2];
            strcpy(pars->label,dup);
            strcat(pars->label,"'");
            break;
        }
        pars = pars->next;
    }
    //changes in production rules
    ProdRule *pars2 = A->first_rule;
    while(pars2!=NULL){
        // deal with LHS
        char *prev = pars2->LHS;
        char *k = strstr(pars2->LHS,dup);

        //copy from 3 parts
        while(k!=NULL){
            char *aux2 = new char[strlen(pars2->LHS)+2]; // new string with +1 characters
            strcpy(aux2,pars2->LHS);
            char *f_part = new char[k-prev+1];
            strncpy(f_part,prev,k-prev);
            char *sec_part = new char[strlen(dup)+2];
            strncpy(sec_part,k,strlen(dup));
            strcat(sec_part,"'");
            char *third_part = new char[strlen(k+strlen(dup))+1];
            strcpy(third_part,k+strlen(dup));

            strcpy(aux2,f_part);
            strcat(aux2,sec_part);
            strcat(aux2,third_part);
            //std::cout<<aux2<<" change made\n";
            strcpy(pars2->LHS,aux2);
            prev = k;
            k = strstr(k+1,dup);
        }
        // deal with RHS
        prev = pars2->RHS;
        k = strstr(pars2->RHS,dup);

        //copy from 3 parts
        while(k!=NULL){
            char *aux2 = new char[strlen(pars2->RHS)+2]; // new string with +1 characters
            strcpy(aux2,pars2->RHS);
            char *f_part = new char[k-prev+1];
            strncpy(f_part,prev,k-prev);
            char *sec_part = new char[strlen(dup)+2];
            strncpy(sec_part,k,strlen(dup));
            strcat(sec_part,"'");
            char *third_part = new char[strlen(k+strlen(dup))+1];
            strcpy(third_part,k+strlen(dup));

            strcpy(aux2,f_part);
            strcat(aux2,sec_part);
            strcat(aux2,third_part);
            //std::cout<<aux2<<" change made\n";
            strcpy(pars2->RHS,aux2);
            prev = k;
            k = strstr(k+1,dup);
        }
        pars2=pars2->next;
    }
}

// get 2 grammars, everything that is duplicate, rename it by adding ' to it
void renameCopies(Grammar *A, Grammar *B){
    // rename nonTerminals
    Terminal *pars = A->first_non_terminal;
    while(pars!=NULL){
        //check all non-terms in A with all non terms and terms in B for conflict
        //non-terms
        Terminal *pars2 = B->first_non_terminal;
        while(pars2!=NULL){
            if(strcmp(pars->label,pars2->label)==0){
                makeUnique(B, pars2->label);
                break;
            }
            pars2=pars2->next;
        }
        //terms
        pars2 = B->first_terminal;
        while(pars2!=NULL){
            if(strcmp(pars->label,pars2->label)==0){
                makeUnique(B, pars2->label);
                break;
            }
            pars2 = pars2->next;
        }
        pars = pars->next;
    }
    //std::cout<<"Done with non terms\n";
    pars = A->first_terminal;
    while(pars!=NULL){
        //check all terms in A with all non terms and terms in B for conflict
        //non-terms
        Terminal *pars2 = B->first_non_terminal;
        while(pars2!=NULL){
            if(strcmp(pars->label,pars2->label)==0){
                makeUnique(B, pars2->label);
                break;
            }
            pars2=pars2->next;
        }
        //terms
        pars2 = B->first_terminal;
        while(pars2!=NULL){
            if(strcmp(pars->label,pars2->label)==0){
                makeUnique(B, pars2->label);
                break;
            }
            pars2 = pars2->next;
        }
        pars = pars->next;
    }
    //std::cout<<"Done with terms\n";

}
