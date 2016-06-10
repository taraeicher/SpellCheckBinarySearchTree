#include "bin_search_tree.h"

/**************************************** Type Definitions **********************************/

typedef Key Element;
typedef struct
{
   Tree tree;
} Set;

/***************************************** Prototypes **************************************/

//Initialize the set s.

void set_init(Set *s); 

//Adds the element e to s.

void set_insert(Set *s, Element e); 

//Removes the element e from s.

void set_delete(Set *s, Element e); 

//Returns true (1) if element e is a member of s and false (0) if it’s not.

int set_member(Element e, Set *s);

//Returns a pointer to the first element of s (or NULL if s is empty).

Element *set_min(Set *s); 

//Returns a pointer to the last element of s (or NULL if s is empty).

Element *set_max(Set *s); 

//Returns true (1) if s is empty and false (0) if it’s not empty.

int set_empty(Set *s);

//Writes out each element of s, one element per line, inorder, to the file fp.

void set_inorder(Set *s, FILE *fp); 

//Deletes all elements of s.

void set_makenull(Set *s); 



