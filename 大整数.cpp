#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
// 设置输出的最长的整数长度
const int SIZE = 1000;
// 双向循环链表结点
struct DualNode
{
    int data;           // 链表每个结点的值
    int len;            // 链表的长度
    DualNode* prior;    // 前继结点
    DualNode* next;     // 后继结点
};

typedef DualNode* DuLinkList;
void jisuan();//判断数据是否格式正确和输入
void InitList(DuLinkList* L, char* str);//初始化
DuLinkList add(DuLinkList a1, DuLinkList b1);// 做加法
DuLinkList sub(DuLinkList a1, DuLinkList b1);// 做减法
DuLinkList solve(DuLinkList a1, DuLinkList b1);// 选择何种计算方法
void print(DuLinkList a);// 输出链表的结果
void menu()
{
    printf("|*****************^-^欢迎使用任意长整数加法计算器^-^****************|\n");
    printf("|                     1.计算       2.退出系统                       |\n");
    printf("|*******************************************************************|\n ");
    printf("请输入选项：");
}
void jisuan()
{
    int gg = 0, ggg = 0;
    int visit1 = 0, visit2 = 0, i = 0, j = 0, sign1 = 0, sign2 = 0;
    char a1[SIZE], b1[SIZE];
    for (j = 0;; j++) {
        visit1 = 0;     //逗号间隔
        gg = 0;          //数据长度
        i = 0;
        sign1 = 0;        //逗号计数
        memset(a1, 0, sizeof(a1));//初始化
        printf("请输入第一个整数(每四位一组，组间用逗号隔开): ");
        scanf("%s", a1);
        gg = strlen(a1);
        while (i < gg && visit1 <= 4) {
            if (a1[i] == ',') {
                sign1++;
                if (sign1 != 1) {
                    if (visit1 != 4) {
                        break;
                    }
                }
                visit1 = 0;
            }
            else if (a1[i] != ',' && a1[i] != '-') {
                visit1++;
            }
            i++;
        }
        if ((visit1 > 4) || (sign1 != 1 && sign1 != 0 && visit1 != 4) || (sign1 == 1 && visit1 < 4)) {
            printf("您输入格式错误，请重新输入。\n");
        }
        else {
            break;
        }
    }
    i = 0;
    for (j = 0;; j++) {
        visit2 = 0;                //逗号间隔
        ggg = 0;                     //数据长度
        i = 0;
        sign2 = 0;                        //逗号计数
        memset(b1, 0, sizeof(b1));       //初始化
        printf("请输入第二个整数(每四位一组，组间用逗号隔开): ");
        scanf("%s", b1);
        ggg = strlen(b1);
        while (i < ggg && visit2 <= 4) {
            if (b1[i] == ',') {
                sign2++;
                if (sign2 != 1) {
                    if (visit2 != 4) {
                        break;
                    }
                }
                visit2 = 0;
            }
            else if (b1[i] != ',' && b1[i] != '-') {
                visit2++;
            }
            i++;
        }
        if (visit2 > 4 || (sign2 != 1 && sign2 != 0 && visit2 != 4) || (sign2 == 1 && visit2 < 4)) {
            printf("您输入格式错误，请重新输入。\n");
        }
        else {
            break;
        }
    }
    DuLinkList* a = (DuLinkList*)malloc(sizeof(DuLinkList));
    DuLinkList* b = (DuLinkList*)malloc(sizeof(DuLinkList));
    InitList(a, a1);    // 初始化链表
    InitList(b, b1);    // 初始化链表
    DuLinkList res;
    res = solve(*a, *b);
    printf("结果: ");
    print(res);
}
void pp()
{
    printf("请输入选项：");
}
int main()
{
    menu();
    while (1) {
        int sum;         //菜单选项
        scanf("%d", &sum);
        switch (sum) {
        case 1:jisuan(); pp(); break;
        case 2:return 0; break;
        }
    }
    return 0;
}
// 将字符串转换成链表，建的是有头的双向循环链表，头部是符号位
void InitList(DuLinkList* L, char* str)
{
    DuLinkList p, q;
    (*L) = (DuLinkList)malloc(sizeof(DualNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = '+';           // 默认符号位为'+'
    p = (*L);
    int len = strlen(str);
    int cc = 1;     //计数
    int LEN = 0;   //链表长度
    int end = 0;
    if (str[0] == '-') {
        (*L)->data = '-';
        end = 1;    // 如果是符号， 则只要到字符串第二个字符位置
    }
    int su = 1, sum = 0;
    for (int i = len - 1; i >= end; --i) {
        if (cc % 5 == 0) {
            q = (DuLinkList)malloc(sizeof(DualNode));
            q->data = sum;
            q->prior = p;
            p->next = q;
            p = q;
            ++LEN;
            sum = 0; su = 1;
        }
        else {
            sum = sum + (str[i] - '0') * su;
            su = su * 10;
        }
        ++cc;
    }
    q = (DuLinkList)malloc(sizeof(DualNode));//循环连接，当第一个逗号前不足四位时
    q->data = sum;
    q->prior = p;
    p->next = q;
    p = q;
    ++LEN;
    p->next = (*L);
    (*L)->prior = p;
    (*L)->len = LEN;                 // 记录链表的长度-1 ————不带符号位的长度
}
DuLinkList add(DuLinkList a1, DuLinkList b1)// 做加法
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // a为较长的整数链表， b为较短的整数链表
    if (len1 > len2) {
        a = a1;
        b = b1;
    }
    else {
        a = b1;
        b = a1;
    }
    len1 = a->len;          // 较长链表长度
    len2 = b->len;          // 较短链表长度
    int cnt = 0;
    int ex = 0;             // 保存进位值
    while (cnt != len1) {
        a = a->next;
        b = b->next;
        if (cnt >= len2)    // 已经超过较短链表长度，所以不需要加b->data
            a->data = a->data + ex;
        else
            a->data = a->data + b->data + ex;
        ex = 0;
        if (a->data >= 10000) {
            a->data -= 10000;
            ex = 1;
        }// 超过10000表示有进位值
        ++cnt;
    }
    if (ex) {   // 如果最后一位还有进位
        // 则创建一个新的结点放到首部
        // 注意插入的顺序
        DuLinkList p = (DuLinkList)malloc(sizeof(DualNode));
        p->data = ex;
        p->next = a->next;
        a->next->prior = p;
        p->prior = a;
        a->next = p;
        a = p;
        ++len1;
    }
    a = a->next;       // 回到符号位
    a->len = len1;      // 注意头部长度变化
    return a;
}
DuLinkList sub(DuLinkList a1, DuLinkList b1)// 做减法
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // a为较长的整数链表， b为较短的整数链表
    if (len1 > len2) {
        a = a1;
        b = b1;
    }
    else if (len1 < len2) {
        a = b1;
        b = a1;
    }
    else {
        // 链表长度相同时， 以绝对值大的数为链表a
        DuLinkList tmp1 = a1, tmp2 = b1;
        int cnt = 0;
        tmp1 = tmp1->prior;
        tmp2 = tmp2->prior;
        while (cnt != len1) {
            if (tmp1->data > tmp2->data) {
                a = a1;
                b = b1;
                break;
            }
            else if (tmp1->data < tmp2->data) {
                a = b1;
                b = a1;
                break;
            }
            tmp1 = tmp1->prior;
            tmp2 = tmp2->prior;
            ++cnt;
        }
        if (cnt == len1) { // 如果两个数是一样的话， 就得执行这里了
            a = a1;
            a->data = '+';       //如果两数绝对值相同符号位设“+”
            b = b1;
        }
    }
    len1 = a->len;          // 较长链表长度
    len2 = b->len;          // 较短链表长度
    int cnt = 0;
    int ex = 0;             // 保存借位值
    while (cnt != len1) {
        a = a->next;
        b = b->next;
        if (cnt >= len2)    // 已经超过较短链表长度，所以不需要减b->data
            a->data = a->data - ex;
        else
            a->data = a->data - b->data - ex;
        ex = 0;
        if (a->data < 0) {
            a->data += 10000;
            ex = 1;
        }// 小于0表示有借位
        ++cnt;
    }
    // 由于是较大的绝对值减去较小的绝对值， 所以最终不会有最高位的借位
    a = a->next;       // 回到符号位
    a->len = len1;      // 注意头部长度变化
    return a;
}
DuLinkList solve(DuLinkList a1, DuLinkList b1)
{
    DuLinkList res;
    if (!(a1->data ^ b1->data))        //按位异或
    {   // 同号做加法
        res = add(a1, b1);
    }
    else {   // 异号做减法
        res = sub(a1, b1);
    }
    return res;
}
// 输出链表的结果
void print(DuLinkList a)
{
    int len = a->len;
    DuLinkList tmp = a;
    if (a->data == '-') {
        printf("%c", a->data);
        a = a->prior;
        while (a->data == 0 && a->prior != tmp)
        { // 第二个条件是避免把 0 的结果去掉
            a = a->prior; // 去掉前导零
            --len;
        }
    }
    else {
        a = a->prior;
        while (a->data == 0 && a->prior != tmp)
        { // 第二个条件是避免把 0 的结果去掉
            a = a->prior; // 去掉前导零
            --len;
        }
    }
    int su = 1;
    while (1) { // 从头开始输出链表
        if (su == 0) {
            printf("%04d", a->data);
        }
        else
        {
            printf("%d", a->data); su = 0;
        }
        a = a->prior;
        --len;
        if (len == 0)break;
        printf(",");
    }
    puts("");
}