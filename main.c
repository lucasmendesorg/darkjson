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
	for(; *jsonText; ++jsonText) {
		if(*jsonText == '[') {
			aux->type = JSON_ARRAY;
			while(*jsonText != ']') {
				++jsonText;
				while(*jsonText == ' ') ++jsonText;
				{
					char *jsonStringEnd = jsonText + 1;
					
					while(*jsonStringEnd != '\'') ++jsonStringEnd;
					
					int jsonPtrSize = (int) (jsonStringEnd - jsonText);
					char *jsonPtr = (char *) malloc(jsonPtrSize);
					
					strncpy(jsonPtr, jsonText + 1, jsonPtrSize - 1);
					
					JSON *newJson = CreateJSON(JSON_STRING, jsonPtr);
					InsertJSON(aux, newJson);
				}
				// FIX
//				if(*jsonText == ']') break;
			}
		}
	}
	return aux;
	
}

int main() {
	char jsonText[] = "[ 'julia', 'piton' ]";
	printf("JSON text = %s\n", jsonText);
	JSON *json = ReadJSON(jsonText);
	for(JSON *j = json; j; j = j->next) {
		static char *types[] = {
			"Root", "String", "Array"
		};
		printf("Entry %p -> %s = '%s'\n",
			j, types[j->type], j->ptr ? (char *) j->ptr : "");
	}
	return 0;
}
