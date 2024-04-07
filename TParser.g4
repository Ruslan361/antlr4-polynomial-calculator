parser grammar TParser;
options { tokenVocab=TLexer; }

input
    : (setValueOrPrintOrCalculate (NL?))+ EOF
    ;


setValueOrPrintOrCalculate: 
    readUserVar EQ plusOrMinus #SetValue
    | PRINT plusOrMinus #Print
| CALCULATE plusOrMinus int int int #Calculate
    ;
readUserVar:
    USERVAR;
plusOrMinus
    : plusOrMinus PLUS  multOrDiv # PlusOp
    | plusOrMinus MINUS multOrDiv # BinaryMinusOp
    | multOrDiv                   # ToMultOrDiv
    ;

multOrDiv
    : multOrDiv MULT atom # MultOp
    | atom                # toAtom
    ;

atom
    :                     
     MINUS plusOrMinus        # UnaryMinusOp
    | POPEN plusOrMinus PCLOSE # ParenthesisOp
    | mon #Monom
    | readUserVar #GetValue
;

mon:
   int(pow)+ #FullMonom
   | int #MonomZeroPower
   | (pow)+ #MonomWithouCoefficient
   
;
readVar: VAR;
pow:
    readVar POW int 
;
int: INT #ConvertToInt;