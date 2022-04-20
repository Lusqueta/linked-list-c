#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int value;
  struct Node *next;   
} Node;

typedef Node List;

List *create_list() {
  List *list = malloc(sizeof(List));

  list->value = 0;
  list->next = NULL;

  return list;
}

Node *create_node(int value) {
  Node *node = malloc(sizeof(Node));

  node->value = value;
  node->next = NULL;

  return node;
}

Node *get_last_node(List *list) {
  Node *node = list;

  while ( (*node).next != NULL ) {
    node = (*node).next;
  }

  return node;
}

void append(List *list, Node *node) {
  get_last_node(list)->next = node;
}

void prepend(List *list, Node *node) {
  Node *first = list;
  Node *old = (*first).next;

  first->next = node;
  first->next->next = old;
}

int get_size(List *list) {
  int size = 0;

  Node *node = (*list).next;

  while ( node != NULL ) {
    size++;
    node = (*node).next;
  }

  return size;
}

int *list_to_array(List *list) {
  int *buffer = (int*) calloc(get_size(list), sizeof(int));

  Node *node = (*list).next;

  int index = 0;
  while ( node != NULL ) {
    buffer[index++] = node->value;
    node = (*node).next;
  }

  return buffer;
}

void print_list(List *list) { 
  int *numbers = list_to_array(list);
  
  for(int index = 0; index < get_size(list); index++)
    printf("%d: %d\n", index, numbers[index]);

  free(numbers);
}

Node *get_list_item(List *list, int index) {
  Node *node = (*list).next;

  if(index >= get_size(list)) {
    return list;
  }

  int i = 0;
  while(i < index) {
    node = (*node).next;
    i++;
  }

  return node;
}

void free_list(List *list) {
  Node *node = (*list).next;

  while ( node != NULL ) {
    Node *old = node;
    node = (*node).next;
    free(old);
  }

  free(list);
}

void remove_item(List *list, int index) {
  Node *node = get_list_item(list, index);
  Node *before = get_list_item(list, index - 1);
  Node *after = get_list_item(list, index + 1);

  (*before).next = after;

  free(node);
}

int main() {
  List *list = create_list();

  printf("Append and preppend:\n");
  append(list, create_node(1));
  append(list, create_node(2));
  append(list, create_node(3));
  append(list, create_node(4));
  
  prepend(list, create_node(5));

  print_list(list);

  printf("Remove item:\n");
  remove_item(list, 2);

  print_list(list);

  printf("Free list:\n");
  free_list(list);

  printf("Press any key to exit...\n");
  gets();

  return 0;
}
