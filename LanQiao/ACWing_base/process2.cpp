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
#define RNUM 5 //5个进程，可改变
#define PTIME 50 //优先级初始值

enum state //枚举类型
{
 ready, //就绪
 execute, //执行
 block, //阻塞
 finish //完成
};//定义进程状态

struct pcb //进程控制块数据结构
{
 char name [4];//进程名
 int priority;//优先权
 int cpuTime;//CPU运行时间
 int needTime;//进程运行所需时间
 int count;//进程执行次数
 int round;//时间片轮转轮次
 enum state process;//进程状态
 struct pcb* next; //链表指针
};//定义进程PCB

struct pcb* getProcess()
{
 struct pcb* q = NULL;
 struct pcb* t = NULL;
 struct pcb* p = NULL;
 int  i = 0;
 printf("请输入进程的名称和运行时间！\n");
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
   t->next = q;//创建就绪进程队列
   t = q;
     }
  i++;
 }
  return p;

}//输入模拟测试的进程名和执行所需时间，初始设置可模拟5个进程的调度

void display(struct pcb* p)
{
 printf("名称\t进程运行时间\t进程所需时间\t\t优先级\t\t状态\n");
 while(p)
 {
  printf("%s\t", p->name);  //输出进程名
  printf("        ");
  printf("%d\t", p->cpuTime); //输出cpu执行时间
  printf("        ");
  printf("%d\t", p->needTime);//输出进程执行所需时间
  printf("        ");
  printf("%d\t", p->priority);//输出优先级
  printf("         ");
  switch(p->process)//输出进程状态
  {
   case ready:
    printf("就绪\n");
    break;
   case execute:
    printf("执行\n");
    break;
   case block:
    printf("阻塞\n");
    break;
   case finish:
    printf("完成\n");
    break;
   default:
    break;
  }
  p = p->next;//指向下一个进程
 }//显示模拟结果，包含进程名、CPU时间、运行所需时间以及优先级
}

int processFinish(struct pcb* q)//进程是否结束，当还有进程没有结束时返回0
{
 int bl = 1;
 while(bl && q)
 {
  bl = bl && (q->needTime == 0);
  q = q->next;
 }
 return bl;

}//结束进程，即将队列中各进程的所需时间设置为0

void couExe(struct pcb* q)
{
 struct pcb* t = q;
 int maxPriority = 0; //设最大优先级为0
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
  q = q->next; //指向下一个进程
 }
 if(t->needTime != 0)//如果q的所需时间不为0
 {
  t->priority -= 3;//优先级=优先级-3
  t->needTime--;//所需时间-1
  t->process = execute;//进程阻塞
  t->cpuTime++; //cup执行时间+1
 }
}
//选择某一进程，给它分配CPU
//计算进程优先级

void priorityCal(void)  //优先数调度
{
 struct pcb* p = NULL;
 system("cls");
 p = getProcess();
 int cpu = 0;
 system("cls");
 while(!processFinish(p))
 {
  cpu++;
  printf("cpuTime:%d\n",cpu);//输出cpu运行时间
  couExe(p);
  display(p);
  Sleep(2);
  //system("cls");
  //clrscr();
 }

 printf("所有进程已经执行完毕，按任意键退出！");
 getchar();
}

void displayMenu(void)
{
 printf("请选择一个算法:\n\n");
 printf("1 动态优先级算法\n\n");
 printf("2 时间片轮转算法\n\n");
 printf("3 退出\n\n");
}//显示调度算法菜单，可供用户选择优先权调度算法和时间片轮转调度算法

struct pcb* getProcessRound()
{
 struct pcb* q = NULL;
 struct pcb* t = NULL;
 struct pcb* p = NULL;
 int i = 0;
 printf("请输入进程名称和进程运行时间：\n");
 while(i < RNUM) //5个进程进行轮转
 {
  q = (struct pcb* )malloc(sizeof(struct pcb)); //分配空间
  scanf("%s", &(q->name));//输入进程名
  scanf("%d", &(q->needTime));//输入进程执行所需时间
  q->cpuTime = 0;
  q->priority = PTIME - (q->needTime);
  q->process = ready; //让进程处于就绪状态
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

}//时间片轮转调度算法创建就绪进程队列

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
 q->process = execute; //进程进入执行状态
}//采用时间片轮转调度算法执行某一进程

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

}//获取下一个进程

void setState(struct pcb* p)
{
 while(p)
 {
  if(p->needTime == 0)
  {
   p->process = finish;//如果所需执行时间为0，则设置运行状态为结東
  }
  if(p->process == execute)
  {
   p->process = ready;//如果为执行状态则设置为就绪
  }
  p = p->next;
 }
}//设置队列中进程执行状态

void displayRound(struct pcb* p)
{
 printf("进程名称\t进程运行时间\t进程所需时间\t进程执行次数\t轮转次数\t状态\n");
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
    printf("就绪\n");
    break;
   case execute:
    printf("执行\n");
    break;
   case finish:
    printf("完成\n");
    break;
  }
  p = p->next; //跳向下一个进程
 }
}//时间片轮转调度算法输出调度信息

void roundCal() //循环轮转调度
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
}//时间片轮转调度算法计算轮次及输出调度信息

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


