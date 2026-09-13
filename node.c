#include "node.h"
#include <stdlib.h>

int Length(struct Node* head){
  struct Node* current;
  int count;

  while(current != NULL){
    count++;
    current = current->next;
  }

  return count;
}

struct Node* BuildOneTwoThree(){
  struct Node* head = malloc(sizeof(struct Node));
  head->data = 1;

  head->next = malloc(sizeof(struct Node));
  head->next->data = 2;

  head->next->next = malloc(sizeof(struct Node));
  head->next->next->data = 3;

  return head;
}

void Push(struct Node** headref, int data){

  struct Node* NewNode = malloc(sizeof(struct Node));
  NewNode->data = data;
  NewNode->next = *headref;

  *headref = NewNode;
}


int main(){}
