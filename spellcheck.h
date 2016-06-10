/*Program Description: Create a dictionary based on an input file and use the dictionary to spell-check sentences. Only alphabetical characters are allowed,
*						except at the end of the word. If a word is not found, allow user to edit it or add it to the dictionary. Print out the dictionary to
*						a file, and print out the user's new sentence at the end.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 12/05/2013
*/

#define WORD_LENGTH 50
#define SENTENCE_LENGTH 1000

//Populate empty list.

int populate(char *filename, Set *s);

//Construct the element from file data.

Element *getElement(FILE *stream, Element *unedited, int *stopFlagStdin);

//Scan and store each word on the screen.

void scan(Element *words, Element *sentence);

//Search for each word in the dictionary.

void search(Set *set, Element *words, int *matches);

//Handle non-matches in a user-determined fashion.

void handleWords(Set *set, Element *words, int *matches, Element *sentence);

//Print set to file.

int printSet(char *filename, Set *s);

//Print sentence from array.

void printSentence(Element *screenInput);
