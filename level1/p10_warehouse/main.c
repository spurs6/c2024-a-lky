#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 50
#define MAX_NUMBER 10

typedef struct{
    int quantity;
    char name[MAX_SIZE];
}inventory;

int count=0;
inventory item[MAX_NUMBER];
//�������ļ������������ɱ����鳤�ȣ��ļ���������file scope��
//���ֻ����һ��ȷ���ĺ궨������ʼ������ĳ���
void load(){
    FILE*file=fopen("inventory.txt","r");
    if(file==NULL) {
        printf("The inventory is empty!\n");
        return;
    }
    //ֻ�������飬������ָ���ԭ�򣺵��ýṹ�������Ա�ķ�ʽ�����֣�
    //һ����ʹ�ö���ĳ�Ա����ȡ����
    //һ���Ƕ���ָ�����ü�ͷ����
    else {
        while (fscanf(file, "%s %d", item[count].name, &item[count].quantity) == 2) {
            count++;
        }
    }
    //scanf��ȡ������ݶ�ͨ�������ĵ�ַ�����ڱ����ˣ������ԭ���scanf����ȫ��ͬ��
    //ֻ��ǰ�ߴ��ĵ����л�ȡ���ݣ������ߴӼ������л�ȡ����
    fclose(file);
}

void display(){
    printf("Now the inventory has goods as follows:\n");
    for(int i=0;i<count;i++){
        printf("%s %d\n",item[i].name,item[i].quantity);
    }
}

void save(){
    FILE*file=fopen("inventory.txt","w");
    for(int i=0;i<count;i++){
        fprintf(file,"%s %d",item[i].name,item[i].quantity);
    }
    fclose(file);
}

void import(){
    FILE*file=fopen("inventory.txt","w");
    if(count==MAX_NUMBER){
        printf("The inventory is already full!");
        return;
    }
    int x=0;
    printf("������������ӵĻ��");
    scanf("%s",item[count].name);
    printf("������������ӵ�������");
    scanf_s("%d",&item[count].quantity);
    for(int i=0;i<count;i++){
        if(strcmp(item[i].name,item[count].name)==0){
             item[i].quantity=item[i].quantity+item[count].quantity;
             x=1;
        }
    }
    if(x==0){
        count++;
    }

    //���count�����̫�ƻ��ˣ����غ�������󣬰�count����1��
    //ʵ���ϴ�ʱ��Ӧ��count��û�����ݵģ����ֱ�Ӵ����ȥ
    //���Ǳ����ʱ����Ҫ�������������޷�������count����������ֶ���count��1
    save();
    fclose(file);
    display();
}

void export() {
    FILE *file = fopen("inventory.txt", "w");
    if (count == 0) {
        printf("The inventory is already empty!");
        return;
    }
    char *title = NULL;
    int value = 0, i = 0;
    title = (char *) malloc(sizeof(char) * MAX_SIZE);
    printf("�����������Ƴ��Ļ��");
    scanf("%s", title);
    printf("�����������Ƴ���������");
    scanf_s("%d", &value);
    for(int i=0;i<count;i++) {
        if (strcmp(item[i].name, title) == 0) {
            item[i].quantity = item[i].quantity - value;
        }
    } //��ִ�г������������
    save();//ֱ���ö���õı��溯��
    fclose(file);
    free(title);
    display();
}
//ͨ�����ʵ�飬�������ᵽ�������Ǹ���ô���õĶ�����������������������
//��һ�γ�����ֻ�ǵ����ĵ��޸���item�����������ֵ����û�н����������������
//Ȼ���Ҷ�����һ��file�ṹָ�룬����fprintf���ĵ�����
//�ַ��˵ڶ��������ҿ϶�ѡ��wģʽ��Ҳ������дģʽ��������һ���Ѿ����ڵ��ļ�ʱ�������Ƚ�������������
//�����൱Ȼ��ֻ���޸ĵ�����fprintf��ȥ����Ȼ���ֻ��һ�������
//�����Ҿ���������forѭ����дһ��
//��ʱ���ַ��˵������������ּ�����һ�Σ����ǳ������б��ظ����ε����
//����ҷ������Ѿ������������������һ�Σ���ִ��һ�γ�����Ȼֻ��Ҫ����һ��

int main(){
    int choice=0;
    load();
    display();
    printf("������������еĲ�����");
    scanf_s("%d",&choice);
    switch(choice){
        case 1:display();break;
        case 2:import();break;
        case 3:export();break;
        case 4:save();break;
    }
}


