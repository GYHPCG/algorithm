//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//struct Process {
//    int id;
//    int arrivalTime;
//    int burstTime;
//    int priority;
//};
//
//bool compareArrivalTime(Process p1, Process p2) {
//    return p1.arrivalTime < p2.arrivalTime;
//}
//
//bool comparePriority(Process p1, Process p2) {
//    return p1.priority > p2.priority;
//}
//
//void priorityScheduling(vector<Process> processes) {
//    sort(processes.begin(), processes.end(), compareArrivalTime);
//
//    int n = processes.size();
//    int currentTime = processes[0].arrivalTime;
//    int waitingTime = 0;
//    int turnaroundTime = 0;
//
//    vector<int> completionTime(n);
//    vector<int> remainingTime(n);
//
//    for (int i = 0; i < n; i++) {
//        remainingTime[i] = processes[i].burstTime;
//    }
//
//    while (true) {
//        bool allProcessesCompleted = true;
//        int highestPriorityProcessIndex = -1;
//        int highestPriority = INT_MIN;
//
//        for (int i = 0; i < n; i++) {
//            if (remainingTime[i] > 0 && processes[i].arrivalTime <= currentTime) {
//                allProcessesCompleted = false;
//                if (processes[i].priority > highestPriority) {
//                    highestPriorityProcessIndex = i;
//                    highestPriority = processes[i].priority;
//                }
//            }
//        }
//
//        if (allProcessesCompleted) {
//            break;
//        }
//
//        if (highestPriorityProcessIndex != -1) {
//            remainingTime[highestPriorityProcessIndex]--;
//            if (remainingTime[highestPriorityProcessIndex] == 0) {
//                completionTime[highestPriorityProcessIndex] = currentTime + 1;
//                waitingTime += completionTime[highestPriorityProcessIndex] - processes[highestPriorityProcessIndex].arrivalTime - processes[highestPriorityProcessIndex].burstTime;
//                turnaroundTime += completionTime[highestPriorityProcessIndex] - processes[highestPriorityProcessIndex].arrivalTime;
//            }
//        }
//        currentTime++;
//    }
//
//    double averageWaitingTime = (double) waitingTime / n;
//    double averageTurnaroundTime = (double) turnaroundTime / n;
//
//    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
//    for (int i = 0; i < n; i++) {
//        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].priority << "\t\t";
//        cout << completionTime[i] << "\t\t" << completionTime[i] - processes[i].arrivalTime - processes[i].burstTime << "\t\t" << completionTime[i] - processes[i].arrivalTime << endl;
//    }
//
//    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
//    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
//}
//
//int main() {
//    vector<Process> processes = {
//        {1, 0, 8, 3},
//        {2, 1, 4, 2},
//        {3, 2, 9, 1},
//        {4, 3, 5, 4},
//        {5, 4, 2, 5}
//    };
//
//    priorityScheduling(processes);
//
//    return 0;
//}


#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<windows.h>
#define RNUM 5 //5�����̣��ɸı�
#define PTIME 50 //���ȼ���ʼֵ

enum state //ö������
{
 ready, //����
 execute, //ִ��
 block, //����
 finish //���
};//�������״̬

struct pcb //���̿��ƿ����ݽṹ
{
 char name [4];//������
 int priority;//����Ȩ
 int cpuTime;//CPU����ʱ��
 int needTime;//������������ʱ��
 int count;//����ִ�д���
 int round;//ʱ��Ƭ��ת�ִ�
 enum state process;//����״̬
 struct pcb* next; //����ָ��
};//�������PCB

struct pcb* getProcess()
{
 struct pcb* q = NULL;
 struct pcb* t = NULL;
 struct pcb* p = NULL;
 int  i = 0;
 printf("��������̵����ƺ�����ʱ�䣡\n");
 while(i < RNUM)
 {
  q=(struct pcb* )malloc(sizeof(struct pcb));
  scanf("%s", &q->name);
  scanf("%d", &q->needTime);
  q->cpuTime = 0;
  q->priority = PTIME - q->needTime;
  q->process = ready;
  q->next = NULL;
  if(i == 0)
  {
   p = q;
   t = q;
  }
  else
  {
   t->next = q;//�����������̶���
   t = q;
     }
  i++;
 }
  return p;

}//����ģ����ԵĽ�������ִ������ʱ�䣬��ʼ���ÿ�ģ��5�����̵ĵ���

void display(struct pcb* p)
{
 printf("����\t��������ʱ��\t��������ʱ��\t\t���ȼ�\t\t״̬\n");
 while(p)
 {
  printf("%s\t", p->name);  //���������
  printf("        ");
  printf("%d\t", p->cpuTime); //���cpuִ��ʱ��
  printf("        ");
  printf("%d\t", p->needTime);//�������ִ������ʱ��
  printf("        ");
  printf("%d\t", p->priority);//������ȼ�
  printf("         ");
  switch(p->process)//�������״̬
  {
   case ready:
    printf("����\n");
    break;
   case execute:
    printf("ִ��\n");
    break;
   case block:
    printf("����\n");
    break;
   case finish:
    printf("���\n");
    break;
   default:
    break;
  }
  p = p->next;//ָ����һ������
 }//��ʾģ������������������CPUʱ�䡢��������ʱ���Լ����ȼ�
}

int processFinish(struct pcb* q)//�����Ƿ�����������н���û�н���ʱ����0
{
 int bl = 1;
 while(bl && q)
 {
  bl = bl && (q->needTime == 0);
  q = q->next;
 }
 return bl;

}//�������̣����������и����̵�����ʱ������Ϊ0

void couExe(struct pcb* q)
{
 struct pcb* t = q;
 int maxPriority = 0; //��������ȼ�Ϊ0
 while(q)
 {
  if(q->process != finish)
  {
   q->process = ready;
   if(q->needTime == 0)
   {
    q->process = finish;
   }
  }
  if(maxPriority < q->priority && q->process != finish)
  {
   maxPriority = q->priority;
   t = q;
  }
  q = q->next; //ָ����һ������
 }
 if(t->needTime != 0)//���q������ʱ�䲻Ϊ0
 {
  t->priority -= 3;//���ȼ�=���ȼ�-3
  t->needTime--;//����ʱ��-1
  t->process = execute;//��������
  t->cpuTime++; //cupִ��ʱ��+1
 }
}
//ѡ��ĳһ���̣���������CPU
//����������ȼ�

void priorityCal(void)  //����������
{
 struct pcb* p = NULL;
 system("cls");
 p = getProcess();
 int cpu = 0;
 system("cls");
 while(!processFinish(p))
 {
  cpu++;
  printf("cpuTime:%d\n",cpu);//���cpu����ʱ��
  couExe(p);
  display(p);
  Sleep(2);
  //system("cls");
  //clrscr();
 }

 printf("���н����Ѿ�ִ����ϣ���������˳���");
 getchar();
}

void displayMenu(void)
{
 printf("��ѡ��һ���㷨:\n\n");
 printf("1 ��̬���ȼ��㷨\n\n");
 printf("2 ʱ��Ƭ��ת�㷨\n\n");
 printf("3 �˳�\n\n");
}//��ʾ�����㷨�˵����ɹ��û�ѡ������Ȩ�����㷨��ʱ��Ƭ��ת�����㷨

struct pcb* getProcessRound()
{
 struct pcb* q = NULL;
 struct pcb* t = NULL;
 struct pcb* p = NULL;
 int i = 0;
 printf("������������ƺͽ�������ʱ�䣺\n");
 while(i < RNUM) //5�����̽�����ת
 {
  q = (struct pcb* )malloc(sizeof(struct pcb)); //����ռ�
  scanf("%s", &(q->name));//���������
  scanf("%d", &(q->needTime));//�������ִ������ʱ��
  q->cpuTime = 0;
  q->priority = PTIME - (q->needTime);
  q->process = ready; //�ý��̴��ھ���״̬
  q->round = 0;
  q->count = 0;
  q->next = NULL;
  if(i == 0)
  {
   p = q;
   t = q;
  }
  else
  {
   t->next = q;
   t = q;
  }
  i++;
 }
 return p;

}//ʱ��Ƭ��ת�����㷨�����������̶���

void cpuRound(struct pcb* q)
{
 q->cpuTime += 2;
 q->needTime -= 2;

 if(q->needTime < 0)
 {
  q->needTime = 0;
 }
 q->count++;
 q->round++;
 q->process = execute; //���̽���ִ��״̬
}//����ʱ��Ƭ��ת�����㷨ִ��ĳһ����

struct pcb* GetNext(struct pcb* k, struct pcb* head)
{
 struct pcb* t;
 t = k;
 do
 {
  t = t->next;
 }
 while(t && t->process == finish);
 if(t == NULL)
 {
  t = head;
  while(t->next != k && t->process == finish)
  {
   t = t->next;
  }
 }
 return t;

}//��ȡ��һ������

void setState(struct pcb* p)
{
 while(p)
 {
  if(p->needTime == 0)
  {
   p->process = finish;//�������ִ��ʱ��Ϊ0������������״̬Ϊ��|
  }
  if(p->process == execute)
  {
   p->process = ready;//���Ϊִ��״̬������Ϊ����
  }
  p = p->next;
 }
}//���ö����н���ִ��״̬

void displayRound(struct pcb* p)
{
 printf("��������\t��������ʱ��\t��������ʱ��\t����ִ�д���\t��ת����\t״̬\n");
 while(p)
 {
  printf("%s\t\t",p->name);
  printf("      ");
  printf("%d\t\t",p->cpuTime);
  printf("      ");
  printf("%d\t\t",p->needTime);
  printf("      ");
  printf("%d\t\t",p->count);
  printf("      ");
  printf("%d\t  ",p->round);
  printf("      ");
  switch(p->process)
  {
   case ready:
    printf("����\n");
    break;
   case execute:
    printf("ִ��\n");
    break;
   case finish:
    printf("���\n");
    break;
  }
  p = p->next; //������һ������
 }
}//ʱ��Ƭ��ת�����㷨���������Ϣ

void roundCal() //ѭ����ת����
{
 struct pcb* p;
 struct pcb* r;
 p = getProcessRound();
 int cpu = 0;
  r = p;
 while(!processFinish(p))
 {
  cpu += 2;
  cpuRound(r);
  r = GetNext(r, p);
  printf("cpu %d\n", cpu);
  displayRound(p);
  setState(p);
  Sleep(5);
 }
}//ʱ��Ƭ��ת�����㷨�����ִμ����������Ϣ

int main()
{
 displayMenu();
 int userInput = 0;
 scanf("%d", &userInput);
 switch(userInput)
 {
  case 1:
   priorityCal();
   break;
  case 2:
   roundCal();
   break;
  case 3:
   break;
  displayMenu();
  scanf("%d", &userInput);
 }
}


