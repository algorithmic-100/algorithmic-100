#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>


typedef struct Data {
    char key[20];
    uint64_t identificationNumber;

} Data;


typedef struct Node  {
    Data * value;
    struct Node * next;
} Node;


typedef struct Structure {
    Node ** buckets;
    size_t size;
    size_t count;
} Structure;




unsigned int GetIndex(Structure * table, char key[20]) {
    unsigned int len = strlen(key);
    return len % table->size;
}


bool init(Structure * structure, size_t size) {
    if(structure == 0 || size == 0) {
        return false;
    }


    structure->buckets = malloc(sizeof (Node*));
    structure->size = size;
    structure->count = 0;
    if(structure->buckets == NULL) {
        return false;
    }


    for (unsigned int i = 0; i < size;i++) {
        structure->buckets[i] = NULL;
    }


    return true;
}












bool insert(Structure * structure, char key[20], Data * value) {
    if(structure == NULL || value == NULL) {
        return false;
    }
    
    unsigned int synonymCount = 0;
    unsigned int hash = GetIndex(structure, key);
    Node * hashNode = structure->buckets[hash];
    
    while(hashNode != NULL) {
        hashNode = hashNode->next;
    }
    
    if(hashNode == NULL) {
        Node * newNode = malloc(sizeof (Node));
        newNode->value = value;
        newNode->next = structure->buckets[hash];
        structure->buckets[hash] = newNode;
    }


    
    Node * helpNode = structure->buckets[hash];
    while(helpNode != NULL) {
        synonymCount++;
        helpNode = helpNode->next;
    }


    if(synonymCount == 2) {
        printf("Realocation \n");
    }




    return true;
}


void printData(Structure * structure) {
    if(structure == NULL) {
        return;
    }
    for (unsigned int i = 0;i<structure->size;i++) {
        Node * bucket = structure->buckets[i];
        while(bucket != NULL) {
            printf("idx %d || ", i);
            printf("%d nid: %lld |",i,bucket->value->identificationNumber);
            printf("\n");
            bucket = bucket->next;
        }
    }
}




void showNodes(char key[20], Node * node) {
    if(node == NULL || key == NULL) {
        return;
    }


    while (node != NULL) {
        unsigned int len = strlen(key);
        printf("Hash: %d | ID: %lld \n", len, node->value->identificationNumber);
        node = node->next;
    }


    return;
}














int main(int argc, const char * argv[]) {
    Structure table;
    size_t size = 2;
    init(&table,size);
    Data corosion = {.key = "Corosion", .identificationNumber = 0};
    Data destruction = {.key = "Destruction", .identificationNumber = 1};
    insert(&table, corosion.key,&corosion);
    insert(&table, destruction.key,&destruction);
    printData(&table);
   
    Data severity = {.key = "Severity", .identificationNumber = 2};
    Data noTest = {.key = "NoTest", .identificationNumber = 3};
    insert(&table, severity.key,&severity);
    insert(&table, noTest.key, &noTest);
    printData(&table);
    showNodes(destruction.key, table.buckets[0]);
    return 0;
}


typedef struct Data {
    char key[20];
    uint64_t identificationNumber;
   // uint16_t timeout;
  //  bool retry;
   // char command[255];
} Data;
