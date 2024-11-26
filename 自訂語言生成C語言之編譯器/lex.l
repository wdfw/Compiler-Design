%{
    #include "main.h"
    #include "yacc.tab.h"
    using namespace std;
    int lines =  1 ; 
    bool show_lines = false ;
    bool show_tokens = false ;
    string add_lines(int i=1);
    extern actionStack semanticStack ; 
    extern OPcode valDtype ;
    extern string dtypeText ;

    extern string idText ;

%}

%x SINGLE_COMMENT 
%x MULTI_COMMENT 
%x ERROR_MODE 

Blank [ \f\r\t\v]+
 
Bool_Value true|false

Char_Value \'(\\[\?\'\"\\\/abfnrtv]|[^\?\'\"\\\/])\'        
String_Value \"(\\[\?\'\"\\\/abfnrtv]|[^\?\'\"\\\/\n])*?\"
Int_Value ([1-9][0-9]*|0[bB][01]+|0[xX][0-9a-fA-F]+|0[0-7]*)
Real_Value ([1-9][0-9]*|0)\.([0-9]+)
Identifier [_a-zA-Z][_a-zA-Z0-9]*
Compare ([\=\!\>\<]\=)|\<|\> 
Dtype bool|char|int|real
Error .
Error_String [^ \f\r\t\v]*
%%
"\n" {if(show_tokens) cout<<"\n" <<add_lines();}
{Blank} {;}

\/\/ {BEGIN SINGLE_COMMENT;}
<SINGLE_COMMENT>.*[^\n]     { BEGIN 0; }

\/\* {BEGIN MULTI_COMMENT;}
<MULTI_COMMENT>\*\/ { BEGIN 0; }
<MULTI_COMMENT>. { ; }
<MULTI_COMMENT>\n { if(show_tokens) cout<<"\n" <<add_lines(); }

\( {if(show_tokens) cout<<"LEFT_PARENTHESES:"<<yytext<<" ; "; return '(';}
\) {if(show_tokens) cout<<"RIGHT_PARENTHESES:"<<yytext<<" ; "; return ')';}

\{ {if(show_tokens) cout<<"LEFT_CURLY_BRACKET:"<<yytext<<" ; ";return '{';}        
\} {if(show_tokens) cout<<"RIGHT_CURLY_BRACKET:"<<yytext<<" ; "; return '}';}

\[ {if(show_tokens) cout<<"LEFT_BRACKET:"<<yytext<<" ; "; return '[';}
\] {if(show_tokens) cout<<"RIGHT_BRACKET:"<<yytext<<" ; "; return']';}

\, {if(show_tokens) cout<<"COMMA:"<<yytext<<" ; "; return ',';}
\; {if(show_tokens) cout<<"SEMICOLON:"<<yytext<<" ; "; return ';';}
\: {if(show_tokens) cout<<"COLON:"<<yytext<<" ; "; return ':';}

"+" {if(show_tokens) cout<<"ADD:"<<yytext<<" ; "; return '+';}
"-" {if(show_tokens) cout<<"SUB:"<<yytext<<" ; "; return '-';}
"*" {if(show_tokens) cout<<"MUL:"<<yytext<<" ; "; return '*';}
"/" {if(show_tokens) cout<<"DIV:"<<yytext<<" ; "; return '/';}
"=" {if(show_tokens) cout<<"ASSIGN:"<<yytext<<";"; return '=';}

{Compare} {if(show_tokens) cout<<"CMP:"<<yytext<<" ; "; }

if {if(show_tokens) cout<<"IF:"<<yytext<<" ; ";}
else {if(show_tokens) cout<<"ELSE:"<<yytext<<" ; ";}
for {if(show_tokens) cout<<"FOR:"<<yytext<<" ; "; return FOR;}
while {if(show_tokens) cout<<"WHILE:"<<yytext<<" ; ";}
do {if(show_tokens) cout<<"DO:"<<yytext<<" ; ";}
switch {if(show_tokens) cout<<"SWITCH:"<<yytext<<" ; ";}
case {if(show_tokens) cout<<"CASE:"<<yytext<<" ; ";}

{Dtype} {if(show_tokens) cout<<"DTYPE:"<<yytext<<" ; ";dtypeText=string(yytext) ;return DTYPE;}
{Bool_Value} {if(show_tokens) cout<<"BOOL_VAULE:"<<yytext<<" ; ";}
{Int_Value} {if(show_tokens) cout<<"INT_VALUE:"<<yytext<<" ; ";valDtype=OPint; return DVAL;}
{Real_Value} {if(show_tokens) cout<<"REAL_VALUE:"<<yytext<<" ; ";valDtype=OPfloat; return DVAL;}
{Char_Value} {if(show_tokens) cout<<"CHAR_VALUE:"<<yytext<<" ; "; }
{String_Value} {if(show_tokens) cout<<"STRING_VALUE:"<<yytext<<" ; ";valDtype=OPstring; return DVAL;}

var {if(show_tokens) cout<<"VAR:"<<yytext<<" ; "; return VAR;}
val {if(show_tokens) cout<<"VAL:"<<yytext<<" ; "; return VAL;}

fun {if(show_tokens) cout<<"FUN:"<<yytext<<" ; "; return FUN;}
ret {if(show_tokens) cout<<"RET:"<<yytext<<" ; "; return RET;}

class {if(show_tokens) cout<<"CLASS:"<<yytext<<" ; ";}

{Identifier} {if(show_tokens) cout<<"ID:"<<yytext<<" ; ";idText=string(yytext); return ID;}

{Error} {BEGIN ERROR_MODE; if(show_tokens) cout<<"\n------------------------\nUnknown Tokens:"<<yytext; }
<ERROR_MODE>{Error_String} { if(show_tokens) cout<<yytext<<"\n------------------------\n"; BEGIN 0;}

%%
//----------------------------------------------------------------------------------------
string add_lines(int i){
    if(show_lines) return to_string(lines++)+ ": " ;
    return "" ;
}

int yywrap(void) {
    return 1;
}
