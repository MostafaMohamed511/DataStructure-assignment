#include <iostream>
#include <cstring>

using namespace std;

struct node
{
  int index;
  int start;
  int len;
  node** children; // 60 children will cover ASCII code from 65(A) to 122(z) and dollar sign
  node(int start, int len, int id)
  {
    this->start = start;
    this->len = len;
    index = id;
    children = new node *[60];
    for (int i = 0; i < 60; i++) children[i] = NULL;
  }
  ~node()
  {
      for (int i=0 ; i<60 ; i++)
        delete children[i] ;
      delete children ;
  }
};

class suffixTree
{
private:
  char* txt;
  node* root;
  void bc(node* n, char word[])
  {
    if (n->index != -1)
    {
      cout << n->index << " ";
      return;
    }
    int len = strlen(word) ;
    int idx = ( (word[0] == '$') ?  59 :  word[0] - 'A' );
    node* currentChild = n->children[idx];
    if (currentChild != NULL)
    {
      int i = 1;
      while (txt[currentChild->start + i] == word[i] && i < currentChild->len)
      {
        i++;
      }
      if (i==len)
      print(currentChild) ;
      else if (i < currentChild->len && i < len)
      {
       cout << "Not Found2 \n";
      }
      else if (len > i)
      {
       bc(currentChild, word + i);
      }
    }
}

  void print(node* n)
  {
    if (n->index != -1)
    {
      cout << n->index << " " ;
      return;
    }
    for (int i = 0; i < 60; i++)
    {
      node* currentChild = n->children[i];
      if (currentChild != NULL)
      {
        print(currentChild);
      }
    }
  }

  void add(node * parent,node * child )
  {
    int start = child->start ;
    int idx =( (txt[start] == '$') ? 59 : txt[start] - 'A' );
    node* currentChild = parent->children[idx];
    if (currentChild == NULL)
    {
      parent->children[idx] = child;
    }
    else if (txt[start] == txt[currentChild->start])
    {
      int q = 0, currentChildStart = currentChild->start ;
      while (q< min(currentChild->len, child->len) && txt[start + q] == txt[currentChildStart+q])
      q++ ;
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
  void deleteTree(node* node)
  {
    if (node == NULL) return;
    for (int i=0 ; i<60 ; i++)
        delete (node ->children[i]) ;
    delete node;
  }
public:
  suffixTree(char word[])
  {
    int n = strlen(word);
    txt=new char[ n ];
    strcpy(txt, word);
    //initializing root node
    root = new node(-1, -1, -1);

    for (int i = n-1; i >=0; i--)
    {
      int len = n-i ;
      node* newNode = new node (i, len, i) ;
      add(root, newNode) ;
    }

  }
  void search(char word[])
  {
    int idx = word[0] - 'A';
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

  void printAll()
  {
    print(root);
  }
  ~suffixTree()
  {
    deleteTree(root);
  }

};

int main()
{

  suffixTree q("bananabanaba$");

  q.search("ana"); // Prints: 1 3 7
  q.search("naba"); // Prints: 4 8



  suffixTree t("banana$");
  t.search("an$"); //not found
  t.search("banana"); // 0
  t.search("banana$"); // 0
  t.search("anana"); // 1
  t.search("nan");// 2
  t.search("an"); // 1 3
  t.search("na"); // 2 4

  return 0;
}
