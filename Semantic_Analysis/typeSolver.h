int TYPE_COMBOS[4][4] = {
   {0,1,2,3}, //str,str//str,const//str,bool//str,var
   {4,5,6,7}, //const,str//const,const//const,bool//const,var
   {8,9,10,11}, //bool,str//bool,const//bool,bool//bool,var
   {12,13,14,15} //var,str//var,const//var,bool//var,var
};

int UNARY_COMBOS[7][4] = {
             //str,const,bool,var
 /*pre inc*/ {0,1,0,1},
 /*pre dec*/ {0,1,0,1},
 /*positive*/{0,1,0,1},
 /*negative*/{0,1,0,1},
 /*not*/     {0,0,1,1},
 /*post inc*/{0,1,0,1},
 /*post dec*/{0,1,0,1},
};
int TYPE_RULES[][20] = {
  /*STR,STR*/{ACTION_ADD, ACTION_NOT_EQ, ACTION_IS_EQ},
  /*STR,CONST*/{ACTION_ADD},
  /*STR,BOOL*/{ACTION_ADD},
  /*STR,VAR*/{},
  /*CONST,STR*/{ACTION_ADD},
  /*CONST,CONST*/{ACTION_ADD,ACTION_MUL,ACTION_SUB,ACTION_DIV, ACTION_NOT_EQ, ACTION_IS_EQ, ACTION_POW, ACTION_MOD, ACTION_GT, ACTION_LT, ACTION_LTE, ACTION_GTE, ACTION_PLUS_ASS, ACTION_MUL_ASS, ACTION_PWR_ASS, ACTION_DIV_ASS, ACTION_SUB_ASS},
  /*CONST,BOOL*/{},
  /*CONST,VAR*/{},
  /*BOOL,STR*/{ACTION_ADD},
  /*BOOL,CONST*/{},
  /*BOOL,BOOL*/{ACTION_LOR, ACTION_LAND, ACTION_NOT_EQ, ACTION_IS_EQ},
  /*BOOL,VAR*/{},
  /*VAR,STR*/{ACTION_ASSIGN},
  /*VAR,CONST*/{ACTION_ASSIGN},
  /*VAR,BOOL*/{ACTION_ASSIGN},
  /*VAR,VAR*/{ACTION_ASSIGN, ACTION_NOT_EQ, ACTION_IS_EQ, ACTION_PLUS_ASS},
};

bool typeCheck(ELEMENT operanda, ACTION A, ELEMENT operandb) {
  int tableSlot = TYPE_COMBOS[operanda.TYPE-133][operandb.TYPE-133];
  for (int i = 0; i<20; i++) {
    if (TYPE_RULES[tableSlot][i]==A) {
      return true;
    }
  }
  return false;
}

bool typeCheck(ACTION A, ELEMENT operand) {
  if(UNARY_COMBOS[A-310][operand.TYPE-133]==1) {
    return true;
  }
  else {
    return false;
  }
}
