int noInstructions=0;
int noFuncInstructions=0;
int noRenderInstructions=0;
int noDrawInstructions=0;
string currentFunctionName;

enum INSTRUCTION {
  STORE=1,
  MUL=2,
  ADDI=3,
  PUSHT=4,
  SUB=5,
  DI=6,
  NEWFUNC=7,
  ENDFUNC=8,
  CALL=9,
  POPT=10,
  RET=11,
};

struct instruction {
    ACTION i;
    TOKEN a;
    TOKEN b;
};


deque<instruction> instructions;
std::unordered_map<std::string,deque<instruction>> functions;

void addInstruction(ACTION E, TOKEN a, TOKEN b) {
    instruction ops = {E,a,b};
    instructions.push_back(ops);
}

void addInstruction(ACTION E, TOKEN a) {
    TOKEN b = {OPERATOR, EPSILON, "NULL", -1, -1, -1};
    instruction ops = {E,a,b};
    instructions.push_back(ops);
}
void addInstruction(ACTION E) {
    TOKEN b = {OPERATOR, EPSILON, "NULL", -1, -1, -1};
    instruction ops = {E,b,b};
    instructions.push_back(ops);
}

void addFuncInstruction(ACTION E, TOKEN a, TOKEN b) {
    instruction ops = {E,a,b};
    functions[currentFunctionName].push_back(ops);
}

void addFuncInstruction(ACTION E, TOKEN a) {
    TOKEN b = {OPERATOR, EPSILON, "NULL", -1, -1, -1};
    instruction ops = {E,a,b};

    if (E==ACTION_NEW_FUNC) {
        currentFunctionName = a.lexeme;
        noFuncInstructions=0;
    }
        functions[currentFunctionName].push_back(ops);


}

void addFuncInstruction(ACTION E) {
    TOKEN b = {OPERATOR, EPSILON, "NULL", -1, -1, -1};
    instruction ops = {E,b,b};
    functions[currentFunctionName].push_back(ops);
}

void resetInstructionData() {
    noFuncInstructions=0;
    noInstructions=0;
}

string itostring(INSTRUCTION I) {
  switch (I) {
    case STORE : {
       return "STORE";
    }
    case MUL : {
       return "MUL";
    }
    case PUSHT : {
       return "PUSHT";
    }
    case ADDI : {
       return "ADDI";
    }
    case NEWFUNC : {
       return "NEWFUNC";
    }
    case ENDFUNC : {
       return "ENDFUNC";
    }
    case CALL : {
       return "CALL";
    }
    case POPT : {
       return "POPT";
    }
    case RET : {
       return "RET";
    }
  }
}
