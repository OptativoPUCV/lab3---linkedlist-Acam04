#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *lista = (List *)malloc(sizeof(List));
  if (lista) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
  }
  return lista;
}

void *firstList(List *list) { 
  if (list->head == NULL)
    return NULL;
  list->current = list->head;
  return (void *)list->current->data;
}

void *nextList(List *list) {
  if (list->current == NULL)
  {
    return NULL;
  }
  if (list->current->next == NULL)
  {
    return NULL;
  }  
  list->current = list->current->next;
  return list->current->data;
}

void *lastList(List *list) { 
  if (list->tail == NULL)
    return NULL;
  list->current = list->tail;
  return (void *)list->current->data;
}

void *prevList(List *list) { 
   if (list->current == NULL)
    {
      return NULL;
    }
    if (list->current->prev == NULL)
    {
      return NULL;
    }  
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List *list, void *data) {
  Node * newNodo = createNode(data);
  if (list->head == NULL)
  {
    list->head = newNodo;
    list->tail = newNodo;
  }
  else
  {
    newNodo->next = list->head;
    list->head->prev = newNodo;
    list->head = newNodo;
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  Node * newNodo = createNode(data);
  if (list->current == NULL)
  {
    list->head = newNodo;
    list->tail = newNodo;
  }
  else
  {
    newNodo->next = list->current->next;
    newNodo->prev = list->current;
    list->current->next = newNodo;
    if (newNodo->next != NULL)
    {
      newNodo->next->prev = newNodo;
    }
    else
    {
      list->tail = newNodo;
    }
  }
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) { 
  void *data = list->current->data;
  if (list->current->prev == NULL)
  {
    list->head = list->current->next;
    if (list->head != NULL)
    {
      list->head->prev = NULL;
    }
  }
  else
  {
    list->current->prev->next = list->current->next;
  }
  if (list->current->next == NULL)
  {
    list->tail = list->current->prev;
    if (list->tail != NULL)
    {
      list->tail->next = NULL;
    }
  }
  else
  {
    list->current->next->prev = list->current->prev;
  }
  free(list->current);
  list->current = NULL;
  return data;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}