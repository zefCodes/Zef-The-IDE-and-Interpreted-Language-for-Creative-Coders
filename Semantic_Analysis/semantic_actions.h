#include "DataType.h"
#include "typeSolver.h"
#include <cmath>
#include "instructions.h"

TOKEN funcName;
bool insideFunction = false;

vector<TOKEN> performAction(int Action, vector<TOKEN> stack) {
			ACTION ACT = (ACTION) Action;

			if(ACT==ACTION_CREATE_VAR) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}
			if(ACT==ACTION_INIT) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}

			if(ACT==ACTION_FUNC_NAME) {
					funcName=stack.back();
					return stack;
			}

			if(ACT==ACTION_PARAM) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}
			if(ACT==ACTION_OWISE) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}
			if(ACT==ACTION_OWISE_IF) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}
			if(ACT==ACTION_OWISE_BRANCH) {
					if (insideFunction) {
							addFuncInstruction(ACT);
					}
					else {
							addInstruction(ACT);
					}
					return stack;
			}
			if(ACT==ACTION_POP) {
				if (insideFunction) {
						addFuncInstruction(ACT);
				}
				else {
					addInstruction(ACT);
				}
				stack.pop_back();
				return stack;
			}

			if (Action==ACTION_NEW_FUNC) {
				insideFunction=true;
			}
			else if (Action==ACTION_END_FUNC) {
				insideFunction=false;
			}
//			TOKEN B = stack.back();
//			stack.pop_back();
////			TOKEN M = stack.back();
////			stack.pop_back();
////			TOKEN A = stack.back();

		    switch(ACT) {
					case ACTION_NEW_FUNC : {
						//cout<<"NEW FUNC: "<<M.lexeme;
                        addFuncInstruction(ACTION_NEW_FUNC,funcName);
						break;
					}
					case ACTION_END_FUNC : {
                        //addFuncInstruction(ACTION_END_FUNC);
						break;
					}
					default: {
						if (insideFunction) {
								addFuncInstruction(ACT);
						}
						else {
							addInstruction(ACT);
						}
					}
				}
    return stack;
}
