#include <iostream>
#include <cstring>

using namespace std;

struct node
{
  int index;  // in leaf nodes only it stores the starting index in the original string of the suffix ending at this node else it stores -1
  int start;  // stores the starting index in the original string of the characters on the edge going to this node.
  int len;  // stores the number of characters on the edge going to this node.
  node** children; // 60 children will cover ASCII code from 65(A) to 122(z) and dollar sign.
  // parametrized constructor to assign values for each node and allocate memory for children
  node(int start, int len, int id)
  {
    this->start = start;
    this->len = len;
    index = id;
    children = new node *[60];
    // setting all children to null value
    for (int i = 0; i < 60; i++) children[i] = NULL;
  }
  // destructor to delete dynamically allocated memory
//  ~node()
//  {
//      for (int i=0 ; i<60 ; i++)
//        delete children[i] ;
//      delete children ;
//  }
};

class suffixTree
{
private:
  char* txt; // stores the string
  node* root;  // the root of the tree
  int length ; // stores the length of the string
//function to print all subtrees of node
  void print(node* n)
  {
    // if the node is a leaf just print its index and return
    if (n->index != -1)
    {
      cout << n->index << " " ;
      return;
    }
    // otherwise printing all children of the node
    for (int i = 0; i < 60; i++)
    {
      node* currentChild = n->children[i];
      if (currentChild != NULL)
        print(currentChild);
    }
  }
  void bc(node* n, char word[])
  {
    int len = strlen(word) ;
    // specify the index of the branch to search in
    int idx = ( (word[0] == '$') ?  59 :  word[0] - 'A' );
    node* currentChild = n->children[idx];
    // if the specified node is not null start searching
    if (currentChild != NULL)
    {
      //count the number of common characters on the branch and the specified word
      int i = 1;
      while (txt[currentChild->start + i] == word[i] && i < currentChild->len) i++;
      // if the number of common characters equals the length of the length of the string we search
      // then we print all subtrees of this branche
      if (i==len)
        print(currentChild) ;
      // if there is still characters we search on this subtree
      else if (len > i)
      {
        bc(currentChild, word + i);
      }
      // if there is still characters which are not common
      // then we just print not found
      else if (i < currentChild->len && i < len)
      {
       cout << "Not Found";
      }
    }
    else
      cout << "Not Found" ;
  }
  // function to build the tree
  // will be called in the constructor
  void buildTree ()
  {
    for (int i = length-1; i >=0; i--)
    {
      int len = length-i ; // length of the suffix sub string
      node* newNode = new node (i, len, i) ;
      add(root, newNode) ;
    }
  }
  // function to add new branch
  void add(node * parent,node * child )
  {
    int start = child->start ; // store the starting index of the new node
    int idx =( (txt[start] == '$') ? 59 : txt[start] - 'A' );
    node* currentChild = parent->children[idx]; // the branch we supposed to add in
    // if the branch is empty we simply add the new child
    if (currentChild == NULL)
    {
      parent->children[idx] = child;
    }
    else if (txt[start] == txt[currentChild->start])
    {
      int q = 0 ; //stores the number of common characters
      int currentChildStart = currentChild->start ;
      while (q< min(currentChild->len, child->len) && txt[start + q] == txt[currentChildStart+q])  q++ ;
      if (q == currentChild->len)
      {
        child -> start += q ;
        child -> len -= q ;
        add(currentChild,child) ;
      }
      else
      {
        node * x = new node (start,q,-1) ;
        parent->children[idx] = x ;

        currentChild -> start =   currentChild -> start +q ;
        currentChild -> len -= q ;

        child -> start += q ;
        child -> len -= q ;

        add(x,child) ;
        add(x, currentChild ) ;
      }
    }
  }
  // function to delete all subtrees of node
  void deleteNode(node* node)
  {
    // if node is null we just return
    if (node == NULL) return;
    // otherwise delete all its children
    for (int i=0 ; i<60 ; i++)
      deleteNode (node ->children[i]) ;
    // then delete the node itself
    delete node;
  }
public:
  suffixTree(char word[])
  {
    // assigning the string
    length = strlen(word);
    txt=new char[ length ];
    strcpy(txt, word);
    //initializing root node
    root = new node(-1, -1, -1);
    // start building the tree
    buildTree();

  }
  void search(char word[])
  {
    // getting the index of the branch that contains the string
    int idx = word[0] - 'A';
    // if the branch is empty then there is no such substring otherwise start searching
    if (root->children[idx] != NULL)
    {
      bc(root, word);
    }
    else
    {
      cout << "Not Found";
    }
    cout << "\n" ;
  }
  // destructor to delete dynamically allocated memory
  ~suffixTree()
  {
    deleteNode(root);
  }

};

int main()
{
  // 1st sample
  cout << "assignment sample without change :\n" ;
  suffixTree t1("bananabanaba$");
  t1.search("ana"); // Prints: 1 3 7
  t1.search("naba"); // Prints: 4 8
  char *word[10] ={ "cocowawa$", "papanpana$", "botatotata$", "catatcat$", "lolipopopo$", "banana$", "ABRACADABRA$", "AAAAAAA$", "MISSISSIPPI$", "GATAGACA$"};
  char *tst1[10] ={ "co"       , "pan"       , "tat"        , "atat"     , "po"         , "ban"    , "BRA"         , "AA"      , "MISS"        , "GTA"} ;
  char *tst2[10] ={ "awa"      , "app"       , "ata"        , "tc"       , "lop"        , "nab"    , "bra"         , "Ac"      , "SSI"         , "GACA"} ;
  char *tst3[10] ={ "wac"      , "na"        , "ota"        , "dog"      , "opo"        , "a"      , "AB"          , "aa"      , "SIP"         , "TAG"} ;
  for (int i= 0 ; i<10 ; i++)
  {
    cout << "sample: " << word[i] << '\n';
    suffixTree tree(word[i]) ;
    cout << tst1[i] << ": " ; tree.search(tst1[i]);
    cout << tst2[i] << ": " ; tree.search(tst2[i]);
    cout << tst3[i] << ": " ; tree.search(tst3[i]);
  }
  return 0;
}
