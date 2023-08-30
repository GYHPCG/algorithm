#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<algorithm>

using namespace std;
#define N 20                            //进程数
#define WFA wait_for_arrival            //进程还未到——所有非零时刻到达的进程执行前的初始状态
#define Ready ready_state               //进程到达后处于就绪状态，等待CPU资源
#define Running running_state           //进程处于运行态
#define Finish end_of_execution         //进程执行结束
///数据结构——通用的进程控制块PCB
struct PCB
{
    char process_name;                  //进程名
    double arrival_time;                //进程到达时间
    double service_time;                //进程要求服务时间
    double start_time;                  //进程开始执行时间
    double need_service_time;           //进程还需占用CPU时间
    double end_time;                    //进程执行完成时间
    double process_priority;            //进程优先级
    double turnaround_time;             //进程周转时间
    double weight_turnaround_time;      //进程带权周转时间
    string status;                      //进程状态
};

PCB pcb[N];                             //每个进程维护一个进程控制块
vector<PCB> pcbList;                    //pcbList向量
queue<PCB>Ready;                        //就绪队列
double average_TT;                      //平均周转时间
double average_WTT;                     //平均带权周转时间
int n;                                  //进程数
int flag = 0;
int time_unit;                          //时间片长度

///在HRRN中所使用的结构体
struct Hrrn{
    float value;
    int id;
};
Hrrn hrrn[N];
///函数定义：
void Select_menu();                      //选择菜单初始化
void Init_process();                     //进程初始化
bool cmp_name(PCB a, PCB b);             //按进程名排序，按序输出
bool cmp_time(PCB a, PCB b);             //按进程到达时间排序
bool cmp_service_time(PCB a, PCB b);     //按服务时间长短排序
bool cmp_process_priority(PCB a, PCB b); //按优先级大小排序
bool cmp_hrrn(Hrrn a, Hrrn b);           //浮点数排序
void FCFS();                             //先来先服务调度算法
void SPF();                              //短进程优先调度算法
void HPF();                              //HPF优先级调度算法
void RR();                               //RR时间片轮转算法
void Status_Output(PCB O_PCB[]);         //SPF输出中间状态
void HRRN();                             //高响应比优先调度算法
void Print(PCB Tmp_pcb[]);               //格式化输出
void Prio_Print(PCB Tmp_pcb[]);          //带优先级格式化输出
void Result_Print(PCB Tmp_pcb[]);        //最终结果打印（各进程的完成时间，各进程的周转时间及带权周转时间）
void RR_Print(PCB Tmp_pcb[],vector<pair<char,int> > solve);  //输出打印RR算法的相关内容，包括中间状态
bool All_finished(PCB pd_pcb[]);         //判断是不是所有进程都已经执行结束，作为循环的判断条件（状态输出的时间优化）

/************************************
主函数：main()
*************************************/
int main()
{
    Init_process();    //进程初始化
    while(1)
    {
        char YorN = 'Y';
        cout<<"请问是否要执行对进程的调度？（格式：Y or N）请输入：";
        cin>>YorN;
        if(YorN == 'N')
        {
            cout<<"执行结束，系统已退出！"<<endl;
            break;
        }
        else if(YorN == 'Y')
        {
            cout << endl;
            Select_menu();     //调度算法选择菜单
            cout << endl;
            int choice;
            cout << endl<<"请输入所选调度算法的序号：";
            cin >> choice;
            switch (choice)
            {
                case 1: FCFS();
                    break;
                case 2: SPF();
                    break;
                case 3: RR();
                    break;
                case 4: HPF();
                    break;
                case 5: HRRN();
                    break;
                default :
                    cout<<"请您按要求输入合法序号！"<<endl;
            }
        }
        else cout<<"请您按要求输入合法字符！"<<endl<<endl;     //防止出现非法字符的输入
    }
    return 0;
}

/************************************
函数名称：Select_menu()
函数功能：初始化
返回值：无
*************************************/
void Select_menu()
{
    string str_FCFS = "1.先来先服务算法(FCFS)";
    string str_SPF = "2.短进程优先算法(SPF)(非抢占式)";
    string str_RR = "3.时间片轮转算法(RR)";
    string str_HPF = "4.优先级调度算法(HPF)(非抢占式)";
    string str_HRRN = "5.高响应比优先调度算法(HRRN)(非抢占式)";

    for(int i = 0; i < 60; i++) cout<<"*";
    cout<<endl;
    cout<<"*\t\t"<<str_FCFS;
    for(int i = 0; i < 43 - str_FCFS.length(); i++) cout<<" ";
    cout<<"*"<<endl;
    cout<<"*\t\t"<<str_SPF;
    for(int i = 0; i < 43 - str_SPF.length(); i++)  cout<<" ";
    cout<<"*"<<endl;
    cout<<"*\t\t"<<str_RR;
    for(int i = 0; i < 43 - str_RR.length(); i++)   cout<<" ";
    cout<<"*"<<endl;
    cout<<"*\t\t"<<str_HPF;
    for(int i = 0; i < 43 - str_HPF.length(); i++)  cout<<" ";
    cout<<"*"<<endl;
    cout<<"*\t\t"<<str_HRRN;
    for(int i = 0; i < 43 - str_HRRN.length(); i++) cout<<" ";
    cout<<"*"<<endl;
    for(int i = 0; i < 60; i++) cout<<"*";
}

/************************************
函数名称：Init_process()
函数功能：进程初始化
返回值：无
*************************************/
void Init_process()
{
    cout<<"******************************您好！欢迎使用本系统！******************************"<<endl;
    cout<<"#请注意：该系统中的进程调度算法可以输出各关键时间节点的所有进程状态，目前支持整数#"<<endl;
    cout<<"**********************************************************************************"<<endl<<endl;
    cout<<"请输入进程数：";
    cin>>n;
    cout<<"请依次输入 进程名 到达时间 服务时间(如：A 0 3)"<<endl;
    for(int i = 0; i < n; i++)
    {
        char p_name;             //进程名
        double p_arrive,p_service; //进程到达时间 服务时间
        cin>>p_name>>p_arrive>>p_service;
        pcb[i].process_name = p_name;
        pcb[i].arrival_time = p_arrive;
        pcb[i].service_time = p_service;
        if(!p_arrive) pcb[i].status = "Ready";
        else pcb[i].status = "WFA";
    }
}

/************************************
函数名称：cmp_name(PCB a, PCB b)
函数功能：按进程名排序，按序输出
返回值：无
*************************************/
bool cmp_name(PCB a, PCB b)
{
    return a.process_name < b.process_name;
}

/************************************
函数名称：Print(PCB Tmp_pcb[])
函数功能：格式化输出
返回值：无
*************************************/
void Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 124; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"进程名"<<setw(14)<<"到达时间"<<setw(13)<<"服务时间"<<setw(12)<<"开始时间"<<setw(11)<<"需CPU时间"
    <<setw(9)<<"结束时间"<<setw(12)<<"周转时间"<<setw(20)<<"带权周转时间"<<setw(13)<<" "<<"进程状态"<<" *"<<endl;
    cout<<"*"<<"Process_name"<<setw(13)<<"Arrival_time"<<setw(13)<<"Service_time"<<setw(11)<<"Start_time"<<setw(10)<<"Need_time"
    <<setw(9)<<"End_time"<<setw(16)<<"Turnaround_time"<<setw(23)<<"Weight_turnaround_time"<<setw(7)<<" "<<"Status"<<"  *"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<"*"<<setw(6)<<cp_pcb[i].process_name<<setw(14)<<cp_pcb[i].arrival_time<<setw(12)<<cp_pcb[i].service_time
        <<setw(12)<<cp_pcb[i].start_time<<setw(11)<<cp_pcb[i].need_service_time<<setw(9)<<cp_pcb[i].end_time<<setw(12)
        <<cp_pcb[i].turnaround_time<<setw(4)<<" "<<"\t\t"<<cp_pcb[i].weight_turnaround_time<<setw(8)<<"\t"<<" "<<" "<<" "<<cp_pcb[i].status;
        for(int j = 0; j < 8 - cp_pcb[i].status.length(); j++)  cout<<" ";
        cout<<"*"<<endl;
    }
    for(int i = 0; i < 124; i++) cout<<"*";
    cout<<endl;
}

/************************************
函数名称：Prio_Print(PCB Tmp_pcb[])
函数功能：带优先级格式化输出
返回值：无
*************************************/
void Prio_Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 132; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"进程名"<<setw(14)<<"到达时间"<<setw(13)<<"服务时间"<<setw(11)<<"优先权"<<setw(11)<<"开始时间"<<setw(11)<<"需CPU时间"
    <<setw(9)<<"结束时间"<<setw(12)<<"周转时间"<<setw(20)<<"带权周转时间"<<setw(11)<<" "<<"进程状态"<<" *"<<endl;
    cout<<"*"<<"Process_name"<<setw(13)<<"Arrival_time"<<setw(13)<<"Service_time"<<setw(10)<<"Priority"<<setw(11)<<"Start_time"<<setw(10)<<"Need_time"
    <<setw(9)<<"End_time"<<setw(16)<<"Turnaround_time"<<setw(23)<<"Weight_turnaround_time"<<setw(5)<<" "<<"Status"<<"  *"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<"*"<<setw(6)<<cp_pcb[i].process_name<<setw(14)<<cp_pcb[i].arrival_time<<setw(12)<<cp_pcb[i].service_time
        <<setw(12)<<cp_pcb[i].process_priority<<setw(12)<<cp_pcb[i].start_time<<setw(11)<<cp_pcb[i].need_service_time<<setw(9)<<cp_pcb[i].end_time<<setw(12)
        <<cp_pcb[i].turnaround_time<<setw(4)<<" "<<"\t\t"<<cp_pcb[i].weight_turnaround_time<<setw(8)<<"\t"<<" "<<" "<<" "<<cp_pcb[i].status;
        for(int j = 0; j < 8 - cp_pcb[i].status.length(); j++)  cout<<" ";
        cout<<"*"<<endl;
    }
    for(int i = 0; i < 132; i++) cout<<"*";
    cout<<endl;
}

/************************************
函数名称：Print(PCB Tmp_pcb[])
函数功能：格式化输出
返回值：无
*************************************/
void Result_Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 100; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"进程名"<<setw(14)<<"到达时间"<<setw(13)<<"服务时间"<<setw(12)<<"开始时间"
    <<setw(9)<<"结束时间"<<setw(12)<<"周转时间"<<setw(20)<<"带权周转时间"<<"\t   *"<<endl;
    cout<<"*"<<"Process_name"<<setw(13)<<"Arrival_time"<<setw(13)<<"Service_time"<<setw(11)<<"Start_time"
    <<setw(9)<<"End_time"<<setw(16)<<"Turnaround_time"<<setw(23)<<"Weight_turnaround_time"<<" *"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<"*"<<setw(6)<<cp_pcb[i].process_name<<setw(14)<<cp_pcb[i].arrival_time<<setw(12)<<cp_pcb[i].service_time
        <<setw(12)<<cp_pcb[i].start_time<<setw(9)<<cp_pcb[i].end_time<<setw(12)
        <<cp_pcb[i].turnaround_time<<setw(4)<<" "<<"\t\t"<<cp_pcb[i].weight_turnaround_time<<setw(8)<<"\t"<<" "<<" "<<" ";
        cout<<"*"<<endl;
    }
    for(int i = 0; i < 100; i++) cout<<"*";
    cout<<endl;
}

/************************************
函数名称：bool All_finished(PCB pd_pcb[]);
函数功能：判断是不是所有进程都已经
执行结束，作为循环的判断条件（状态
输出的时间优化）
返回值：true or false
*************************************/
bool All_finished(PCB pd_pcb[])
{
    int t=0;
    for(int i = 0; i < n; i++)
    {
        if(pd_pcb[i].status == "Finish")
            t++;   //继续循环执行
    }
    if(t==n)  return false;
    else return true;
}

/************************************
函数名称：cmp_time(PCB a, PCB b)
函数功能：按进程到达时间排序
返回值：无
*************************************/
bool cmp_time(PCB a, PCB b)
{
    return a.arrival_time < b.arrival_time;
}

/************************************
函数名称：FCFS()
函数功能：先来先服务调度算法
返回值：无
*************************************/
void FCFS()
{
    PCB FCFS_pcb[N];
    for(int i=0; i < n; i++)
        FCFS_pcb[i] = pcb[i];
    sort(FCFS_pcb,FCFS_pcb+n,cmp_time);          //按到达时间排序
    for(int excute_time = FCFS_pcb[0].arrival_time; All_finished(FCFS_pcb); excute_time++)    //按总时间遍历 输出中间状态
    {
        for (int i = 0; i < n; i++)                                              //遍历进程
        {
            if(FCFS_pcb[i].arrival_time == excute_time && !flag)
            {
                FCFS_pcb[i].start_time = excute_time;                            //当前CPU空闲，且进程已到达，从当前时间开始执行
                FCFS_pcb[i].end_time = excute_time + FCFS_pcb[i].service_time;   //修改该进程的结束时间 = 当前时间 + 服务时间
                FCFS_pcb[i].status = "Running";                                  //修改进程状态 为 Running
                FCFS_pcb[i].need_service_time = FCFS_pcb[i].service_time;
                flag = 1;                                                        //当前CPU已被占用
                cout << "T = "<<excute_time<<":"<<endl;
                Print(FCFS_pcb);
                for(int j = i; j < n; j++)                                        //其他有在当前时刻到达的进程置为Ready
                {
                    if(FCFS_pcb[j].arrival_time <= excute_time && FCFS_pcb[j].status == "WFA")
                        FCFS_pcb[j].status = "Ready";
                }
                cout<<endl;
                break;
            }
            else if(FCFS_pcb[i].arrival_time == excute_time && flag && FCFS_pcb[i].status == "WFA")
            {
                FCFS_pcb[i].status = "Ready";             //某进程到达，但是CPU被占用着，该进程状态为 Ready
                for(int j = 0; j < i; j++)                //修改当前进程之前进程的状态
                {
                    if(FCFS_pcb[j].status == "Running")   //找到状态为Running的进程——一定只有一个
                    {
                        FCFS_pcb[j].need_service_time = FCFS_pcb[j].end_time - excute_time;
                        //结束时间 - 当前时间 = 进程仍需CPU的时间
                        break;
                    }
                }
                cout << "T = "<<excute_time<<":"<<endl;
                Print(FCFS_pcb);
                for(int j = i; j < n; j++)                                        //其他有在当前时刻到达的进程置为Ready
                {
                    if(FCFS_pcb[j].arrival_time <= excute_time && FCFS_pcb[j].status == "WFA")
                        FCFS_pcb[j].status = "Ready";
                }
                cout<<endl;
                break;
            }
            else if(FCFS_pcb[i].end_time == excute_time && FCFS_pcb[i].status == "Running")    //某进程当前时刻执行完毕
            {
                FCFS_pcb[i].status = "Finish";           //某进程执行完毕
                flag = 0;                                //CPU空闲
                FCFS_pcb[i].need_service_time = 0;       //不再需要CPU
                FCFS_pcb[i].turnaround_time = excute_time - FCFS_pcb[i].arrival_time;
                //周转时间 = 当前时间 - 到达时间
                FCFS_pcb[i].weight_turnaround_time = 1.0 * (FCFS_pcb[i].turnaround_time)/(FCFS_pcb[i].service_time);
                //带权周转时间 = 周转时间 / 服务时间
                FCFS_pcb[i].weight_turnaround_time = ((int)((FCFS_pcb[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //保留两位小数——四舍五入
                for(int j = i; j < n; j++)                //如果当前进程执行结束时，下一进程刚好到达，状态位需进行修改
                {
                    if(FCFS_pcb[j].arrival_time == FCFS_pcb[i].end_time)
                    {
                        FCFS_pcb[j].status = "Ready";
                    }
                }
                for(int j = i; j < n; j++)                                               //找第一个ready进程
                {
                    if(FCFS_pcb[j].status == "Ready")
                    {
                        flag = 1;
                        FCFS_pcb[j].start_time = excute_time;                            //开始时间等于当前时间
                        FCFS_pcb[j].end_time = excute_time + FCFS_pcb[j].service_time;   //进程的结束时间 = 当前时间 + 服务时间
                        FCFS_pcb[j].status = "Running";                                  //修改进程状态 为 Running
                        FCFS_pcb[j].need_service_time = FCFS_pcb[j].service_time;
                        break;
                    }
                }
                cout << "T = "<<excute_time<<":"<<endl;
                Print(FCFS_pcb);
                cout<<endl;
                break;
            }
        }
    }
    cout<<endl<<"各进程的执行顺序为："<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<FCFS_pcb[i].process_name<<", ";
    cout<<FCFS_pcb[n-1].process_name<<"}"<<endl;
    cout<<endl<<"最终结果打印："<<endl;
    Result_Print(FCFS_pcb);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += FCFS_pcb[i].turnaround_time;
        average_WTT += FCFS_pcb[i].weight_turnaround_time;
    }
    cout<<"平均周转时间 = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"平均带权周转时间 = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
函数名称：Status_Output(PCB O_PCB[])
函数功能：输出中间状态
SPF输出中间状态
故封装成函数调用
返回值：无
*************************************/
void Status_Output(PCB O_PCB[])
{
    PCB Res_PCB[N];
    int t = 0;
    int excute_time = O_PCB[0].arrival_time;
    flag = 0;
    for(int i = 0; i < n; i++)                //找 所有进程中 最早到达的进程时间 即为 系统的初始时间
    {
        excute_time = excute_time > O_PCB[i].arrival_time ? O_PCB[i].arrival_time : excute_time;
    }
    for(; All_finished(O_PCB); excute_time++)             //按总时间遍历 输出中间状态
    {
        for (int i = 0; i < n; i++)                             //遍历进程
        {
            if(O_PCB[i].arrival_time == excute_time && !flag)   //先到的进程若CPU空闲则先执行，就绪队列中有其他进程排队时，选择服务时间短的进程
            {
                for(int j = i; j < n; j++)                                             //同时间到达的，均修改状态
                {
                    if(O_PCB[j].arrival_time <= excute_time && O_PCB[j].status == "WFA")
                        O_PCB[j].status = "Ready";
                }
                for(int j = 0; j <= i; j++)                                            //同时间到达的，先选服务时间短的
                {
                    if(O_PCB[j].status == "Ready")
                    {
                        O_PCB[j].start_time = excute_time;                             //当前CPU空闲，到达的进程执行
                        O_PCB[j].end_time = excute_time + O_PCB[j].service_time;       //非抢占式，故该进程结束时间= 当前时间 + 服务时间
                        O_PCB[j].need_service_time = O_PCB[j].service_time;            //仍需要占用CPU的时间
                        O_PCB[j].status = "Running";                                   //修改当前进程的状态为Running
                        Res_PCB[t++] = O_PCB[j];
                        flag = 1;
                        break;
                    }
                }
                cout<<"T = " <<excute_time<<":"<<endl;
                Print(O_PCB);
                cout<<endl;
                break;
            }
            else if(O_PCB[i].arrival_time == excute_time && flag && O_PCB[i].status == "WFA")   //某进程结束，当前进程到达
            {
                int mark = 0;
                O_PCB[i].status = "Ready";                //某进程到达，但CPU被占用着，该状态为Ready
                if(mark == 0)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(O_PCB[j].status == "Running" && O_PCB[j].end_time == excute_time)    //找到正在执行的进程，有且只有一个,这个进程刚好结束
                        {
                            O_PCB[j].status = "Finish";       //某进程执行完毕
                            flag = 0;
                            O_PCB[j].need_service_time = 0;   //不再需要CPU资源
                            O_PCB[j].turnaround_time = excute_time - O_PCB[j].arrival_time;     //周转时间 = 当前时间 - 到达时间
                            O_PCB[j].weight_turnaround_time = 1.0 * (O_PCB[j].turnaround_time)/(O_PCB[j].service_time);   //带权周转时间 = 周转时间 / 服务时间
                            O_PCB[j].weight_turnaround_time = ((int)((O_PCB[j].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                            for(int m = i; m < n; m++)         //如果当前进程执行结束时，下一进程刚好到达，状态位需进行修改
                            {
                                if(O_PCB[m].arrival_time == O_PCB[j].end_time && O_PCB[j].status=="WFA")
                                {
                                    O_PCB[m].status = "Ready";
                                }
                            }
                            for(int k = 0; k < n; k++)                                             //找第一个ready进程
                            {
                                if(O_PCB[k].status == "Ready")
                                {
                                    flag = 1;
                                    O_PCB[k].start_time = excute_time;                           //开始时间等于当前时间
                                    O_PCB[k].end_time = excute_time + O_PCB[k].service_time;   //进程的结束时间 = 当前时间 + 服务时间
                                    O_PCB[k].status = "Running";                                 //修改进程状态 为 Running
                                    Res_PCB[t++] = O_PCB[k];
                                    O_PCB[k].need_service_time = O_PCB[k].service_time;
                                    break;
                                }
                            }
                            mark = 1;
                        }
                        else if(O_PCB[j].status == "Running" && O_PCB[j].end_time!=excute_time) //找到正在执行的进程，有且只有一个，正在执行
                        {
                            O_PCB[j].need_service_time = O_PCB[j].end_time - excute_time;       //结束时间 - 当前时间 = 进程仍需CPU时间
                            mark = 1;
                            for(int m = i; m < n; m++)         //若有其他进程也在当前时刻到达，状态位需进行修改
                            {
                                if(O_PCB[m].arrival_time <= O_PCB[i].arrival_time && O_PCB[m].status=="WFA")
                                {
                                    O_PCB[m].status = "Ready";
                                }
                            }
                        }
                        if(mark) break;        //有且只能有一个Running进程，遍历到之后就不需要再遍历了，直接break
                    }  //for
                }  //if mark == 0;
                cout<<"T = " <<excute_time<<":"<<endl;
                Print(O_PCB);
                cout<<endl;
                break;
            }
            else if(O_PCB[i].end_time == excute_time && O_PCB[i].status == "Running")   //某进程执行结束
            {
                O_PCB[i].status = "Finish";         //某进程执行完毕
                flag = 0;
                O_PCB[i].need_service_time = 0;     //不再需要CPU资源
                O_PCB[i].turnaround_time = excute_time - O_PCB[i].arrival_time;
                //周转时间 = 当前时间 - 到达时间
                O_PCB[i].weight_turnaround_time = 1.0 * (O_PCB[i].turnaround_time)/(O_PCB[i].service_time);
                //带权周转时间 = 周转时间 / 服务时间
                O_PCB[i].weight_turnaround_time = ((int)((O_PCB[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //保留两位小数——四舍五入
                for(int j = 0; j < n; j++)          //如果当前进程执行结束时，下一进程刚好到达，状态位需进行修改
                {
                    if(O_PCB[j].arrival_time <= O_PCB[i].end_time && O_PCB[j].status=="WFA")
                    {
                        O_PCB[j].status = "Ready";
                    }
                }
                for(int j = 0; j < n; j++)                                         //找第一个ready进程
                {
                    if(O_PCB[j].status == "Ready")
                    {
                        flag = 1;
                        O_PCB[j].start_time = excute_time;                         //开始时间等于当前时间
                        O_PCB[j].end_time = excute_time + O_PCB[j].service_time;   //进程的结束时间 = 当前时间 + 服务时间
                        O_PCB[j].status = "Running";                               //修改进程状态 为 Running
                        Res_PCB[t++] = O_PCB[j];
                        O_PCB[j].need_service_time = O_PCB[j].service_time;
                        break;
                    }
                }
                cout << "T = "<<excute_time<<":"<<endl;
                Print(O_PCB);
                cout<<endl;
                break;
            }
        }
    }
    cout<<endl<<"各进程的执行顺序为："<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<Res_PCB[i].process_name<<", ";
    cout<<Res_PCB[n-1].process_name<<"}"<<endl;
    cout<<endl<<"最终结果打印："<<endl;
    Result_Print(O_PCB);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += O_PCB[i].turnaround_time;
        average_WTT += O_PCB[i].weight_turnaround_time;
    }
    cout<<"平均周转时间 = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"平均带权周转时间 = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
函数名称：cmp_service_time(PCB a, PCB b)
函数功能：按服务时间长短排序
返回值：无
*************************************/
bool cmp_service_time(PCB a, PCB b)
{
    if(a.arrival_time != b.arrival_time)
        return a.service_time < b.service_time;
    else return a.arrival_time < b.arrival_time;
}

/************************************
函数名称：SPF()
函数功能：短进程优先调度算法
返回值：无
*************************************/
void SPF()
{
    PCB SPF_pcb[N];
    for(int i=0; i < n; i++)
        SPF_pcb[i] = pcb[i];
    sort(SPF_pcb,SPF_pcb+n,cmp_service_time);    //按服务时间长短排序
    Status_Output(SPF_pcb);
}

/************************************
函数名称：cmp_process_priority(PCB a, PCB b)
函数功能：按优先级大小排序
（注：优先级数值越大，优先级越高）
返回值：无
*************************************/
bool cmp_process_priority(PCB a, PCB b)
{
    if(a.arrival_time != b.arrival_time)
        return a.process_priority > b.process_priority;
    else return a.arrival_time < b.arrival_time;
}

/************************************
函数名称：HPF()
函数功能：HPF优先级调度算法
返回值：无
*************************************/
void HPF()
{
    PCB HPF_pcb[N];
    PCB Res_PCB[N];
    int t = 0;
    for(int i = 0; i < n; i++)
        HPF_pcb[i] = pcb[i];
    cout<<"请您依次输入代表进程{";
    for(int i = 0; i < n-1; i++)
        cout<<HPF_pcb[i].process_name<<" ";
    cout<<HPF_pcb[n-1].process_name<<"}的优先级的数值:(数值越大，优先级越高，输入用空格隔开即可)"<<endl;
    for(int i = 0; i < n; i++)
        cin>>HPF_pcb[i].process_priority;
    sort(HPF_pcb,HPF_pcb+n,cmp_process_priority);                 //按优先级大小排序
    //for(int i = 0; i < n; i++)
    //    cout<<HPF_pcb[i].process_name << " "<<HPF_pcb[i].arrival_time<<" "<<HPF_pcb[i].service_time<<" "<<HPF_pcb[i].process_priority<<endl;
    cout<<endl;
    int excute_time = HPF_pcb[0].arrival_time;
    flag = 0;
    for(int i = 0; i < n; i++)                                    //找 所有进程中 最早到达的进程时间 即为 系统的初始时间
    {
        excute_time = excute_time > HPF_pcb[i].arrival_time ? HPF_pcb[i].arrival_time : excute_time;
    }
    for(; All_finished(HPF_pcb); excute_time++)               //按总时间遍历 输出中间状态
    {
        for (int i = 0; i < n; i++)                               //遍历进程
        {
            if(HPF_pcb[i].arrival_time == excute_time && !flag)   //先到的进程若CPU空闲则先执行，就绪队列中有其他进程排队时，选择优先级高的进程
            {
                for(int j = 0; j < n; j++)                        //同时间到达的，均修改状态
                {
                    if(HPF_pcb[j].arrival_time <= excute_time && HPF_pcb[j].status == "WFA")
                        HPF_pcb[j].status = "Ready";
                }
                for(int j = 0; j <= i; j++)                                          //同时间到达的，先选优先级高的
                {
                    if(HPF_pcb[j].status == "Ready")
                    {
                        HPF_pcb[j].start_time = excute_time;                          //当前CPU空闲，到达的进程执行
                        HPF_pcb[j].end_time = excute_time + HPF_pcb[j].service_time;  //非抢占式，故该进程结束时间= 当前时间 + 服务时间
                        HPF_pcb[j].need_service_time = HPF_pcb[j].service_time;       //仍需要占用CPU的时间
                        HPF_pcb[j].status = "Running";                                //修改当前进程的状态为Running
                        Res_PCB[t++] = HPF_pcb[j];
                        flag = 1;
                        break;
                    }
                }
                cout<<"T = " <<excute_time<<":"<<endl;
                Prio_Print(HPF_pcb);
                cout<<endl;
                break;
            }
            else if(HPF_pcb[i].arrival_time == excute_time && flag && HPF_pcb[i].status == "WFA")   //某进程结束，当前进程到达
            {
                bool mark = 0;
                HPF_pcb[i].status = "Ready";                //某进程到达，但CPU被占用着，该状态为Ready
                for(int j = 0; j < n; j++)
                {
                    if(HPF_pcb[j].status == "Running" && HPF_pcb[j].end_time == excute_time)    //找到正在执行的进程，有且只有一个,这个进程刚好结束
                    {
                        HPF_pcb[j].status = "Finish";       //某进程执行完毕
                        flag = 0;
                        HPF_pcb[j].need_service_time = 0;   //不再需要CPU资源
                        HPF_pcb[j].turnaround_time = excute_time - HPF_pcb[j].arrival_time;     //周转时间 = 当前时间 - 到达时间
                        HPF_pcb[j].weight_turnaround_time = 1.0 * (HPF_pcb[j].turnaround_time)/(HPF_pcb[j].service_time);   //带权周转时间 = 周转时间 / 服务时间
                        HPF_pcb[j].weight_turnaround_time = ((int)((HPF_pcb[j].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                        for(int m = i; m < n; m++)         //若有其他进程也在当前时刻到达，状态位需进行修改
                        {
                            if(HPF_pcb[m].arrival_time <= HPF_pcb[j].end_time && HPF_pcb[j].status == "WFA")
                            {
                                HPF_pcb[m].status = "Ready";
                            }
                        }
                        for(int k = 0; k < n; k++)                                             //找第一个ready进程
                        {
                            if(HPF_pcb[k].status == "Ready")
                            {
                                flag = 1;
                                HPF_pcb[k].start_time = excute_time;                           //开始时间等于当前时间
                                HPF_pcb[k].end_time = excute_time + HPF_pcb[k].service_time;   //进程的结束时间 = 当前时间 + 服务时间
                                HPF_pcb[k].status = "Running";                                 //修改进程状态 为 Running
                                Res_PCB[t++] = HPF_pcb[k];
                                HPF_pcb[k].need_service_time = HPF_pcb[k].service_time;
                                break;
                            }
                        }
                        mark = 1;
                    }
                    else if(HPF_pcb[j].status == "Running" && HPF_pcb[j].end_time!=excute_time) //找到正在执行的进程，有且只有一个，正在执行
                    {
                        HPF_pcb[j].need_service_time = HPF_pcb[j].end_time - excute_time;       //结束时间 - 当前时间 = 进程仍需CPU时间
                        mark = 1;
                        for(int m = i; m < n; m++)
                        {
                            if(HPF_pcb[m].arrival_time <= excute_time && HPF_pcb[m].status == "WFA")
                            {
                                HPF_pcb[m].status = "Ready";
                            }
                        }
                    }
                    if(mark) break;
                }
                cout<<"T = " <<excute_time<<":"<<endl;
                Prio_Print(HPF_pcb);
                cout<<endl;
                break;
            }
            else if(HPF_pcb[i].end_time == excute_time && HPF_pcb[i].status == "Running")   //某进程执行结束
            {
                HPF_pcb[i].status = "Finish";        //某进程执行完毕
                flag = 0;
                HPF_pcb[i].need_service_time = 0;    //不再需要CPU资源
                HPF_pcb[i].turnaround_time = excute_time - HPF_pcb[i].arrival_time;
                //周转时间 = 当前时间 - 到达时间
                HPF_pcb[i].weight_turnaround_time = 1.0 * (HPF_pcb[i].turnaround_time)/(HPF_pcb[i].service_time);
                //带权周转时间 = 周转时间 / 服务时间
                HPF_pcb[i].weight_turnaround_time = ((int)((HPF_pcb[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //保留两位小数——四舍五入
                for(int j = i; j < n; j++)           //如果当前进程执行结束时，下一进程刚好到达，状态位需进行修改
                {
                    if(HPF_pcb[j].arrival_time == HPF_pcb[i].end_time && HPF_pcb[j].status == "WFA")
                    {
                        HPF_pcb[j].status = "Ready";
                    }
                }
                for(int j = 0; j < n; j++)                                             //找第一个ready进程
                {
                    if(HPF_pcb[j].status == "Ready")
                    {
                        flag = 1;
                        HPF_pcb[j].start_time = excute_time;                           //开始时间等于当前时间
                        HPF_pcb[j].end_time = excute_time + HPF_pcb[j].service_time;   //进程的结束时间 = 当前时间 + 服务时间
                        HPF_pcb[j].status = "Running";                                 //修改进程状态 为 Running
                        Res_PCB[t++] = HPF_pcb[j];
                        HPF_pcb[j].need_service_time = HPF_pcb[j].service_time;
                        break;
                    }
                }
                cout << "T = "<<excute_time<<":"<<endl;
                Prio_Print(HPF_pcb);
                cout<<endl;
                break;
            }
        }
    }
    cout<<endl<<"各进程的执行顺序为："<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<Res_PCB[i].process_name<<", ";
    cout<<Res_PCB[n-1].process_name<<"}"<<endl;
    cout<<endl<<"最终结果打印："<<endl;
    Result_Print(HPF_pcb);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += HPF_pcb[i].turnaround_time;
        average_WTT += HPF_pcb[i].weight_turnaround_time;
    }
    cout<<"平均周转时间 = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"平均带权周转时间 = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
函数名称：RR()
函数功能：时间片轮转调度算法
返回值：无
vector<PCB> pcbList;  //pcbList向量
queue<PCB>Ready       //就绪队列
*************************************/
void RR()
{
    PCB RR_pcb[N];
    int t=0;
    cout<<"请输入时间片大小：";
    cin>>time_unit;
    vector<pair<char,int> > solve;
	for(int i = 0; i < n; i++)
        RR_pcb[i] = pcb[i];
	for(int i=0;i<n;i++)
	{
		pcbList.push_back(pcb[i]);    //向量初始化
	}
	sort(RR_pcb,RR_pcb+n,cmp_time);   //按到达时间进行排序
	sort(pcbList.begin(),pcbList.end(),cmp_time);
	//for (int i = 0; i < n; i++)
    //    cout<<pcbList[i].process_name;
    //cout<<endl;
	int excute_time =(*pcbList.begin()).arrival_time;  //第一个进程开始时间
	Ready.push(*pcbList.begin());
	pcbList.erase(pcbList.begin());
    while(!pcbList.empty()||!Ready.empty())
    {
        while(!pcbList.empty()&&excute_time>=(*pcbList.begin()).arrival_time)//将新进程加入就绪队列
        {
            Ready.push(*pcbList.begin());
            pcbList.erase(pcbList.begin());
        }
		if(Ready.front().end_time + time_unit < Ready.front().service_time)//将时间片用完但没运行完的进程加入队尾
		{
            solve.push_back(pair<char,int>(Ready.front().process_name,time_unit));
			Ready.front().end_time += time_unit;
			excute_time += time_unit;
			while(!pcbList.empty()&& (*pcbList.begin()).arrival_time <= excute_time)    //未执行完，将其放入ready的末尾
            {
			 	Ready.push(*pcbList.begin());
        	    pcbList.erase(pcbList.begin());
		    }
			Ready.push(Ready.front());
			Ready.pop();
		}
		else      //进程执行完
        {
            int tmp_time_unit = time_unit;
			if(Ready.front().service_time - Ready.front().end_time<tmp_time_unit)
			{
				tmp_time_unit -= Ready.front().service_time - Ready.front().end_time;
			}
			solve.push_back(pair<char,int>(Ready.front().process_name,tmp_time_unit));   //存执行进程的信息
			excute_time += tmp_time_unit;
			Ready.front().end_time = excute_time;
			Ready.front().turnaround_time = Ready.front().end_time - Ready.front().arrival_time;
			Ready.front().weight_turnaround_time = (double)Ready.front().turnaround_time / Ready.front().service_time;
            for(int i = 0; i < n; i++)
            {
                if(RR_pcb[i].process_name == Ready.front().process_name)
                {
                    RR_pcb[i].turnaround_time = Ready.front().turnaround_time;
                    RR_pcb[i].weight_turnaround_time = Ready.front().weight_turnaround_time;
                    RR_pcb[i].end_time = RR_pcb[i].turnaround_time + RR_pcb[i].arrival_time;
                }
            }
			Ready.pop();
			if(Ready.empty() && !pcbList.empty())
            {
				excute_time = (*pcbList.begin()).arrival_time;
			}
		}
	}
    RR_Print(RR_pcb,solve);
}

/************************************
函数名称：RR_Print
(PCB Tmp_pcb[],vector<pair<char,int> > solve)
函数功能：RR算法的格式化输出
返回值：无
*************************************/
void RR_Print(PCB Tmp_pcb[],vector<pair<char,int> > solve)
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    int excute_time = Tmp_pcb[0].arrival_time;
    int total_time = Tmp_pcb[0].arrival_time;
    for(int i = 0; i < n; i++)
        total_time += Tmp_pcb[i].service_time;
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 62; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"进程名"<<setw(14)<<"到达时间"<<setw(13)<<"服务时间"<<setw(12)<<"执行时间"
    <<setw(11)<<"切换时间"<<" *"<<endl;
    cout<<"*"<<"Process_name"<<setw(13)<<"Arrival_time"<<setw(13)<<"Service_time"<<setw(11)<<"Start_time"
    <<setw(10)<<"Tran_time"<<" *"<<endl;
    vector<pair<char,int> >::iterator iter;
    int it = 1;
    for (iter = solve.begin();excute_time <= total_time && iter!=solve.end();)
    {
        for(int i = 0; i < n; i++)
        {
            if(cp_pcb[i].process_name == (*iter).first)
            {
                cout<<"*"<<setw(6)<<cp_pcb[i].process_name<<setw(14)<<cp_pcb[i].arrival_time<<setw(12)<<cp_pcb[i].service_time
                <<setw(12)<<excute_time<<setw(9)<<excute_time + (*iter).second<<setw(8)<<"*"<<endl;
                iter++;it++;
                excute_time = excute_time + (*iter).second;
            }
        }
    }

    for(int i = 0; i < 62; i++) cout<<"*";
    cout<<endl;
    cout<<endl<<"各进程的执行顺序为："<<endl;
    cout<<"{";
    for(iter = solve.begin(); iter != solve.end(); iter++)
    {
        cout<<(*iter).first;
        if(iter != solve.end()-1)
            cout<<", ";
    }
    cout<<"}"<<endl;

    cout<<endl<<"最终结果打印:"<<endl;
    for(int i = 0; i < 92; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"进程名"<<setw(14)<<"到达时间"<<setw(13)<<"服务时间"
    <<setw(11)<<"结束时间"<<setw(12)<<"周转时间"<<setw(20)<<"带权周转时间"<<"\t   *"<<endl;
    cout<<"*"<<"Process_name"<<setw(13)<<"Arrival_time"<<setw(13)<<"Service_time"
    <<setw(9)<<"End_time"<<setw(16)<<"Turnaround_time"<<setw(23)<<"Weight_turnaround_time"<<"    *"<<endl;
    for(int i = 0; i < n; i++)
    {
        cout<<"*"<<setw(6)<<cp_pcb[i].process_name<<setw(14)<<cp_pcb[i].arrival_time<<setw(12)<<cp_pcb[i].service_time
        <<setw(9)<<cp_pcb[i].end_time<<setw(12)
        <<cp_pcb[i].turnaround_time<<setw(4)<<" "<<"\t\t"<<cp_pcb[i].weight_turnaround_time<<setw(8)<<"\t"<<" "<<" "<<" ";
        cout<<"*"<<endl;
    }
    for(int i = 0; i < 92; i++) cout<<"*";
    cout<<endl;

    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += cp_pcb[i].turnaround_time;
        average_WTT += cp_pcb[i].weight_turnaround_time;
    }
    cout<<"平均周转时间 = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"平均带权周转时间 = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
函数名称：cmp_hrrn(Hrrn a, Hrrn b)
函数功能：浮点数排序
返回值：无

struct Hrrn{
    float value;
    int id;
};
Hrrn hrrn[N];
//该结构体中存的是 已经到达且没有执行
的所有进程的响应比的值与下标（按递减
排序，取响应比最大的进程执行）
*************************************/
bool cmp_hrrn(Hrrn a, Hrrn b)
{
    return a.value > b.value;
}

/************************************
函数名称：HRRN()
函数功能：高响应比优先调度算法
          （响应比高者优先）
返回值：无
响应比计算：ri = (Tw/Ts)+1
其中：Tw:等待时间；Ts:服务时间
*************************************/
void HRRN()
{
    PCB HRRN_pcb[N];
    bool vis[N] ={0};                            //标记数组，标记进程是不是被放进执行序列汇总
    int sequence[N] = {0},t=0;                   //存进程执行的序列下标 ——便于转化PCB结构体数组，得到正确的执行顺序
    for(int i = 0; i < n; i++)
        HRRN_pcb[i] = pcb[i];                    //备份PCB结构体数组
    sort(HRRN_pcb,HRRN_pcb+n,cmp_time);          //先对各进程按到达时间排序
    int excute_time = HRRN_pcb[0].arrival_time;
    int total_time = HRRN_pcb[0].arrival_time;   //第一个进程到达时间 + 所有进程的服务时间 = 总时间
    flag = 0;                                    //flag=0 表示CPU空闲
    for(int i = 0; i < n; i++)                   //计算总时间
    {
        total_time += HRRN_pcb[i].service_time;
        excute_time = excute_time > HRRN_pcb[i].arrival_time ? HRRN_pcb[i].arrival_time : excute_time;//开始时间（找最早到达的进程到达时间）
    }
    int Cutoftime = excute_time;                 //时间片切割（为了回溯遍历到达进程，以计算各进程响应比）
    for(; excute_time<=total_time; excute_time++)    //按总时间遍历 先确定执行顺序
    {
        if(excute_time == Cutoftime)             //时间切割
        {
            int obj = 0;
            memset(hrrn,0,sizeof(0));            //初始化动态变化的一维数组（存响应比）
            for(int i = 0; i < n; i++)
            {
                if(HRRN_pcb[i].arrival_time <= Cutoftime && !vis[i])
                {
                    hrrn[obj].value = (Cutoftime - HRRN_pcb[i].arrival_time)*1.0/HRRN_pcb[i].service_time + 1;
                    hrrn[obj].id = i;
                    obj++;
                }
            }
            sort(hrrn,hrrn+obj,cmp_hrrn);
            sequence[t++] = hrrn[0].id;                      //取响应比值最大的 下标加入序列
            vis[hrrn[0].id] = 1;
            Cutoftime += HRRN_pcb[hrrn[0].id].service_time;  //更新切割时间段  继续循环
        }
        else continue;
    }
    cout<<"该调度算法下进程执行顺序为：（对应的下标输出）"<<endl; //输出进程执行序列
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<sequence[i] << ", ";
    cout<<sequence[n-1]<<"}"<<endl<<endl;
    PCB t_HRRN_pcb[N];
    for(int i = 0; i < n; i++)
        t_HRRN_pcb[i] = HRRN_pcb[sequence[i]];                 //用计算得到的顺序执行HRRN
    Status_Output(t_HRRN_pcb);
}


/*
A 0 3
B 2 6
C 4 4
D 6 5
E 8 2
*/
/*
A 0 3
B 0 6
C 4 4
D 3 5
E 6 2
A 0 3
B 1 6
C 4 4
D 3 5
E 6 2

优先级是1 2 3 4 5
出现极端情况
（已解决）
*/
/*
A 1 10
B 2 6
C 3 2
D 4 4
E 5 8
*/

/*
A 1 3
B 6 3
C 4 2
D 9 1
E 10 4

SPF出现极端情况
（已解决）
*/

