/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

// Insere uma nova linha (verticalmente/token->Down) no final de *tree
Token *AppendToTokenTree(TokenTree *tree, Token *token) {
	token->Up = token->Down = NULL;
	if(!tree->First) {
		debugf(MYSELF, "%s '%s' is now the first token of TokenTree %p",
			GetTokenType(token->Type), token->Value, tree);
		return (tree->First = tree->Last = token);
	}
	tree->Last->Down = token;
	tree->Last = token;
	debugf(MYSELF, "Appending %s '%s' to the end Tree %p",
		GetTokenType(token->Type), token->Value, tree);
	return token;
}

TokenTree *CreateTokenTree() {
	TokenTree *aux = (TokenTree *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc new tree");
		return aux;
	}
	aux->First = aux->Last = NULL;
	debugf(MYSELF, "New TokenTree %p", aux);
	return aux;
}
