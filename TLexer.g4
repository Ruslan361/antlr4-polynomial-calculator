// DELETE THIS CONTENT IF YOU PUT COMBINED GRAMMAR IN Parser TAB
lexer grammar TLexer;

INT : [0-9]+;
WS  : [ \t\r]+ -> skip;
NL  : '\n';

PLUS   : '+';
MINUS  : '-';
MULT   : '*';
DIV    : '/';
POPEN  : '(';
PCLOSE : ')';
VAR    : [xyz];
POW    : '^';
EQ     : '=';
USERVAR: [A-Z]+;
PRINT  : 'print';
CALCULATE : 'calculate';