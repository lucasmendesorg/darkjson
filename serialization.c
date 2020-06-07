/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

void SerializeToken(Token *t, int order) {
	int shouldClose = 0;
	switch (t->Type) {
		case TOKEN_TYPE_ARRAY:
			printf("[ ");
			shouldClose = SERIALIZE_SHOULD_CLOSE_ARRAY;
			break;
		case TOKEN_TYPE_DICTIONARY:
			printf("{ ");
			shouldClose = SERIALIZE_SHOULD_CLOSE_DICTIONARY;
			break;
		default:
			if(t->Up->Type == TOKEN_TYPE_DICTIONARY) {
				if(!order) {
					printf("'%s': ", t->Value);
					order = 1;
				} else {
					if(t->Type == TOKEN_TYPE_NUMBER) printf("%s, ", t->Value);
					else printf("'%s', ", t->Value);
					order = 0;
				}
			} else {
				if(t->Type == TOKEN_TYPE_NUMBER) printf("%s, ", t->Value);
				else printf("'%s', ", t->Value);
			}
			break;
	}
	if(t->NextDictionary) SerializeToken(t->NextDictionary, order);
	if(shouldClose == SERIALIZE_SHOULD_CLOSE_DICTIONARY) printf("}, ");
	if(t->NextArray) SerializeToken(t->NextArray, order);
	if(shouldClose == SERIALIZE_SHOULD_CLOSE_ARRAY) printf("], ");
}

void SerializeTokenTree(TokenTree *t) {
	printf("-- BEGIN --\n");
	for(Token *line = t->First; line; line = line->Down) {
		SerializeToken(line, 0);
	}
	printf("\n-- END --\n");
}
