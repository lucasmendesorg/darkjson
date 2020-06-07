/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

Token *Number_Create(double value) {
	char buffer[512];
	snprintf(buffer, sizeof(buffer), "%f", value);
	return CreateToken(buffer, TOKEN_TYPE_NUMBER);
}

Token *String_Create(char *value) {
	return CreateToken(value, TOKEN_TYPE_STRING);
}

Token *Dictionary_AppendDictionary(Token *dictionary, char *key, Token *token) {
	AppendTokenToDictionary(dictionary, String_Create(key));
	AppendTokenToDictionary(dictionary, token);
	return dictionary;
}

Token *Dictionary_AppendArray(Token *dictionary, char *key, Token *array) {
	AppendTokenToDictionary(dictionary, String_Create(key));
	AppendTokenToDictionary(dictionary, array);
	return dictionary;
}

Token *Dictionary_AppendNumber(Token *dictionary, char *key, double number) {
	AppendTokenToDictionary(dictionary, String_Create(key));
	AppendTokenToDictionary(dictionary, Number_Create(number));
	return dictionary;
}

Token *Dictionary_AppendString(Token *dictionary, char *key, char *pair) {
	AppendTokenToDictionary(dictionary, String_Create(key));
	AppendTokenToDictionary(dictionary, String_Create(pair));
	return dictionary;
}

Token *Dictionary_Create(char *name) {
	return CreateToken(name, TOKEN_TYPE_DICTIONARY);
}

Token *Array_Create(char *name) {
	return CreateToken(name, TOKEN_TYPE_ARRAY);
}
