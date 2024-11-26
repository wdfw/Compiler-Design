#include "main.h"
#include "yacc.tab.h"

extern int yyparse(void);
extern FILE* yyin;
extern bool show_tokens ;
extern bool show_lines ;
extern int yylex(void) ;


int main(int argc, char* argv[]){
    
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Can't open file.\n");
        return -1;
    }


    if(argc>=4 && string(argv[3])=="-s") show_tokens=true ;


    yyin = fp;
    yyparse();
    fclose(fp);

    return 0;
}