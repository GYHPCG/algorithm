//#include <iostream>
//#include <string>
//#include <sstream>
//#include <vector>
//
//using namespace std;
//
//int main() {
//    vector<vector<int>> nums; // 二维动态数组，用于存储每行的数字
//    string line; // 用于存储每行输入
//    while (getline(cin, line)) { // 按行读取输入
//        istringstream iss(line); // 将每行字符串转换为istringstream对象
//        vector<int> row; // 用于存储当前行的数字
//        int num;
//        while (iss >> num) { // 从每行字符串中读取数字
//            row.push_back(num); // 将数字存入当前行的数组
//        }
//        nums.push_back(row); // 将当前行的数组存入二维数组中
//    }
//    // 输出二维数组中每个元素
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
pthread_mutex_t mutex;  //互斥信号量
pthread_cond_t cond;   //条件变量的数据类型，用于线程间的同步和通信
int mom_done = 0;
int daughter_done = 0;

void *daughter_thread(void *arg)
{
    printf("儿女线程：肚子饿了\n");
	pthread_mutex_lock(&mutex);
    printf("儿女线程：让妈妈做菜 \n");

    printf("儿女线程：等待妈妈做菜\n");
    pthread_cond_wait(&cond, &mutex);  // 等待妈妈做菜完成

    printf("儿女线程：等待妈妈唤醒吃饭\n");
    pthread_cond_wait(&cond, &mutex);  // 等待妈妈唤醒吃饭

    daughter_done = 1;
    printf("儿女线程：儿女线程正在吃饭\n");
    pthread_cond_signal(&cond);  // 通知妈妈线程儿女吃饭完毕

    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void *mom_thread(void *arg)
{
    printf("妈妈线程：儿女肚子饿了吗？\n");

    sleep(2);  // 模拟做菜时间

    pthread_mutex_lock(&mutex);
    printf("妈妈线程：饭做完了\n");
    pthread_cond_signal(&cond);  // 唤醒儿女线程，让儿女线程知道妈妈做好了菜

    printf("妈妈线程：儿女可以开始吃饭了\n");
    pthread_cond_signal(&cond);  // 告知儿女线程可以开始吃饭

    while (!daughter_done) {
        pthread_cond_wait(&cond, &mutex);  // 等待儿女吃饭完毕
    }

    printf("妈妈线程：儿女吃饭完毕\n");
    mom_done = 1;
    pthread_cond_signal(&cond);  // 通知儿女线程妈妈完成了任务

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


