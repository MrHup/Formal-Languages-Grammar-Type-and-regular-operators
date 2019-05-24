#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include "include/GrammarTest.h"
#include "include/Nodes.h"
#include "include/UsefulFunc.h"
#include "include/Combine.h"

std::ifstream f("input.in");

Grammar createG(char *txt){
    Grammar G;
    // returns a grammar. The sets are separated by $space and the elements from within by comma
    int n=strlen(txt);
    char *t=new char[n];
    strcpy(t,txt);
    //std::cout<<t<<"\n";
    // removes space and other unwanted characters
    removeSpecialChars(t);
    // add non-terminals
        //get the first set
        int x = getWhatsInsideBrackets(t);
        char *k = strtok(t,",");
        while(k!=NULL){
            G.append_non_terminal(k);
            //std::cout<<"Appended non-terminal: "<<k<<"\n";
            k=strtok(NULL,",");

        }
        strcpy(t,t+x);
    // add terminals
        x = getWhatsInsideBrackets(t);
        k = strtok(t,",");
        while(k!=NULL){
            G.append_terminal(k);
            //std::cout<<"Appended terminal: "<<k<<"\n";
            k=strtok(NULL,",");
        }
        strcpy(t,t+x);
    // add starting points
        x = getWhatsInsideBrackets(t);
        k = strtok(t,",");
        while(k!=NULL){
            G.append_start(k);
            //std::cout<<"Appended start: "<<k<<"\n";
            k=strtok(NULL,",");
        }
        strcpy(t,t+x);
    // add production rules
        x = getWhatsInsideBrackets(t);
        k = strtok(t,",");
        while(k!=NULL){
            //std::cout<<"Rule: "<<k<<"\n";
            G.createRule(k);
            //std::cout<<"Appended rule: "<<k<<"\n";
            k=strtok(NULL,",");
        }
    return G;

}

int main()
{
    //Grammar G1=createG("{A,B,C,S} {a,b,c} {S} {S-aA, A-bB|b, B-cC|c}");
    int n;
    f>>n;
    f.get();

    if(n==1){
        char a[100]="";
        f.get(a,99);
        if(strlen(a)%8==0){
            strcat(a," ");
        }
        if(check_pattern(a) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G1 = createG(a);

        if(check_unique(&G1)==false) return 0;
        std::cout<<"Type of first grammar: "<<G1.get_type()<<"\n";
        f.get();
        char b[100]="";
        while(f.get(b,99)){
            if(strlen(b)%8==0){
                strcat(b," ");
            }
            if(check_pattern(b) == false){
                std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
                return 0;
            }
            Grammar G2 = createG(b);

            if(check_unique(&G2)==false) return 0;
            std::cout<<"Type of grammar: "<<G2.get_type()<<"\n";
            f.get();
        }

    }
    else if(n==2){
            char a[100]="";
        f.get(a,99);
        if(strlen(a)%8==0){
            strcat(a," ");
        }
        if(check_pattern(a) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G1 = createG(a);

        if(check_unique(&G1)==false) return 0;
        std::cout<<"Type of first grammar: "<<G1.get_type()<<"\n";

        char b[100]="";
        f.get();
        f.get(b,99);
        if(strlen(b)%8==0){
            strcat(b," ");
        }
        if(check_pattern(b) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G2 = createG(b);

        if(check_unique(&G2)==false) return 0;
        std::cout<<"Type of second grammar: "<<G2.get_type()<<"\n\n";

        renameCopies(&G1,&G2);

        G1.show_grammar();
        std::cout<<"\n";
        G2.show_grammar();

        std::cout<<"----\n";
        Grammar G3 = Union(&G1,&G2);
        G3.show_grammar();
    }
    else if(n==3){
            char a[100]="";
        f.get(a,99);
        if(strlen(a)%8==0){
            strcat(a," ");
        }
        if(check_pattern(a) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G1 = createG(a);

        if(check_unique(&G1)==false) return 0;
        std::cout<<"Type of first grammar: "<<G1.get_type()<<"\n";

        char b[100]="";
        f.get();
        f.get(b,99);
        if(strlen(b)%8==0){
            strcat(b," ");
        }
        if(check_pattern(b) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G2 = createG(b);

        if(check_unique(&G2)==false) return 0;
        std::cout<<"Type of second grammar: "<<G2.get_type()<<"\n\n";

        renameCopies(&G1,&G2);

        G1.show_grammar();
        std::cout<<"\n";
        G2.show_grammar();

        std::cout<<"----\n";
        Grammar G3 = Product(&G1,&G2);
        G3.show_grammar();
    }
    else if(n==4){
            char a[100]="";
        f.get(a,99);
        if(strlen(a)%8==0){
            strcat(a," ");
        }
        if(check_pattern(a) == false){
            std::cout<<"ERROR\\\\::The input does not follow the required format.\n";
            return 0;
        }
        Grammar G1 = createG(a);

        if(check_unique(&G1)==false) return 0;
        std::cout<<"Type of grammar: "<<G1.get_type()<<"\n";
        G1.show_grammar();

        std::cout<<"----\n";
        Grammar G3 = Kleene(&G1);
        G3.show_grammar();
    }
    system("PAUSE");
    return 0;
}
