#include <stdio.h>
#include <stdlib.h>

//打印时定义临时变量是因为保证原有数据结构的完整性
//释放时定义临时变量是向把头节点的next指针存起来，防止释放完头节点后再访问next就没有意义了

typedef struct Node {
    int data;
    struct Node* next;
}Node;
//之前想修改整型的值，传的是参数的地址
//现在想修改指针的值，而指针的值就是地址，地址就是一个指针，因此还要定义一个指向地址的指针，来修改指针的地址


Node* insertNode(Node*head,int value) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    if (newnode == NULL) {
        printf("The memory allocation is faluty!");
    }
    newnode->data = value;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
    }
    else {
        Node* current=head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newnode;
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head=NULL;
    head=insertNode(head, 1);
    head=insertNode(head, 2);
    head=insertNode(head, 3);
    printList(head);
    Node* temp;
    while (head!=NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
}

