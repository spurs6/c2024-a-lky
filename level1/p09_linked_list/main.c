#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node*next;
}Node;

Node*createnode(Node*head,int value){
    Node*newnode=(Node*)malloc(sizeof(Node));
    newnode->data=value;
    newnode->next=head;
    head=newnode;
    return head;
}

Node*reversenode(Node*head){
    Node*pre=NULL;
    Node*current=head;
    Node*temp=NULL;
    while(current!=NULL){
        temp=current->next;
        current->next=pre;
        pre=current;
        current=temp;
    }
    head=pre;
    return head;
}

int seekfirstnode(Node*head,int target){
    Node*current=head;
    int count2=1;
    while(head!=NULL){
        if(current->data==target){
            return count2;
        }
        current=current->next;
        count2++;
    }
}

int seeksecondnode(Node*head,int target){
    Node*current=head;
    int count1=0,count2=1;
    while(head!=NULL){
        if(current->data==target){
            count1++;
            if(count1==2){
                return count2;
            }
        }
        current=current->next;
        count2++;
    }
}



void printList(Node*head){
    Node*current=head;
    while(current!=NULL){
        printf("%d->",current->data);
        current=current->next;
    }
    printf("NULL\n");
}

int main(){
    Node*head=NULL;
    head=createnode(head,1);
    head=createnode(head,2);
    head=createnode(head,3);
    head=createnode(head,4);
    head=createnode(head,5);
    head=createnode(head,6);
    head=createnode(head,7);
    head=createnode(head,5);
    printList(head);
    head=reversenode(head);
    printList(head);
    int answer=seekfirstnode(head,5);
    printf("%d\n",answer);
    int answer1=seeksecondnode(head,5);
    printf("%d\n",answer1);
    Node*temp=head;
    while(head!=NULL){
        temp=head->next;
        free(head);
        head=temp;
    }
}

