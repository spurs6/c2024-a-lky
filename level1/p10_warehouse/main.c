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
//不能在文件作用域声明可变数组长度（文件作用域是file scope）
//因此只能用一个确定的宏定义来初始化数组的长度
void load(){
    FILE*file=fopen("inventory.txt","r");
    if(file==NULL) {
        printf("The inventory is empty!\n");
        return;
    }
    //只能用数组，不能用指针的原因：调用结构体里面成员的方式有两种：
    //一种是使用定义的成员来点取调用
    //一种是定义指针来用箭头调用
    else {
        while (fscanf(file, "%s %d", item[count].name, &item[count].quantity) == 2) {
            count++;
        }
    }
    //scanf读取完的数据都通过变量的地址储存在变量了，而这个原理跟scanf是完全相同的
    //只是前者从文档流中获取数据，而后者从键盘流中获取数据
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
    printf("请输入你想添加的货物：");
    scanf("%s",item[count].name);
    printf("请输入你想添加的数量：");
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

    //这个count真的是太狡猾了，加载函数的最后，把count加了1，
    //实际上此时对应的count是没有数据的，这次直接传入进去
    //但是保存的时候需要遍历，但遍历无法遍历到count，因此这里手动给count加1
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
    printf("请输入你想移除的货物：");
    scanf("%s", title);
    printf("请输入你想移除的数量：");
    scanf_s("%d", &value);
    for(int i=0;i<count;i++) {
        if (strcmp(item[i].name, title) == 0) {
            item[i].quantity = item[i].quantity - value;
        }
    } //先执行出库的算术操作
    save();//直接用定义好的保存函数
    fclose(file);
    free(title);
    display();
}
//通过这个实验，我深刻体会到了脑子是个多么好用的东西！！！！！！！！！！
//第一次出错，我只是单纯的的修改了item数组里面的数值，并没有将它存放在数组里面
//然后我定义了一个file结构指针，将其fprintf到文档里面
//又犯了第二个错误：我肯定选择w模式，也就是重写模式，当它打开一个已经存在的文件时，它会先将里面的内容清空
//但我相当然的只将修改的数据fprintf进去，自然最后只有一个结果，
//所以我决定单独用for循环重写一次
//此时我又犯了第三个错误，我又加载了一次，于是出现了列表重复两次的请况
//最后我发现我已经在主函数里面加载了一次，而执行一次程序显然只需要加载一次

int main(){
    int choice=0;
    load();
    display();
    printf("请输入你想进行的操作：");
    scanf_s("%d",&choice);
    switch(choice){
        case 1:display();break;
        case 2:import();break;
        case 3:export();break;
        case 4:save();break;
    }
}


