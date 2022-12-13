#include <iostream>
#include <cstring>

using namespace std;

struct node
{
    int index ;
    int start,len;
    node **children ;
    node(){
        index = -1 ;
        children = new node*[100] ;
        for (int i=0 ; i<100 ; i++)
            children[i] = NULL ;
    }
    node(int start,int len,int id)
    {
        this->start=start;
        this->len=len;
        index = id ;
        children = new node*[100] ;
        for (int i=0 ; i<100 ; i++) children[i] = NULL ;

    }
};
class suffixTree{
public :
    char * txt;
    node *root ;
    void print(node* n){
        if (n->index  != -1){
            return;
        }
        for (int i=0 ; i<100 ; i++){
            node* currentChild = n->children[i] ;
            if (currentChild == NULL){
                return ;
            }
            else{
                for(int i=0;i<currentChild->len;i++){
                    cout<<txt[(currentChild->start)+i];
                }
                print(currentChild) ;
            }

        }

    }
public:
    suffixTree(char word[])
    {
        // txt=new char[sizeof(word)];
        strcpy(txt,word);
        //initializing root node
        root = new node(-1,-1,-1) ;
        // adding special char
        //strcat(word, "$") ;

        int n = strlen(word) ;


        for (int i=0 ; i<n ; i++)
        {
            // getting suffix substring from i
            char *a = word + i ;
            char *suffix=new char[sizeof(word)-i];
            strcpy(suffix,a) ;
            //cout<<suffix;

            for (int j=0 ; j<100 ; j++)
            {
                node* currentChild =  root->children[j] ;
                if (currentChild == NULL){
                    root->children[j] = new node(i,sizeof(suffix)-i, i) ;
                    break ;
                }
                else if (suffix[0] == txt[currentChild->start])
                {
                    int q=0 ;
                    while ( currentChild->len>q && suffix[q] == txt[currentChild->start+q]){
//                        cout << "#" << suffix[q] << "\n" ;
                        q++ ;
                    }
                    // char commonLabel[100] ;
//                    cout << "1-common: "<<currentChild->label << " " << q<< endl;
                    // strncpy(commonLabel, currentChild->label, q) ;
                    // commonLabel[q] = '\0' ;
//                    cout << "common: "<<commonLabel << endl;

                    node *x = new node (currentChild->start , q , -1);

                    //modify the current child
                    currentChild->start+=q;
                    currentChild->len-=q;

                    x->children[0] = currentChild ;
                    x->children[1] = new node (i+q, sizeof(suffix)-i-q, i) ;
                    root->children[j] = x ;
                    break;
                }
            }
        }

    }
    void printAll ()
    {
        print(root) ;
    }

};

int main()
{
    suffixTree t("abbc") ;
    /*for (int i=0 ; i<4 ; i++)
    {
        if (t.root->children[i] != NULL)
            cout << t.root->children[i]->index << " " << t.root->children[i]->label << endl;
        else
            cout << "null\n";
    }
    /*cout << t.root->children[1]->children[0]->index << " " << t.root->children[1]->children[0]->label << endl;
    cout << t.root->children[1]->children[1]->index << " " << t.root->children[1]->children[1]->label << endl;
//    cout << t.root->children[1]->children[1]->label << endl;
    cout << "all \n" ;*/
    t.printAll();

    return 0;
}
