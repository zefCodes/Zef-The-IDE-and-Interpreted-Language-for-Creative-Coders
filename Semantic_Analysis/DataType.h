#include <map>
#include <unordered_map>

struct VARIABLE {
    string val;
    TOKEN_TYPE_T T;
    TOKENS name;
    int lineNo;
    int column;
    deque<ELEMENT> list;
};


string typeToString(TOKEN_TYPE_T T) {
  switch(T) {
    case CONSTANT : return "number";
    case BOOL_LITERAL : return "boolean";
    case STR_LITERAL : return "string";
    case IDENTIFIER : return "variable";
    case DATAL : return "list";
    case REFL : return "reference";
  }
}

struct Scope {
  std::unordered_map<string, VARIABLE> vars;
};

std::unordered_map<string, VARIABLE> var_tab;
Scope scope={var_tab};
deque<Scope> scopeStack;

void logAllVariables(Scope scope) {
  std::cout <<"\nVARIABLES"<<std::flush;
  for (std::unordered_map<string,VARIABLE>::iterator it=scope.vars.begin(); it!=scope.vars.end(); ++it) {
    std::cout << "\n[" << it->first << " : " << it->second.val <<" : "<< typeToString(it->second.T) <<']'<<std::flush;
  }
  std::cout <<"\n"<<std::flush;
}

void storeVariable(string name, ELEMENT T, int tableIndex) {
    string value = T.lexeme;
    int lineNo = T.lineNo;
    int column = T.column;
    TOKENS NAME = T.NAME;
    TOKEN_TYPE_T type = T.TYPE;

   scopeStack[tableIndex].vars[name] = {value,type,NAME,lineNo,column,T.list};
}
