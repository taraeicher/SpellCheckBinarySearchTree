/*Program Description: Manipulate a binary search tree. Key is a string defined in corresponding header file.
*						Contains file I/O used for printing and capturing key data.
*Programer Name: Tara Eicher
*WSU ID: z847x563
*Professor: Karen Milberger
*Date Completed: 11/23/2013
*/

//maximum length of key string

#define KEY_LENGTH 100

/* Type definitions */

//Define array of characters as a key.

typedef char Key[KEY_LENGTH];

//Define a node for a binary tree.

typedef struct node
{
Key key;
struct node *parent;
struct node *leftchild;
struct node *rightchild;
} Node;

//Define a binary tree.

typedef Node * Tree;

/* Type definition end */



/* Functions */

//Sets the key a to the value of the key b.

void key_setequal(Key a, Key b);

//Returns true (1) if the two keys are equal, or false (0) otherwise.
 
int key_isequal(Key a, Key b);

//Returns true (1) if a comes before b in the order used for sorting.

int key_lessthan(Key a, Key b);

//Initialize tree.

void tree_init(Tree *t);

//makes a new Node (with malloc), sets its key to k, its parent to parent, and its left and right children to NULL.

Node *tree_makenode(Key k, Node *parent);

//Return a pointer to the root of the tree.

Node *tree_root(Tree t);

//Return a pointer to the parent of a given node.

Node *tree_parent(Node *n);

//Return a pointer to the left child of a given node.

Node *tree_leftchild(Node *n);

//Return a pointer to the right child of a given node.

Node *tree_rightchild(Node *n); 

//Find and return the node that matches a given key.

Node *tree_search(Key k, Tree t);

//Return the number of children of a given node.

int tree_num_children(Node *n);

//Insert a new node into the tree in sorted order.

void tree_insert(Tree *t, Key k);

//Delete node with a given key.

void tree_delete(Tree t, Key k);

//Print the contents of the list to a given file in preorder.

void tree_preorder(Node *n, FILE *fp);

//Print the contents of the list to a given file in postorder.

void tree_postorder(Node *n, FILE *fp);

//Print the contents of the list to a given file in inorder.

void tree_inorder(Node *n, FILE *fp);

//Determine whether the tree is empty.

int tree_empty(Tree t);

//Find the height of the tree.

int tree_height(Tree t);

//Delete all nodes in the tree.

void tree_makenull(Tree t);




