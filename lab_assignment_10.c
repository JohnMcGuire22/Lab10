#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:4996)

// Trie structure
struct Trie
{
	int count;
	struct Trie* child[26];
};

struct Trie* createTrie();

// Inserts the word to the trie structure
void insert(struct Trie* pTrie, char* word)
{
	struct Trie* temp = pTrie;
	int i = 0;
	while (word[i] != '\0') {
		if (temp->child[word[i] - 'a'] == NULL) {
			temp->child[word[i] - 'a'] = createTrie();
		}
		temp = temp->child[word[i] - 'a'];
		i++;
	}
	temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie* pTrie, char* word)
{
	struct Trie* temp = pTrie;
	int i = 0;
	while (word[i] != '\0') {
		if (temp->child[word[i] - 'a'] == NULL) {
			return 0; //not found
		}
		temp = temp->child[word[i] - 'a'];
		i++;
	}
	return temp->count;
}

// deallocate the trie structure
struct Trie* deallocateTrie(struct Trie* pTrie)
{
	if (pTrie == NULL) return; //done
	for (int i = 0; i < 26; i++) {
		if (pTrie->child[i] != NULL) {
			deallocateTrie(pTrie->child[i]);
		}
	}
	free(pTrie);
	return NULL;
}

// Initializes a trie structure
struct Trie* createTrie()
{
	struct Trie* temp = (struct Trie*)malloc(sizeof(struct Trie));
	if (temp != NULL) {
		temp->count = 0;
		for (int i = 0; i < 26; i++) temp->child[i] = NULL;
	}
	else {
		printf("Allocation failed\n");
		exit(-1);
	}
	return temp;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char* filename, char** pInWords)
{
	FILE* fptrIN = fopen(filename, "r");
	if (fptrIN == NULL) {
		printf("Failed to open file\n");
		exit(-1);
	}

	int n;
	fscanf(fptrIN, "%d ", &n);
	
	for (int i = 0; i < n; i++) {
		pInWords[i] = (char*)malloc(256 * sizeof(char));
		if (pInWords[i] == NULL) {
			printf("Allocation failed\n");
			exit(-1);
		}
		fscanf(fptrIN, "%s", pInWords[i]);
	}

	fclose(fptrIN);
	return n;
}

int main(void)
{
	char* inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}

	struct Trie* pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char* pWords[] = { "notaword", "ucf", "no", "note", "corg" };
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}