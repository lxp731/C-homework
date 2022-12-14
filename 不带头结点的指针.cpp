typedef int elemType ;
 
// 定义单链表结点类型
typedef struct ListNode{
    elemType element;      //数据域
    struct ListNode *next;   //地址域
}Node;

（2）初始化线性表
// 1.初始化线性表，即置单链表的表头指针为空
void initList(Node *pNode){
 
    pNode = NULL;
    printf("%s函数执行，初始化成功\n",__FUNCTION__);
}
当声明一个头结点后，把该头结点设置为空，即把数据域和地址域都设为空，即可完成该链表的初始化。
（3）创建线性表

// 2.创建线性表，此函数输入负数终止读取数据
Node *creatList(Node *pHead){
 
    Node *p1;//表头节点，始终指向头结点
    Node *p2;//表尾节点，始终指向链表的最后一个元素
 
    p1 = p2 = (Node *)malloc(sizeof(Node)); //申请新节点,分配空间
    if(p1 == NULL || p2 == NULL){
 
        printf("内存分配失败\n");
        exit(0);
    }
    memset(p1,0,sizeof(Node));
 
    scanf("%d",&p1->element);    //输入新节点的值
    p1->next = NULL;         //新节点的指针置为空
    while(p1->element > 0){        //输入的值大于0则继续，直到输入的值为负
        if(pHead == NULL){       //空表，接入表头
            pHead = p1;          //直接把p1作为头结点，也可以理解为把pHead头结点指向p1
        }else{
            p2->next = p1;       //非空表，接入表尾
        }
        p2 = p1;                //p1插入后，p1就是尾结点，所以p2要指向尾结点
        p1 = (Node *)malloc(sizeof(Node));    //再重申请一个节点
        if(p1 == NULL || p2 == NULL){
 
            printf("内存分配失败\n");
            exit(0);
        }
        memset(p1,0,sizeof(Node));
        scanf("%d",&p1->element);
        p1->next = NULL;
    }
    printf("%s函数执行，链表创建成功\n",__FUNCTION__);
    return pHead;           //返回链表的头指针
}

我这里使用手动的方式输入元素，直到输入0或者负数停止。

（4）打印链表

// 3.打印链表，链表的遍历
void printList(Node *pHead){
    if(NULL == pHead){   //链表为空
        printf("%s函数执行，链表为空\n",__FUNCTION__);
    }else{
        while(NULL != pHead){
            
            printf("%d ",pHead->element);
            pHead = pHead->next;
        }
        printf("\n");
    }
}

使用地址域顺序打印即可。


（5）清空链表

// 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表
void clearList(Node *pHead){
 
    Node *pNext;            //定义一个与pHead相邻节点,理解为当前节点的下一个节点
    if(pHead == NULL){
        printf("%s函数执行，链表为空\n",__FUNCTION__);
    }
    while(pHead->next != NULL){
 
        pNext = pHead->next;//保存下一结点的指针
        free(pHead);   //释放当前节点
        pHead = pNext;      //指向下一个节点
    }
    printf("%s函数执行，链表已经清除\n",__FUNCTION__);
}

想要检验是否清空成功，可以使用（4）中的链表打印检验即可。
（6）计算链表长度

// 5.返回单链表的长度
int sizeList(Node *pHead){
 
    int size = 0;
    while(pHead != NULL){
 
        size++;
        pHead = pHead->next;
    }
    printf("%s函数执行，链表长度 %d \n",__FUNCTION__,size);
    return size;    //链表的实际长度
}

也就是计算有多少个节点。
（7）判断链表是否为空

// 6.检查单链表是否为空，若为空则返回１，否则返回０
int isEmptyList(Node *pHead){
    if(pHead == NULL){
 
        printf("%s函数执行，链表为空\n",__FUNCTION__);
        return 1;
    }
    printf("%s函数执行，链表非空\n",__FUNCTION__);
 
    return 0;
}

（8）查找链表某个位置元素
// 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行
void getElement(Node *pHead, int pos){
 
    int i = 0;
    if(pos < 1){
        printf("%s函数执行，pos值非法\n",__FUNCTION__);
    }
 
    if(pHead == NULL){
        printf("%s函数执行，链表为空\n",__FUNCTION__);
    }
 
    while(pHead != NULL){
 
        i++;
        if(i == pos){
            break;
        }
        pHead = pHead->next;    //移到下一结点
    }
    if(i < pos){                  //pos值超过链表长度
        printf("%s函数执行，pos值超出链表长度\n",__FUNCTION__);
    }
 
    printf("%s函数执行，位置 %d 中的元素为 %d\n",__FUNCTION__,pos,pHead->element);
}

（9）返回某元素值在链表中的内存地址
// 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL
elemType* getElemAddr(Node *pHead, elemType x){
    if(NULL == pHead){
 
        printf("%s函数执行，链表为空\n",__FUNCTION__);
        return NULL;
    }
 
    while((pHead->element != x) && (NULL != pHead->next)) {//判断是否到链表末尾，以及是否存在所要找的元素
        pHead = pHead->next;
    }
 
    if((pHead->element != x) && (pHead != NULL)){
        //当到达最后一个节点
        printf("%s函数执行，在链表中未找到x值\n",__FUNCTION__);
        return NULL;
    }
 
    if(pHead->element == x){
        printf("%s函数执行，元素 %d 的地址为 0x%x\n",__FUNCTION__,x,&(pHead->element));
    }
 
    return &(pHead->element);//返回元素的地址
}

（10）修改某个节点的值

// 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０
int modifyElem(Node *pNode,int pos,elemType x){
 
    int i = 0;
    if(NULL == pNode){
        printf("%s函数执行，链表为空\n",__FUNCTION__);
        return 0;
    }
 
    if(pos < 1){
 
        printf("%s函数执行，pos值非法\n",__FUNCTION__);
        return 0;
    }
 
    while(pNode != NULL){
 
        i++;
        if(i == pos){
            break;
        }
        pNode = pNode->next; //移到下一结点
    }
 
    if(i < pos) {                 //pos值大于链表长度
 
        printf("%s函数执行，pos值超出链表长度\n",__FUNCTION__);
        return 0;
    }
    pNode->element = x;
    printf("%s函数执行\n",__FUNCTION__);
 
    return 1;
}

（11）表头插入一个节点
// 10.向单链表的表头插入一个元素
int insertHeadList(Node **pNode,elemType insertElem){
 
    Node *pInsert;
    pInsert = (Node *)malloc(sizeof(Node));
    memset(pInsert,0,sizeof(Node));
    pInsert->element = insertElem;
    pInsert->next = *pNode;
    *pNode = pInsert;          //头节点*pNode指向刚插入的节点，注意和上一行代码的前后顺序；
    printf("%s函数执行，向表头插入元素成功\n",__FUNCTION__);
 
    return 1;
}

（12）表尾插入一个节点
// 11.向单链表的末尾添加一个元素
int insertLastList(Node **pNode,elemType insertElem){
 
    Node *pInsert;
    Node *pHead;
 
    pHead = *pNode;
    pInsert = (Node *)malloc(sizeof(Node)); //申请一个新节点
    memset(pInsert,0,sizeof(Node));
    pInsert->element = insertElem;
 
    while(pHead->next != NULL){
        pHead = pHead->next;
    }
    pHead->next = pInsert;   //将链表末尾节点的下一结点指向新添加的节点
 
    printf("%s函数执行，向表尾插入元素成功\n",__FUNCTION__);
    
    return 1;
}

（13）测试函数
int main(int argc, const char * argv[]) {
 
    Node *pList;            //声明头结点
 
    initList(pList);       //链表初始化
    printList(pList);       //遍历链表，打印链表
 
    pList = creatList(pList); //创建链表
    printList(pList);
 
    sizeList(pList);        //链表的长度
    printList(pList);
 
    isEmptyList(pList);     //判断链表是否为空链表
 
    getElement(pList,3);  //获取第三个元素，如果元素不足3个，则返回0
    printList(pList);
 
    getElemAddr(pList,5);   //获得元素5的内存地址
 
    modifyElem(pList,4,1);  //将链表中位置4上的元素修改为1
    printList(pList);
 
    insertHeadList(&pList,5);   //表头插入元素5
    printList(pList);
 
    insertLastList(&pList,10);  //表尾插入元素10
    printList(pList);
 
    clearList(pList);       //清空链表
    printList(pList);
 
    return 0;
}

