%{
    #include "main.h"

    void yyerror(const char *s);
    extern int yylex();
    extern int yyparse();
    extern const char* yytext ;
    actionStack semanticStack ; 
    
    int dimsDepth = 0; 
    int anchor = 0;
    int tabs = 0 ;
    OPcode valDtype ;
    string idText ;
    string dtypeText ;
    ofstream fp("gen.c") ;
    ostream& operator<<(ostream& os, action act){
        for(int i=0; i<act.size(); i++) os <<"[" << act.at2(i,0) << " , " <<  act.at2(i,1) << "]" ;
        return os ;    
    }

    ostream& operator<<(ostream& os, actionStack acts){
        os << "{ " ;
        for(int i=0; i<acts.size(); i++) os << acts[i] << "," ;
        os << " }\n" ;
        return os ;    
    }

%}

%token FUN
%token ID
%token VAR
%token VAL
%token DTYPE
%token DVAL
%token RET
%token FOR

%start start

%left ','
%left '='
%left '+' '-'
%left '*' '/' 
%left '{' 
%left '('
%left '['

%nonassoc UMINUS


%%
start:

    | {fp << "#include<stdio.h>\n"; fp << "#include<stdlib.h>\n";} statement 
    ;

declareFunction:
    FUN fid_ '(' initialList ')'  {tabs++;fp<<semanticStack.declareFunction();semanticStack.clear();fp<<"{\n"+string(tabs,'\t');} '{' statement
    | FUN fid_ '(' initialList ')' ':' DTYPE_ {tabs++;fp<<semanticStack.declareFunction(true);semanticStack.clear();fp<<"{\n"+string(tabs,'\t');} '{' statement
    ;
fid_:
    ID  {semanticStack.push(OPfun,string(idText));}
    ;
aid_:
    ID  {semanticStack.push(OPid,string(idText));}
    ;  
entry :
    '{' {fp<<"{\n"+string(++tabs,'\t');semanticStack.symbolTable.push();} statement statement 
    ;

statement:
    | '}' {fp <<"\r" << string(--tabs,'\t') << "}\n";semanticStack.symbolTable.pop_back();}
    | defination newline {semanticStack.clear();} statement 
    | expr {fp << semanticStack.exprToString();semanticStack.clear();}  newline statement 
    | newline statement
    | declareFunction {semanticStack.clear();} statement
    | RET nullableExpr {fp<<"return " << semanticStack.exprToString(); semanticStack.clear();} newline statement
    | FOR '(' {fp<<"for(";}  loopVariable splitdot loopVariable  splitdot loopVariable ')' {fp<<")";semanticStack.clear();} entry  statement
    | entry
    ;

splitdot:
    ';' {fp<<";";}
    ;
loopVariable:
    |  defination {semanticStack.clear();}
    | expr {fp << semanticStack.exprToString();semanticStack.clear();}
    ;
newline:
    ';' {fp<<";\n"+string(tabs,'\t');}
    ;
defination:
      VAR aid_ ':' DTYPE_ {fp << semanticStack.assignment(false);semanticStack.clear();}
    | VAL aid_ ':' DTYPE_ {fp << semanticStack.assignment(true);semanticStack.clear();}
    | VAR aid_ ':' DTYPE_ '=' expr {fp << semanticStack.assignment(false,true);semanticStack.clear();}
    | VAL aid_ ':' DTYPE_ '=' expr {fp << semanticStack.assignment(true,true);semanticStack.clear();}
    ;

deimensionalIndex:

    |  '[' expr {semanticStack.clacluateExpr(); dimsDepth--;} ']' deimensionalIndex
    ;

variableIndex2 :
    | rbracket expr  lbracket variableIndex2
    ;    
variableIndex:
      rbracket expr  lbracket variableIndex2
    ;
lbracket:
    ']' {semanticStack.push(OParithmetic,"]");}
    ;
rbracket:
    '[' {semanticStack.push(OParithmetic,"[");anchor=semanticStack.size();}
    ;
initialList :

    | fid_ ':' DTYPE_ 
    | initialList ',' initialList  
    ;

expr:
       expr ',' expr {semanticStack.push(OParithmetic,",");}
    |  expr '+' expr {semanticStack.push(OParithmetic,"+");}
    |  expr '-' expr {semanticStack.push(OParithmetic,"-");}
    |  expr '*' expr {semanticStack.push(OParithmetic,"*");}
    |  expr '/' expr {semanticStack.push(OParithmetic,"/");}
    |  expr '=' expr {semanticStack.push(OParithmetic,"=");}
    | '('  expr ')' 
    | '{' {semanticStack.push(OParithmetic,"{");} expr '}' {semanticStack.push(OParithmetic,"}");}
    |  cfid '(' {semanticStack.push(OParithmetic,"(");} nullableExpr ')' {semanticStack.push(OParithmetic,")");}
    |  caid variableIndex 
    | '-' expr %prec UMINUS {semanticStack.push(OParithmetic,"m");}
    |  caid 
    |  DVAL {semanticStack.push(OPdimension,to_string(0)); semanticStack.back().push(valDtype,string(yytext));}
cfid:
    ID  {semanticStack.push(OPfindfun,string(idText));}
    ;
caid:
    ID {semanticStack.push(OPfind,string(idText)); }
    ;
nullableExpr:

    | expr 
    ;

DTYPE_:
    add_dtype deimensionalIndex {semanticStack.combineDtype(dimsDepth-1); dimsDepth=0;}
    ;
add_dtype:
    DTYPE {semanticStack.push_dtype(dtypeText);}
    ;
functionEntry:
      '{' statement  
    ;
%%

void yyerror(const char *s) {
    printf("%s ", s);
}
//{semanticStack.push(OPdimension,to_string(0));semanticStack.back().push(OPint,string(yytext));}