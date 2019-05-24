#ifndef USEFULFUNC_H_INCLUDED
#define USEFULFUNC_H_INCLUDED

int getWhatsInsideBrackets(char *a);
void removeSpecialChars(char *txt);
Grammar makeUnion(Grammar *A, Grammar *B);
void renameCopies(Grammar *A, Grammar *B);
bool check_unique(Grammar *A);
bool check_pattern(char *txt);

#endif // USEFULFUNC_H_INCLUDED
