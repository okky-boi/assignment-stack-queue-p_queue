#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Node
{
  int value;
  Node *next, *prev; // next ke depan, prev ke belakang
} *front, *rear;

Node *createNode(int value)
{
  Node *newRear = (Node *)malloc(sizeof(Node));
  newRear->value = value;
  newRear->next = newRear->prev = NULL;
  return newRear;
}

void pushRear(int value)
{
  Node *newRear = createNode(value);

  if (!front)
  { // if linked list is empty
    front = rear = newRear;
  }
  else
  {                      // if there's more than 1 node
    rear->prev = newRear; // top will point to the new node
    newRear->next = rear; // new node will point to the current top
    rear = newRear;       // the new top will be the newly created node
  }
}

void pushQueue(int res)
{
  Node *newNode = createNode(res);

  if (!front || rear->value < res)
  { // if linked list is empty
    pushRear(res);
  }
  else if (front->value > res)
  {
    front->next = newNode;
    newNode->prev = front;
    front = newNode;
  }
  else
  {
    Node *currentNode = rear->next;
    while (currentNode->value > res){
        currentNode = currentNode->next;
    } 
    newNode->next = currentNode;
    currentNode->prev->next = newNode;
    newNode->prev = currentNode->prev;
    currentNode->prev = newNode;
  }
}

void removeFront()
{
  if (!front)
  { // if linked is empty
    return;
  }
  else if (!front->prev) // if only 1 node, top has no node below it
  {
    free(front);  // free allocated memory
    front = NULL; // set the value to NULL
  }
  else // if there are more than 1 node,
  {
    Node *newFront = front->prev;        // the new top candidate will be below the current top
    front->prev = newFront->next = NULL; // isolate the current top
    free(front);                         // free the allocated memory
    front = newFront;                    // the new top will replace the deleted top
  }
}

void readNode(Node *currentNode)
{
  printf("Value: %d\n", currentNode->value);
  printf("Alamat node sebelumnya: %p\n", currentNode->prev);
  printf("Alamat node sekarang: %p\n", currentNode);
  printf("Alamat node setelahnya: %p\n", currentNode->next);
}

void printQueue()
{
  for (Node *temp = rear; temp != NULL; temp = temp->next)
  {
    readNode(temp);
    puts("|");
    puts("v");
  }
  puts("NULL");
}


int main (){
    pushQueue(5);
    pushQueue(10);
    pushQueue(12);
    pushQueue(6);

    printQueue(); // print from rear to front

    removeFront();

    printQueue();

    return 0;
}
