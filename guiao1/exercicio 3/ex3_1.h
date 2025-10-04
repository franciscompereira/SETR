#ifndef ex31_H
#define ex31_H

typedef struct Node Node;
Node* createNode(int data);

void printList(Node* head);

void insertAtEnd(Node** head, int data);

void deleteNode(Node** head, int value);

#endif