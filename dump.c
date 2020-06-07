/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

void DumpToken(Token *t) {
	debugf(MYSELF, "'%s' as %s child of '%s'",
		t->Value, GetTokenType(t->Type),
		t->Up ? t->Up->Value : "(TolkenTree)");
	if(t->NextDictionary) DumpToken(t->NextDictionary);
	if(t->NextArray) DumpToken(t->NextArray);
}

void DumpTokenTree(TokenTree *t) {
	for(Token *line = t->First; line; line = line->Down) {
		DumpToken(line);
	}
}
