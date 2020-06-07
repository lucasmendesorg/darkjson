/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

Token *AppendTokenToDictionary(Token *dictionary, Token *token) {
	Token *last;
	for(last = dictionary; last->NextDictionary; last = last->NextDictionary);
	last->NextDictionary = token;
	token->Up = dictionary;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		GetTokenType(token->Type), token->Value,
		GetTokenType(dictionary->Type), dictionary->Value);
	return dictionary;
}

Token *AppendTokenToArray(Token *array, Token *token) {
	Token *last;
	for(last = array; last->NextArray; last = last->NextArray);
	last->NextArray = token;
	token->Up = array;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		GetTokenType(token->Type), token->Value,
		GetTokenType(array->Type), array->Value);
	return array;
}

Token *CreateToken(char *value, int type) {
	Token *aux = (Token *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc new token");
		return aux;
	}
	aux->Up = aux->Down = aux->NextArray = aux->NextDictionary = NULL;
	aux->Value = (char *) malloc(strlen(value) + 1);
	if(!aux->Value) {
		free(aux);
		debugf(MYSELF, "Cannot alloc value for new token");
		return NULL;
	}
	strcpy(aux->Value, value);
	aux->Type = type;
	debugf(MYSELF, "New %s '%s'", GetTokenType(type), value);
	return aux;
}
