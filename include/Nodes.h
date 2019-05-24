#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED


class ProdRule{
public:
    char *LHS, *RHS;
    int type;
    bool passed;
    ProdRule *next;
    ProdRule();
    ProdRule(const char *left_side, const char *right_side);

    void updateType();
};

class Terminal{
public:
    char *label;
    Terminal *next;
    ~Terminal();
    Terminal(const char *lb);
};

#endif // NODES_H_INCLUDED
