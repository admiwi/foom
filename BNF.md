
```
if stmt = "if" , ws , "(" , exp , ")" , closure;

for stmt = "for" , ws , "(" ,
          assignment exp | "" , ";" , 
          logical exp | "" , ";",
          exp | "" , ")" , closure;


closure = "{" , ws , 
        [[data type|class , {ws}+] , variable , 
          {ws , "," , ws , [data type|class , {wsp}+] , variable}*,  ws , ":" , ws] , 
        [exp , {exp end , exp}*] , "}";

assignment exp = bare tuple , ws , assignment op , ws , exp;
binary exp = exp , ws , exp;
unary exp = unary op , ws , exp;
logical exp = exp , ws , logical op , ws , exp , {ws , logical op , ws , exp}*; 
end exp = newline 
        | ";";
exp = assignment exp 
    | binary exp 
    | unary exp 
    | logical exp
    | "(" , exp , ")";

func call = func , "(" , bare list , ")";
func = op func
     | closure;
op func = "`" , overload op , "`";

declare var = data type , space , variable
            | class , space , variable;

tuple = "<>"
      | "<" , bare list , ">";
bare tuple = variable , {" , ", variable}*;

map = "[:]"
    | "[" , ws , term , space , ":" , ws , term , ws , {term , space , ":" , ws , term}* , ws , "]";
bare map = term , space , ":" , ws , term , ws , {term , ws , ":" , ws , term}*;

list = "[" , [term , {" , ",term}* , "]";

bare list = term , {" , ",term}*;

member = term,".",term;
term  = member
      |variable
      |string
      |decimal
      |integer
      |class
      |data type
      |func call
      |func;

string  = '"' , {utf|dquote escapes|format} , '"'
        | "'" , {utf|squote escapes|format} , "'";

format = "%{" , sp , variable , [sp , ":" , sp , {fmt flag} , ["." , precision]] , "}";

fmt flag = integer 
         | "+" 
         | "-" 
         | "0";

variable = {letter|"_"} , {letter|digit|"_"}*;

decimal = {digit} , ["." , {digit}];

integer = {digit};

return type = {_return type_ , ","}* _return type_ 
            | "(" , {_return type_ , ","}* _return type_ , ")";
_return type_ = (data type 
                | class);

class = ucase letter , {letter|digit|"_"};
data type  = "obj" | "int" | "dec" | "bool" | "func" | "bin" | "list" | "map";

sp = {" "}*;
ws = {wsp}*;
wsp = ? white space characters ? ;
newline = "\n"|"\r\n"|"\r";

overload op = "^" | "&" | "*" | ":" | "+" | "-" | "==" | "and" | "or" | 'as';
logical op = '<' | '>' | '<=' | '>=' | '==' | '!=' | '&&' | '||' | 'and' | 'or' | 'xor';
unary op = '&' | '*' | '+' | '-' | '~' | '!' | 'not';
binary op = '*' | '/' | '%' | '+' | '-' | '<<' | '>>' | 'div' | '&' | '^' | '|' | 'is' | 'was' | 'as';
assignment op	= '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|=';

dquote escapes = '\"'|escapes;
squote escapes = "\'"|escapes;

letter = ucase|lcase
ucase letter = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z";
lcase letter = "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | "u" | "v" | "W" | "X" | "Y" | "Z";
hex = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "A" | "B" | "C" | "D" | "E" | "F";
digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9";
octal = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7";
utf = ? utf8 ?;
escapes = "\%" | "\a" | "\b" | "\f" | "\n" | "\r" | "\t" | "\v" | "\\" | "\" , octal , octal , octal|"\x" , hex , hex|"\x" , hex , hex , hex , hex;
```