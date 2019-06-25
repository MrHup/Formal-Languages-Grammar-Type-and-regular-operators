# Formal-Languages-Grammar-Type-and-regular-operators
A program that computes the type of some given grammars and applies the regular operations on them accordingly.

## Functionality

Input: Vn, Vt, q, P

4 sets containing the non-terminals, terminals, starting point and production rules.
Example of input: 
**type
{A} {END,0} {A} {A-END|0}**

If type=0 the program determines the type of the given grammars.
If type=1 the program does the union on the first 2 given grammars.
If type=2 the product is performed.
Else the Kleene Closure rules are applied on the n given grammars.
