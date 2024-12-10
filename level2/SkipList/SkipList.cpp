#include <stdio.h>
#include <stdlib.h>
#define MAX_LEVEL 5
#define MAX 10


//这里先是定义了跳表里面节点定义的结构体
typedef struct node {
    //key是节点代表的值
    int key;
    /*这是定义了一个指针数组，顾名思义就是数组里面全是指针的数组，
     这也叫做双指针，这里数组里面的长度定义成0其实是数组长度声明的
     一种形式，只是声明但并没有分配具体的内存，但是在c语言中，这是错误
     用法就是指针数组里面的第i个元素代表第i层上这个指针指向的下一个节点
     这个与链表里面的next指针定义有之处相同，只不过这里定义了好多层是，所以
     用了一个指针数组来代表不同层数的next指针
     */
    struct node** forward;
}Node;


//这里正式定义跳表，其实本质上跳表就是将链表分了好多层而已
typedef struct skiplist {
    //基于本质，这里先定义跳表的层数level
    //跳表的层种类分成原始链表和索引链表
    int level;
    //这里定义了一个跳表的头指针，用于遍历原始链表
    Node* header;
}Skiplist;

//结构体定义完成之后，自然就要初始化
Node* createnode(int key, int level) {
    //正常操作：还是先定义一个新节点
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->key = key;
    //我这里相当于给一个数组分配内存，和整型数组分配内存的原理是一样的
    //level+1的原因是原始链表定义成索引0，
    newnode->forward = (Node**)malloc(sizeof(Node*) * (level + 1));
    return newnode;
}

Skiplist* createskiplist() {
    Skiplist* skiplist1 = ( Skiplist*)malloc(sizeof(Skiplist));
    skiplist1->level = 0;//这里先初始化成当前层数为0
    skiplist1->header = createnode(MAX, MAX_LEVEL);
    //这个for循环就是让指针数组里面的所有指针全部初始化为0
    //元素的数量是level+1,操作就是层层调用成员变量
    for (int i = 0; i <= MAX_LEVEL; i++) {
        skiplist1->header->forward[i] = NULL;
    }
    return skiplist1;
}

//编写一个生成随机层数的函数
//这个函数的巧妙就在于它的随机性，利用rand()函数生成奇数和偶数的
//概率相同来生成随机层数，这个函数最近在五子棋项目里面也使用过，就是当
//有多个点的评分相同的时候，我们除以它的最大值列表的长度，然后随机生成
//一个值，作为落子点的索引
int randomlevel() {
    int level = 0;
    while (rand() % 2 == 0 && level <= MAX_LEVEL) {
        level++;
    }
    return level;
}

void insertnode(Skiplist* skiplist, int key) {
    //这里定义了一个更新的指针数组，负责存储新节点在每一层插入的位置
    //数组的下标代表的是数组的长度，而跳表一共有max_level+1
    Node* update[MAX_LEVEL + 1];
    //这里还是定义一个临时的指针，代替每一行的头指针完成遍历的操作
    Node* current = skiplist->header;

    //对于所有的双指针的初始化的问题，都是用for循环来实现的
    for (int i = 0; i <= MAX_LEVEL; i++) {
        //里面的都是指针变量，因此全部初始化成空指针
        update[i] = NULL;
    }

    //从最高层开始，每层都要找到插入节点的位置
    for (int i = skiplist->level; i >= 0; i--) {
        //遍历条件还是需要谨慎思考的,这就是每一层的遍历，这样做
        //的前提就是前面已经利用头指针初始化了整个跳表的指针
        //current就是一个包含所有行的头节点指针，从小到大
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            /*动态过程，始终在向下寻找合适的层，因此在不改变行的前提之下
            forward数组中的第i个元素就是第i层该节点的下一个节点
            这里能够遍历的原因也是使用不同节点的forward[i],从而实现
            遍历操作
            */
            current = current->forward[i];
        }
        update[i] = current;
    }

    int newlevel = randomlevel();

    /*如果生成的层数大于当前跳表的层数，更新当前跳表的层数
    同时还要更新当前存储位置数组的指针
    由于没有数据，因此我们直接让这个节点指向头指针即可*/

    if (newlevel > skiplist->level) {
        for (int i = skiplist->level + 1; i <= newlevel; i++) {
            update[i] = skiplist->header;
        }
        skiplist->level = newlevel;
    }

    //万事具备，直接创建一个节点即可
    Node* newnode = createnode(key, newlevel);

    for (int i = 0; i <= newlevel; i++) {
        //我只能说这又是一个太过巧妙的跳表插入结构，其实
        //如果前面的代码全都理解，这步的插入操作应该是
        //顺理成章的
        /*update存储的是原跳表中数值小于等于key值的节点，而update->
         *forward[i] 是存储的第i行的下一个节点的位置，根据key值的特点，
         * 新节点就应该插入在这两者之间，然后就是常见的插入操作，相当于断开
         * 中点的两侧，先让新节点的forward指针指向存储数组的下一个指针
         * 然后再让更新数组的下一个指针指向新指针，这里也涉及到前后的顺序问题
         * */
        newnode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newnode;
    }
}


Node* searchnode(Skiplist* skiplist, int key) {

    Node* current = skiplist->header;

    /*遍历跳表的基本步骤我们也可以归纳出来了
    就是在每一层都需要遍历，而遍历的层数是确定的，
    因此外面先用一个for循环，而节点在每一层上的遍历是不确定的
    因此需要用while循环，然后设置合理的边界条件进行每一层的遍历
    而这不正是链表遍历的写法吗：当前指针不为0或者当前指针的下一个
    指针也不为0，同时这也是链表编写时一个比较容易出错的点
    */
    for (int i = skiplist->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
        }
    }

    //在最后一层找到节点之后，确定值是相等的而不是大于的
    //这也是为什么是小于，而不是小于等于的原因，就是因为current->forward存储的是下一个节点的位置
    if (current->forward[0] != NULL && current->forward[0]->key == key) {
        return current->forward[0];
    }

    return NULL;
}

void printList(Skiplist* skiplist) {
    for (int i = skiplist->level; i >= 0; i--) {
        //这里打印跳表所用的思想就完全是链表单行打印的操作了
        //为了保证头指针的安全性，先是定义了一个临时指针变量，用于表示头指针
        Node* current = skiplist->header->forward[i];
        printf("level:%d    ", i);
        //这里条件设置成是current，而不是current->forward[i]的原因就是防止它跨行打印
        while (current != 0) {
            printf("%d->", current->key);
            current = current->forward[i];
        }
        printf("NULL\n");
    }
    printf("%c", '\n');
}

//释放节点
void freeNode(Node* node) {
    free(node->forward);
    free(node);
}

//释放跳表
void freeSkipList(Skiplist* skipList) {
    Node* current = skipList->header->forward[0];
    Node* next;

    while (current != NULL) {
        next = current->forward[0];
        freeNode(current);
        current = next;
    }

    free(skipList->header->forward);
    free(skipList->header);
    free(skipList);
}

int main() {
    Skiplist* skiplist = createskiplist();

    insertnode(skiplist, 3);
    insertnode(skiplist, 6);
    insertnode(skiplist, 7);
    insertnode(skiplist, 9);
    insertnode(skiplist, 19);
    insertnode(skiplist, 22);
    insertnode(skiplist, 25);

    printList(skiplist);

    int searchkey = 9;

    Node* result = searchnode(skiplist, searchkey);

    if (result != NULL) {
        printf("The node with the %d is found", searchkey);
    }
    else {
        printf("The node with the %d is not found", searchkey);
    }

    freeSkipList(skiplist);
}











