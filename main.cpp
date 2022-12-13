#include <iostream>
#include <cstring>

using namespace std;

struct node
{
    int index ;
    char label[100] ;
    node **children ;
    node()
    {
        index = -1 ;
        children = new node*[100] ;
        for (int i=0 ; i<100 ; i++)
            children[i] = NULL ;
    }
    node(char sub[] , int id)
    {
        strcpy(label, sub) ;
        index = id ;
        children = new node*[100] ;
        for (int i=0 ; i<100 ; i++)
            children[i] = NULL ;

    }
};
class suffixTree
{
public :
    node *root ;
    void print(node* n , const char a[100])
    {
        if (n->index  != -1)
        {
            cout << a << endl;
            return;
        }
        for (int i=0 ; i<100 ; i++)
        {
            node* currentChild = n->children[i] ;
            if (currentChild == NULL)
                break ;
            else
            {
                char x[100] ;
                strcpy(x,a) ;
                strcat(x,currentChild->label) ;
                print(currentChild , x) ;
            }

        }

    }
public:
    suffixTree(char word[])
    {
        //initializing root node
        root = new node() ;
        // adding special char
        //strcat(word, "$") ;

        int n = strlen(word) ;


        for (int i=0 ; i<n ; i++)
        {
            // getting suffix substring from i
            char *a = word + i ;
            char suffix[100];
            strcpy(suffix,a) ;

            for (int j=0 ; j<100 ; j++)
            {
                node* currentChild =  root->children[j] ;
                if (currentChild == NULL)
                {
                    root->children[j] = new node(suffix , i) ;
                    break ;
                }
                else if (suffix[0] == currentChild->label[0])
                {
                    int q=0 ;
                    while ( currentChild->label[q]!= '\0' && suffix[q] == currentChild->label[q] )
                    {
//                        cout << "#" << suffix[q] << "\n" ;
                        q++ ;
                    }
                    char commonLabel[100] ;
//                    cout << "1-common: "<<currentChild->label << " " << q<< endl;
                    strncpy(commonLabel, currentChild->label, q) ;
                    commonLabel[q] = '\0' ;
//                    cout << "common: "<<commonLabel << endl;
                    node *x = new node (commonLabel , -1);

                    x->children[0] = currentChild ;
                    x->children[1] = new node (suffix+q , i) ;
                    root->children[j] = x ;
                    char aa[100] ;
                    strcpy(aa ,currentChild->label) ;
                    char *bb = aa+q ;
                    strcpy( currentChild->label , bb ) ;
                    break;
                }
            }
        }

    }
    void printAll ()
    {
        print(root , "") ;
    }

};

int main()
{
    suffixTree t("abbc") ;
    for (int i=0 ; i<4 ; i++)
    {
        if (t.root->children[i] != NULL)
            cout << t.root->children[i]->index << " " << t.root->children[i]->label << endl;
        else
            cout << "null\n";
    }
    cout << t.root->children[1]->children[0]->index << " " << t.root->children[1]->children[0]->label << endl;
    cout << t.root->children[1]->children[1]->index << " " << t.root->children[1]->children[1]->label << endl;
//    cout << t.root->children[1]->children[1]->label << endl;
    cout << "all \n" ;
    t.printAll();

    return 0;
}
