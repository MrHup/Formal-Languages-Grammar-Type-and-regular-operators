#include "Nodes.h"

#ifndef GRAMMARTEST_H_INCLUDED
#define GRAMMARTEST_H_INCLUDED



class Grammar{
public:
    // no reason to use different classes for terminals and non terminals as they have the same structure
    Terminal *first_terminal, *first_non_terminal, *last_terminal, *last_non_terminal, *first_start, *last_start;
    // list of production rules for easy access when doing operations
    ProdRule *first_rule, *last_rule;

    Grammar();
    //~Grammar();
    void append_prodRule(const char *LHS, const char *RHS);
    void append_terminal(const char *name);
    void append_non_terminal(const char *name);

    void append_start(const char *name);
    void parse_and_print(Terminal *pars_t);

    void createRule(const char *text);
    char* replaceWithSymb(const char *str);
    void updateRules();
    int get_type();

    void show_grammar();

};

#endif
