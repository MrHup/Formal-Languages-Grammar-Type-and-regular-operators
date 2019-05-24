#ifndef COMBINE_H_INCLUDED
#define COMBINE_H_INCLUDED

void copyTerminals(Grammar *A, Grammar *B, Grammar *G);
void copyTerminals(Grammar *A, Grammar *G);
Grammar Union(Grammar *A, Grammar *B);
Grammar Product(Grammar *A, Grammar *B);
Grammar Kleene(Grammar *A);

#endif // COMBINE_H_INCLUDED
