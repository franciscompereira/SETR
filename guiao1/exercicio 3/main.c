#include <stdlib.h>
#include "ex3_1.h"

int main(void){
    /*
    Node* n1 = createNode(10);
    Node* n2 = createNode(20);
    Node* n3 = createNode(30);

    // liga-os manualmente
    n1->next = n2;
    n2->next = n3;

    // testa o print
    printList(n1);
    return 0;
    */

    Node* head = NULL; // lista vazia

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printList(head);

    deleteNode(&head, 20);  // remove o nó com valor 20
    printList(head);

    deleteNode(&head, 10);  // remove o primeiro nó
    printList(head);

    deleteNode(&head, 99);  // tenta remover valor inexistente
    printList(head);

}
