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
#define N 20                            //������
#define WFA wait_for_arrival            //���̻�δ���������з���ʱ�̵���Ľ���ִ��ǰ�ĳ�ʼ״̬
#define Ready ready_state               //���̵�����ھ���״̬���ȴ�CPU��Դ
#define Running running_state           //���̴�������̬
#define Finish end_of_execution         //����ִ�н���
///���ݽṹ����ͨ�õĽ��̿��ƿ�PCB
struct PCB
{
    char process_name;                  //������
    double arrival_time;                //���̵���ʱ��
    double service_time;                //����Ҫ�����ʱ��
    double start_time;                  //���̿�ʼִ��ʱ��
    double need_service_time;           //���̻���ռ��CPUʱ��
    double end_time;                    //����ִ�����ʱ��
    double process_priority;            //�������ȼ�
    double turnaround_time;             //������תʱ��
    double weight_turnaround_time;      //���̴�Ȩ��תʱ��
    string status;                      //����״̬
};

PCB pcb[N];                             //ÿ������ά��һ�����̿��ƿ�
vector<PCB> pcbList;                    //pcbList����
queue<PCB>Ready;                        //��������
double average_TT;                      //ƽ����תʱ��
double average_WTT;                     //ƽ����Ȩ��תʱ��
int n;                                  //������
int flag = 0;
int time_unit;                          //ʱ��Ƭ����

///��HRRN����ʹ�õĽṹ��
struct Hrrn{
    float value;
    int id;
};
Hrrn hrrn[N];
///�������壺
void Select_menu();                      //ѡ��˵���ʼ��
void Init_process();                     //���̳�ʼ��
bool cmp_name(PCB a, PCB b);             //�����������򣬰������
bool cmp_time(PCB a, PCB b);             //�����̵���ʱ������
bool cmp_service_time(PCB a, PCB b);     //������ʱ�䳤������
bool cmp_process_priority(PCB a, PCB b); //�����ȼ���С����
bool cmp_hrrn(Hrrn a, Hrrn b);           //����������
void FCFS();                             //�����ȷ�������㷨
void SPF();                              //�̽������ȵ����㷨
void HPF();                              //HPF���ȼ������㷨
void RR();                               //RRʱ��Ƭ��ת�㷨
void Status_Output(PCB O_PCB[]);         //SPF����м�״̬
void HRRN();                             //����Ӧ�����ȵ����㷨
void Print(PCB Tmp_pcb[]);               //��ʽ�����
void Prio_Print(PCB Tmp_pcb[]);          //�����ȼ���ʽ�����
void Result_Print(PCB Tmp_pcb[]);        //���ս����ӡ�������̵����ʱ�䣬�����̵���תʱ�估��Ȩ��תʱ�䣩
void RR_Print(PCB Tmp_pcb[],vector<pair<char,int> > solve);  //�����ӡRR�㷨��������ݣ������м�״̬
bool All_finished(PCB pd_pcb[]);         //�ж��ǲ������н��̶��Ѿ�ִ�н�������Ϊѭ�����ж�������״̬�����ʱ���Ż���

/************************************
��������main()
*************************************/
int main()
{
    Init_process();    //���̳�ʼ��
    while(1)
    {
        char YorN = 'Y';
        cout<<"�����Ƿ�Ҫִ�жԽ��̵ĵ��ȣ�����ʽ��Y or N�������룺";
        cin>>YorN;
        if(YorN == 'N')
        {
            cout<<"ִ�н�����ϵͳ���˳���"<<endl;
            break;
        }
        else if(YorN == 'Y')
        {
            cout << endl;
            Select_menu();     //�����㷨ѡ��˵�
            cout << endl;
            int choice;
            cout << endl<<"��������ѡ�����㷨����ţ�";
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
                    cout<<"������Ҫ������Ϸ���ţ�"<<endl;
            }
        }
        else cout<<"������Ҫ������Ϸ��ַ���"<<endl<<endl;     //��ֹ���ַǷ��ַ�������
    }
    return 0;
}

/************************************
�������ƣ�Select_menu()
�������ܣ���ʼ��
����ֵ����
*************************************/
void Select_menu()
{
    string str_FCFS = "1.�����ȷ����㷨(FCFS)";
    string str_SPF = "2.�̽��������㷨(SPF)(����ռʽ)";
    string str_RR = "3.ʱ��Ƭ��ת�㷨(RR)";
    string str_HPF = "4.���ȼ������㷨(HPF)(����ռʽ)";
    string str_HRRN = "5.����Ӧ�����ȵ����㷨(HRRN)(����ռʽ)";

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
�������ƣ�Init_process()
�������ܣ����̳�ʼ��
����ֵ����
*************************************/
void Init_process()
{
    cout<<"******************************���ã���ӭʹ�ñ�ϵͳ��******************************"<<endl;
    cout<<"#��ע�⣺��ϵͳ�еĽ��̵����㷨����������ؼ�ʱ��ڵ�����н���״̬��Ŀǰ֧������#"<<endl;
    cout<<"**********************************************************************************"<<endl<<endl;
    cout<<"�������������";
    cin>>n;
    cout<<"���������� ������ ����ʱ�� ����ʱ��(�磺A 0 3)"<<endl;
    for(int i = 0; i < n; i++)
    {
        char p_name;             //������
        double p_arrive,p_service; //���̵���ʱ�� ����ʱ��
        cin>>p_name>>p_arrive>>p_service;
        pcb[i].process_name = p_name;
        pcb[i].arrival_time = p_arrive;
        pcb[i].service_time = p_service;
        if(!p_arrive) pcb[i].status = "Ready";
        else pcb[i].status = "WFA";
    }
}

/************************************
�������ƣ�cmp_name(PCB a, PCB b)
�������ܣ������������򣬰������
����ֵ����
*************************************/
bool cmp_name(PCB a, PCB b)
{
    return a.process_name < b.process_name;
}

/************************************
�������ƣ�Print(PCB Tmp_pcb[])
�������ܣ���ʽ�����
����ֵ����
*************************************/
void Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 124; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"������"<<setw(14)<<"����ʱ��"<<setw(13)<<"����ʱ��"<<setw(12)<<"��ʼʱ��"<<setw(11)<<"��CPUʱ��"
    <<setw(9)<<"����ʱ��"<<setw(12)<<"��תʱ��"<<setw(20)<<"��Ȩ��תʱ��"<<setw(13)<<" "<<"����״̬"<<" *"<<endl;
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
�������ƣ�Prio_Print(PCB Tmp_pcb[])
�������ܣ������ȼ���ʽ�����
����ֵ����
*************************************/
void Prio_Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 132; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"������"<<setw(14)<<"����ʱ��"<<setw(13)<<"����ʱ��"<<setw(11)<<"����Ȩ"<<setw(11)<<"��ʼʱ��"<<setw(11)<<"��CPUʱ��"
    <<setw(9)<<"����ʱ��"<<setw(12)<<"��תʱ��"<<setw(20)<<"��Ȩ��תʱ��"<<setw(11)<<" "<<"����״̬"<<" *"<<endl;
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
�������ƣ�Print(PCB Tmp_pcb[])
�������ܣ���ʽ�����
����ֵ����
*************************************/
void Result_Print(PCB Tmp_pcb[])
{
    PCB cp_pcb[N];
    for(int i=0; i < n; i++)
        cp_pcb[i] = Tmp_pcb[i];
    sort(cp_pcb,cp_pcb+n,cmp_name);
    for(int i = 0; i < 100; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"������"<<setw(14)<<"����ʱ��"<<setw(13)<<"����ʱ��"<<setw(12)<<"��ʼʱ��"
    <<setw(9)<<"����ʱ��"<<setw(12)<<"��תʱ��"<<setw(20)<<"��Ȩ��תʱ��"<<"\t   *"<<endl;
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
�������ƣ�bool All_finished(PCB pd_pcb[]);
�������ܣ��ж��ǲ������н��̶��Ѿ�
ִ�н�������Ϊѭ�����ж�������״̬
�����ʱ���Ż���
����ֵ��true or false
*************************************/
bool All_finished(PCB pd_pcb[])
{
    int t=0;
    for(int i = 0; i < n; i++)
    {
        if(pd_pcb[i].status == "Finish")
            t++;   //����ѭ��ִ��
    }
    if(t==n)  return false;
    else return true;
}

/************************************
�������ƣ�cmp_time(PCB a, PCB b)
�������ܣ������̵���ʱ������
����ֵ����
*************************************/
bool cmp_time(PCB a, PCB b)
{
    return a.arrival_time < b.arrival_time;
}

/************************************
�������ƣ�FCFS()
�������ܣ������ȷ�������㷨
����ֵ����
*************************************/
void FCFS()
{
    PCB FCFS_pcb[N];
    for(int i=0; i < n; i++)
        FCFS_pcb[i] = pcb[i];
    sort(FCFS_pcb,FCFS_pcb+n,cmp_time);          //������ʱ������
    for(int excute_time = FCFS_pcb[0].arrival_time; All_finished(FCFS_pcb); excute_time++)    //����ʱ����� ����м�״̬
    {
        for (int i = 0; i < n; i++)                                              //��������
        {
            if(FCFS_pcb[i].arrival_time == excute_time && !flag)
            {
                FCFS_pcb[i].start_time = excute_time;                            //��ǰCPU���У��ҽ����ѵ���ӵ�ǰʱ�俪ʼִ��
                FCFS_pcb[i].end_time = excute_time + FCFS_pcb[i].service_time;   //�޸ĸý��̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                FCFS_pcb[i].status = "Running";                                  //�޸Ľ���״̬ Ϊ Running
                FCFS_pcb[i].need_service_time = FCFS_pcb[i].service_time;
                flag = 1;                                                        //��ǰCPU�ѱ�ռ��
                cout << "T = "<<excute_time<<":"<<endl;
                Print(FCFS_pcb);
                for(int j = i; j < n; j++)                                        //�������ڵ�ǰʱ�̵���Ľ�����ΪReady
                {
                    if(FCFS_pcb[j].arrival_time <= excute_time && FCFS_pcb[j].status == "WFA")
                        FCFS_pcb[j].status = "Ready";
                }
                cout<<endl;
                break;
            }
            else if(FCFS_pcb[i].arrival_time == excute_time && flag && FCFS_pcb[i].status == "WFA")
            {
                FCFS_pcb[i].status = "Ready";             //ĳ���̵������CPU��ռ���ţ��ý���״̬Ϊ Ready
                for(int j = 0; j < i; j++)                //�޸ĵ�ǰ����֮ǰ���̵�״̬
                {
                    if(FCFS_pcb[j].status == "Running")   //�ҵ�״̬ΪRunning�Ľ��̡���һ��ֻ��һ��
                    {
                        FCFS_pcb[j].need_service_time = FCFS_pcb[j].end_time - excute_time;
                        //����ʱ�� - ��ǰʱ�� = ��������CPU��ʱ��
                        break;
                    }
                }
                cout << "T = "<<excute_time<<":"<<endl;
                Print(FCFS_pcb);
                for(int j = i; j < n; j++)                                        //�������ڵ�ǰʱ�̵���Ľ�����ΪReady
                {
                    if(FCFS_pcb[j].arrival_time <= excute_time && FCFS_pcb[j].status == "WFA")
                        FCFS_pcb[j].status = "Ready";
                }
                cout<<endl;
                break;
            }
            else if(FCFS_pcb[i].end_time == excute_time && FCFS_pcb[i].status == "Running")    //ĳ���̵�ǰʱ��ִ�����
            {
                FCFS_pcb[i].status = "Finish";           //ĳ����ִ�����
                flag = 0;                                //CPU����
                FCFS_pcb[i].need_service_time = 0;       //������ҪCPU
                FCFS_pcb[i].turnaround_time = excute_time - FCFS_pcb[i].arrival_time;
                //��תʱ�� = ��ǰʱ�� - ����ʱ��
                FCFS_pcb[i].weight_turnaround_time = 1.0 * (FCFS_pcb[i].turnaround_time)/(FCFS_pcb[i].service_time);
                //��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
                FCFS_pcb[i].weight_turnaround_time = ((int)((FCFS_pcb[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //������λС��������������
                for(int j = i; j < n; j++)                //�����ǰ����ִ�н���ʱ����һ���̸պõ��״̬λ������޸�
                {
                    if(FCFS_pcb[j].arrival_time == FCFS_pcb[i].end_time)
                    {
                        FCFS_pcb[j].status = "Ready";
                    }
                }
                for(int j = i; j < n; j++)                                               //�ҵ�һ��ready����
                {
                    if(FCFS_pcb[j].status == "Ready")
                    {
                        flag = 1;
                        FCFS_pcb[j].start_time = excute_time;                            //��ʼʱ����ڵ�ǰʱ��
                        FCFS_pcb[j].end_time = excute_time + FCFS_pcb[j].service_time;   //���̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                        FCFS_pcb[j].status = "Running";                                  //�޸Ľ���״̬ Ϊ Running
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
    cout<<endl<<"�����̵�ִ��˳��Ϊ��"<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<FCFS_pcb[i].process_name<<", ";
    cout<<FCFS_pcb[n-1].process_name<<"}"<<endl;
    cout<<endl<<"���ս����ӡ��"<<endl;
    Result_Print(FCFS_pcb);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += FCFS_pcb[i].turnaround_time;
        average_WTT += FCFS_pcb[i].weight_turnaround_time;
    }
    cout<<"ƽ����תʱ�� = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"ƽ����Ȩ��תʱ�� = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
�������ƣ�Status_Output(PCB O_PCB[])
�������ܣ�����м�״̬
SPF����м�״̬
�ʷ�װ�ɺ�������
����ֵ����
*************************************/
void Status_Output(PCB O_PCB[])
{
    PCB Res_PCB[N];
    int t = 0;
    int excute_time = O_PCB[0].arrival_time;
    flag = 0;
    for(int i = 0; i < n; i++)                //�� ���н����� ���絽��Ľ���ʱ�� ��Ϊ ϵͳ�ĳ�ʼʱ��
    {
        excute_time = excute_time > O_PCB[i].arrival_time ? O_PCB[i].arrival_time : excute_time;
    }
    for(; All_finished(O_PCB); excute_time++)             //����ʱ����� ����м�״̬
    {
        for (int i = 0; i < n; i++)                             //��������
        {
            if(O_PCB[i].arrival_time == excute_time && !flag)   //�ȵ��Ľ�����CPU��������ִ�У����������������������Ŷ�ʱ��ѡ�����ʱ��̵Ľ���
            {
                for(int j = i; j < n; j++)                                             //ͬʱ�䵽��ģ����޸�״̬
                {
                    if(O_PCB[j].arrival_time <= excute_time && O_PCB[j].status == "WFA")
                        O_PCB[j].status = "Ready";
                }
                for(int j = 0; j <= i; j++)                                            //ͬʱ�䵽��ģ���ѡ����ʱ��̵�
                {
                    if(O_PCB[j].status == "Ready")
                    {
                        O_PCB[j].start_time = excute_time;                             //��ǰCPU���У�����Ľ���ִ��
                        O_PCB[j].end_time = excute_time + O_PCB[j].service_time;       //����ռʽ���ʸý��̽���ʱ��= ��ǰʱ�� + ����ʱ��
                        O_PCB[j].need_service_time = O_PCB[j].service_time;            //����Ҫռ��CPU��ʱ��
                        O_PCB[j].status = "Running";                                   //�޸ĵ�ǰ���̵�״̬ΪRunning
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
            else if(O_PCB[i].arrival_time == excute_time && flag && O_PCB[i].status == "WFA")   //ĳ���̽�������ǰ���̵���
            {
                int mark = 0;
                O_PCB[i].status = "Ready";                //ĳ���̵����CPU��ռ���ţ���״̬ΪReady
                if(mark == 0)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(O_PCB[j].status == "Running" && O_PCB[j].end_time == excute_time)    //�ҵ�����ִ�еĽ��̣�����ֻ��һ��,������̸պý���
                        {
                            O_PCB[j].status = "Finish";       //ĳ����ִ�����
                            flag = 0;
                            O_PCB[j].need_service_time = 0;   //������ҪCPU��Դ
                            O_PCB[j].turnaround_time = excute_time - O_PCB[j].arrival_time;     //��תʱ�� = ��ǰʱ�� - ����ʱ��
                            O_PCB[j].weight_turnaround_time = 1.0 * (O_PCB[j].turnaround_time)/(O_PCB[j].service_time);   //��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
                            O_PCB[j].weight_turnaround_time = ((int)((O_PCB[j].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                            for(int m = i; m < n; m++)         //�����ǰ����ִ�н���ʱ����һ���̸պõ��״̬λ������޸�
                            {
                                if(O_PCB[m].arrival_time == O_PCB[j].end_time && O_PCB[j].status=="WFA")
                                {
                                    O_PCB[m].status = "Ready";
                                }
                            }
                            for(int k = 0; k < n; k++)                                             //�ҵ�һ��ready����
                            {
                                if(O_PCB[k].status == "Ready")
                                {
                                    flag = 1;
                                    O_PCB[k].start_time = excute_time;                           //��ʼʱ����ڵ�ǰʱ��
                                    O_PCB[k].end_time = excute_time + O_PCB[k].service_time;   //���̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                                    O_PCB[k].status = "Running";                                 //�޸Ľ���״̬ Ϊ Running
                                    Res_PCB[t++] = O_PCB[k];
                                    O_PCB[k].need_service_time = O_PCB[k].service_time;
                                    break;
                                }
                            }
                            mark = 1;
                        }
                        else if(O_PCB[j].status == "Running" && O_PCB[j].end_time!=excute_time) //�ҵ�����ִ�еĽ��̣�����ֻ��һ��������ִ��
                        {
                            O_PCB[j].need_service_time = O_PCB[j].end_time - excute_time;       //����ʱ�� - ��ǰʱ�� = ��������CPUʱ��
                            mark = 1;
                            for(int m = i; m < n; m++)         //������������Ҳ�ڵ�ǰʱ�̵��״̬λ������޸�
                            {
                                if(O_PCB[m].arrival_time <= O_PCB[i].arrival_time && O_PCB[m].status=="WFA")
                                {
                                    O_PCB[m].status = "Ready";
                                }
                            }
                        }
                        if(mark) break;        //����ֻ����һ��Running���̣�������֮��Ͳ���Ҫ�ٱ����ˣ�ֱ��break
                    }  //for
                }  //if mark == 0;
                cout<<"T = " <<excute_time<<":"<<endl;
                Print(O_PCB);
                cout<<endl;
                break;
            }
            else if(O_PCB[i].end_time == excute_time && O_PCB[i].status == "Running")   //ĳ����ִ�н���
            {
                O_PCB[i].status = "Finish";         //ĳ����ִ�����
                flag = 0;
                O_PCB[i].need_service_time = 0;     //������ҪCPU��Դ
                O_PCB[i].turnaround_time = excute_time - O_PCB[i].arrival_time;
                //��תʱ�� = ��ǰʱ�� - ����ʱ��
                O_PCB[i].weight_turnaround_time = 1.0 * (O_PCB[i].turnaround_time)/(O_PCB[i].service_time);
                //��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
                O_PCB[i].weight_turnaround_time = ((int)((O_PCB[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //������λС��������������
                for(int j = 0; j < n; j++)          //�����ǰ����ִ�н���ʱ����һ���̸պõ��״̬λ������޸�
                {
                    if(O_PCB[j].arrival_time <= O_PCB[i].end_time && O_PCB[j].status=="WFA")
                    {
                        O_PCB[j].status = "Ready";
                    }
                }
                for(int j = 0; j < n; j++)                                         //�ҵ�һ��ready����
                {
                    if(O_PCB[j].status == "Ready")
                    {
                        flag = 1;
                        O_PCB[j].start_time = excute_time;                         //��ʼʱ����ڵ�ǰʱ��
                        O_PCB[j].end_time = excute_time + O_PCB[j].service_time;   //���̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                        O_PCB[j].status = "Running";                               //�޸Ľ���״̬ Ϊ Running
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
    cout<<endl<<"�����̵�ִ��˳��Ϊ��"<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<Res_PCB[i].process_name<<", ";
    cout<<Res_PCB[n-1].process_name<<"}"<<endl;
    cout<<endl<<"���ս����ӡ��"<<endl;
    Result_Print(O_PCB);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += O_PCB[i].turnaround_time;
        average_WTT += O_PCB[i].weight_turnaround_time;
    }
    cout<<"ƽ����תʱ�� = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"ƽ����Ȩ��תʱ�� = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
�������ƣ�cmp_service_time(PCB a, PCB b)
�������ܣ�������ʱ�䳤������
����ֵ����
*************************************/
bool cmp_service_time(PCB a, PCB b)
{
    if(a.arrival_time != b.arrival_time)
        return a.service_time < b.service_time;
    else return a.arrival_time < b.arrival_time;
}

/************************************
�������ƣ�SPF()
�������ܣ��̽������ȵ����㷨
����ֵ����
*************************************/
void SPF()
{
    PCB SPF_pcb[N];
    for(int i=0; i < n; i++)
        SPF_pcb[i] = pcb[i];
    sort(SPF_pcb,SPF_pcb+n,cmp_service_time);    //������ʱ�䳤������
    Status_Output(SPF_pcb);
}

/************************************
�������ƣ�cmp_process_priority(PCB a, PCB b)
�������ܣ������ȼ���С����
��ע�����ȼ���ֵԽ�����ȼ�Խ�ߣ�
����ֵ����
*************************************/
bool cmp_process_priority(PCB a, PCB b)
{
    if(a.arrival_time != b.arrival_time)
        return a.process_priority > b.process_priority;
    else return a.arrival_time < b.arrival_time;
}

/************************************
�������ƣ�HPF()
�������ܣ�HPF���ȼ������㷨
����ֵ����
*************************************/
void HPF()
{
    PCB HPF_pcb[N];
    PCB Res_PCB[N];
    int t = 0;
    for(int i = 0; i < n; i++)
        HPF_pcb[i] = pcb[i];
    cout<<"������������������{";
    for(int i = 0; i < n-1; i++)
        cout<<HPF_pcb[i].process_name<<" ";
    cout<<HPF_pcb[n-1].process_name<<"}�����ȼ�����ֵ:(��ֵԽ�����ȼ�Խ�ߣ������ÿո��������)"<<endl;
    for(int i = 0; i < n; i++)
        cin>>HPF_pcb[i].process_priority;
    sort(HPF_pcb,HPF_pcb+n,cmp_process_priority);                 //�����ȼ���С����
    //for(int i = 0; i < n; i++)
    //    cout<<HPF_pcb[i].process_name << " "<<HPF_pcb[i].arrival_time<<" "<<HPF_pcb[i].service_time<<" "<<HPF_pcb[i].process_priority<<endl;
    cout<<endl;
    int excute_time = HPF_pcb[0].arrival_time;
    flag = 0;
    for(int i = 0; i < n; i++)                                    //�� ���н����� ���絽��Ľ���ʱ�� ��Ϊ ϵͳ�ĳ�ʼʱ��
    {
        excute_time = excute_time > HPF_pcb[i].arrival_time ? HPF_pcb[i].arrival_time : excute_time;
    }
    for(; All_finished(HPF_pcb); excute_time++)               //����ʱ����� ����м�״̬
    {
        for (int i = 0; i < n; i++)                               //��������
        {
            if(HPF_pcb[i].arrival_time == excute_time && !flag)   //�ȵ��Ľ�����CPU��������ִ�У����������������������Ŷ�ʱ��ѡ�����ȼ��ߵĽ���
            {
                for(int j = 0; j < n; j++)                        //ͬʱ�䵽��ģ����޸�״̬
                {
                    if(HPF_pcb[j].arrival_time <= excute_time && HPF_pcb[j].status == "WFA")
                        HPF_pcb[j].status = "Ready";
                }
                for(int j = 0; j <= i; j++)                                          //ͬʱ�䵽��ģ���ѡ���ȼ��ߵ�
                {
                    if(HPF_pcb[j].status == "Ready")
                    {
                        HPF_pcb[j].start_time = excute_time;                          //��ǰCPU���У�����Ľ���ִ��
                        HPF_pcb[j].end_time = excute_time + HPF_pcb[j].service_time;  //����ռʽ���ʸý��̽���ʱ��= ��ǰʱ�� + ����ʱ��
                        HPF_pcb[j].need_service_time = HPF_pcb[j].service_time;       //����Ҫռ��CPU��ʱ��
                        HPF_pcb[j].status = "Running";                                //�޸ĵ�ǰ���̵�״̬ΪRunning
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
            else if(HPF_pcb[i].arrival_time == excute_time && flag && HPF_pcb[i].status == "WFA")   //ĳ���̽�������ǰ���̵���
            {
                bool mark = 0;
                HPF_pcb[i].status = "Ready";                //ĳ���̵����CPU��ռ���ţ���״̬ΪReady
                for(int j = 0; j < n; j++)
                {
                    if(HPF_pcb[j].status == "Running" && HPF_pcb[j].end_time == excute_time)    //�ҵ�����ִ�еĽ��̣�����ֻ��һ��,������̸պý���
                    {
                        HPF_pcb[j].status = "Finish";       //ĳ����ִ�����
                        flag = 0;
                        HPF_pcb[j].need_service_time = 0;   //������ҪCPU��Դ
                        HPF_pcb[j].turnaround_time = excute_time - HPF_pcb[j].arrival_time;     //��תʱ�� = ��ǰʱ�� - ����ʱ��
                        HPF_pcb[j].weight_turnaround_time = 1.0 * (HPF_pcb[j].turnaround_time)/(HPF_pcb[j].service_time);   //��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
                        HPF_pcb[j].weight_turnaround_time = ((int)((HPF_pcb[j].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                        for(int m = i; m < n; m++)         //������������Ҳ�ڵ�ǰʱ�̵��״̬λ������޸�
                        {
                            if(HPF_pcb[m].arrival_time <= HPF_pcb[j].end_time && HPF_pcb[j].status == "WFA")
                            {
                                HPF_pcb[m].status = "Ready";
                            }
                        }
                        for(int k = 0; k < n; k++)                                             //�ҵ�һ��ready����
                        {
                            if(HPF_pcb[k].status == "Ready")
                            {
                                flag = 1;
                                HPF_pcb[k].start_time = excute_time;                           //��ʼʱ����ڵ�ǰʱ��
                                HPF_pcb[k].end_time = excute_time + HPF_pcb[k].service_time;   //���̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                                HPF_pcb[k].status = "Running";                                 //�޸Ľ���״̬ Ϊ Running
                                Res_PCB[t++] = HPF_pcb[k];
                                HPF_pcb[k].need_service_time = HPF_pcb[k].service_time;
                                break;
                            }
                        }
                        mark = 1;
                    }
                    else if(HPF_pcb[j].status == "Running" && HPF_pcb[j].end_time!=excute_time) //�ҵ�����ִ�еĽ��̣�����ֻ��һ��������ִ��
                    {
                        HPF_pcb[j].need_service_time = HPF_pcb[j].end_time - excute_time;       //����ʱ�� - ��ǰʱ�� = ��������CPUʱ��
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
            else if(HPF_pcb[i].end_time == excute_time && HPF_pcb[i].status == "Running")   //ĳ����ִ�н���
            {
                HPF_pcb[i].status = "Finish";        //ĳ����ִ�����
                flag = 0;
                HPF_pcb[i].need_service_time = 0;    //������ҪCPU��Դ
                HPF_pcb[i].turnaround_time = excute_time - HPF_pcb[i].arrival_time;
                //��תʱ�� = ��ǰʱ�� - ����ʱ��
                HPF_pcb[i].weight_turnaround_time = 1.0 * (HPF_pcb[i].turnaround_time)/(HPF_pcb[i].service_time);
                //��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
                HPF_pcb[i].weight_turnaround_time = ((int)((HPF_pcb[i].weight_turnaround_time*1000) + 0.5)) * 1.0 / 1000;
                //������λС��������������
                for(int j = i; j < n; j++)           //�����ǰ����ִ�н���ʱ����һ���̸պõ��״̬λ������޸�
                {
                    if(HPF_pcb[j].arrival_time == HPF_pcb[i].end_time && HPF_pcb[j].status == "WFA")
                    {
                        HPF_pcb[j].status = "Ready";
                    }
                }
                for(int j = 0; j < n; j++)                                             //�ҵ�һ��ready����
                {
                    if(HPF_pcb[j].status == "Ready")
                    {
                        flag = 1;
                        HPF_pcb[j].start_time = excute_time;                           //��ʼʱ����ڵ�ǰʱ��
                        HPF_pcb[j].end_time = excute_time + HPF_pcb[j].service_time;   //���̵Ľ���ʱ�� = ��ǰʱ�� + ����ʱ��
                        HPF_pcb[j].status = "Running";                                 //�޸Ľ���״̬ Ϊ Running
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
    cout<<endl<<"�����̵�ִ��˳��Ϊ��"<<endl;
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<Res_PCB[i].process_name<<", ";
    cout<<Res_PCB[n-1].process_name<<"}"<<endl;
    cout<<endl<<"���ս����ӡ��"<<endl;
    Result_Print(HPF_pcb);
    average_TT = 0;
    average_WTT = 0;
    for(int i = 0; i < n; i++)
    {
        average_TT += HPF_pcb[i].turnaround_time;
        average_WTT += HPF_pcb[i].weight_turnaround_time;
    }
    cout<<"ƽ����תʱ�� = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"ƽ����Ȩ��תʱ�� = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
�������ƣ�RR()
�������ܣ�ʱ��Ƭ��ת�����㷨
����ֵ����
vector<PCB> pcbList;  //pcbList����
queue<PCB>Ready       //��������
*************************************/
void RR()
{
    PCB RR_pcb[N];
    int t=0;
    cout<<"������ʱ��Ƭ��С��";
    cin>>time_unit;
    vector<pair<char,int> > solve;
	for(int i = 0; i < n; i++)
        RR_pcb[i] = pcb[i];
	for(int i=0;i<n;i++)
	{
		pcbList.push_back(pcb[i]);    //������ʼ��
	}
	sort(RR_pcb,RR_pcb+n,cmp_time);   //������ʱ���������
	sort(pcbList.begin(),pcbList.end(),cmp_time);
	//for (int i = 0; i < n; i++)
    //    cout<<pcbList[i].process_name;
    //cout<<endl;
	int excute_time =(*pcbList.begin()).arrival_time;  //��һ�����̿�ʼʱ��
	Ready.push(*pcbList.begin());
	pcbList.erase(pcbList.begin());
    while(!pcbList.empty()||!Ready.empty())
    {
        while(!pcbList.empty()&&excute_time>=(*pcbList.begin()).arrival_time)//���½��̼����������
        {
            Ready.push(*pcbList.begin());
            pcbList.erase(pcbList.begin());
        }
		if(Ready.front().end_time + time_unit < Ready.front().service_time)//��ʱ��Ƭ���굫û������Ľ��̼����β
		{
            solve.push_back(pair<char,int>(Ready.front().process_name,time_unit));
			Ready.front().end_time += time_unit;
			excute_time += time_unit;
			while(!pcbList.empty()&& (*pcbList.begin()).arrival_time <= excute_time)    //δִ���꣬�������ready��ĩβ
            {
			 	Ready.push(*pcbList.begin());
        	    pcbList.erase(pcbList.begin());
		    }
			Ready.push(Ready.front());
			Ready.pop();
		}
		else      //����ִ����
        {
            int tmp_time_unit = time_unit;
			if(Ready.front().service_time - Ready.front().end_time<tmp_time_unit)
			{
				tmp_time_unit -= Ready.front().service_time - Ready.front().end_time;
			}
			solve.push_back(pair<char,int>(Ready.front().process_name,tmp_time_unit));   //��ִ�н��̵���Ϣ
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
�������ƣ�RR_Print
(PCB Tmp_pcb[],vector<pair<char,int> > solve)
�������ܣ�RR�㷨�ĸ�ʽ�����
����ֵ����
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
    cout<<"*"<<setw(3)<<" "<<"������"<<setw(14)<<"����ʱ��"<<setw(13)<<"����ʱ��"<<setw(12)<<"ִ��ʱ��"
    <<setw(11)<<"�л�ʱ��"<<" *"<<endl;
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
    cout<<endl<<"�����̵�ִ��˳��Ϊ��"<<endl;
    cout<<"{";
    for(iter = solve.begin(); iter != solve.end(); iter++)
    {
        cout<<(*iter).first;
        if(iter != solve.end()-1)
            cout<<", ";
    }
    cout<<"}"<<endl;

    cout<<endl<<"���ս����ӡ:"<<endl;
    for(int i = 0; i < 92; i++) cout<<"*";
    cout<<endl;
    cout<<"*"<<setw(3)<<" "<<"������"<<setw(14)<<"����ʱ��"<<setw(13)<<"����ʱ��"
    <<setw(11)<<"����ʱ��"<<setw(12)<<"��תʱ��"<<setw(20)<<"��Ȩ��תʱ��"<<"\t   *"<<endl;
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
    cout<<"ƽ����תʱ�� = ";
    cout<<average_TT<<"/"<<n<<" = "<<average_TT/n<<endl;
    cout<<"ƽ����Ȩ��תʱ�� = ";
    cout<<average_WTT<<"/"<<n<<" = "<<average_WTT/n<<endl<<endl;
}

/************************************
�������ƣ�cmp_hrrn(Hrrn a, Hrrn b)
�������ܣ�����������
����ֵ����

struct Hrrn{
    float value;
    int id;
};
Hrrn hrrn[N];
//�ýṹ���д���� �Ѿ�������û��ִ��
�����н��̵���Ӧ�ȵ�ֵ���±꣨���ݼ�
����ȡ��Ӧ�����Ľ���ִ�У�
*************************************/
bool cmp_hrrn(Hrrn a, Hrrn b)
{
    return a.value > b.value;
}

/************************************
�������ƣ�HRRN()
�������ܣ�����Ӧ�����ȵ����㷨
          ����Ӧ�ȸ������ȣ�
����ֵ����
��Ӧ�ȼ��㣺ri = (Tw/Ts)+1
���У�Tw:�ȴ�ʱ�䣻Ts:����ʱ��
*************************************/
void HRRN()
{
    PCB HRRN_pcb[N];
    bool vis[N] ={0};                            //������飬��ǽ����ǲ��Ǳ��Ž�ִ�����л���
    int sequence[N] = {0},t=0;                   //�����ִ�е������±� ��������ת��PCB�ṹ�����飬�õ���ȷ��ִ��˳��
    for(int i = 0; i < n; i++)
        HRRN_pcb[i] = pcb[i];                    //����PCB�ṹ������
    sort(HRRN_pcb,HRRN_pcb+n,cmp_time);          //�ȶԸ����̰�����ʱ������
    int excute_time = HRRN_pcb[0].arrival_time;
    int total_time = HRRN_pcb[0].arrival_time;   //��һ�����̵���ʱ�� + ���н��̵ķ���ʱ�� = ��ʱ��
    flag = 0;                                    //flag=0 ��ʾCPU����
    for(int i = 0; i < n; i++)                   //������ʱ��
    {
        total_time += HRRN_pcb[i].service_time;
        excute_time = excute_time > HRRN_pcb[i].arrival_time ? HRRN_pcb[i].arrival_time : excute_time;//��ʼʱ�䣨�����絽��Ľ��̵���ʱ�䣩
    }
    int Cutoftime = excute_time;                 //ʱ��Ƭ�иΪ�˻��ݱ���������̣��Լ����������Ӧ�ȣ�
    for(; excute_time<=total_time; excute_time++)    //����ʱ����� ��ȷ��ִ��˳��
    {
        if(excute_time == Cutoftime)             //ʱ���и�
        {
            int obj = 0;
            memset(hrrn,0,sizeof(0));            //��ʼ����̬�仯��һά���飨����Ӧ�ȣ�
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
            sequence[t++] = hrrn[0].id;                      //ȡ��Ӧ��ֵ���� �±��������
            vis[hrrn[0].id] = 1;
            Cutoftime += HRRN_pcb[hrrn[0].id].service_time;  //�����и�ʱ���  ����ѭ��
        }
        else continue;
    }
    cout<<"�õ����㷨�½���ִ��˳��Ϊ������Ӧ���±������"<<endl; //�������ִ������
    cout<<"{";
    for(int i = 0; i < n-1; i++)
        cout<<sequence[i] << ", ";
    cout<<sequence[n-1]<<"}"<<endl<<endl;
    PCB t_HRRN_pcb[N];
    for(int i = 0; i < n; i++)
        t_HRRN_pcb[i] = HRRN_pcb[sequence[i]];                 //�ü���õ���˳��ִ��HRRN
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

���ȼ���1 2 3 4 5
���ּ������
���ѽ����
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

SPF���ּ������
���ѽ����
*/

