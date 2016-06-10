/*Program Description: Create a dictionary based on an input file and use the dictionary to spell-check sentences. Only alphabetical characters are allowed,
*						except at the end of the word. If a word is not found, allow user to edit it or add it to the dictionary. Print out the dictionary to
*						a file, and print out the user's new sentence at the end.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 12/05/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "spellcheck.h"

//main function

int main(void)
{
	/******************************VARS**********************************************/
	char input[]={"dictionary.txt\0"};				//input file name
	char output[]={"alphaorder.txt\0"};				//output file name
	Set dictionary;									//dictionary
	Element sentence[SENTENCE_LENGTH]={{0}};		//screen input from user
	Element words[SENTENCE_LENGTH]={{0}};			//edited screen input
	int found[SENTENCE_LENGTH]={0};					//holds data on whether a particular element was found in the dictionary.
	/*************************VARS**************************************************/ 

	//Initialize the list and read in the data from the input file.
	//Exit if dictionary population is unsuccessful.
	
	set_init(&dictionary);
	if(populate(input,&dictionary)==1);
	{
		//Get user input and search for each word in the dictionary, handling un-matching words as needed. Print sentence when finished.
		
		printf("\nEnter a sentence: ");
		scan(words,sentence);
		search(&dictionary,words,found);
		handleWords(&dictionary,words,found,sentence);
		printSentence(sentence);

		//Print set. If set was successfully printed, notify the user.

		if(printSet(output,&dictionary)==1)
			printf("The dictionary was saved in the file %s.\n",output);
	}
	
	//Close and exit the program.
	
	return 0;
}

//Populate empty list.

int populate(char *filename, Set *s)
{
	int zero=0;		//trivials value for getElement parameter
	Element orig;

	//Open the input file. Exit if file could not be opened.

	FILE *fp=fopen(filename,"r");
	if(!fp)
	{
		printf("The file %s did not open properly. The program will now terminate.\n",filename);
		return 0;
	}

	//If file is not empty, begin populating array.		

	while(!feof(fp))
	{
		Element *e=getElement(fp,&orig,&zero);			//Get the element.

		//If end of file, exit.
		//Otherwise, create a Node and populate element field. Free the space allocated for the element.
	
		if(**e!='!'&&**e!='\0')
			set_insert(s,*e);
		free(e);
	}

	//Close the file. Print a message if the file could not be closed.

	if(!(fclose(fp)==0))
	{
		printf("The file %s did not close properly. The program will now terminate.\n",filename);
		return 2;
	}
	
	//Return 1 if all went well.
	
	return 1;
}

//Print set to file.

int printSet(char *filename, Set *s)
{
	//Open the output file. Exit if the file could not be opened.
	FILE *fp=fopen(filename,"w");
	if(!fp)
	{
		printf("The file %s did not open properly. The program will now terminate.\n",filename);
		return 0;
	}
	
	//Print the dictionary to the output file.
	
	set_inorder(s,fp);
	
	//Exit if the file did not close (returns 0).
	
	if(fclose(fp)!=0)
	{
		printf("The file %s did not close properly. The program will now terminate.\n",filename);
		return 2;
	}
	
	//Return 1 if all went well.
	
	return 1;
}

//Construct the element from file data.

Element *getElement(FILE *fp, Element *unedited, int *stopFlagStdin)
{
	Element *e=malloc(sizeof(Element));			//Element string where input should be stored

	//Scan the element and copy it to designated location for an unedited element if it can be scanned.

	char *c='\0';			//Pointer to character in string, used as index
	char *lastChar='\0';		//Pointer to last character of the element
	
	//Get data from the screen.

	if(fp==stdin)
	{
		char ch=getchar();	//character from screen
		char *pos=*e;		//position in element

		//Stop when newline character is reached or when whitespace is reached.

		while(ch!='\n'&&ch!=' ')
		{
			*pos=ch;
			pos++;
			ch=getchar();
		}

		//Set flag if newline.

		if(ch=='\n')
			*stopFlagStdin=1;

		//Make element a string.

		*pos='\0';
	}
	else
		fscanf(fp,"%s",*e);	

	//Copy the data to designated location for an unedited element.
	//Prepare to test for alphanumeric values.									

	strcpy(*unedited,*e);
	lastChar=*e+strlen(*e)-1;	
	c=*e;

	//If the last character is not a letter, remove it. Place a null character at the end regardless.

	if(*lastChar<'A'||(*lastChar>'Z'&&*lastChar<'a')||*lastChar>'z')
		*lastChar='\0';
	lastChar++;
	*lastChar='\0';

	//If there are any non-letter characters in the string, return '!' and disregard the string.
	//Search each character.

	while(*c)
	{
		//If the character is not a letter, return '!' and break out of the loop.

		if(*c<'A'||(*c>'Z'&&*c<'a')||*c>'z')
		{
			**e='!';
			char *next=*e+1;	//position to make null
			*next='\0';
			*c='\0';
		}
		else c++;
	}

	//Return the element pointer.

	return e;
}

//Scan and store each word on the screen.

void scan(Element *words, Element *sentence)
{
	Element *wordsBegin=words;			//beginning position of "words" array
	Element temp;					//temp storage for unedited element
	int stop=0;

	//Keep getting words until space runs out or until there is nothing left to scan.
	
	do 
	{
		Element *e=getElement(stdin,&temp,&stop);		//stores element created in "getElement" function

		//If element is valid, store it and prepare for next element.
	
		if(**e!='!'&&**e!='\0')
		{
			strcpy(*words,*e);
			strcpy(*sentence,temp);
			words++;
			sentence++;
		}

		free(e);
	}
	while(words<wordsBegin+SENTENCE_LENGTH&&!stop);
}

//Search for each word in the dictionary.

void search(Set *set, Element *words, int *matches)
{
	while(**words&&words<words+SENTENCE_LENGTH)
	{		
		//Store whether the word is a member of the dictionary.
	
		if(set_member(*words,set))
			*matches=1;
		words++;
		matches++;
	}
}

//Handle non-matches in a user-determined fashion.

void handleWords(Set *set, Element *words, int *matches, Element *sentence)
{
	//Track starting positions.

	Element *startWords=words;
	int *startMatches=matches;
	Element *startSentence=sentence;
	
	char nullChar='\0';		//null character
	
	int correct=1;		//Any misspellings present?
	
	//Examine each word and its corresponding "match" boolean.

	for(;strcmp(*words,&nullChar)!=0;words++,matches++,sentence++)
	{
		//If the word does not match a word in the dictionary, prompt user to either edit or add to dictionary.
	
		if(!(*matches))
		{
			char edit[10]={0};		//Does user want to edit the word?
			char add[10]={0};			//Does user want to add the word to the dictionary?
			char newline='\n';		//Storage place for newline character in user entry.

			//Prompt user to edit the word.
			
			printf("\nThe word \"%s\" is not in the dictionary.\n\tWould you like to edit it? (y=yes, N=NO) ",*words);
			scanf("%s",edit);
		
			//If user chooses to edit, store the new word in the old word's place.
						
			if(strcmp(edit,"y")==0)
			{
				printf("Please enter the edited word: ");
				scanf("%s",*words);
				newline=getchar();
				Element temp;
				strcpy(temp,*words);
				
				//Check for a non-alphabetical character at the end of this element of the sentence. If so, append it to temp.
				//Store temp string in sentence element slot.
				
				char punctuation=*(*sentence+strlen(*sentence)-1);
			
				if(punctuation<'A'||(punctuation>'Z'&&punctuation<'a')||punctuation>'z')
				{
					char *end=temp+strlen(temp);
					*end=punctuation;
					end++;
					*end='\0';
				}
				strcpy(*sentence,temp);
			}
			else
			{
				//Prompt user to add the word.
				
				printf("\tWould you like to add \"%s\" to the dictionary? (y=yes, N=NO) ",*words);
				scanf("%s",add);
				
				//If user chooses to add the word to the dictionary, add it.
				
				if(strcmp(add,"y")==0)
					set_insert(set,*words);
			}
			
			//Set "correct" to false.
			
			correct=0;
		}
		
		//If there were misspellings, search the dictionary again and handle any un-matching cases.
			
		if(!correct)
		{
			search(set,startWords,startMatches);
			handleWords(set,startWords,startMatches,startSentence);
		}
	}
}

//Print sentence from array.

void printSentence(Element *sentence)
{
	char nullChar='\0';		//null character

	printf("\nYour final sentence is:\n\t");

	//Print each element of the sentence.

	while(strcmp(*sentence,&nullChar)!=0)
	{
		printf("%s ",*sentence);
		sentence++;
	}
	printf("\n");
}

