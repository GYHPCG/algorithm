/*
 * @Descripttion: MyCode
 * @Author: CGPan
 * @Date: 2022-10-19 10:31:52
 * @LastEditors: CGPan
 * @LastEditTime: 2022-10-19 10:54:13
 */
#include <iostream>

using namespace std;
struct Node {
    int Data; 
    int xueHao;
    struct Node * Next; 
};
Node* creatHead( ) {

    Node* dummy = new Node();
    dummy->Data = 0;
    dummy->Next = nullptr;
    dummy->xueHao = 0;
    return dummy;
}
void addlist(Node* L,int x,int xueHao) {
    Node* p = new Node();
    Node* head = L;
    //找到结尾
    while(head->Next) {
        head = head->Next;
    }
    head->Next = p;
    p->Data = x;
    p->xueHao = xueHao;
    p->Next = nullptr;
    
}
int Length(Node* L) {
    int len = 0;
    Node* head = L;
    while(head->Next) {
        ++len;
        head = head->Next;
    }
    return len;
}
void SortList(Node* L) {
    Node* head1 = L->Next;
    if (head1 == nullptr || head1->Next == nullptr) return ;
    int size = Length(L);
    //bubble_sort
    Node* head2 = L->Next;
    //swap Value;
    for (int i = 0; i < size; ++i) {
        head1 = head2;
        for(int j = 0; j < size - i - 1; ++j) {
            if (head1->xueHao > head1->Next->xueHao) {
                swap(head1->xueHao,head1->Next->xueHao);
                swap(head1->Data,head1->Next->Data);
            }
            head1 = head1->Next;
        }
    }
   

 }
 void CombineLst(Node* L1, Node* L2, Node* L3) {
    //归并排序
    Node* HpL1 = L1->Next;
    Node* HpL2 = L2->Next;
    Node* HpL3 = L3;
    while(HpL1 != nullptr && HpL2 != nullptr) {
        if (HpL1->xueHao >= HpL2->xueHao) {
            HpL3->Next = HpL2;
            HpL2 = HpL2->Next;
            } else {
            HpL3->Next = HpL1;
            HpL1 = HpL1->Next;
        }
         HpL3 = HpL3->Next;
    }
    if(HpL1) {
        HpL3->Next = HpL1;
    }
    if(HpL2) {
        HpL3->Next = HpL2;
    }
} 
void print(Node* L) {
    Node* head = L;
    while(head->Next) {
        cout << head->Next->xueHao << " " << head->Next->Data << endl;
        head = head->Next;
    }
    cout << endl;
}
void deleteAllList(Node* L) {
    Node* head = L;
    if(head == nullptr) return;
    Node* tmp = nullptr;
    while(head) {
        tmp = head;
        head = head->Next;
        delete tmp;
    }
    
}
int main()
{
    int n, m;
    cin >> n >> m;
    Node* L1 = creatHead();
    Node* L2 = creatHead();
    [[gnu::unused]]
    Node* L3 = creatHead();
    int xuehao, score;
    for (int  i = 0; i < n; ++i) {
        cin >> xuehao >> score;
        addlist(L1,score,xuehao);
    }
    for (int i = 0; i < m; ++i) {
        cin >> xuehao >> score;
        addlist(L2,score,xuehao);
    }
    // print(L1);
    // print(L2);
    // cout << "按学号排序后: " << endl;
    // cout << "L1: " << endl;
    SortList(L1);
    // print(L1);
    // cout << "L2: " << endl;
    SortList(L2);
    // print(L2);
    // cout << "排序后: " << endl;
    CombineLst(L1,L2,L3);
    print(L3);
    deleteAllList(L3);
    delete L1;
    delete L2;
    // deleteAllList(L1);
    // deleteAllList(L2);
    return 0;

}
