#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#define TIME_SLICE 2

// ����״̬������ ���� ���
enum process_type {
    process_type_wait = 'W',
    process_type_run = 'R',
    process_type_finish = 'F'
};

// ���̿��ƿ�ṹ��
typedef struct node{
    // ���̵�����
    char *name;
    // ���̵���ʱ��
    int arrive_time;
	//�������ȼ�����ʼΪ50��������� 50��ȥʣ������ʱ�䣬������stillneed_time
    int priority;
    // ��������ʱ��
    int stillneed_time;
    // ���̵�״̬������ �ȴ� ���
    char state;
    // ʱ��Ƭ
    int time_slice;
    // cpuʱ�� ->������ʱ��
    int cpu_time;
    // ������
    int time_count;
    // ����ʱ��
    int serve_time;
    // ָ����һ��Ҫִ�еĽ���
    struct node *next;
}PCB;

// ѡ��˵�
int menu();
// �������̶���
void create_list(PCB * running_list,int p_number);
// �����µĽ���
void create_process(PCB *running_list,char *name,int arrive_time,int stillneed_time);
// ���½��̷������������
void insert(PCB *running_list,PCB *newProcess);
// �ҵ���ǰ�����е�һ�����̣�����״̬��Ϊ����
void set_run(PCB *running_list);
// չʾ��ǰ��������״̬
void show(PCB *running_list);
// ���õ����㷨
int invoke_algorithm(PCB *running_list,int number);
//ʱ����ת�㷨
int round_robin(PCB *running_list);
// �����������㷨
int highest_priority(PCB *running_list);

int main(int argc, const char * argv[]) {

    // ���ò˵� �������ز�����Ӧ���
    int number = menu();

    // ����������Ŀ
    int p_number;
    printf("   ������Ҫ�����Ľ�������");
    scanf("%d",&p_number);
    printf("\n");

    // ����(����)����(ͷ��㲻������Ϣ)
    PCB *running_list = (PCB *)malloc(sizeof(PCB));
    running_list->next = NULL;

    // �������̶���
    create_list(running_list,p_number);

    // ���õ����㷨
    int total_cometofinish_time = invoke_algorithm(running_list,number);
    printf("�ý��̵����㷨�Ľ���ƽ����תʱ�䣺%0.2f\n",(float)total_cometofinish_time/p_number);

    return 0;
}

// �˵�
int menu(){

    // ѡ�ý��̵����㷨
    printf("��ѡ�ý��̵����㷨��\n\n");
    //printf("    1.�̽������ȵ����㷨\n");
    printf("   1.ʱ��Ƭ��ת�����㷨\n");
    printf("   2.��̬�����������㷨\n\n");
    printf("������ѡ�������ţ���");

    int number;
    scanf("%d",&number);
    printf("\n");
    return number;
}

// �������̶���
void create_list(PCB * running_list,int p_number){

	printf("���̵���ʱ��Ϊ�Զ������������(0~20)\n");
    // ѭ����������
    for (int i = 1; i <= p_number; i++) {
        // ������
        char *name = (char *)malloc(sizeof(char));
        printf("�������%d���������ͽ�������Ҫʱ��: ",i);
         // ��������ʱ��
        int stillneed_time;
        scanf("%s %d",name, &stillneed_time);
        if(i == p_number){
            printf("\n");
        }

        // ���̵���ʱ��
        int arrive_time;
        srand(int(time(NULL)));
        if(1 == i){
            // ��һ�����̵���ʱ��Ϊ0
            arrive_time = 0;
        }else{
            // �������������������ʱ�� (0~20)
            arrive_time = rand()%20;
        }
        create_process(running_list,name,arrive_time,stillneed_time);
    }
}


// �����µĽ���
void create_process(PCB *running_list,char *name,int arrive_time,int stillneed_time){

    // ����һ���ڴ���ƿ�Ŀռ�
    PCB *p = (PCB *)malloc(sizeof(PCB));
    // ��̬�ڴ��Ƿ����ɹ�
    if(p == NULL){
        printf("�ڴ����ʧ�ܣ�");
    }

    // ���øÿ��ƿ��ֵ
    p->name = name;
    // ����ʱ��
    p->arrive_time = arrive_time;
    // ��������ʱ��
    p->stillneed_time = stillneed_time;
    // ������ʱ
    p->serve_time = stillneed_time;

    // ��Ӧ��
    p->priority = 50;
    // ״̬
    p->state = process_type_wait;
    // ʱ��Ƭ
    p->time_slice = 0;
    // cpuʱ��
    p->cpu_time = 0;
    // ������
    p->time_count = 0;
    // �¸�����
    p->next = NULL;

    // �������������
    insert(running_list,p);
}

// չʾ��ǰ����״̬
void show(PCB *running_list){
    PCB *p = running_list->next;
    if (p == NULL) {
        printf("��ǰ�������޽���\n");
        return;
    }

    printf("������  ����ʱ��  ���ȼ�  ʱ��Ƭ  cpuʱ��  ����ʱ��  ����״̬  ������\n");
    while (p != NULL) {
printf("   %s     %4d      %4d   %4d    %4d     %4d          %c     %4d\n",p->name,p->arrive_time,p->priority,p->time_slice,p->cpu_time,p->stillneed_time,p->state,p->time_count);

        p = p->next;
    }
    printf("\n");
}

// ���õ����㷨
int invoke_algorithm(PCB *running_list,int number){

    int time = 0;
    switch(number){
        case 1:
            // ʱ��Ƭ��ת�����㷨
            set_run(running_list);
            printf("���̵���ǰ:\n");
            printf("---------------------------------------------------------------------\n");
            show(running_list);
            printf("---------------------------------------------------------------------\n");
            printf("���̵��Ⱥ�:\n");
            time = round_robin(running_list);
            break;
        case 2:
            // ���ȼ������㷨
            printf("���̵���ǰ:\n");
            printf("---------------------------------------------------------------------\n");
            show(running_list);
            printf("---------------------------------------------------------------------\n");
            printf("���̵��Ⱥ�:\n");
            time = highest_priority(running_list);
            break;
        default:
            exit(0);
            break;
    }
    return time;
}

// �����½���
void insert(PCB *running_list,PCB *newProcess){

    // �жϽ��̶����Ƿ�Ϊ��
    if(running_list->next == NULL){
        running_list->next = newProcess;
        return;
    }

    // �½��̵���ʱ��
    int arrive_time = newProcess->arrive_time;
    // �ƶ�ָ��
    PCB *move = running_list->next;
    while(move->next != NULL){
        if(move->next->arrive_time > arrive_time){
            newProcess->next = move->next;
            move->next = newProcess;
            return;
        }
        move = move->next;
    }
    move->next = newProcess;
}

// �ҵ���ǰ�����е�һ�����̣�����״̬��Ϊ����
void set_run(PCB *running_list){
    PCB *s = running_list->next;
    if (s == NULL) {
        printf("��ǰ�����ѿ�\n");
        return;
    }

    if (s->state != process_type_finish) {
        s->state = process_type_run;
        return;
    }
}

// ʱ��Ƭ��ת�����㷨
int round_robin(PCB *running_list){
    /*
    ÿ����������̺�
        �������������ϣ��Ὣ�ý��̴Ӷ��׵�����β
        ������������������һ���̵���ʱ����ڽ���������ʱ�䣬����ǰ����ȫ��ִ���꣬�ȴ���һ���̵���
        �����������δ��ϣ����ý��̵�����δ��ɶ��е�ĩβ
     */
    // ��¼��һ������λ��
    PCB *index = running_list->next;

    // �жϽ����Ƿ񵽴���̵����ѹ��೤ʱ��
    int total_run_time = 0;
    // ��¼�㷨�Ľ�������תʱ��
    int total_cometofinish_time = 0;
    PCB *s = NULL;
    while (index != NULL && index->state != process_type_finish) {
        // �����Ƿ񵽴�
        if(index -> state == process_type_run){
            // ��ʱ��Ƭ���иý��̣����޸Ľ��̵�cpuʱ�������Ҫʱ�䡢������
            s = index;
            s->time_slice = TIME_SLICE;

            // ��¼���cpuʱ��
            int old_cpu_time = s->cpu_time;
            // cpuʱ�䣨������ʱ��) = ����ʱ�� -����ǰcpuʱ��+ʱ��Ƭ)
            // ���������ֱ����ʾ����ʱ��
            s->cpu_time = (s->cpu_time + TIME_SLICE) < s->serve_time ? s->cpu_time + TIME_SLICE : s->serve_time;
            // ����ǰ����ʱ���ʱ��ƬС�ڵ����㣬��˵�����������
            s->stillneed_time = (s->stillneed_time - TIME_SLICE) > 0 ? s->stillneed_time - TIME_SLICE : 0;
            // ������+1
            s->time_count += 1;

            // ������̵���������ʱ��
            if (s->cpu_time == s->serve_time){
                total_run_time += (s->serve_time - old_cpu_time);
            }else{
                total_run_time += TIME_SLICE;
            }

            // �жϸý����Ƿ����
            if (s->stillneed_time == 0) {
                // �޸Ľ���״̬,������ɶ���
                s->state = process_type_finish;
                //finish_process.push_back(s);
                printf("�������\n");
                printf("��ǰ���̵���������ʱ�䣺%d\n",total_run_time);
                total_cometofinish_time += (total_run_time - s->arrive_time);
                printf("��ǰ���̵����㷨������תʱ�䣺%d\n",total_cometofinish_time);
            }else{
                s->state = process_type_wait;
            }

            // ��ǰ������ִ����
            if (s->state == process_type_finish){
                // ������ɽ��̵���������ɶ���ĩβ
                // 1.ͷָ��ָ����Ԫ������һ�����
                running_list->next = s->next;

                // 2.������������������뵽����ɶ��е���β��
                PCB *p = running_list;
                while (p->next != NULL) {
                    p = p->next;
                }
                p->next = s;
                s->next = NULL;

                // ���̵���������ʱ��С����һ���̵���ʱ��
                if (total_run_time < running_list->next->arrive_time){
                    // ��ǰ����ȫ��ִ���꣬�ȴ���һ���̵���
                    printf("��ǰ���̵���ִ��ʱ�䣺%d\n",total_run_time);
                    printf("��ǰû���½��̵���ȴ��½��̵���...\n");
                    printf("�ȴ�ʱ�䣺%d\n",running_list->next->arrive_time-total_run_time);
                    // ���½��̵���������ʱ��
                    total_run_time += running_list->next->arrive_time-total_run_time;
                    printf("��ǰ���̵���ִ��ʱ�䣺%d\n",total_run_time);
                }
            } else {
                // ��ǰ���̶��������������Ŷ�
                // 1.ͷָ��ָ����Ԫ������һ�����
                running_list->next = s->next;

                // 2.������������������뵽δ��ɶ��е���β��(���������ɵĶ���)
                PCB *p = running_list;
                // 2.1Ѱ�Ҳ���λ��
                while (p->next != NULL && p->next->arrive_time <= total_run_time && p->next->state != process_type_finish) {
                    p = p->next;
                }
                // 2.2�жϲ���λ��
                if (p->next == NULL) {
                    // ���һ��
                    p->next = s;
                    p->next->next = NULL;
                }else{
                    // �������һ����������н��
                    s->next = p->next;
                    p->next = s;
                }
            }
        }
        index = running_list->next;

        if(total_run_time >= index->arrive_time){
            set_run(running_list);
        }

        // չʾ��ǰ����״��
        printf("---------------------------------------------------------------------\n");
        show(running_list);
        printf("---------------------------------------------------------------------\n");
    }
    return total_cometofinish_time;
}

// ���ȼ������㷨
int highest_priority(PCB *running_list){

    // ��¼��һ������λ��
    PCB *highest = running_list->next;

    // �жϽ����Ƿ񵽴���̵����ѹ��೤ʱ��
    int total_run_time = 0;
    // ��¼�㷨�Ľ�������תʱ��
    int total_cometofinish_time = 0;

    // index��λ���еĵ�һ������
    PCB *index = highest;
    PCB *p = highest;
    while(index != NULL && index->state != process_type_finish){
        // ���½��̵���Ӧ��
        PCB *update = index;
        while(update != NULL && update->arrive_time <= total_run_time && update->state != process_type_finish){
			update->priority =  update->priority -  update->stillneed_time;
			update = update->next;
        }

	    // ��¼��һ�����̵ĵ�ǰ���ȼ�
		int highest_priority = index->priority;
        // ���ѵ���������ҵ�ǰ���ȼ���ߵĽ���
        while(p != NULL){
            if (p->arrive_time <= total_run_time && highest_priority < p->priority && p->state != process_type_finish) {
                highest = p;
            }
            p = p->next;
        }

        // ����������ҳ����ȼ���ߵĽ��̣��жϸý����Ƿ񵽴�
        // �ų�û�н��̵�������
        if (highest->arrive_time > total_run_time) {
            // ��ǰ���½��̵���
            // ��ǰ����ȫ��ִ���꣬�ȴ���һ���̵���
            printf("��ǰ���̵���ִ��ʱ�䣺%d\n",total_run_time);
            printf("��ǰû���½��̵���ȴ��½��̵���...\n");
            printf("�ȴ�ʱ�䣺%d\n",running_list->next->arrive_time - total_run_time);
            // ���½��̵���������ʱ��
            total_run_time += running_list->next->arrive_time - total_run_time;
            printf("��ǰ���̵���ִ��ʱ�䣺%d\n",total_run_time);
        } else {
            // ���е�ǰ���������е�ǰ���ȼ���ߵĽ���
            highest->state = process_type_run;

            printf("---------------------------------------------------------------------\n");
            show(running_list);
            printf("---------------------------------------------------------------------\n");

            // ��������ʱ��
            highest->stillneed_time = 0;
            // cpuʱ�� ->������ʱ��
            highest->cpu_time = highest->serve_time;
            // ����״̬����Ϊ���
            highest->state = process_type_finish;

            // ������̵���������ʱ��
            total_run_time += highest->serve_time;
            // ��¼�㷨�Ľ�������תʱ��
            total_cometofinish_time += total_run_time - highest->arrive_time;

            // ��������ĵ�ǰ���ȼ���ߵĽ��̵�������β
            if(running_list->next == highest){
                // ���������Ľ���Ϊ���еĵ�һ������
                // ��λ���һ������
                PCB *move = running_list->next;
                while(move->next != NULL){
                    move = move->next;
                }
                move->next = highest;
                running_list->next = highest->next;
                highest->next = NULL;
            }else{
                // ��λ��ǰ���ȼ���ߵĽ��̵�ǰһ������
                PCB *move1 = index;
                // ��λ���һ������
                PCB *move2 = index;
                while(move1->next != highest){
                    move1 = move1->next;
                }
                while(move2->next != NULL){
                    move2 = move2->next;
                }
                move1->next = highest->next;
                move2->next = highest;
                highest->next = NULL;
            }

            // չʾ��ǰ����״��
            printf("�������\n");
            printf("��ǰ���̵���ִ��ʱ�䣺%d\n",total_run_time);
            printf("��ǰ���̵����㷨������תʱ�䣺%d\n",total_cometofinish_time);
            printf("---------------------------------------------------------------------\n");
            show(running_list);
            printf("---------------------------------------------------------------------\n");
        }
        highest = running_list->next;
        index = highest;
        p = highest;
    }
    return total_cometofinish_time;
}


