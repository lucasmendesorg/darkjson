/*
	DarkJSON - JSON for C
		(c) 2020 Lucas Mendes <lucas@lucasmendes.org>
*/

#include <darkjson.h>

void test1() {
	TokenTree *tree = CreateTokenTree();

	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendToTokenTree(tree, dict0);

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendTokenToDictionary(dict0, array0);

	AppendTokenToDictionary(array0, CreateToken("username", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("email", TOKEN_TYPE_STRING));

	DumpTokenTree(tree);
	SerializeTokenTree(tree);
}

void test2() {
	TokenTree *tree = CreateTokenTree();

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendToTokenTree(tree, array0);

	AppendTokenToDictionary(array0, CreateToken("username", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("firstname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("lastname", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(array0, CreateToken("email", TOKEN_TYPE_STRING));

	DumpTokenTree(tree);
	SerializeTokenTree(tree);
}

void test3() {
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

	DumpTokenTree(tree);
	SerializeTokenTree(tree);
}

void test4() {
	TokenTree *tree = CreateTokenTree();

	Token *array0 = CreateToken("array0", TOKEN_TYPE_ARRAY);
	AppendToTokenTree(tree, array0);

	Token *shines = CreateToken("Shine on you crazy diamond", TOKEN_TYPE_STRING);
	AppendTokenToArray(array0, shines);

	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendTokenToArray(array0, dict0);

	AppendTokenToDictionary(dict0, CreateToken("description", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("On the turning away", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("price", TOKEN_TYPE_STRING));
	AppendTokenToDictionary(dict0, CreateToken("9.90", TOKEN_TYPE_NUMBER));

	Token *wish = CreateToken("Wish you were here", TOKEN_TYPE_STRING);
	AppendTokenToArray(array0, wish);
	
	Token *key = CreateToken("my_array", TOKEN_TYPE_STRING);
	AppendTokenToDictionary(dict0, key);
	Token *array1 = CreateToken("array1", TOKEN_TYPE_ARRAY);
	AppendTokenToDictionary(dict0, array1);
	
	Token *gilmour = CreateToken("David Gilmour", TOKEN_TYPE_STRING);
	AppendTokenToArray(array1, gilmour);
	
	Token *waters = CreateToken("Roger Waters", TOKEN_TYPE_STRING);
	AppendTokenToArray(array1, waters);

	DumpTokenTree(tree);
	SerializeTokenTree(tree);
}

void test5() {
	TokenTree *tree = CreateTokenTree();
	
	Token *dict0 = CreateToken("dict0", TOKEN_TYPE_DICTIONARY);
	AppendToTokenTree(tree, dict0);
	
	Dictionary_AppendString(dict0, "description", "candy bar");
	Dictionary_AppendNumber(dict0, "price", 4.99);
	
	DumpTokenTree(tree);
	SerializeTokenTree(tree);
}

int main() {
	test4();
	return 0;
}