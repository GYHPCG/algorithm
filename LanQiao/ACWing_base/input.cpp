//#include <iostream>
//#include <string>
//#include <sstream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    vector<vector<int>> nums; // ��ά��̬���飬���ڴ洢ÿ�е�����
//    string line; // ���ڴ洢ÿ������
//    while (getline(cin, line)) { // ���ж�ȡ����
//        istringstream iss(line); // ��ÿ���ַ���ת��Ϊistringstream����
//        vector<int> row; // ���ڴ洢��ǰ�е�����
//        int num;
//        while (iss >> num) { // ��ÿ���ַ����ж�ȡ����
//            row.push_back(num); // �����ִ��뵱ǰ�е�����
//        }
//        nums.push_back(row); // ����ǰ�е���������ά������
//    }
//    // �����ά������ÿ��Ԫ��
//    for (auto row : nums) {
//        for (auto num : row) {
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;  //�����ź���
pthread_cond_t cond;   //�����������������ͣ������̼߳��ͬ����ͨ��
int mom_done = 0;
int daughter_done = 0;

void *daughter_thread(void *arg)
{
    printf("��Ů�̣߳����Ӷ���\n");
	pthread_mutex_lock(&mutex);
    printf("��Ů�̣߳����������� \n");

    printf("��Ů�̣߳��ȴ���������\n");
    pthread_cond_wait(&cond, &mutex);  // �ȴ������������

    printf("��Ů�̣߳��ȴ����軽�ѳԷ�\n");
    pthread_cond_wait(&cond, &mutex);  // �ȴ����軽�ѳԷ�

    daughter_done = 1;
    printf("��Ů�̣߳���Ů�߳����ڳԷ�\n");
    pthread_cond_signal(&cond);  // ֪ͨ�����̶߳�Ů�Է����

    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void *mom_thread(void *arg)
{
    printf("�����̣߳���Ů���Ӷ�����\n");

    sleep(2);  // ģ������ʱ��

    pthread_mutex_lock(&mutex);
    printf("�����̣߳���������\n");
    pthread_cond_signal(&cond);  // ���Ѷ�Ů�̣߳��ö�Ů�߳�֪�����������˲�

    printf("�����̣߳���Ů���Կ�ʼ�Է���\n");
    pthread_cond_signal(&cond);  // ��֪��Ů�߳̿��Կ�ʼ�Է�

    while (!daughter_done) {
        pthread_cond_wait(&cond, &mutex);  // �ȴ���Ů�Է����
    }

    printf("�����̣߳���Ů�Է����\n");
    mom_done = 1;
    pthread_cond_signal(&cond);  // ֪ͨ��Ů�߳��������������

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t mom_tid, daughter_tid;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&mom_tid, NULL, mom_thread, NULL);
    pthread_create(&daughter_tid, NULL, daughter_thread, NULL);

	pthread_join(daughter_tid, NULL);
	pthread_join(mom_tid, NULL);

    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

      return 0;
}


