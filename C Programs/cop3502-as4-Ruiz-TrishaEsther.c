#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define COUNT 10 

//structure for items under trees
struct item_node_struct
{
 char name[32];
 int count;
 struct item_node_struct *left, *right;
};
typedef struct item_node_struct item_node;

//structure for trees
struct tree_name_node_struct
{
 char treeName[32];
 struct tree_name_node_struct *left, *right;
 item_node *theTree;
};
typedef struct tree_name_node_struct tree_name_node;

//initialize tree name struct
tree_name_node *new_tree_node(char treeName[32]) {
  tree_name_node *t = malloc(sizeof(tree_name_node));
  strcpy(t->treeName, treeName);
  t->left = NULL;
  t->right = NULL;
  t->theTree = NULL;
  return t;
}

//initialize item node structure
item_node *new_item_node(char itemName[32], int count){
  item_node *i = malloc(sizeof(item_node));
  strcpy(i->name, itemName);
  i->count = count;
  i->left = NULL;
  i->right = NULL;
  return i;
}


// Remove carriage return and/or line feed characters from a string.
void remove_crlf(char *str)
{
    char *train_ptr = str + strlen(str);
    train_ptr--;
    while ((train_ptr >= str) && (*train_ptr == '\n' || *train_ptr == '\r'))
    {
        *train_ptr = '\0';
        train_ptr--;
    }
}

//gets next non blank line
void get_next_nonblank_line(FILE *ifp, char *str, int max_length)
{
    str[0] = '\0';

    while (str[0] == '\0')
    {
        fgets(str, max_length, ifp);
        remove_crlf(str);
    }
}

//actually required methods


//search methods

//searches for tree in top half
tree_name_node *search_for_name_node(tree_name_node *root, char tree[32]){
  if(root == NULL){
    return NULL;
  }else if(strcmp(root->treeName, tree) == 0){
    return root;
  }else if(strcmp(tree, root->treeName) < 0){
    return search_for_name_node(root->left, tree);
  }else {
    return search_for_name_node(root->right, tree);
  }
}

//searches theTree for the given item
item_node *search_item(item_node *root, char item[32]){

  if(root == NULL){
    return NULL;
  }else if(strcmp(root->name, item) == 0){
    return root;
  }else if(strcmp(item, root->name) < 0){
    return search_item((root->left), item);
  }else{
    return search_item((root->right), item);
  }
}

//searches for item in bottom half
item_node *search_in_name_node(tree_name_node *root, char item[32]){

  item_node *parent = root->theTree;
  if(parent == NULL){
    return NULL;
  }
  return search_item(parent, item);

}

//printing methods

//prints items in order
void print_item_only(item_node *root,FILE *ofp) {
  if(root->left) {
    print_item_only(root->left, ofp);
  }

  fprintf(ofp, "%s ", root->name);
  printf("%s ", root->name);
  

  if(root->right) {
    print_item_only(root->right, ofp);
  }
}

//prints only trees
void print_only_trees(tree_name_node *root, FILE *ofp){
  if(root->left) {
    print_only_trees(root->left, ofp);
  }

  printf("%s ", root->treeName);
  fprintf(ofp, "%s ", root->treeName);

  if(root->right) {
    print_only_trees(root->right, ofp);
  }  
}

//prints both trees and items
void print_trees_and_items(tree_name_node *root, FILE *ofp){
  if(root->left) {
    print_trees_and_items(root->left, ofp);
  }

  fprintf(ofp, "\n===%s===\n", root->treeName);
  printf("\n===%s===\n", root->treeName);
  print_item_only(root->theTree, ofp);
  if(root->right) {
    print_trees_and_items(root->right, ofp);
  }  
}

//print the tree in the format shown at the top of the output file. 
void transverse_in_order(tree_name_node *root, FILE *ofp){
  //print four trees first
  printf("\n");
  fprintf(ofp, "\n");
  print_only_trees(root, ofp);

  //print per tree & its items in order
  print_trees_and_items(root, ofp);
}

//insertion for top half

//Sets trees left child
void set_left_child_top_half(tree_name_node *parent, tree_name_node *child) {
  parent->left = child;
}

//Sets trees right child
void set_right_child_top_half(tree_name_node *parent, tree_name_node *child) {
  parent->right = child;
}

//insert trees into tree name structure top half
tree_name_node *insert_top_half(tree_name_node *parent, tree_name_node *new_node) {
  if(strcmp(new_node->treeName, parent->treeName)<0){
    if(parent->left != NULL){
      return insert_top_half(parent->left, new_node);
    }else{
      set_left_child_top_half(parent, new_node);
      return new_node;
    }
  }else{
    if(parent->right != NULL){
      return insert_top_half(parent->right, new_node);
    }else{
      set_right_child_top_half(parent, new_node);
      return new_node;
    }
  }
}

//insertion bottom half

//sets item left
void set_left_child_bottom_half(item_node *parent, item_node *child){
  parent->left = child;
}

//sets item right
void set_right_child_bottom_half(item_node *parent, item_node *child){
  parent->right = child;
}

//insert items into bottom half
item_node *insert_bottom_half(item_node *parent, item_node *new_node){
  if(strcmp(new_node->name, parent->name)<0){
    if(parent->left != NULL){
      return insert_bottom_half(parent->left, new_node);
    }else{
      set_left_child_bottom_half(parent, new_node);
      return new_node;
    }
  }else{
    if(parent->right != NULL){
      return insert_bottom_half(parent->right, new_node);
    }else{
      set_right_child_bottom_half(parent, new_node);
      return new_node;
    }
  }
}


//DELETION OF TREES HELP



//setting up the trees

//sets up top half trees
tree_name_node *set_top_half(int ntrees, FILE *ifp){

  char line_tree[63];
  char name_holder[32];

  get_next_nonblank_line(ifp, line_tree, 63);
  sscanf(line_tree, "%s", name_holder);

  tree_name_node *root = new_tree_node(name_holder);

  for(int i = 0; i<ntrees-1; i++){

    char line_subtree[63];
    get_next_nonblank_line(ifp, line_subtree, 63);

    sscanf(line_subtree, "%s", name_holder);

    //printf("\nmaking child %s", name_holder);
    tree_name_node *new_node = new_tree_node(name_holder);

    //printf("\ninserting new node into tree");
    insert_top_half(root, new_node);
  }
  return root;
}

//sets up bottom half of whole tree
void set_bottom_half(int nitems, int ntrees, FILE *ifp, tree_name_node *t){
  
  char tree_name[32];
  char name_holder[32];
  char line[32];
  int count = 0;
  
  
  for(int i = 0; i<nitems; i++){
    get_next_nonblank_line(ifp, line, 63);

    sscanf(line, "%s %s %d", tree_name, name_holder, &count);
    
    //find the node with the right tree label
    tree_name_node *i = search_for_name_node(t,tree_name);
    
    //if the tree is null connect that node to the tree else insert into binary tree
    if(i->theTree ==  NULL){
      i->theTree = new_item_node(name_holder, count);
    }else{
      insert_bottom_half(i->theTree, new_item_node(name_holder, count));
    }                           
    
  } 

}

/*
search <tree> <item>
  Search for item item in tree tree. Print the count if it’s found, “<item> not found in <tree>” if the item doesn’t exist there, or “<tree> does not exist” if the tree doesn’t exist. 
*/

//searches the tree through given subtree for given item
void search(tree_name_node *root, char item[32], FILE *ofp){

  //finds items in given tree
  item_node *i = search_in_name_node(root, item);

  //check if item exists
  if(i == NULL){
    fprintf(ofp, "\n%s not found in %s", item, root->treeName);    
    printf("\n%s not found in %s", item, root->treeName);
    return;
  }

  //check item is found
  if(strcmp(i->name, item) == 0){
    fprintf(ofp, "\n%d %s found in %s", i->count, i->name, root->treeName);
    printf("\n%d %s found in %s", i->count, i->name, root->treeName);
  }

}

//initializes for search function
void feed_search(tree_name_node *root, char tree[32], char item[32], FILE *ofp){
  tree_name_node *holder = search_for_name_node(root, tree);

  //check if tree exists, then if item can be found, else not found
  if( holder == NULL){
    fprintf(ofp, "\n%s does not exist", tree);
    printf("\n%s does not exist", tree);
    return;
  }  

  search(holder, item, ofp);

}

//count item
void recurse_item_before(item_node *root, char item[32], int *found, int *final_count){

  //transverse through function and count how many items must be passed till we get to desired item

  if(root->left) {  
    recurse_item_before(root->left, item, found, final_count);
  } 

  if(strcmp(root->name, item) == 0) *found = 1;
  if(*found == 0) *final_count += 1;

  if(root->right) {
    recurse_item_before(root->right, item, found, final_count);
  }
}

/*
item_before <tree> <item>
  Count the number of items lexographically before item item in tree tree.
*/

//count item_before
int item_before(tree_name_node *root, char item[32], FILE *ofp){
  item_node *holder = root->theTree;
  int found = 0;
  int final_count = 0;
  int *final_count_ptr = &final_count;
  int *found_ptr = &found;

  //printf("\n transversing through %s", holder->name);
  recurse_item_before(holder, item, found_ptr, final_count_ptr);

  fprintf(ofp, "\nitem before %s: %d", item, final_count);
  printf("\nitem before %s: %d", item, final_count);

  return final_count;

}

//feeds item_before recursion
void feed_item_before(tree_name_node *root, char item[32], char tree[32], FILE *ofp){
  tree_name_node *t = search_for_name_node(root,tree);
  item_before (t, item, ofp);
}


//finds max between two nums
int max(int one, int two){
  if(one>two) return one;
  else return two;
}

//get height of subtree
int find_height(item_node *root){
  if(root == NULL)
    return -1;

  return max(find_height(root->left), find_height(root->right))+1;
}

/*
 height_balance <tree>
▪ Prints the heights of the left and right subtrees of tree tree, and whether or not they’re
balanced.
▪ A tree is balanced if the heights of its left and right subtrees differ by at most one.
▪ A tree with only a root has height 0.
▪ A null reference has height -1.
*/
void height_balance(tree_name_node *root, FILE *ofp){
  item_node *holder = root->theTree;

  int left_height = find_height(holder->left);
  int right_height = find_height(holder->right);

  fprintf(ofp, "left height %d, right height %d, difference %d", left_height, right_height, abs(left_height-right_height));
  printf("left height %d, right height %d, difference %d", left_height, right_height, abs(left_height-right_height));

  if(abs(left_height-right_height) <= 1){
    fprintf(ofp, ", balanced");
    printf(", balanced");
  }
  else {
    fprintf(ofp, ", not balanced");
    printf(", not balanced");
  }

}

//initializes for height balance function
void feed_height_balance(tree_name_node *root, char tree[32], FILE *ofp){
  tree_name_node *holder = search_for_name_node(root, tree);
  
  fprintf(ofp, "\n%s: ", tree);
  printf("\n%s: ", tree);
  height_balance(holder, ofp);
}

/*
 count <tree>
▪ Prints the total number of items in tree tree.
▪ Cackling is not permitted.

*/

//recursion for count function
void recurse_count(item_node *root, int *final_count){
  //transverse through function and count how many items must be passed till we get to desired item

  if(root->left) {  
    recurse_count(root->left, final_count);
  } 

  *final_count += root->count;

  if(root->right) {
    recurse_count(root->right, final_count);
  }
}

//sums up counts
void count(tree_name_node *root, FILE *ofp){
  item_node *holder = root->theTree;
  int final_count = 0;
  int *final_count_ptr = &final_count;
  
  recurse_count(holder, final_count_ptr);

  fprintf(ofp, " count %d", final_count);
  printf(" count %d", final_count);
}

//initializes for sum function
void feed_count(tree_name_node *root, char tree[32], FILE *ofp){
  //find the node with the right tree label
  tree_name_node *t = search_for_name_node(root,tree);

  //check if tree exists, then if item can be found, else not found
  if(t == NULL){
    fprintf(ofp,"\n%s does not exist", tree);
    printf("\n%s does not exist", tree);
    return;
  }

  fprintf(ofp, "\n%s", tree);
  printf("\n%s", tree);
  count(t, ofp);

}

/*
delete <tree> <item>
  Deletes item item from tree tree.
*/

//gives smalles item
item_node *minItem(item_node *item)
{
    item_node *curr = item;
 
    //find most left leaf
    while (curr && curr->left != NULL)
        curr = curr->left;
 
    return curr;
}

//deletes item from tree recursion
item_node *delete_recurse(item_node *root, char item[32]){

  
  if (root == NULL)
    return root;

  //shift nodes first
  if(strcmp(item, root->name) < 0){
    root->left = delete_recurse(root->left, item);
  }else if(strcmp(item, root->name) > 0){
    root->right = delete_recurse(root->right, item);
  }else{

    //then delete the actual node

    //deletes item with one or no children
    if (root->left == NULL) {
      item_node *holder = root->right;
      free(root);
      root = NULL;
      return holder;
      }
    else if (root->right == NULL) {
      item_node *holder = root->left;
      free(root);
      root = NULL;
      return holder;
    }


    item_node *smallestItem  = minItem(root->right);
    strcpy(root->name, smallestItem->name);
    root->count = smallestItem->count;
    root->right = delete_recurse(root->right, smallestItem->name);
  }

  return root;
}

//delete specific item from tree
void delete(tree_name_node *root, char item[32]){
  item_node *holder = root->theTree;

  holder = delete_recurse(holder, item);
}

//initializes delete function
void feed_delete(tree_name_node *root, char tree[32], char item[32], FILE *ofp){

  tree_name_node *holder = search_for_name_node(root,tree);

  delete(holder, item);

  fprintf(ofp, "\n%s deleted from %s", item, tree);
  printf("\n%s deleted from %s", item, tree);
}

/*
delete_tree <tree>
  Deletes tree tree.
*/

//helps delete from top half
tree_name_node *minTree(tree_name_node *tree)
{
    tree_name_node *curr = tree;
 
    //find most left leaf
    while (curr && curr->left != NULL)
        curr = curr->left;
 
    return curr;
}

//delete from top_half
tree_name_node *delete_tree_top(tree_name_node *root, char tree[32]){

  
  if (root == NULL)
    return root;

  //shift nodes first
  if(strcmp(tree, root->treeName) < 0){
    root->left = delete_tree_top(root->left, tree);
  }else if(strcmp(tree, root->treeName) > 0){
    root->right = delete_tree_top(root->right, tree);
  }else{

    //then delete the actual node

    //deletes item with one or no children
    if (root->left == NULL) {
      tree_name_node *holder = root->right;
      free(root);
      root = NULL;
      return holder;
      }
    else if (root->right == NULL) {
      tree_name_node *holder = root->left;
      free(root);
      root = NULL;
      return holder;
    }


    tree_name_node *smallestTree  = minTree(root->right);
    strcpy(root->treeName, smallestTree->treeName);
    root->right = delete_tree_top(root->right, smallestTree->treeName);
  }

  return root;
}

//delete bottom half
void delete_tree_bottom(item_node *root){
  if(root == NULL)
    return;

  delete_tree_bottom(root->left);
  delete_tree_bottom(root->right);

  
  free(root);
  root = NULL;

}

//initiates deleting a tree
void feed_delete_tree(tree_name_node *root, char tree[32], FILE *ofp){
  tree_name_node *tree_holder = search_for_name_node(root, tree);
  item_node *holder = tree_holder->theTree;

  delete_tree_bottom(holder);
  delete_tree_top(root, tree);

  fprintf(ofp, "\n%s deleted", tree);
  printf("\n%s deleted", tree);
}

//sets up all tree
tree_name_node *set_up_trees(int ntrees, int nitems, FILE *ifp, tree_name_node *tree){
    tree = set_top_half(ntrees, ifp);
    
    printf("\n");
    
    set_bottom_half(nitems, ntrees, ifp, tree);
    
    return tree;
}

//reads all commands
void read_commands(tree_name_node *tree, FILE *ifp, int ncommands, FILE *ofp){
  
  char line[63];
  char command[63];
  printf("\n=====Processing Commands=====");
  fprintf(ofp, "\n=====Processing Commands=====");

  for(int i = 0; i < ncommands; i++){

    //scan in the read_command
    get_next_nonblank_line(ifp, line, 63);
    sscanf(line, "%s", command);

    //check which command
    if(strcmp(command, "search") == 0){

      char tree_name[32];
      char item[32];
      sscanf(line, "%s %s %s",command, tree_name, item);

      feed_search(tree, tree_name, item, ofp);
      

    }else if(strcmp(command, "item_before") == 0){

      char tree_name[32];
      char item[32];
      sscanf(line, "%s %s %s",command, tree_name, item);

      feed_item_before(tree, item, tree_name, ofp);

    }else if(strcmp(command, "height_balance") == 0){

      char tree_name[32];
      sscanf(line, "%s %s",command, tree_name);

      feed_height_balance(tree, tree_name, ofp);

    }else if(strcmp(command, "count") == 0){

      char tree_name[32];
      sscanf(line, "%s %s",command, tree_name);

      feed_count(tree, tree_name, ofp);

    }else if(strcmp(command, "delete") == 0){
      
      char tree_name[32];
      char item[32];
      sscanf(line, "%s %s %s",command, tree_name, item);

      feed_delete(tree, tree_name, item, ofp);

    }else if(strcmp(command, "delete_tree") == 0){

      char tree_name[32];
      sscanf(line, "%s %s",command, tree_name);

      feed_delete_tree(tree, tree_name, ofp);


    }

  }

  
}

int main(void) {
   //opens input files and output files
    FILE *ifp;
    FILE *ofp;
    ifp = fopen("cop3502-as4-input.txt", "r");
    ofp = fopen(" cop3502-as4-output-Ruiz-TrishaEsther.txt", "w");

    //read ntrees, nitems, ncommands
    int ntrees;
    int nitems;
    int ncommands;

    //gets ntrees, nitems, ncommands
    char line[63];
    get_next_nonblank_line(ifp, line, 63);
    sscanf(line, "%d %d %d", &ntrees, &nitems, &ncommands);
    
    //sets up tree from file
    tree_name_node *tree = set_up_trees(ntrees, nitems, ifp, tree);

    //prints out in order
    transverse_in_order(tree, ofp);
    
    //reads through commands
    read_commands(tree, ifp, ncommands, ofp);
   
    //closes file
    fclose(ifp);
    fclose(ofp);

  return 0;
}