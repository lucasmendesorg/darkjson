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
			.next = NULL,
			.type = STRING || NUMBER,
			value = "..."
		}
		
	Para ARRAY, *next aponta para os membros do array, seguindo o
	modelo padrão para STRING e NUMBER. Chamamos isso de colunas.
	
	Para DICTIONARY, *next aponta para os membros do dictionary,
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
#include <darkjson.h>

#define TOKEN_TYPE_UNKNOWN	0
#define TOKEN_TYPE_STRING	1
#define TOKEN_TYPE_NUMBER	2
#define TOKEN_TYPE_ARRAY	3
#define TOKEN_TYPE_DICTIONARY	4

static const char *TokenType[] = {
	"Unknown", "String", "Number", "Array", "Dictionary",
};

typedef struct Token {
	struct Token *down;
	struct Token *next;
	char *value;
	int type;
} Token;
/*
typedef struct TokenTree {
	struct Token *first;
	struct Token *last;
} TokenTree;
*/
// Insere uma nova coluna (verticlmente, token->next) no final da lista *container
Token *AppendTokenColumn(Token *container, Token *token) {
	Token *last;
	if(container->type != TOKEN_TYPE_ARRAY && container->type != TOKEN_TYPE_DICTIONARY) {
		debugf(MYSELF, "Cannot append column to %s", TokenType[container->type]);
		return NULL;
	}
	for(last = container; last->next; last = last->next);	// Isso pode ser otimizado, mantendo um cache de *last
	last->next = token;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		TokenType[token->type], token->value,
		TokenType[container->type], container->value);
	return container;
}

// Insere uma nova linha (horizontalmente, token->down) no final da arvore *tree
Token *AppendTokenLine(Token *tree, Token *token) {
	Token *last;
	for(last = tree; last->down; last = last->down);	// Isso pode ser otimizado, mantendo um cache de *last
	last->down = token;
	debugf(MYSELF, "Appending %s '%s' to the end of %s '%s'",
		TokenType[token->type], token->value,
		TokenType[tree->type], tree->value);
	return tree;
}

Token *CreateToken(char *value, int type) {
	Token *aux = (Token *) malloc(sizeof(*aux));
	if(!aux) {
		debugf(MYSELF, "Cannot alloc new token");
		return aux;
	}
	aux->down = aux->next = NULL;
	aux->value = value;
	aux->type = type;
	debugf(MYSELF, "New %s '%s'", TokenType[type], value);
	return aux;
}

// output: outPtr = token capturado
// return: gotten token type 
int GetToken(char *outPtr, int length) {
	// FIX
	return -1;
}

void TestLine() {
	Token *root = CreateToken("my_array", TOKEN_TYPE_ARRAY);
	AppendTokenLine(root, CreateToken("one", TOKEN_TYPE_STRING));
	AppendTokenLine(root, CreateToken("two", TOKEN_TYPE_STRING));
	for(Token *line = root; line; line = line->down) {
		debugf(MYSELF, "Found line '%s' as %s", line->value, TokenType[line->type]);
	}
}

void TestColumn() {
	Token *tree = CreateToken("julia", TOKEN_TYPE_STRING);
	AppendTokenLine(tree, CreateToken("piton", TOKEN_TYPE_STRING));
	AppendTokenColumn(tree, CreateToken("it-should-cause-an-error", TOKEN_TYPE_STRING));
	for(Token *column = tree; column; column = column->down) {
		debugf(MYSELF, "Found column '%s' as %s", column->value, TokenType[column->type]);
	}
}

void TestLineAndColumn() {
	Token *rootArray = CreateToken("usersArray", TOKEN_TYPE_ARRAY);
	Token *userDict0 = CreateToken("user0", TOKEN_TYPE_DICTIONARY);
	Token *userDict1 = CreateToken("user1", TOKEN_TYPE_DICTIONARY);
	AppendTokenLine(rootArray, userDict0);
	AppendTokenLine(rootArray, userDict1);
	AppendTokenColumn(userDict0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict0, CreateToken("Julia", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict0, CreateToken("Piton", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict1, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict1, CreateToken("Lucas", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict1, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenColumn(userDict1, CreateToken("Mendes", TOKEN_TYPE_STRING));
	for(Token *line = rootArray; line; line = line->down) {
		debugf(MYSELF, "Found line '%s' as %s", line->value, TokenType[line->type]);
		for(Token *column = line->next; column; column = column->next) {
			debugf(MYSELF, "\tFound column on %s '%s': '%s' as %s",
				TokenType[line->type], line->value,
				column->value, TokenType[column->type]);
		}
	}
}

int main() {
	return 0;
}
