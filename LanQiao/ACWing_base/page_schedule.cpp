#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define UNSED -1 //初始化所有页帧为unsed,表示未使用
#define LEN 7   //页面帧的数量

//页帧队列
int mem_list[LEN];

//初始化队列
void init(int list[], int number) {
    for (int i = 0; i < number; i++) {
        list[i] = UNSED;
    }
}

//获取引用串
void get_reference_str(int reference_str[], int page_num)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < page_num; i++) {
        reference_str[i] = rand() % 10;
    }

}
//展示队列状态
void showList(int list[], int number) {
    for (int i = 0; i < number; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

//展示当前内存状态
void showmem_list(int list[], int page_frame_num) {
    for (int i = 0; i < page_frame_num; i++) {
        if (list[i] == UNSED) {
            break;
        }
        printf("|%d| \n", list[i]);
    }
    printf("\n");
}

void informationCount(int miss_count, int replace_count, int page_num) {
    printf("\n缺页次数:%d   缺页率:%d/%d = %.2f\n", miss_count, miss_count, page_num, miss_count*1.0 / page_num);
    double result = (double)(page_num - miss_count) / (double)page_num;
    printf("置换次数:%d  命中率:%.2f\n\n", replace_count, result);
}

//找到该页面下次要访问的位置
int get_next_pos(int cur_page, int cur_pos, int reference_str[], int page_num) {

    for (int i = cur_pos + 1; i < page_num; i++) {
        if (reference_str[i] == cur_page) {
            return i;
        }
    }

    return 100;
}

//最佳置换算法
void OPT(int mem_list[], int page_frame_num, int reference_str[], int page_num) {

    //置换次数
    int replace_count = 0;
    //缺页次数
    int miss_count = 0;

    //记录在内存的物理块的下一次访问位置
    int nextPosition[LEN];
    //int remote_index = 0;
    //初始化
    init(nextPosition, page_frame_num);

    //记录当前页面的访问情况: 0 未访问
    int visit;

    for (int i = 0; i < page_num; i++) {
        visit = 0;
        //判断是否需要置换->内存已满且需要访问的页面不在内存中
        for (int j = 0; j < page_frame_num; j++) {
            if (mem_list[j] == reference_str[i]) {
                //该页面已经存在内存中
                //记录下一次访问它的位置
                nextPosition[j] = get_next_pos(mem_list[j], i, reference_str, page_num);

                //修改访问情况
                visit = 1;

                //展示
			   	printf("访问的页面命中：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
            if (mem_list[j] == UNSED) {
                //页面不在内存中且内存未满->直接存入
                mem_list[j] = reference_str[i];
                nextPosition[j] = get_next_pos(mem_list[j], i, reference_str, page_num);

                miss_count++;

                //修改访问情况
                visit = 1;

                //展示
			    printf("访问的页面不命中，但页帧数不满：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
        }

        if (!visit) {

            //当前页面还没访问过
            //内存已满且当前访问不在内存中->进行置换
            //1.寻找到最晚才被访问到的页面
            int max = 0;
            for (int k = 1; k < page_frame_num; k++) {
                if (nextPosition[max] < nextPosition[k]) {
                    max = k;
                }
            }
            
            //2.将该位置的页面换出
            printf("访问的页面不命中：%d\n", reference_str[i]);
            printf("被置换的页面号是：%d\n", mem_list[max]);//打印被调出内存的页号
            mem_list[max] = reference_str[i];
            nextPosition[max] = get_next_pos(mem_list[max], i, reference_str, page_num);

            miss_count++;
            replace_count++;

            //展示
            showmem_list(mem_list, page_frame_num);
            printf("\n\n");
        }
    }
    informationCount(miss_count, replace_count, page_num);
}
//先进先出置换算法
void FIFO(int mem_list[], int page_frame_num, int reference_str[], int page_num) {

    //置换次数
    int replace_count = 0;
    //缺页次数
    int miss_count = 0;

    //记录当前最早进入内存的下标
    int pointer = 0;

    //记录当前页面的访问情况: 0 未访问
    int visit = 0;
    for (int i = 0; i < page_num; i++) {
        visit = 0;

        //判断是否需要置换->内存已满且需要访问的页面不在内存中
        for (int j = 0; j < page_frame_num; j++) {
            if (mem_list[j] == reference_str[i]) {
                //该页面已经存在内存中
                //修改访问情况
                visit = 1;
                //修改访问时间
                //展示
                printf("访问的页面命中：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
            if (mem_list[j] == UNSED) {
                //页面不在内存中且内存未满->直接存入
                mem_list[j] = reference_str[i];
                //修改访问情况
                visit = 1;
                miss_count++;
                //展示
                printf("访问的页面不命中，但页帧数不满：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
        }

        if (!visit) {
            //当前页面还未被访问过->需要进行页面置换
            //直接把这个页面存到所记录的下标中
            printf("访问的页面不命中：%d\n", reference_str[i]);
            printf("被置换的页面号是：%d\n", mem_list[pointer]);//打印被调出内存的页号
            mem_list[pointer] = reference_str[i];

            //下标指向下一个
            pointer++;

            //如果到了最后一个，将下标归零
            if (pointer > page_frame_num - 1) {
                pointer = 0;
            }

            miss_count++;
            replace_count++;

            //展示
            showmem_list(mem_list, page_frame_num);
            printf("\n\n");
        }
    }
    informationCount(miss_count, replace_count, page_num);
}

//最近最久未使用置换算法
void LRU(int mem_list[], int page_frame_num, int reference_str[], int page_num) {

    //置换次数
    int replace_count = 0;
    //缺页次数
    int miss_count = 0;

    //记录内存中最近一次访问至今的时间
    int timeRecord[LEN];
    //初始化
    init(timeRecord, page_frame_num);

    //记录当前页面的访问情况: 0 未访问
    int visit = 0;

    //记录已经在内存中的页面数量
    int pageCount = 0;
    for (int i = 0; i < page_num; i++) {
        visit = 0;

        //时间加一
        for (int p = 0; p < pageCount; p++) {
            if (mem_list[p] != UNSED) {
                timeRecord[p] ++;
            }
        }

        //是否需要置换
        for (int j = 0; j < page_frame_num; j++) {
            if (mem_list[j] != UNSED) {
                timeRecord[j] ++;
            }
            if (mem_list[j] == reference_str[i]) {
                //该页面已经存在内存中
                //修改访问情况
                visit = 1;
                //重置访问时间
                timeRecord[j] = UNSED;
                //展示
				printf("访问的页面命中：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
            if (mem_list[j] == UNSED) {
                //页面不在内存中且内存未满->直接存入
                mem_list[j] = reference_str[i];
                pageCount++;
                //修改访问情况
                visit = 1;
                //修改访问时间
                timeRecord[j] ++;

                miss_count++;
                //展示
			    printf("访问的页面不命中，但页帧数不满：%d\n", reference_str[i]);
                showmem_list(mem_list, page_frame_num);
                printf("\n\n");
                break;
            }
        }

        if (!visit) {
            //需要置换
            //1.遍历时间记录表，寻找最久未访问的页面所在的内存下标
            int max = 0;
            for (int k = 0; k < page_frame_num; k++) {
                if (timeRecord[max] < timeRecord[k]) {
                    max = k;
                }
            }
            printf("访问的页面不命中：%d\n", reference_str[i]);
            printf("被置换的页面号是：%d\n", mem_list[max]);//打印被调出内存的页号
            //2.将该位置的页面换出
            mem_list[max] = reference_str[i];
            timeRecord[max] = UNSED;

            miss_count++;
            replace_count++;

            //展示队列
            showmem_list(mem_list, page_frame_num);
            printf("\n\n");

        }
    }
    informationCount(miss_count, replace_count, page_num);
}
void show_reference_str(int reference_str[], int page_num)
{
	printf("生成长度为%d的引用串:\n", page_num);
    showList(reference_str, page_num);
}
void choose_page_replace_algorithm(int reference_str[],int page_frame_num, int page_num)
{
	int chose;
    printf("请选择所需的置换算法:\n");
    printf("1.FIFO 2.OPT 3.LRU");
    printf("你选择的置换算法是: %d", page_num);
    scanf("%d", &chose);
    printf("\n");
    switch (chose) {
    case 1:
		show_reference_str(reference_str, page_num);
		FIFO(mem_list, page_frame_num, reference_str, page_num);
        break;
    case 2:
		show_reference_str(reference_str, page_num);
	    OPT(mem_list, page_frame_num, reference_str, page_num);
        break;
    case 3:
		show_reference_str(reference_str, page_num);
        LRU(mem_list, page_frame_num, reference_str, page_num);
        break;
    default:
        return;
    }

}
int main()
{

    //进程页帧的数量
    int page_frame_num;
    printf("请输入页帧数: ");
    scanf("%d", &page_frame_num);

    //初始化内存状态
    init(mem_list, page_frame_num);//未使用的内存块标记为UNSED；

    //页面数量
    int page_num;
    printf("请输入要访问的引用串长度: ");
    scanf("%d", &page_num);

    //保存页面号引用串
    int reference_str[100];
	get_reference_str(reference_str, page_num);
	
	// 选择算法
    choose_page_replace_algorithm(reference_str,page_frame_num, page_num);
    
    return 0;
}