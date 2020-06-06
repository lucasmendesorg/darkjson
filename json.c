#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define JSON_NULL	0
#define JSON_STRING	1
#define JSON_ARRAY	2

typedef struct JSON {
	struct JSON *next;
	int type;
	void *ptr;
} JSON;


JSON *InsertJSON(JSON *parent, JSON *node) {
	node->next = parent->next;
	parent->next = node;
	return parent;
}

JSON *CreateJSON(int type, void *ptr) {
	JSON *aux = (JSON *) malloc(sizeof(*aux));
	if(!aux) return aux;
	aux->next = NULL;
	aux->type = type;
	aux->ptr = ptr;
	return aux;
}

JSON *ReadJSON(char *jsonText) {
	JSON *aux = CreateJSON(JSON_NULL, NULL);
	if(!aux) return aux;
	for(int currentBlock = 0; *jsonText; ++jsonText) {
		if(*jsonText == '[') {
			aux->type = JSON_ARRAY;
			++jsonText;
			currentBlock = JSON_ARRAY;
			printf("1: jsonText = %s\n", jsonText);
			while(*jsonText == ' ') ++jsonText;
			printf("2: jsonText = %s\n", jsonText);
			{
				char *jsonStringEnd = jsonText + 1;
				while(*jsonStringEnd != '\'') ++jsonStringEnd;
				printf("3: jsonStringEnd = %s\n", jsonStringEnd);
				printf("4: jsonStringEnd - jsonText = %d bytes\n", (int) (jsonStringEnd - jsonText));
				int jsonPtrSize = (int) (jsonStringEnd - jsonText);
				char *jsonPtr = (char *) malloc(jsonPtrSize);
				strncpy(jsonPtr, jsonText + 1, jsonPtrSize - 1);
				printf("5: jsonPtr = %s\n", (char *) jsonPtr);
				
				JSON *newJson = CreateJSON(JSON_STRING, jsonPtr);
				InsertJSON(aux, newJson);
			}
			// FIX
		}
	}
	return aux;
	
}

void main() {
	char jsonText[] = "[ 'julia', 'piton' ]";
	printf("0: %s\n", jsonText);
	JSON *json = ReadJSON(jsonText);
	for(JSON *j = json; j; j = j->next) {
		printf("j->next = %p, j->type = %d, j->ptr = %s\n",
			j->next, j->type, j->ptr ? (char *) j->ptr : "");
	}
}
