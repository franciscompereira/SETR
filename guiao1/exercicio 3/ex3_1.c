#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ex3_1.h"

struct Node{
    int data;
    struct Node* next;
};

// Cria um node
Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {             // verifica se malloc deu NULL
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;       // se for o ultimo next = NULL
    return newNode;
}

// Print a todos os elementos na list
void printList(Node* head) {
    Node* current = head;

    // If the list is empty
    if (current == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("List elements: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Inserir um node no fim da lista
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);

    // If the list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Otherwise, find the last node
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the new node at the end
    current->next = newNode;
}


// Deletar um node escolhido
void deleteNode(Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    // If the head node is the one to delete
    if (current->data == value) {
        *head = current->next;
        free(current);
        return;
    }

    // Search for the node to delete
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    // Value not found
    if (current == NULL) {
        printf("Value %d not found in list.\n", value);
        return;
    }

    // Skip over the node and free it
    prev->next = current->next;
    free(current);
}
