void addPrimitiveFunctions() {
  //
  TOKEN T = {IDENTIFIER,ID,"console",-10,-10,10};
  TOKEN N = {IDENTIFIER,ID,"string",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,T);
  addFuncInstruction(FUNC_LOG);
  FunctionData funcD = {{"string"},1};
  funcData["console"] = funcD;


  TOKEN TP = {IDENTIFIER,ID,"consolenl",-10,-10,10};
  TOKEN NP = {IDENTIFIER,ID,"string",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,TP);
  addFuncInstruction(FUNC_LOG_2);
  FunctionData funcDP = {{"string"},1};
  funcData["consolenl"] = funcDP;

  TOKEN C = {IDENTIFIER,ID,"drawOval",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_DRAW_OVAL_PRIM);
  FunctionData funcC = {{"segments","height","width","y","x"},5};
  funcData["drawOval"] = funcC;


  C = {IDENTIFIER,ID,"fillOval",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_FILL_OVAL_PRIM);
  funcC = {{"segments","height","width","y","x"},5};
  funcData["fillOval"] = funcC;

  C = {IDENTIFIER,ID,"fillArc",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_FILL_ARC_PRIM);
  funcC = {{"segments","end","start","height","width","y","x"},7};
  funcData["fillArc"] = funcC;

  C = {IDENTIFIER,ID,"drawArc",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_DRAW_ARC_PRIM);
  funcC = {{"segments","end","start","height","width","y","x"},7};
  funcData["drawArc"] = funcC;


  C = {IDENTIFIER,ID,"drawRect",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_DRAW_RECT_PRIM);
  funcC = {{"height","width","y","x"},4};
  funcData["drawRect"] = funcC;

  C = {IDENTIFIER,ID,"fillRect",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_FILL_RECT_PRIM);
  funcC = {{"height","width","y","x"},4};
  funcData["fillRect"] = funcC;

  C = {IDENTIFIER,ID,"drawLine",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_DRAW_LINE_PRIM);
  funcC = {{"endy","endx","starty","startx"},4};
  funcData["drawLine"] = funcC;

  C = {IDENTIFIER,ID,"setBackgroundColor",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SET_BACKGROUND_PRIM);
  funcC = {{"a","b","g","r"},4};
  funcData["setBackgroundColor"] = funcC;

  C = {IDENTIFIER,ID,"setLineWeight",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SET_LINE_WEIGHT_PRIM);
  funcC = {{"weight"},1};
  funcData["setLineWeight"] = funcC;

  C = {IDENTIFIER,ID,"setPaintColor",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SET_COLOR_PRIM);
  funcC = {{"b","g","r"},3};
  funcData["setPaintColor"] = funcC;

  C = {IDENTIFIER,ID,"clearCanvas",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_CLEAR_SCREEN_PRIM);
  funcC = {{},0};
  funcData["clearCanvas"] = funcC;

  C = {IDENTIFIER,ID,"size",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SIZE_PRIM);
  funcC = {{"list"},1};
  funcData["size"] = funcC;




  C = {IDENTIFIER,ID,"sin",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SIN_PRIM);
  funcC = {{"a"},1};
  funcData["sin"] = funcC;

  C = {IDENTIFIER,ID,"cos",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_COS_PRIM);
  funcC = {{"a"},1};
  funcData["cos"] = funcC;

  C = {IDENTIFIER,ID,"tan",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_TAN_PRIM);
  funcC = {{"a"},1};
  funcData["tan"] = funcC;

  C = {IDENTIFIER,ID,"asin",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ASIN_PRIM);
  funcC = {{"a"},1};
  funcData["asin"] = funcC;

  C = {IDENTIFIER,ID,"acos",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ACOS_PRIM);
  funcC = {{"a"},1};
  funcData["acos"] = funcC;

  C = {IDENTIFIER,ID,"atan",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ATAN_PRIM);
  funcC = {{"a"},1};
  funcData["atan"] = funcC;




  C = {IDENTIFIER,ID,"log",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_LOG_PRIM);
  funcC = {{"a","base"},2};
  funcData["log"] = funcC;

  C = {IDENTIFIER,ID,"root",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ROOT_PRIM);
  funcC = {{"a","root"},2};
  funcData["root"] = funcC;



  C = {IDENTIFIER,ID,"abs",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ABS_PRIM);
  funcC = {{"a"},1};
  funcData["abs"] = funcC;

  C = {IDENTIFIER,ID,"floor",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_FLOOR_PRIM);
  funcC = {{"a"},1};
  funcData["floor"] = funcC;

  C = {IDENTIFIER,ID,"ceil",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_CEIL_PRIM);
  funcC = {{"a"},1};
  funcData["ceil"] = funcC;

  C = {IDENTIFIER,ID,"random",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_RAND_PRIM);
  funcC = {{"b","a"},2};
  funcData["random"] = funcC;

  C = {IDENTIFIER,ID,"radians",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_RADIANS_PRIM);
  funcC = {{"a"},1};
  funcData["radians"] = funcC;

  C = {IDENTIFIER,ID,"degrees",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_DEGREES_PRIM);
  funcC = {{"a"},1};
  funcData["degrees"] = funcC;




  C = {IDENTIFIER,ID,"rotate",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_ROT_PRIM);
  funcC = {{"r"},1};
  funcData["rotate"] = funcC;

  C = {IDENTIFIER,ID,"translate",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_TRANS_PRIM);
  funcC = {{"y","x"},2};
  funcData["translate"] = funcC;

  C = {IDENTIFIER,ID,"scale",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_SCALE_PRIM);
  funcC = {{"y","x"},2};
  funcData["scale"] = funcC;

  C = {IDENTIFIER,ID,"mouseX",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_MOUSE_X_PRIM);
  funcC = {{},0};
  funcData["mouseX"] = funcC;

  C = {IDENTIFIER,ID,"mouseY",-10,-10,10};
  addFuncInstruction(ACTION_NEW_FUNC,C);
  addFuncInstruction(FUNC_MOUSE_Y_PRIM);
  funcC = {{},0};
  funcData["mouseY"] = funcC;


}
