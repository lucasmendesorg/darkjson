/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

const char *GetTokenType(int type) {
	static const char *TokenType[] = {
		"Unknown", "String", "Number", "Array", "Dictionary", NULL,
	};
	return TokenType[type];
};
