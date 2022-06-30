#include <iostream>
using namespace std;
class SuffixTrieNode;
class LinkedListNode{
public:
    char character;
    SuffixTrieNode * nextchild;
    LinkedListNode * nxtnode;
};
class LinkedList{
public:
    LinkedListNode* head;
    LinkedListNode* tail;
    LinkedList(){
        head=NULL;
        tail=NULL;
    }
    void printList();
    void insertchr(char c);
    LinkedListNode* ifContain(char character);
};
class SuffixTrieNode{
public:
    LinkedList linkedList;
    int index=-1;
    SuffixTrieNode(){
        linkedList.head=NULL;
    }
};
class SuffixTrie{
public:
    char* input;
    int size;
    SuffixTrieNode * root=new SuffixTrieNode();
    SuffixTrie(char*);// to construct the Suffix trie
    void Search(char* a);
    int getSize(char *);
};
int SuffixTrie::getSize(char * input) {
    int size=0;
    for(int i=0;input[i]!=NULL;i++){
        size++;
    }
    this->size=size;
    return size;
}
SuffixTrie::SuffixTrie(char* data)
{
    getSize(data);
    input = new char[size];
    input = data;
    //traverse through the char array
    for (int i = 0; i < size; i++)
    {
        if (root->linkedList.head == NULL)
        {
            // inset first elem
            root->linkedList.insertchr(input[i]);
            root->linkedList.head->nextchild = new SuffixTrieNode();
        }
        else
        {
                LinkedListNode *head1 = root->linkedList.ifContain(input[i - 1]);
                // to finish constructing the hole char array
                for (int j = i; j < size; j++)
                {
                    // to insert different characters in the root
                    if (root->linkedList.ifContain(input[j])==NULL)
                    {
                         root->linkedList.insertchr(input[j]);
                         LinkedListNode * node =root->linkedList.ifContain(input[j]);
                         node->nextchild=new SuffixTrieNode();
                         // condition to assign index to the $ in the root
                        if(input[j]=='$')
                        {
                             node->nextchild->index=size-1;
                        }
                    }
                    // to not insert the same character in the same path
                    if (head1->nextchild->linkedList.ifContain(input[j])==NULL)
                    {
                        head1->nextchild->linkedList.insertchr(input[j]);
                        head1 = head1->nextchild->linkedList.ifContain(input[j]);
                        head1->nextchild = new SuffixTrieNode();
                    }
                    else
                    {
                        head1 = head1->nextchild->linkedList.ifContain(input[j]);
                    }
                }
                // to assign suitable index at the end of the path
                head1->nextchild->index=i-1;
        }
    }
}
void SuffixTrie::Search(char* sub){
    int SuffixSize = getSize(sub);
    size = getSize(input);
    int *out= new int[size];// array to hold the result
    int position=0;

    // pointer to hold the start of the sub
    LinkedListNode *head1 = root->linkedList.head;
    int cnt=0;// to have the first index of the sun in the hole char array
    //to get the start index of the sub
    while (head1->nxtnode!=NULL)
    {
        if (head1->character != sub[0])
        {
            head1=head1->nxtnode;
            cnt++;
        }
        else
        {
            break;
        }
    }
    if (head1!=NULL)
    {
        // to search for the sub in the suffix trie
        for (int i = 1; i < SuffixSize; i++)
        {
             while(head1->nextchild->linkedList.ifContain(sub[i])!=NULL)
             {
                 head1=head1->nextchild->linkedList.ifContain(sub[i]);
             }
        }
        // to have the same position of head1
         LinkedListNode *head2=head1;
        // to print the correct indices
        for (int j = cnt+SuffixSize; j <size ; j++)
        {
            int k=j;
            while(k<size)
            {
                char c= input[k];
                if (head2->nextchild->linkedList.ifContain(c)!=NULL)
                {
                    head2 = head2->nextchild->linkedList.ifContain(input[k]);
                }
                k++;
            }
            // to convert int to char
            out[position]=head2->nextchild->index;
            position++;
            head2=head1;// return head2 to the same position of head1
        }
        for(int i=0;i<size;i++)
        {
            int j;
            for(j=0;j<i;j++)
                if (out[i]==out[j])
                    break;
            if (i==j &&out[i]>=0)
            {
                cout<<out[i]<<" ";
            }
        }
        cout<<endl;
    }
}
void LinkedList:: printList(){
    LinkedListNode * current = head;
    while (current!= NULL)
    {
        cout << current->character<<"  ";
        current = current->nxtnode;
    }
    cout <<endl;
}
LinkedListNode* LinkedList:: ifContain(char character)
{
    if(head==NULL)
    {
        return false;
    }
    LinkedListNode*start=head;
    LinkedListNode*end=tail;
    for(;;start=start->nxtnode)
    {
        if(character==start->character)
            return start;
        if(start==end)
            break;
    }
    return NULL;
}
void  LinkedList:: insertchr(char c)
{
    if(head==NULL)
    {
        head=new LinkedListNode();
        head->character=c;
        head->nxtnode=NULL;
        tail=head;
        tail->nxtnode=NULL;
    }
    else
    {
        LinkedListNode*newNode=new LinkedListNode();
        newNode->character=c;
        tail->nxtnode=newNode;
        newNode->nxtnode=NULL;
        tail=newNode;
    }
}
int main()
{
    // Construct a suffix trie containing all suffixes of "bananabanaba$"
    //                 0123456789012
    SuffixTrie t("bananabanaba$");
    t.Search("ana"); // Prints: 1 3 7
    t.Search("naba"); // Prints: 4 8
}
