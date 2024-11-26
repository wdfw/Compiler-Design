#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

typedef enum OPcode{
    OParithmetic, // + - * / = ,
    OPbracket, // [] {} ()  
    OPdtype, // int float intArray floatArray

    //Dval
    OPint, 
    OPfloat, 
    OPstring, 
    OPdimension,
    OPintCombine, 
    OPfloatCombine, 

    OPpunctuation, // , ; :   

    OPid, //function variable
    OPfun,
    OPother,
    OPsplit,
    OPcombine,
    OPfind,
    OPfindfun,
    OPvoid 
} OPcode ;

//[{OPdimension,1},{OPdimension,1}, ] +2
//[{OPdimension,0},{OPint,1}, ] 1

//[{OPid,wdfw},{OPintCombine,c}] 2
//[{OPfun,wdfw},{OPint,c},{OPfloat,c},{OPint,c}] ...





typedef class action : public vector<pair<OPcode,string>> {

    void checkDims(action& act){
        int dims = stoi(front().second) ;
        for(int i=0; i<dims+1; i++)
            if(act[i].second != at(i).second || act[i].second != at(i).second)  
                yyerror("ERROR: mismatched dimensions") ;
    }
    void changeDtype(action& act){
        int dims = stoi(front().second) ;
        OPcode dtype = at(dims+1).first ;
        for(int i=dims+1; i<size(); i++){
            if(act[i].first==OPfloat){
                at(i).first = OPfloat ;
            }else if(act[i].first==OPfloatCombine){
                at(i).first = OPfloatCombine ;
            }else if(act[i].first==OPintCombine){
                if(dtype==OPint || dtype==OPintCombine) at(i).first = OPintCombine ;
                else at(i).first = OPfloatCombine ;
            }
        }
    }
    void oepration(action& act, int opcode){
        int dims = stoi(front().second) ;
        for(int i=dims+1; i<size(); i++){
            switch (opcode){
            case 0: //+
                if(at(i).first==OPint){
                    at(i).second = to_string(stoi(at(i).second) + stoi(act[i].second));
                }else if(at(i).first==OPfloat){
                    at(i).second = to_string(stof(at(i).second) + stof(act[i].second));
                }else if(at(i).first==OPintCombine){
                    at(i).second = "(" + at(i).second + "+" + act[i].second + ")" ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second = "(" + at(i).second + "+" + act[i].second + ")" ;
                }
                break;
            case 1: //-
                if(at(i).first==OPint){
                    at(i).second = to_string(stoi(at(i).second) - stoi(act[i].second));
                }else if(at(i).first==OPfloat){
                    at(i).second = to_string(stof(at(i).second) - stof(act[i].second));
                }else if(at(i).first==OPintCombine){
                    at(i).second = "(" + at(i).second + "-" + act[i].second + ")" ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second = "(" + at(i).second + "-" + act[i].second + ")" ;
                }
                break;
            case 2: //*
                if(at(i).first==OPint){
                    at(i).second = to_string(stoi(at(i).second) * stoi(act[i].second));
                }else if(at(i).first==OPfloat){
                    at(i).second = to_string(stof(at(i).second) * stof(act[i].second));
                }else if(at(i).first==OPintCombine){
                    at(i).second = "(" + at(i).second + "*" + act[i].second + ")" ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second = "(" + at(i).second + "*" + act[i].second + ")" ;
                }
                break;
            case 3: // /
                if(at(i).first==OPint){
                    if(stoi(act[i].second)==0) yyerror("ERROR: zero divisor (int)") ;
                    at(i).second = to_string(stoi(at(i).second) / stoi(act[i].second));
                }else if(at(i).first==OPfloat){
                    if(stof(act[i].second)==0.0) yyerror("ERROR: zero divisor (float)") ;
                    at(i).second = to_string(stof(at(i).second) / stof(act[i].second));
                }else if(at(i).first==OPintCombine){
                    at(i).second = "(" + at(i).second + "/" + act[i].second + ")" ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second = "(" + at(i).second + "/" + act[i].second + ")" ;
                }
                break;
            case 4: // =
                if(at(i).first==OPint){
                    at(i).second = "(" + at(i).second + " = " + act[i].second + ")" ;
                }else if(at(i).first==OPfloat){
                    at(i).second = "(" + at(i).second + " = " + act[i].second + ")" ;
                }else if(at(i).first==OPintCombine){
                    at(i).second = "(" + at(i).second + " = " + act[i].second + ")" ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second = "(" + at(i).second + " = " + act[i].second + ")" ;
                }
                break;
            case 5: //-A
                if(at(i).first==OPint){
                    at(i).second = "-" + at(i).second ;
                }else if(at(i).first==OPfloat){
                    at(i).second = "-" + at(i).second ;
                }else if(at(i).first==OPintCombine){
                    at(i).second = "-" + at(i).second ;
                }else if(at(i).first==OPfloatCombine){
                    at(i).second ="-" + at(i).second ;
                }
                break;
            default:
                yyerror("Error: unsupport operator!") ;
                break;
            }
        }
    }
    public :
        void yyerror(string s){
            cout << s << "\n" ;
            throw "error" ;
        }
        action(){};
        action(pair<OPcode,string> act){
            push_back(act) ;
        }    
        action(OPcode opcode, string token){
            push_back(pair<OPcode,string>{opcode, token}) ;
        }

        void push(OPcode opcode, string token){
            push_back(pair<OPcode,string>{opcode, token}) ;
        }

        pair<OPcode,string> pop(){
            pair<OPcode,string> t = back() ;
            pop_back() ;
            return t ;
        }

        string at2(int i, int j){
            if(j==0){
                switch (at(i).first){
                    case OParithmetic: return "OParithmetic" ;
                    case OPbracket: return "OPbracket" ;
                    case OPdtype: return "OPdtype" ;
                    case OPint: return "OPint" ;
                    case OPfloat: return "OPfloat" ;
                    case OPstring: return "OPstring" ;
                    case OPdimension: return "OPdimension" ;
                    case OPintCombine: return "OPintCombine" ;
                    case OPfloatCombine: return "OPfloatCombine" ;
                    case OPpunctuation: return "OPpunctuation" ;
                    case OPid: return "OPid" ;
                    case OPfun: return "OPfun" ;
                    case OPsplit: return "OPsplit" ;
                    case OPcombine: return "OPcombine" ;
                    case OPother : return "OPother" ;
                    case OPfind : return "OPfind" ;
                    case OPfindfun : return "OPfindfun" ;
                    case OPvoid : return "OPvoid" ;
                }
            }else if(j==1){
                return at(i).second ;
            }
            return "0" ;   
        }
        void show(){
            for(int i=0; i<size(); i++) cout <<"[" << at2(i,0) << " , " <<  at2(i,1) << "]" ;
        }
        void operator+=(action& act){

            if(front().first==OPdimension && act[0].first==OPdimension){
                checkDims(act) ;
                changeDtype(act) ;
                oepration(act,0) ;

            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }
        void operator-=(action& act){
            if(front().first==OPdimension && act[0].first==OPdimension){
                checkDims(act) ;
                changeDtype(act) ;
                oepration(act,1) ;
            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }
        void operator*=(action& act){
            if(front().first==OPdimension && act[0].first==OPdimension){
                checkDims(act) ;
                changeDtype(act) ;
                oepration(act,2) ;
            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }
        void operator/=(action& act){
            if(front().first==OPdimension && act[0].first==OPdimension){
                checkDims(act) ;
                changeDtype(act) ;
                oepration(act,3) ;
            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }

        void operator==(action& act){
            if(act[0].first==OPdimension){
                checkDims(act) ;

                int k = act.dimensElementCount();
                
                int dims = stoi(act[0].second) ;
                string id = at(0).second ;
                if(at(0).first==OPdimension) id = at(1).second ;
                
                resize(act.size()) ;
                if(dims==0){
                    if(act.size()!=2) yyerror("Error: invalid dimenstion.!") ;
                    at(0) = act[0] ;
                    at(1).first = act[1].first ;
                    at(1).second = "(" + id + "=" + act[1].second + ")" ;
                }else{
                    at(0) = act[0] ;
                    vector<int>dimsElement ;

                    for(int i=dims+1; i<act.size();i++){
                        if(at(i).second.back()==']')
                            at(i).second = at(i).second + " = " + act[i].second ;
                        else 
                            yyerror("Error: invalid rvalue assign!") ;
                    }
                }
            }else{
                yyerror("Error: invalid assign!") ;
            }
        }
        void uminus(){
            action a;
            oepration(a,5) ;
        }

        void shrinkDims(){
            at(0).second = to_string(stoi(at(0).second) - 1);
            for(int i=2;i<size(); i++) at(i-1) = at(i) ;
            pop() ;
        }
        void expendDims(){
            push(OPother,"") ;
            for(int i=size()-2;i>=1; i--) at(i+1) = at(i) ;
            at(0).second = to_string(stoi(at(0).second) + 1);
            at(1).first = OPdimension ;
            at(1).second = "1" ;
        }
        void combine(action& act){
            int dims = stoi(front().second) ; 
            string s = at(1).second ;
            if(front().second!="0" || dims!=0) yyerror("Error: can't combine array.") ;
            if(act[0].second!="0"){
                int actdims = stoi(act[0].second) ;
                string st = act[actdims+1].second;
                s = s + ", " + st.substr(0,st.find_first_of("["));
            }
            else{ 
                for(int i=1+dims; i<act.size(); i++){   
                    
                    s = s + "," + act[i].second ;
                }
            }
            at(1).first = OPcombine ;
            at(1).second = s ;
        }
        int dimensElementCount(int start=0){
            int dims = stoi(at(start).second) ; 
            int res = 1 ;
            for(int i=1+start; i<dims+1; i++){
                res *= stoi(at(i).second) ;
            }
            return res ;
        }
        void refitDims(){
            int dims = stoi(front().second) ; 
            if(size()-1-dims>dims){
                push(OPother,"") ;
                for(int i=size()-2;i>=1; i--) at(i+1) = at(i) ;

                at(0).first = OPdimension ;
                at(0).second = to_string(stoi(at(0).second) + 1);

                at(1).second = "1" ;
                at(1).first = OPdimension ;
                at(1).second = to_string((size()-dims-2)/dimensElementCount()) ;
            }
        }
        void combineDimensional(action& act){
            if(front().first==OPdimension && act[0].first==OPdimension){
                checkDims(act) ;

                int dims = stoi(front().second) ; 
                for(int i=1+dims; i<act.size(); i++) push_back(act[i]) ;

            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }
        void append(action& act){
            
            if(front().first==OPdimension && act[0].first==OPdimension){
                int dims =  stoi(front().second) ;
                for(int i=0; i<dims+1; i++)
                    if(i!=1)
                        if(act[i].second != at(i).second || act[i].first != at(i).first){
                            string a = "";
                            string b = "";
                            for(int j = 1; j<stoi(at(0).second)+1; j++){
                                a = a + at(j).second ;
                                if(j!=stoi(at(0).second)) a += " x " ;
                            }                            
                            for(int j = 1; j<stoi(act[0].second)+1; j++){
                                b = b + act[j].second ;
                                if(j!=stoi(act[0].second)) b += " x " ;
                            }
                            yyerror("ERROR: mismatched dimensions (" + a + ") and (" + b +")") ;
                        }
                            
                
                for(int i=dims+1; i<act.size();i++) push(act[i].first,act[i].second) ;
                at(1).second = to_string(stoi(act[1].second)+stoi(at(1).second));
            }else{
                yyerror("Error: unsupport operant!") ;
            }
        }
    
}action ;

class actionTable : public vector<map<string,action>> {
    public :
        actionTable(){};
        void yyerror(string s){
            cout << s << "\n" ;
            throw "error" ;
        }
        void push(map<string,action> table = map<string,action>{}){
            push_back(map<string,action>{}) ;
        }     
        void insert_back(pair<string, action>s){
            back().insert(s) ;
        }
        action& at_check(string s){
            for(int i=size()-1; i>=0; i--){
                if(at(i).find(s) != at(i).end()) return at(i)[s] ;
            }
            yyerror("Error: Undeclared variable \"" + s + "\".") ;
            return at(0)[0];
        }
        int find(string s){
            for(int i=size()-1; i>=0; i--){
                if(at(i).find(s) != at(i).end()) return i+1;
            }
            return 0 ;
        }
        
                
} ;

class actionStack : public vector<action> {

    public :
        actionTable symbolTable;
        void yyerror(string s){
            cout << s << "\n" ;
            throw "error" ;
        }
        actionStack(){ 
            symbolTable.push();
            symbolTable.insert_back(pair<string, action>{"print",action(OPfun,"print")}) ;
            symbolTable.insert_back(pair<string, action>{"println",action(OPfun,"println")}) ;
        };

        void push(action act){
            push_back(act) ;
        }
        void push_dtype(string dtypeText){
            action act ;
            string token ;
            OPcode opcode = OPdtype;
            if(dtypeText=="int"){
                token = "int" ;
            }else if(dtypeText=="real"){
                token = "float" ;
            }else{
                yyerror("Error : invalid data type.") ;
            }
            act.push(opcode,token) ;
            push_back(act) ;
        }
        void push(OPcode opcode, string token){
            if(opcode==OPfind){
                push_back(symbolTable.at_check(token)) ;
            }else if(opcode==OPfindfun){
                push_back(symbolTable.at_check(token)) ;
            }else{
                push_back(action(opcode,token)) ;
            }
        }
        
        action pop(){
            action t = this->back() ;
            pop_back() ;
            return t ;
        }
        void expendExpr(){
            for(int i=0; i<size();i++){
                if(at(i).front().first==OPdimension) at(i).expendDims() ;
                else if(at(i).front().first==OPsplit) at(i).front().first=OParithmetic;
            }
        }
        void show(int start=0, int end=-1){
            if(end==-1) end = size() ;
            cout << "{ " ;
            for(int i=start; i<end; i++) {
                at(i).show() ;
                cout << ", ";
            }
            cout << " }\n" ;
        }
        void move(int start){
            for(int i=start; i<size()-1;i++) at(i) = at(i+1) ;
            pop();
        }
        string printList(action& act, bool newline = false){
            string s1 = "\"" ;
            string s2 = "" ;

            int dims = stoi(act[0].second) ;

            for(int i=dims+1; i<act.size();i++){
                s2 = s2  + act[i].second ;
                if(act[i].first==OPint || act[i].first==OPintCombine){
                    s1 = s1 + "\%d" ;
                }else if(act[i].first==OPfloat || act[i].first==OPfloatCombine){
                    s1 = s1 + "\%f" ;
                }
                if(i!=act.size()-1){
                     s1 = s1 + ", ";
                     s2 = s2 + ", ";
                }
            }
            if(newline) return  s1 + "\\n\"," + s2 ;
            return  s1 + "\"," + s2 ;
        }
        void clacluateExpr(int start=0, int end=-1,bool isTop=false){
            
            if(end==-1) end = size() ;
            actionStack stack ;
            action top ;
            string operation ;
            OPcode opcode ;
            vector<string> bracketStack = {""};
            int depth = 0 ;
            for(int i=start; i<min(size_t(end),size());i++){
                stack.push(at(i)) ;
                // stack.show() ;

                if(at(i).front().first==OParithmetic){
                    operation = stack.back().front().second ;
                    if(operation!="{"){
                        opcode = stack.back().front().first ;
                        stack.pop() ;
                        top = stack.pop() ;
                    }

                    if(operation=="+") stack.back() += top ;
                    else if(operation=="-") stack.back() -= top ;
                    else if(operation=="*") stack.back() *= top ;
                    else if(operation=="/") stack.back() /= top ;
                    else if(operation=="=") {
                        stack.back() == top ;
                    }
                    else if(operation==","){
                        if(bracketStack.back()=="[") yyerror("Error: invalid index.") ;
                        else if(bracketStack.back()=="{") stack.back().combineDimensional(top) ;
                        else stack.back().combine(top) ;
                    }else if(operation=="m"){
                        top.uminus() ;
                        stack.push(top) ;
                    }else if(operation=="("){
                        bracketStack.push_back("(") ;
                        stack.push(top) ;
                    }else if(operation==")"){
                        bracketStack.pop_back() ;
                        string s = stack.back()[0].second ;
                        if(stack.back()[0].first!=OPfun){
                            yyerror("Error: invalid function name.");
                        }else{
                            if(s=="print"){
                                s = "printf" ;
                                if(top[1].first==OPstring){
                                    s = s + "(\"\%s\"," + top[1].second + ")" ;
                                }else{
                                    s = s + "(" + printList(top,false) + ")" ;
                                }
                                
                            }else if(s=="println"){
                                s = "printf" ;
                                if(top[1].first==OPstring){
                                    s = s + "(\"\%s\\n\"," + top[1].second + ")" ;
                                }else {
                                    s = s + "(" + printList(top,true) + ")" ;
                                }
                            }else if(top[0].first==OPdimension){

                                 if(top[0].second!="0"){
                                    string st = top.back().second ;
                                    string id_ = st.substr(0,st.find_first_of('[')) ;
                                    OPcode type = stack.back().back().first ;
                                    top.resize(2) ;
                                    top[0].second = "0" ;
                                    top[1].first = type ;
                                    top[1].second = id_;
                                    
                                }
                                s = s + "(" + top[1].second + ")" ;
                            }else{
                                yyerror("Error: invalid parameter.");
                            }
                        }
                        stack.back().resize(2) ;
                        stack.back()[0].first = OPdimension;
                        stack.back()[0].second = "0";
                        stack.back()[1].first = OPintCombine;
                        stack.back()[1].second = s;
                    }else if(operation=="{"){
                        if(bracketStack.back()=="(") yyerror("Error: can't use initial list as parameter.") ;
                        bracketStack.push_back("{") ;
                        depth ++ ;
                    }else if(operation=="}"){
                        
                        bracketStack.pop_back() ;
                        stack.pop_back() ;
                        top.refitDims();
                        
                        stack.push(top) ;
                        depth -- ;

                        
                    }else if(operation=="["){
                        bracketStack.push_back("[") ;
                        stack.push(top) ;
                    }else if(operation=="]"){
                        bracketStack.pop_back() ;
                        string s ;
                        OPcode type ;
                        string id ;
                        if(stack.back().back().second.back()==']'){

                            if(stack.back()[0].second!="0"){
                                s = stack.back().back().second ;
                                id = s.substr(0,s.find_first_of('[')) ;
                                type = stack.back().back().first ;
                                stack.back().resize(2) ;
                                stack.back()[0].second = "0" ;
                                stack.back()[1].first = type ;
                                stack.back()[1].second = id;
                            }

                            if(top[0].first==OPdimension && top[0].second=="0"){
                                if(stack.back()[0].first==OPid) s = stack.back()[0].second ;
                                else s = stack.back()[1].second ;

                                if(top[1].first==OPint || top[1].first==OPintCombine){
                                    s = s + "[" + top[1].second + "]" ;
                                }else{
                                    yyerror("Error: invalid index(float).");
                                }
                            }else{
                                yyerror("Error: invalid index.");
                            }
                        }
                        stack.back().resize(2) ;
                        stack.back()[0].first = OPdimension;
                        stack.back()[0].second = "0";
                        if(id.size()) stack.back()[1].first = symbolTable.at_check(id).back().first;
                        stack.back()[1].second = s;
                    }
                }
            }

            for(int i=0; i<stack.size();i++){
                at(i+start) = stack[i] ;
            }
            
            for(int i=end; i<size()-1; i++){
                at(start+stack.size()+i-end) = at(i) ;
            }
            
             resize(start+stack.size()+size()-end) ;
            //stack.show() ;
        }
        string arrayToCstyle(string dtype, string id){
            int i=dtype.find_first_of('[');
            if(i==string::npos) return dtype + " " +id ;
            
            return dtype.substr(0,i) + " " + id + dtype.substr(i) ; 
        }
        string arrayValueString(action& act){
            
            int dims =stoi( act[0].second ) ;
            if(dims==0) return act[1].second ;
            vector<int>dimsElement ;
            string s = "";
            for(int i=dims+1; i<act.size(); i++){
                s = s + act[i].second ;
                if(i!=act.size()-1) s = s + " , " ;
            }
            s = "{" + s + "}" ;
            return s; 
        }
        vector<string> dtypeToArray(action& act){
            string s = act[0].second ;
            vector<string> result ;
            if(s.find_first_of('[')!=string::npos){
                int anchor = 0 ;
                result.push_back(s.substr(0,s.find_first_of('['))) ;
                
                for(int i=0; i<s.size();i++){
                    if(s[i]=='[') anchor = i+1 ;
                    else if(s[i]==']'){
                        result.push_back(s.substr(anchor,i-anchor)) ;
                    }
                }
            }else{
                result.push_back(s) ;
            }
            return result;
        }
        OPcode stringTocode(string s){
            if(s=="int") return OPintCombine ;
            else if(s=="float") return OPfloatCombine ;
            else if(s=="string") return OPstring ;
            else if(s=="void") return OPvoid;
            return OPother;
        }
        string assignment(bool isConst=false, bool assign=false, int start=0){
            string s ;
            s = "" ;
            if(isConst) s = s + "const " ;

            action& act = at(start) ;
            action& dtype = at(start+1) ;
            int dimscount = 1 ;

            if(act[0].first!=OPid) yyerror("Error : invalid assigement.") ;
            if(dtype[0].first!=OPdtype) yyerror("Error : invalid data type.") ;
            s = s + arrayToCstyle(dtype[0].second, act[0].second) ;

            if(symbolTable.find(act[0].second)==symbolTable.size()){
                yyerror("Error: variable \""+ act[0].second +"\" duplicate declaration") ;
            }
            vector<string>dimsArray =  dtypeToArray(dtype) ;
            action assginDtype(OPdimension,to_string(dimsArray.size()-1)) ;
            for(int i=1; i<dimsArray.size(); i++){
                assginDtype.push(OPdimension, dimsArray[i]) ;
            }
            if(dimsArray.size()==1){
                assginDtype.push(stringTocode(dimsArray[0]),act[0].second) ;
            }else{
                dimscount = assginDtype.dimensElementCount() ;
                string t ="";
                int k ; 
                for(int i=0; i<dimscount; i++){
                    k  = i ;
                    t = "" ;
                    for(int j=dimsArray.size()-1; j>=1; j--){
                        t =  "["+ to_string(k % stoi(dimsArray[j])) + "]" + t;
                        k = k/stoi(dimsArray[j]) ;
                    }
                    assginDtype.push(stringTocode(dimsArray[0]),act[0].second + t) ;
                }
            }
            if(assign){
                s = s + " = " ;
                clacluateExpr(start+2) ;
                if(at(start+2).dimensElementCount()!=dimscount) yyerror("ERROR: assign different dimensions") ;
                s = s + arrayValueString(at(start+2)) ;
                
            }
            symbolTable.insert_back(pair<string, action>{act[0].second, assginDtype}) ;

            return s ;
        }
        string combineDtype(int start=0){
            if(start<0) start = size() + start ;
            action& act = at(start) ;
            string s = "";
            if(act[0].first!=OPdtype) yyerror("Error : invalid data type.") ;
            s = act[0].second ;
            for(int i=start+1; i<size(); i++){
                if(at(i)[1].first==OPint) s = s + "["+ at(i)[1].second +"]" ;
                else yyerror("Error : invalid array index.") ;
            }
            act[0].second = s ;
            resize(start+1) ;
            return s ;
        }
       
        string dimensionToString(action act){
            string result = "" ;
            int dims = stoi(act[0].second) ;
            for(int i=1; i<dims+1; i++) result = result + "[" + act[i].second + "]" ;
            return result ;
        }
        
        string exprToString(int start=0){

            if(start<0) start = size() + start ;
            if(start>=size()) return "" ;
            string s ;
               
            clacluateExpr(start) ;
            
            if(at(start).front().second=="0"){
                s = at(start)[1].second ;
            }else{
                s = "" ;
                for(int j=stoi(at(start)[0].second)+1; j<at(start).size();j++){
                    s = s + at(start)[j].second  ;
                    if(j!=at(start).size()-1) s = s + ",";
                }
                // cout << s ;
            }
            resize(start+1) ;
            
            return s;
        }


        string declareFunction(bool isReturn=false){
            //if(at(0)[0].first != OPfun) yyerror("Error: unknown function name.\n") ;
            string functionName = at(0)[0].second ;
            string returnType =  "void" ;
            string s = "" ;
            vector<string>dimsArray = {"0"} ; 

            if(isReturn){
                dimsArray = dtypeToArray(back()) ;
                returnType = back()[0].second ;
                if(returnType.back()==']') 
                    yyerror("Error: unsupport multiple dimensions return.");
                //returnType = "void" ;//returnType = returnType.substr(0,returnType.find_first_of("[")) + "*" ;
                pop();
            }

            action functionType(OPfun,functionName) ;
            functionType.push(stringTocode(returnType),returnType) ;
            
            functionType.push(OPdimension,to_string(dimsArray.size()-1)) ;

            
            symbolTable.push();


            

            int dimscount ;
            for(int i=1; i<size(); i+=2){
                //symbolTable.insert_back()
                vector<string>dimsArray =  dtypeToArray(at(i+1)) ;
                action assginDtype(OPdimension,to_string(dimsArray.size()-1)) ;
                for(int j=1; j<dimsArray.size(); j++)assginDtype.push(OPdimension, dimsArray[j]) ;
                
                if(dimsArray.size()==1) assginDtype.push(stringTocode(dimsArray[0]),at(i)[0].second) ;
                else{
                    dimscount = assginDtype.dimensElementCount() ;
                    string t ="";
                    int k ; 
                    for(int x=0; x<dimscount; x++){
                        k  = x ;
                        t = "" ;
                        for(int j=dimsArray.size()-1; j>=1; j--){
                            t =  "["+ to_string(k % stoi(dimsArray[j])) + "]" + t;
                            k = k/stoi(dimsArray[j]) ;
                        }
                        assginDtype.push(stringTocode(dimsArray[0]),at(i)[0].second + t) ;
                    }
                }
                for(int wd=0; wd<assginDtype.size();wd++){
                    functionType.push_back(assginDtype[wd]) ;
                }
                symbolTable.insert_back(pair<string, action>{at(i)[0].second, assginDtype}) ;

                s = s + arrayToCstyle(at(i+1)[0].second,at(i)[0].second) ;
                if(i+2<size()) s = s + ", " ;
            }
            symbolTable[int(symbolTable.size()-2)].insert(pair<string,action>{functionName,functionType}) ;
            return returnType + " " + functionName + " " + "(" + s + ")" ;
        }

} ;
