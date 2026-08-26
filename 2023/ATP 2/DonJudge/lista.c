#include <stdio.h>
#include <stdlib.h>

typedef struct person{
  int age;
  int time;
  struct person *next;
} Queue;

void enqueue(Queue **, Queue **, int, int);
void prioritize(Queue **, Queue **, int, int);
void dequeue(Queue **, Queue **);
void printQueue(Queue *);

int main(void) {
  int i, N, I, T, served=3, age, total_time, inserted=1;
  Queue *tempHead = NULL, *tempTail = NULL, *head = NULL, *tail = NULL;

  scanf("%d", &N);

  for(i=0; i<N; i++){
    scanf("%d %d", &I, &T);
    enqueue(&tempHead, &tempTail, I, T);
  }

  age = tempHead->age;
  total_time = tempHead->time;

  prioritize(&head, &tail, tempHead->age, tempHead->time);
  dequeue(&tempHead, &tempTail);

  while(!(tempHead == NULL && head == NULL)){
    if(served >= 3){
      served = 0;
      if(head == NULL){
        prioritize(&head, &tail, tempHead->age, tempHead->time);
        total_time = tempHead->time;
        dequeue(&tempHead, &tempTail);
        inserted = 1;
      }
      age = head->age;
      dequeue(&head, &tail);
    }
    while(tempHead != NULL && total_time >= tempHead->time){
      prioritize(&head, &tail, tempHead->age, tempHead->time);
      dequeue(&tempHead, &tempTail);
      inserted = 1;
    }
    if(inserted){
      puts("%d ", age);
      printQueue(head);
    }
    inserted = 0;
    total_time++;
    served++;
  }
  return 0;
}

void enqueue(Queue **start, Queue **end, int id, int t){
  Queue *newNode = malloc(sizeof(Queue)), *temp, *before;
  newNode->age = id;
  newNode->time = t;
  if(*start == NULL){
    *start = newNode;
    *end = newNode;
    (*start)->next  = NULL;
    return;
  }
  if(newNode->time < (*start)->time || (newNode->time == (*start)->time && newNode->age > 59 && newNode->age > (*start)->age)){
    newNode->next = *start;
    *start = newNode;
    return;
  }
  if(newNode->time > (*end)->time){
    newNode->next = NULL;
    (*end)->next = newNode;
    *end = newNode;
    return;
  }
  
  temp = (*start)->next;
  before = *start;
  
  while(temp != NULL){
    if(newNode->time < temp->time || (newNode->time == temp->time && newNode->age > 59 && newNode->age > temp->age)){
      before->next = newNode;
      newNode->next = temp;
      return;
    }
    before = temp;
    temp = temp->next;
  }
   if(newNode->time == (*start)->time && ((*start)->next == NULL || (*start)->next->time != newNode->time)){
    newNode->next = (*start)->next;
    (*start)->next = newNode;
    return;
  }

  temp = (*start)->next;
  
  while(temp != NULL){
    if(newNode->time == temp->time && (temp->next == NULL || temp->next->time != newNode->time)){
      newNode->next = temp->next;
      temp->next = newNode;
      if(newNode->next == NULL) 
        *end = newNode;
      return;
    }
    temp = temp->next;
  }
}

void prioritize(Queue **start, Queue **end, int id, int t){
  Queue *newNode = malloc(sizeof(Queue)), *temp, *before;
  newNode->age = id;
  newNode->time = t;
  if(*start == NULL){
    *start = newNode;
    *end = newNode;
    newNode->next = NULL;
    return;
  }
  if(newNode->age > 59){
    if(newNode->age > (*start)->age){
      newNode->next = *start;
      *start = newNode;
      return;
    }
    temp = (*start)->next;
    before = (*start);
    while(temp != NULL){
      if(newNode->age > temp->age){
        before->next = newNode;
        newNode->next = temp;
        return;
      }
      before = temp;
      temp = temp->next;
    }
  }
  (*end)->next = newNode;
  newNode->next = NULL;
  *end = newNode;
}

void dequeue(Queue **start, Queue **end){
  if(*start == NULL) 
    return;
  if((*start)->next == NULL){
    free(*start);
    *end = NULL;
    *start = NULL;
    return;
  }
  if((*start)->next == *end){
    free(*start);
    *start = *end;
    return;
  }
  Queue *temp = *start;
  *start = (*start)->next;
  free(temp);
}

void printQueue(Queue *head){
  while(head != NULL){
    puts("%d ", head->age);
    head = head->next;
  }
  puts("\n");
}
