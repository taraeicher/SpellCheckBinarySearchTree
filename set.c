#include <stdio.h>
#include "set.h"

//Initialize the set s.

void set_init(Set *s)
{
	tree_init(&((*s).tree));
} 

//Adds the element e to s.

void set_insert(Set *s, Element e)
{
	tree_insert(&((*s).tree),e);
}

//Removes the element e from s.

void set_delete(Set *s, Element e)
{
	tree_delete((*s).tree,e);
} 

//Returns true (1) if element e is a member of s and false (0) if it’s not.

int set_member(Element e, Set *s)
{
	//Search for element in tree.

	if(tree_search(e,(*s).tree))
		return 1;
	else return 0;
}

//Returns a pointer to the first element of s (or NULL if s is empty).

Element *set_min(Set *s)
{
	Tree tree=s->tree;
	
	//Move down the left side of the tree to find the min.
	
	while(tree_leftchild(tree))
		tree=tree_leftchild(tree);
	return &((*tree).key);
} 

//Returns a pointer to the last element of s (or NULL if s is empty).

Element *set_max(Set *s)
{
	Tree tree=s->tree;
	
	//Move down the right side of the tree to find the max.
	
	while(tree_rightchild(tree))
		tree=tree_rightchild(tree);
	return &((*tree).key);
} 

//Returns true (1) if s is empty and false (0) if it’s not empty.

int set_empty(Set *s)
{
	return tree_empty((*s).tree);
}

//Writes out each element of s, one element per line, inorder, to the file fp.

void set_inorder(Set *s, FILE *fp)
{
	tree_inorder((*s).tree,fp);
} 

//Deletes all elements of s.

void set_makenull(Set *s)
{
	tree_makenull((*s).tree);
}
