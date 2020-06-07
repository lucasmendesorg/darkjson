/*
	A árvore de tokens é organizada em Token * p/ STRING e NUMBER,
	definido em token->type, sendo token->value o conteúdo do token e
	token->next = NULL (STRING e NUMBER não são containers, como
	ARRAY e DICTIONARY; logo, *next = NULL).

	token->down aponta para a próxima linha (horizontal), sendo outro
	field do data model, completamente independente do anterior.

	Ex.:
		Token {
			.down = próximo-campo-do-modelo
			.up = ARRAY || DICTIONARY || NULL-se-for-filho-de-TokenTree,
			.arrayNext = NULL,
			.dictionaryNext = NULL,
			.type = STRING || NUMBER,
			value = "..."
		}

	Para ARRAY, *arrayNext aponta para os membros do array, seguindo o
	modelo padrão para STRING e NUMBER. Chamamos isso de colunas.

	Para DICTIONARY, *dictionaryNext aponta para os membros do dictionary,
	tratados em pares (key + value), sendo "key" sempre STRING e
	"value" podendo ser STRING ou NUMBER. Chamamos isso de colunas.

	Ex. com *down e *next:
		0: Token { STRING }
		1: Token { NUMBER }
		2: Token { STRING }
		3: Token { STRING }
		4: Token { ARRAY } -> Token { STRING } -> Token { NUMBER } -> ...
		5: Token { ARRAY } -> Token { NUMBER } -> Token { NUMBER } -> ...
		6: Token { ARRAY } -> Token { STRING } -> Token { STRING } -> ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MYSELF			__FUNCTION__

#define TOKEN_TYPE_UNKNOWN	0
#define TOKEN_TYPE_STRING	1
#define TOKEN_TYPE_NUMBER	2
#define TOKEN_TYPE_ARRAY	3
#define TOKEN_TYPE_DICTIONARY	4

static const char* TokenType[] = {
	"Unknown", "String", "Number", "Array", "Dictionary",
};

typedef struct Token {
	struct Token *up, *down;
	struct Token *arrayNext;
	struct Token *dictionaryNext;
	char* value;
	int type;
} Token;

typedef struct TokenTree {
	struct Token *first;
	struct Token *last;
} TokenTree;

int debugf(const char *who, const char *fmt, ...) {
	va_list args;
	char buffer[4096];
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	if(!who) who = "";
	return fprintf(stderr, "%24s - %s\n", who, buffer);
}

// Insere uma nova linha (verticalmente/token->down) no final de *tree
Token *AppendToTokenTree(TokenTree *tree, Token *token) {
	token->up = token->down = NULL;
	if(!tree->first) {
		debugf(MYSELF, "%s '%s' is now the first token of TokenTree %p",
			TokenType[token->type], token->value, tree);
		return (tree->first = tree->last = token);
	}
	tree->last->down = token;
	tree->last = token;
	debugf(MYSELF, "Appending %s '%s' to the end Tree %p",
		TokenType[token->type], token->value, tree);
	return token;
}

TokenTree *CreateTokenTree() {
	TokenTree *aux = (TokenTree *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc new tree");
		return aux;
	}
	aux->first = aux->last = NULL;
	debugf(MYSELF, "New TokenTree %p", aux);
	return aux;
}

Token *AppendTokenToDictionary(Token *dictionary, Token *token) {
	Token *last;
	for(last = dictionary; last->dictionaryNext; last = last->dictionaryNext);
	last->dictionaryNext = token;
	token->up = dictionary;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		TokenType[token->type], token->value,
		TokenType[dictionary->type], dictionary->value);
	return dictionary;
}

Token *AppendTokenToArray(Token *array, Token *token) {
	Token *last;
	for(last = array; last->arrayNext; last = last->arrayNext);
	last->arrayNext = token;
	token->up = array;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		TokenType[token->type], token->value,
		TokenType[array->type], array->value);
	return array;
}

Token *CreateToken(char *value, int type) {
	Token *aux = (Token *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc new token");
		return aux;
	}
	aux->up = aux->down = aux->arrayNext = aux->dictionaryNext = NULL;
	aux->value = value;
	aux->type = type;
//	debugf(MYSELF, "New %s '%s'", TokenType[type], value);
	return aux;
}

void DumpToken(Token *t) {
	debugf(MYSELF, "'%s' as %s child of '%s'",
		t->value, TokenType[t->type],
		t->up ? t->up->value : "(TolkenTree)");
	if(t->dictionaryNext) DumpToken(t->dictionaryNext);
	if(t->arrayNext) DumpToken(t->arrayNext);
}

void DumpTokenTree(TokenTree *t) {
	for(Token *line = t->first; line; line = line->down) {
		DumpToken(line);
	}
}

enum {
	SERIALIZE_SHOULD_CLOSE_ARRAY = 1,
	SERIALIZE_SHOULD_CLOSE_DICTIONARY,
};

void SerializeToken(Token *t, int order) {
	int shouldClose = 0;
	switch (t->type) {
		case TOKEN_TYPE_ARRAY:
//			if(t->up) {
//				if(t->up->type != TOKEN_TYPE_ARRAY) {
//					printf("'%s': ", t->value);
//				}
//			}
			printf("[ ");
			shouldClose = SERIALIZE_SHOULD_CLOSE_ARRAY;
			break;
		case TOKEN_TYPE_DICTIONARY:
//			if(t->up) {
//				if(t->up->type != TOKEN_TYPE_ARRAY) {
//					printf("'%s': ", t->value);
//				}
//			}
			printf("{ ");
			shouldClose = SERIALIZE_SHOULD_CLOSE_DICTIONARY;
			break;
		default:
			if(t->up->type == TOKEN_TYPE_DICTIONARY) {
				if(!order) {
					printf("'%s': ", t->value);
					order = 1;
				} else {
					printf("'%s', ", t->value);
					order = 0;
				}
			} else {
				printf("'%s', ", t->value);
			}
			break;
	}
//	if(shouldClose == SERIALIZE_SHOULD_CLOSE_ARRAY) printf("], ");
//	if(shouldClose == SERIALIZE_SHOULD_CLOSE_DICTIONARY) printf("}, ");
//	if(t->dictionaryNext) SerializeToken(t->dictionaryNext, order);
//	if(t->arrayNext) SerializeToken(t->arrayNext, order);

	if(t->dictionaryNext) SerializeToken(t->dictionaryNext, order);
	if(shouldClose == SERIALIZE_SHOULD_CLOSE_DICTIONARY) printf("}, ");
	
	if(t->arrayNext) SerializeToken(t->arrayNext, order);
	if(shouldClose == SERIALIZE_SHOULD_CLOSE_ARRAY) printf("], ");
}

void SerializeTokenTree(TokenTree *t) {
	printf("-- BEGIN --\n");
	for(Token *line = t->first; line; line = line->down) {
		SerializeToken(line, 0);
	}
	printf("\n-- END --\n");
}

int main1() {
	TokenTree *tree = CreateTokenTree();

	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendToTokenTree(tree, dict0);

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendTokenToDictionary(dict0, array0);

	AppendTokenToDictionary(array0, CreateToken("username", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("email", TOKEN_TYPE_STRING));

	SerializeTokenTree(tree);
	return 0;
}

int main2() {
	TokenTree *tree = CreateTokenTree();

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendToTokenTree(tree, array0);

	AppendTokenToDictionary(array0, CreateToken("username", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("email", TOKEN_TYPE_STRING));

	SerializeTokenTree(tree);
	return 0;
}

int main3() {
	TokenTree *tree = CreateTokenTree();

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendToTokenTree(tree, array0);

	Token *array1 = CreateToken("array1", TOKEN_TYPE_ARRAY);
	AppendTokenToArray(array0, array1);

	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendTokenToDictionary(dict0, CreateToken("key1", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("pair1", TOKEN_TYPE_STRING));
	AppendTokenToArray(array1, dict0);

	Token *dict1 = CreateToken("dict1", TOKEN_TYPE_DICTIONARY);
	AppendTokenToDictionary(dict1, CreateToken("key2", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict1, CreateToken("pair2", TOKEN_TYPE_STRING));
	AppendTokenToArray(array1, dict1);

	//DumpTokenTree(tree);
	SerializeTokenTree(tree);
	return 0;
}

int main() {
	TokenTree *tree = CreateTokenTree();

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendToTokenTree(tree, array0);

	Token *shines = CreateToken("Shine on you crazy diamond", TOKEN_TYPE_STRING);
	AppendTokenToArray(array0, shines);

	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendTokenToArray(array0, dict0);

	AppendTokenToDictionary(dict0, CreateToken("username", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("email", TOKEN_TYPE_STRING));

	Token *wish = CreateToken("Wish you were here", TOKEN_TYPE_STRING);
	AppendTokenToArray(array0, wish);
	
	Token *key = CreateToken("my_array", TOKEN_TYPE_STRING);
	AppendTokenToDictionary(dict0, key);
	Token *array1 = CreateToken("array1", TOKEN_TYPE_ARRAY);
	AppendTokenToDictionary(dict0, array1);
	//AppendTokenToArray(array0, array1);
	
	Token *gilmour = CreateToken("David Gilmour", TOKEN_TYPE_STRING);
	AppendTokenToArray(array1, gilmour);
	
	Token *waters = CreateToken("Roger Waters", TOKEN_TYPE_STRING);
	AppendTokenToArray(array1, waters);

	DumpTokenTree(tree);
	SerializeTokenTree(tree);
	return 0;
}
