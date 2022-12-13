#include <iostream>
#include <cstring>

using namespace std;

struct node
{
    int index ;
    //char label[26] ;
    int begn;
    int length;
    node **children ;
    node()
    {
        index = -1 ;
        begn=-1;
        length=0;
        children = new node*[26] ;
        for (int i=0 ; i<26 ; i++)
            children[i] = NULL ;
    }
    node(char sub[] , int id)
    {
        //strcpy(label, sub) ;
        index = id ;
        begn=id;
        length=strlen(sub);
        children = new node*[26] ;
        for (int i=0 ; i<26 ; i++)
            children[i] = NULL ;

    }
};
class suffixTree
{
public :
    node *root ;
    /*void print(node* n , const char a[26])
    {
        if (n->index  != -1)
        {
            cout << a << endl;
            return;
        }
        for (int i=0 ; i<26 ; i++)
        {
            node* currentChild = n->children[i] ;
            if (currentChild == NULL)
                break ;
            else
            {
                char x[26] ;
                strcpy(x,a) ;
                strcat(x,currentChild->label) ;
                print(currentChild , x) ;
            }

        }

    }*/
public:
    suffixTree(char word[])
    {
        //initializing root node
        root = new node() ;
        // adding special char
        strcat(word, "$") ;

        int n = strlen(word) ;

        for (int i=0 ; i<n ; i++)
        {
            // getting suffix substring from i
            char *a = word + i ;
            char suffix[26];
            strcpy(suffix,a) ;

            for (int j=0 ; j<26 ; j++)
            {
                char label[26];
                node* currentChild =  root->children[j] ;
                if (currentChild == NULL)
                {
                    root->children[j] = new node(suffix , i) ;
                    break ;
                }
                strncpy(label,word+currentChild->begn,currentChild->length);
                if (suffix[0] == label[0])
                {
                    int q=0 ;
                    while ( label[q]!= '\0' && suffix[q] ==label[q] )
                    {
//                        cout << "#" << suffix[q] << "\n" ;
                        q++ ;
                    }
                    char commonLabel[26] ;
//                    cout << "1-common: "<<currentChild->label << " " << q<< endl;
                    strncpy(commonLabel, label, q) ;
                    commonLabel[q] = '\0' ;
//                    cout << "common: "<<commonLabel << endl;
                    node *x = new node (commonLabel , -1);
                    x->begn=currentChild->begn;
                    x->length=q;

                    x->children[0] = currentChild ;
                    x->children[1] = new node (suffix+q , i+q) ;
                    root->children[j] = x ;
                    currentChild->begn=currentChild->begn+q;
                    currentChild->length-=q;
                    /*char aa[26] ;
                    strcpy(aa ,currentChild->label) ;
                    char *bb = aa+q ;
                    strcpy( currentChild->label , bb ) ;*/
                    break;
                }
            }
        }

    }
   /* void printAll ()
    {
        print(root , "") ;
    }*/

};

int main()
{
    char a[]="banana";
    suffixTree t(a) ;
    for (int i=0 ; i<4 ; i++)
    {
        if (t.root->children[i] != NULL)
            cout << t.root->children[i]->index << " "<<t.root->children[i]->begn<<" "<<t.root->children[i]->length << endl;
        else
            cout << "null\n";
    }
    cout << t.root->children[2]->children[0]->index <<" " << t.root->children[2]->children[0]->begn<< " "<< t.root->children[2]->children[0]->length<< endl;
    cout << t.root->children[2]->children[1]->index <<" " << t.root->children[2]->children[1]->begn<< " "<< t.root->children[2]->children[1]->length<< endl;
//    cout << t.root->children[1]->children[1]->label << endl;
    cout << "all \n" ;
   // t.printAll();

    return 0;
}
