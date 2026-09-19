#include "node.h"
#include <stdlib.h>
#include <assert.h>

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

int Count(struct Node* head, int searchFor){

  struct Node* current  = head;
  int count = 0;

  while(current != NULL){
    if(current->data == searchFor)
        count++;
    current = current->next;
  }

  return count;
}

int GetNth(struct Node* head, int index){
  
  struct Node* current = head;

  while(current != NULL){
    if(!index)
        return current->data;
        
    current = current->next;
    index--;
  }
  
  assert(0);
}

void DeleteList(struct Node** headRef){

  struct Node* current = *headRef;
  *headRef = NULL;
  headRef = &current;

  while(current != NULL){
    headref = &(current->next);
    free(current);
    current = *headref;
  }

}

int Pop(struct Node** headRef){

  assert(*headRef != NULL);
  struct Node* current = *headRef;
  *headRef = current->next;

  free(current);
}

void InsertNth(struct Node** headRef, int index, int data){

  struct Node** current = headRef;
  
  while(*current != NULL && index){
    index--;
    current = &((*current)->next);
  }

  assert(*current != NULL);
  Push(current, data);
}

void SortedInsert(struct Node** headRef, struct Node* newNode){
  struct Node** current = headRef;

  while(*current != NULL){
    if((*current)->data >= newNode->data)
        break;
    current = &((*current)->next);
  }

  struct Node** currentTemp = current;
  *current = newNode;
  newNode->next = *currentTemp;
}

void InsertSort(struct Node** headRef){
  struct Node* current = *headRef;
  struct Node* new = NULL;
  struct Node* next;

  while(current != NULL){
    next = current->next;    
    SortedInsert(&new, current);
    current = next;
  }

  *headRef = new;

  return;
}

void Append(struct Node** aRef, struct Node** bRef){
  struct Node** current = aRef;
  while(*current != NULL)
      current = &((*current)->next);

  *current = *bRef;
  *bRef = NULL;
}


void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef){

  int len = Length(source);

  if(len <= 0){
    *frontRef = NULL;
    *backRef = NULL;
    return;
  }

  int frontLen = (len - 1) / 2;

  struct Node* current = source;

  while(frontLen--)
    current = current->next;
  
  *backRef = current->next;
  current->next = NULL;
  *frontRef = source;
}

//el nick decia asumir q esta ordenada

void RemoveDuplicates(struct Node* head){

  struct Node* current = head;
  struct Node* next = head;
  struct Node* victim = head;

  while(current != NULL){
    next = current->next;  
    while(next != NULL && next->data == current->data){
      victim = next;
      next = next->next;
      free(victim);  
    }

    current->next = next;
    current = next;
  }

  return;
}

void MoveNode(struct Node** destRef, struct Node** sourceRef){

  struct Node* current = *destRef;
  struct Node* oldSource = *sourceRef;

  *sourceRef = (*sourceRef)->next;
  *destRef = oldSource;
  (*destRef)->next = current;

  return;
}


void AlternatingSplit(struct Node* source, struct Node** aRef, struct Node** bRef){

  int len = Length(source);
  
  assert(len > 0);

  struct Node dummyA = {0,NULL};
  struct Node dummyB = {0,NULL};
  struct Node* current = source;

  *aRef = &dummyA;
  *bRef = &dummyB;

  int index = 0;

  while(current != NULL){
    if(index % 2 == 0){
      (*aRef)->next = current;
      *aRef = current;
    }

    else{
      (*bRef)->next = current;
      *bRef = current;
    }

    current = current->next;
    index++;
  }

  (*bRef)->next = NULL;
  (*aRef)->next = NULL;

  *aRef = dummyA.next;
  *bRef = dummyB.next;

  return;
}

struct Node* ShuffleMerge(struct Node* a, struct Node* b){
  struct Node dummy = {0, NULL};
  struct Node* s = &dummy;
  
  struct Node* currentA = a;
  struct Node* currentB = b;

  while(currentA && currentB){
    s->next = currentA;
    s = s->next;

    s->next = currentB;
    s = s->next;

    currentA = currentA->next;
    currentB = currentB->next;
  }

  if(currentA)
    s->next = currentA;
  if(currentB)
    s->next = currentB;

  return dummy.next;

  //dummy esta rotisimo para estas cosas, saalio la idea bastante rapido a comparacion de hacer malabares para no salirse del rango
}
struct Node* SortedMerge(struct Node* a, struct Node* b){

  struct Node dummy = {0, NULL};
  struct Node* s = &dummy;

  struct Node* currentA = a;
  struct Node* currentB = b;

  while(currentA && currentB){
    if(currentA->data < currentB->data){
      s->next = currentA;
      s = s->next;
      currentA = currentA->next;
    }
    else{
      s->next = currentB;
      s = s->next;
      currentB = currentB->next;
    }
  }
// no hace falta el !current del otro porq si o si solo queda uno q no sea null
  if(currentA)
    s->next = currentA;

  if(currentB)
    s->next = currentB;
  

  return dummy.next;
}

void MergeSort(struct Node** headRef){
  
  // nada q ordenar si esta vacio o si tiene solo un elemento, abusando de como evalua c las condiciones(nivel hacker)

  if(*headRef == NULL || (*headRef)->next == NULL)
      return;

  struct Node* left,right;
  FrontBackSplit(*headref, &left, &right);

  MergeSort(&left);
  MergeSort(&right);

  *headRef = SortedMerge(left, right);  
}
struct Node* SortedIntersect(struct Node* a, struct Node* b){}
void Reverse(struct Node** headRef){}
void RecursiveReverse(struct Node** headRef){}

int main(){}
