#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef struct Data {
    char name[20];
} Data;


typedef struct Node {
    struct Data data;
    struct Node * left;
    struct Node * right;
} Node;


typedef struct Structure {
    struct Node * root;
    unsigned int count;
} Structure;






bool init(Structure * structure){
    if (structure == NULL){
        return false;
    }
    
    structure->root = NULL;
    structure->count = 0;


    return true;
}








typedef struct DepthAware {
    unsigned int depth;
} DepthAware;


//  struct student arr_student[MAX];




struct DepthAware nodes[100];


int indexa = -1;


bool insert(Structure * const structure, Data insertData){
   
    if (structure == NULL){
        return false;
    }
    
    if (structure->count == 0){
        printf("INSERTING INTO ROOT \n");
        Node * node = malloc(sizeof(Node));
        if (node == NULL){
            return false;
            
        }
        // 1 ---------------------------------------- initializing first element
        //strcpy(node->name, insertNode.name);
        node->data = insertData;
        node->left = NULL;
        node->right = NULL;
        structure->root = node;
        structure->count++;
        return true;
    }
    
    
    printf("HERE \n");
    
    
    if (structure->count > 0){
        Node * next = structure->root;
        Node * last = NULL;
        
        while (next != NULL){
           /* bool isEqual = next->val == insertValue;
            bool isLess = next->val < insertValue;
            bool isLarger = next->val > insertValue;
            
            */
            
            int compare = strcmp(next->data.name, insertData.name);
           
            bool isEqual = compare == 0;
            bool isLess = compare < 0;
            bool isLarger = compare > 0;
            
            if (isEqual){
                last = next;
                next = next->right;
               // return false;
            }
            
          //  printf("BELOW COND \n");
            
            if (isLess){
              //  printf("RIGHT \n");
                last = next;
                next = next->right;
            }
            
            if (isLarger){
              // printf("LEFT \n");
                last = next;
                next = next->left;
            }
        }
        
        Node * node = malloc(sizeof(Node));
        node->data = insertData;
        node->left = NULL;
        node->right = NULL;
        
        int comparea = strcmp(last->data.name, insertData.name); // FUCKING BUG HERE !!!
        printf("COMPARING BUG %s  NEXT %s", node->data.name, insertData.name);
        printf("COMPARE IS %d (has to be 0 ><) \n", comparea);
        int isLarger = comparea > 0;
        
        if (isLarger){
            printf(" \n INSERTING INTO LEFT \n");
            last->left = node;
        } else {
            printf(" \n INSERTING INTO RIGHT \n");
            last->right = node;
        }
        
        indexa += 1;
        structure->count++;
        return true;
    }
    
    return false;
}




void traverse(struct Node* node)
{
    if (node == NULL){
        printf("---------------------- \n");
        return;
    }
  
    traverse(node->left);
    printf("NODE IS %s \n", node->data.name);
    traverse(node->right);
}










int getLevelCount(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int leftMaxLevel = 1 + getLevelCount(node->left);
    int rightMaxLevel = 1 + getLevelCount(node->right);
    if (leftMaxLevel > rightMaxLevel)
    {
        return leftMaxLevel;
    }
    else
    {
        return rightMaxLevel;
    }
}




void printLevel(Node *node, int level)
{
    if (node != NULL && level == 0)
    {
        printf("%s\n", node->data.name);
    }
    else if (node != NULL)
    {
        printf("----FLOOR---- \n");
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}




void printElements(Node * node)
{
    int i;
    int levelCount = getLevelCount(node);
    for (i = 0; i < levelCount; i++)
    {
        printLevel(node, i);
    }
}








int TREE_GET_OCCURANCES(Structure * const root, /*Node data*/ Data data) {
    
    if (root == NULL){
        return -1; // can I do that?
    }
    
    Node * next = root->root;
    Node * dataa = NULL;
    
    int occurances = 0;
    int cmp;
    
    
    while (next != NULL){
        
        int cmp = strcmp(&next->data.name, data.name);
        
        if (cmp < 0){
        next = next->right;
        } else if (cmp > 0){
            next = next->left;
        } else {
            occurances++;
           
            next = next->right; // without this an infinite cycle would be here
        }
    }
    
    
    return occurances;
}






//queue will be used to keep track of nodes of tree level-wise
struct Node* queue[100];
int rear = 0,front = -1, size = 0;


unsigned int nicest[10];
int idxaa = -1;


//Adds new node to the queue
void enqueue(struct Node* temp) {
    queue[rear++]=temp;
    size++;
}
//Deletes a node from the queue
struct Node* dequeue() {
    size--;
    return queue[++front];
}
   
//findMaximumWidth() will find out the maximum width of the given binary tree
int findMaximumWidth(Node * root) {
    int maxWidth = 0;
      
    //Variable nodesInLevel keep tracks of number of nodes in each level
    int nodesInLevel = 0;
      
    //Check if root is null, then width will be 0
    if(root == NULL) {
        printf("Tree is empty\n");
        return 0;
    } else {
        //Add root node to queue as it represents the first level
        enqueue(root);
          
        while(size != 0) {
            //Variable nodesInLevel will hold the size of queue i.e. number of elements in queue
            nodesInLevel = size;
            idxaa += 1;
            printf("NODES %d ", nodesInLevel);
            nicest[idxaa] = nodesInLevel;
            
            //maxWidth will hold maximum width.
            //If nodesInLevel is greater than maxWidth then, maxWidth will hold the value of nodesInLevel
            maxWidth = (maxWidth < nodesInLevel) ? nodesInLevel : maxWidth;
   
            //If variable nodesInLevel contains more than one node
            //then, for each node, we'll add left and right child of the node to the queue
            while(nodesInLevel > 0) {
                struct Node *current = dequeue();
                if(current->left != NULL){
                    enqueue(current->left);
                }
                  
                if(current->right != NULL) {
                    enqueue(current->right);
                }
                nodesInLevel--;
            }
        }
    return maxWidth;
    }
}




int main(int argc, const char * argv[]) {
    
    Structure structure;
    init(&structure);
    
    Data first = {.name = "A"};
    insert(&structure, first);
    
    Data second = {.name = "C"};
    insert(&structure, second);
    
    Data seventh = {.name = "B"};
    insert(&structure, seventh);
    
    Data seventha = {.name = "M"};
    insert(&structure, seventha);
    
    Data fourth = {.name = "W"};
    insert(&structure, fourth);
    
    traverse(structure.root);
    
    int maxWidth = findMaximumWidth(structure.root);
    printf("MAX BINARY TREE WIDTH IS %d \n", maxWidth);
    
    int n=sizeof(nicest)/sizeof(nicest[0]);


    for(int i=0;i<n;i++) {
        if (nicest[i] == maxWidth){
            printf("WIDEST FLOOR WITH LENGTH %d IS AT INDEX %d \n ", nicest[i], i);
        }
       }
    
    Node * root = structure.root;
    
    printf("A IS %s \n", root->data.name);
    printf("C IS %s \n", root->right->data.name);
    printf("M IS %s \n", root->right->right->data.name);
    printf("B IS %s \n", root->right->left->data.name);
    printf("W IS %s \n", root->right->right->right->data.name);
    
    int occurs = TREE_GET_OCCURANCES(&structure, second);
    printf(" \n N.O.: %d", occurs);
    
    return 0;
}
