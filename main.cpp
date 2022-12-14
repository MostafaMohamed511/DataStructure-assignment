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
        children = new node*[53] ;
        for (int i=0 ; i<53 ; i++)
            children[i] = NULL ;
    }
    node(int start,int len,int id)
    {
        this->start=start;
        this->len=len;
        index = id ;
        children = new node*[53] ;
        for (int i=0 ; i<53 ; i++) children[i] = NULL ;

    }
};
class suffixTree{
public :
    char * txt;
    node *root ;


    void bc(node* n,string word){
        if (n->index  != -1){
            cout<<n->index<<" ";
            return;
        }
        int idx=word[0]-'a';    if(word[0]=='$')  idx=52;
        if(n->children[idx]!=NULL){
            int i=1;
            node* currentChild = n->children[idx] ;
            while(txt[currentChild->start+i]==word[i] && i<currentChild->len){
                i++;
            }
            if(i<currentChild->len && i<word.size()){
                cout<<"Not Found1 \n";
            }
            else{
                if(word.size()>i){
                    bc(currentChild,word.substr(i));
                }
                else {
                    print(currentChild);
                }
            }
        }
        else 
        {
            cout<<"Not Found \n";
        }

    }


    void print(node* n){
        if (n->index  != -1){
            cout<<n->index<<" ";
            return;
        }
        for (int i=0 ; i<53 ; i++){
            node* currentChild = n->children[i] ;
            if (currentChild != NULL){
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
        root = new node(0,0,-1) ;

        int n = strlen(word) ;

        for (int i=0 ; i<n ; i++)
        {
            // getting suffix substring from i
            char *a = word + i ;
            char *suffix=new char[sizeof(word)-i];
            strcpy(suffix,a) ;
            int idx=suffix[0]-'a';
            if(suffix[0]=='$')  idx=52;
            node* currentChild =  root->children[idx] ;
            if (currentChild == NULL){
                root->children[idx] = new node(i,sizeof(suffix)-i-1, i) ;

            }
            else if (suffix[0] == txt[currentChild->start])
            {
                int q=0 ;
                while ( currentChild->len>q && suffix[q] == txt[currentChild->start+q]){
                    q++;
                }

                node *x = new node (currentChild->start , q , -1);

                //modify the current child
                currentChild->start+=q;
                currentChild->len-=q;

                int y = txt[currentChild->start]=='$'?52:txt[currentChild->start]-'a';
                x->children[y] = currentChild ;
                y=txt[i+q]=='$'?52:txt[i+q]-'a';
                x->children[y] = new node (i+q, sizeof(suffix)-i-q-1, i) ;
                root->children[idx] = x ;
            }

        }

    }
    void search(char word[]){
        int idx=word[0]-'a';
        if(root->children[idx]!=NULL){
            bc(root,word);
        }
        else {
            cout<<"Not Found \n";
        }
    }
    void printAll (){
        print(root) ;
    }

};

int main()
{
    suffixTree t("banana$") ;
    
    //t.search("banana");
    //t.search("banana$");
    //t.search("anana");
    //t.search("nan");
    // t.search("an");
    // t.search("na");
    //t.printAll();

    return 0;
}
