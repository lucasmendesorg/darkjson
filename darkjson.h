/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#ifndef DARKJSON_H
#define DARKJSON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define MYSELF			__func__

enum {
	SERIALIZE_SHOULD_CLOSE_ARRAY = 1,
	SERIALIZE_SHOULD_CLOSE_DICTIONARY,
};

enum {
	TOKEN_TYPE_UNKNOWN = 0,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_ARRAY,
	TOKEN_TYPE_DICTIONARY,
};

typedef struct Token {
	struct Token *Up, *Down;
	struct Token *NextArray;
	struct Token *NextDictionary;
	char *Value;
	int Type;
} Token;

typedef struct TokenTree {
	struct Token *First;
	struct Token *Last;
} TokenTree;

#ifdef DEBUG
int		debugf				(const char *who, const char *fmt, ...);
#else
#define		debugf(...)
#endif
int		tracef				(const char *who, const char *fmt, ...);

const char *	GetTokenType			(int type);

Token *		AppendToTokenTree		(TokenTree *tree, Token *token);

TokenTree *	CreateTokenTree();

Token *		AppendTokenToDictionary		(Token *dictionary, Token *token);
Token *		AppendTokenToArray		(Token *array, Token *token);
Token *		CreateToken			(char *value, int type);

void		DumpToken			(Token *t);
void		DumpTokenTree			(TokenTree *t);

void		SerializeToken			(Token *t, int order);
void		SerializeTokenTree		(TokenTree *t);

Token *		Number_Create			(double value);
Token *		String_Create			(char *value);
Token *		Dictionary_AppendDictionary	(Token *dictionary, char *key, Token *token);
Token *		Dictionary_AppendArray		(Token *dictionary, char *key, Token *array);
Token *		Dictionary_AppendNumber		(Token *dictionary, char *key, double number);
Token *		Dictionary_AppendString		(Token *dictionary, char *key, char *pair);
Token *		Dictionary_Create		(char *name);
Token *		Array_Create			(char *name);

#endif
