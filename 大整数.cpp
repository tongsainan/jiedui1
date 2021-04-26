#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
// ��������������������
const int SIZE = 1000;
// ˫��ѭ��������
struct DualNode
{
    int data;           // ����ÿ������ֵ
    int len;            // ����ĳ���
    DualNode* prior;    // ǰ�̽��
    DualNode* next;     // ��̽��
};

typedef DualNode* DuLinkList;
void jisuan();//�ж������Ƿ��ʽ��ȷ������
void InitList(DuLinkList* L, char* str);//��ʼ��
DuLinkList add(DuLinkList a1, DuLinkList b1);// ���ӷ�
DuLinkList sub(DuLinkList a1, DuLinkList b1);// ������
DuLinkList solve(DuLinkList a1, DuLinkList b1);// ѡ����ּ��㷽��
void print(DuLinkList a);// �������Ľ��
void menu()
{
    printf("|*****************^-^��ӭʹ�����ⳤ�����ӷ�������^-^****************|\n");
    printf("|                     1.����       2.�˳�ϵͳ                       |\n");
    printf("|*******************************************************************|\n ");
    printf("������ѡ�");
}
void jisuan()
{
    int gg = 0, ggg = 0;
    int visit1 = 0, visit2 = 0, i = 0, j = 0, sign1 = 0, sign2 = 0;
    char a1[SIZE], b1[SIZE];
    for (j = 0;; j++) {
        visit1 = 0;     //���ż��
        gg = 0;          //���ݳ���
        i = 0;
        sign1 = 0;        //���ż���
        memset(a1, 0, sizeof(a1));//��ʼ��
        printf("�������һ������(ÿ��λһ�飬����ö��Ÿ���): ");
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
            printf("�������ʽ�������������롣\n");
        }
        else {
            break;
        }
    }
    i = 0;
    for (j = 0;; j++) {
        visit2 = 0;                //���ż��
        ggg = 0;                     //���ݳ���
        i = 0;
        sign2 = 0;                        //���ż���
        memset(b1, 0, sizeof(b1));       //��ʼ��
        printf("������ڶ�������(ÿ��λһ�飬����ö��Ÿ���): ");
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
            printf("�������ʽ�������������롣\n");
        }
        else {
            break;
        }
    }
    DuLinkList* a = (DuLinkList*)malloc(sizeof(DuLinkList));
    DuLinkList* b = (DuLinkList*)malloc(sizeof(DuLinkList));
    InitList(a, a1);    // ��ʼ������
    InitList(b, b1);    // ��ʼ������
    DuLinkList res;
    res = solve(*a, *b);
    printf("���: ");
    print(res);
}
void pp()
{
    printf("������ѡ�");
}
int main()
{
    menu();
    while (1) {
        int sum;         //�˵�ѡ��
        scanf("%d", &sum);
        switch (sum) {
        case 1:jisuan(); pp(); break;
        case 2:return 0; break;
        }
    }
    return 0;
}
// ���ַ���ת����������������ͷ��˫��ѭ������ͷ���Ƿ���λ
void InitList(DuLinkList* L, char* str)
{
    DuLinkList p, q;
    (*L) = (DuLinkList)malloc(sizeof(DualNode));
    (*L)->prior = NULL;
    (*L)->next = NULL;
    (*L)->data = '+';           // Ĭ�Ϸ���λΪ'+'
    p = (*L);
    int len = strlen(str);
    int cc = 1;     //����
    int LEN = 0;   //������
    int end = 0;
    if (str[0] == '-') {
        (*L)->data = '-';
        end = 1;    // ����Ƿ��ţ� ��ֻҪ���ַ����ڶ����ַ�λ��
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
    q = (DuLinkList)malloc(sizeof(DualNode));//ѭ�����ӣ�����һ������ǰ������λʱ
    q->data = sum;
    q->prior = p;
    p->next = q;
    p = q;
    ++LEN;
    p->next = (*L);
    (*L)->prior = p;
    (*L)->len = LEN;                 // ��¼����ĳ���-1 ����������������λ�ĳ���
}
DuLinkList add(DuLinkList a1, DuLinkList b1)// ���ӷ�
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // aΪ�ϳ����������� bΪ�϶̵���������
    if (len1 > len2) {
        a = a1;
        b = b1;
    }
    else {
        a = b1;
        b = a1;
    }
    len1 = a->len;          // �ϳ�������
    len2 = b->len;          // �϶�������
    int cnt = 0;
    int ex = 0;             // �����λֵ
    while (cnt != len1) {
        a = a->next;
        b = b->next;
        if (cnt >= len2)    // �Ѿ������϶������ȣ����Բ���Ҫ��b->data
            a->data = a->data + ex;
        else
            a->data = a->data + b->data + ex;
        ex = 0;
        if (a->data >= 10000) {
            a->data -= 10000;
            ex = 1;
        }// ����10000��ʾ�н�λֵ
        ++cnt;
    }
    if (ex) {   // ������һλ���н�λ
        // �򴴽�һ���µĽ��ŵ��ײ�
        // ע������˳��
        DuLinkList p = (DuLinkList)malloc(sizeof(DualNode));
        p->data = ex;
        p->next = a->next;
        a->next->prior = p;
        p->prior = a;
        a->next = p;
        a = p;
        ++len1;
    }
    a = a->next;       // �ص�����λ
    a->len = len1;      // ע��ͷ�����ȱ仯
    return a;
}
DuLinkList sub(DuLinkList a1, DuLinkList b1)// ������
{
    int len1 = a1->len;
    int len2 = b1->len;
    DuLinkList a, b;        // aΪ�ϳ����������� bΪ�϶̵���������
    if (len1 > len2) {
        a = a1;
        b = b1;
    }
    else if (len1 < len2) {
        a = b1;
        b = a1;
    }
    else {
        // ��������ͬʱ�� �Ծ���ֵ�����Ϊ����a
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
        if (cnt == len1) { // �����������һ���Ļ��� �͵�ִ��������
            a = a1;
            a->data = '+';       //�����������ֵ��ͬ����λ�衰+��
            b = b1;
        }
    }
    len1 = a->len;          // �ϳ�������
    len2 = b->len;          // �϶�������
    int cnt = 0;
    int ex = 0;             // �����λֵ
    while (cnt != len1) {
        a = a->next;
        b = b->next;
        if (cnt >= len2)    // �Ѿ������϶������ȣ����Բ���Ҫ��b->data
            a->data = a->data - ex;
        else
            a->data = a->data - b->data - ex;
        ex = 0;
        if (a->data < 0) {
            a->data += 10000;
            ex = 1;
        }// С��0��ʾ�н�λ
        ++cnt;
    }
    // �����ǽϴ�ľ���ֵ��ȥ��С�ľ���ֵ�� �������ղ��������λ�Ľ�λ
    a = a->next;       // �ص�����λ
    a->len = len1;      // ע��ͷ�����ȱ仯
    return a;
}
DuLinkList solve(DuLinkList a1, DuLinkList b1)
{
    DuLinkList res;
    if (!(a1->data ^ b1->data))        //��λ���
    {   // ͬ�����ӷ�
        res = add(a1, b1);
    }
    else {   // ���������
        res = sub(a1, b1);
    }
    return res;
}
// �������Ľ��
void print(DuLinkList a)
{
    int len = a->len;
    DuLinkList tmp = a;
    if (a->data == '-') {
        printf("%c", a->data);
        a = a->prior;
        while (a->data == 0 && a->prior != tmp)
        { // �ڶ��������Ǳ���� 0 �Ľ��ȥ��
            a = a->prior; // ȥ��ǰ����
            --len;
        }
    }
    else {
        a = a->prior;
        while (a->data == 0 && a->prior != tmp)
        { // �ڶ��������Ǳ���� 0 �Ľ��ȥ��
            a = a->prior; // ȥ��ǰ����
            --len;
        }
    }
    int su = 1;
    while (1) { // ��ͷ��ʼ�������
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