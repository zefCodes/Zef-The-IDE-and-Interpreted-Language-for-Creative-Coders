#include <cstdlib>
#include "TOKEN.h"
#include <vector>

std::vector<TOKEN> token_Buffer;
int t_Index=0;
int tokensPushed=0;

void pushToken(TOKEN T) {
	token_Buffer.push_back(T);
	tokensPushed++;
}

TOKEN nextToken() {
	TOKEN nextToken = token_Buffer[t_Index];
	t_Index++;
	return nextToken;
}

void resetTokenBuffer() {
	t_Index=0;
}

void clearTokens() {
    //token_Buffer = std::vector<TOKEN>;
    //cout<<"HEEEII";
    token_Buffer.clear();
    tokensPushed=0;
    t_Index=0;

}
