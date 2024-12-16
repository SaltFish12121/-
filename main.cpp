#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MemoryPageNumber 3 	// 最多允许的内存页面 
#define MemoryHistorySize 100 // 假设我们最多记录100次分配历史

// 作业结构体
typedef struct Task{ 
    // 作业名
    char process_name[5];    
    // 到达时间
    int arrive_time;
    // 新增优先级字段
    int priority; 
    // cpu运行所需时间
		int need_time; 
    // 进程状态：运行 W、就绪 R、阻塞 B、完成 F
    // 但完成状态不显示在进程队列中，完成则调出内存 
    char status;
    // 进程阻塞时长
    int block_time; 
    // 指令条数 
    int instruction_number;
    // 页表号 
    int table_number; 

//    // 后向指针
//    Task *next; 
}Task; 

// 页表结构
typedef struct PageTable{
	// 页号
	int page_number;
	// 对应的物理块 
	int physical_block_number;
	// 是否执行完  完成， 未完成 
	bool ifFinsih; 
}PageTable; 

// 内存页面 
typedef struct MemoryPage{
	// 块号 
	int block_number;
	// 指令名称 
	char instruction_name[10];
	// 阻塞时间 
	int block_time;
}MemoryPage;


// 创建五个进程的数组
Task tasks[5] = {
    {"T1", 0, 9, 13, 'R', 0, 13, 1},
    {"T2", 1, 34, 8, 'R', 0, 8, 2},
    {"T3", 2, 30, 14, 'R', 0, 14, 3},
    {"T4", 3, 29, 11, 'R', 0, 11, 4},
    {"T5", 4, 10, 12, 'R', 0, 12, 5}
};


// 每个进程的页表
PageTable pageTable1[13] = {
		{1,1,false},
		{2,1,false},
		{3,1,false},
		{1,1,false},
		{5,1,false},
		{6,1,false},
		{7,1,false},
		{8,1,false},
		{9,1,false},
		{10,1,false},
		{1,2,false},
		{2,2,false},
		{3,2,false}
}; 

PageTable pageTable2[8] = {
		{1,1,false},
		{2,1,false},
		{3,1,false},
		{4,1,false},
		{5,1,false},
		{6,1,false},
		{7,1,false},
		{8,1,false}
}; 

PageTable pageTable3[14] = {
		{1,1,false},
		{2,1,false},
		{3,1,false},
		{4,1,false},
		{5,1,false},
		{6,1,false},
		{7,1,false},
		{8,1,false},
		{9,1,false},
		{10,1,false},
		{1,2,false},
		{2,2,false},
		{3,2,false},
		{4,2,false}
}; 

PageTable pageTable4[11] = {
		{1,1,false},
		{2,1,false},
		{3,1,false},
		{4,1,false},
		{5,1,false},
		{6,1,false},
		{7,1,false},
		{8,1,false},
		{9,1,false},
		{10,1,false},
		{1,2,false}
}; 

PageTable pageTable5[12] = {
		{1,1,false},
		{2,1,false},
		{3,1,false},
		{4,1,false},
		{5,1,false},
		{6,1,false},
		{7,1,false},
		{8,1,false},
		{9,1,false},
		{10,1,false},
		{1,2,false},
		{2,2,false}
}; 

// 十个页面 （模拟的内存物理块）
MemoryPage page1[2] = {
	{1, "11", 0},
	{2, "12", 0},
}; 

MemoryPage page2[2] = {
	{1, "21", 0},
	{2, "22", 0},
}; 

MemoryPage page3[2] = {
	{1, "31", 0},
	{2, "32", 0},
}; 

MemoryPage page4[2] = {
	{1, "41", 0},
	{2, "42", 0},
}; 

MemoryPage page5[1] = {
	{1, "51", 0}
}; 

MemoryPage page6[1] = {
	{1, "61", 0}
}; 

MemoryPage page7[1] = {
	{1, "71", 0}
}; 

MemoryPage page8[1] = {
	{1, "81", 0}
};

MemoryPage page9[1] = {
	{1, "91", 0}
};

MemoryPage page10[1] = {
	{1, "101", 0}
};


// 分配的页面
int Memory[MemoryHistorySize][MemoryPageNumber] = {0}; // 初始化所有页面为未分配状态
int current_history_index = 0; // 当前历史索引 
int current_time = 0;	// 当前时间 

// 全局数组，记录每个页面最后一次被访问的时间
int last_used[10] = {0}; // 假设有10个页面

// 页表 
PageTable *pageTables[5] = {pageTable1, pageTable2, pageTable3, pageTable4, pageTable5};
	
// 模拟内存物理块，存储：块号、指令名称、（如果可以阻塞，则给出阻塞时间)
MemoryPage *pages[10] = {page1, page2, page3, page4, page5, page6, page7, page8, page9, page10};

// 模拟进程执行指令

// 处理缺页中断


// 更新任务优先级 
void update_priority(Task tasks[], int task_count);
// 找到优先级最高的任务
int find_highest_priority_task(Task tasks[], int task_count, int last_number);
// 打印页表 
void print_page_table(PageTable *pageTable, int pageTableSize); 
// 模拟任务执行
void simulate_task_execution(Task *task, int memory_size);
// 页面置换 
void page_replacement(int new_page, PageTable *pageTable, int index);

// 打印任务状态
void print_task_status(Task tasks[], int task_count);
// 打印页面状态
void print_page_status(MemoryPage *pages[], int memory_size);
// 更新最后使用时间
//void update_last_used(MemoryPage *pages[], int memory_size, int *last_used[], int current_time);


int find_lru_page(MemoryPage memory[][2], int size);
void simulate_scheduling(Task tasks[], PageTable *pageTables[], int task_count, MemoryPage *pages[], int memory_size);


// 抢占式动态优先级调度算法
/**
 * 当前任务：增加阻塞挂起和完成阻塞 
 * 修改成为LRU 
 */
int main() {
		int task_count = 5;
	
	  // 初始化最后使用时间数组
	  int last_used[10] = {0}; // 假设有10个页面
	  
	  int memory_size = 10; // 假设有10个内存页面
	  
	  Task comeTasks[5] = {};	// 到达任务 
	 	int comeTask_count = 0; // 到达任务数
		
		int last_number= -1; // 上一次最高优先级 
		
		// 等待区(按到达顺序） 
		Task awaitTasks[5] = {
		    {"T1", 0, 9, 13, 'R', 0, 13, 1},
		    {"T2", 1, 34, 8, 'R', 0, 8, 2},
		    {"T3", 2, 30, 14, 'R', 0, 14, 3},
		    {"T4", 3, 29, 11, 'R', 0, 11, 4},
		    {"T5", 4, 10, 12, 'R', 0, 12, 5}
		};
		
		/*
		主要修改 comeTasks和 awaitTasks
		Tasks不应该作为修改 
		*/
		

    // 模拟操作系统运行
    while (1) {
	   		// 存储到达的任务 
	   		if (tasks[comeTask_count].arrive_time <= current_time && comeTask_count < task_count) {
	   			// comeTasks进入 
	   			comeTasks[comeTask_count] = tasks[comeTask_count];
	   			printf("\t\t\t任务到达\n");
	   			printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
	   			printf("\t%s \t%c \t%d \t%d \t%d \t%d \t%d\n", 
					 comeTasks[comeTask_count].process_name, comeTasks[comeTask_count].status, comeTasks[comeTask_count].arrive_time, 
					 comeTasks[comeTask_count].priority, comeTasks[comeTask_count].need_time, comeTasks[comeTask_count].instruction_number, comeTasks[comeTask_count].table_number); 
					printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
					comeTask_count +=1 ;
				}

    	
        // 更新任务优先级
        update_priority(comeTasks, comeTask_count);
        
        // 打印当前任务状态
        print_task_status(comeTasks, comeTask_count);

        // 找到优先级最高的任务
        int highest_priority_index = find_highest_priority_task(comeTasks, comeTask_count, last_number);
        if (highest_priority_index == -1) {
            // 没有到达的任务，增加时间单位
            current_time++;
            continue;
        }
        // 当前优先级最高的任务 
        Task *current_task = &comeTasks[highest_priority_index];
        last_number =  highest_priority_index;
				printf("当前优先级最高的任务为： %s 优先级为：%d   执行该任务\n\n", current_task->process_name, current_task->priority);
				printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");

    		// 找到对应的页表 
    		PageTable *pageTable = pageTables[current_task->table_number - 1];
    		printf("进程 %s 的页表： \n", current_task->process_name);
    		
				// 打印页表 
				print_page_table(pageTable, current_task->instruction_number); 
				
				
        // 模拟任务执行(只执行一条) 
        simulate_task_execution(current_task, memory_size);

				// 打印需要时间
				printf("需要时间:%d\n\n", current_task->need_time) ;

//        // 打印当前页面状态
//        print_page_status(pages, memory_size);

        // 检查任务是否完成
        if (current_task->need_time == 0) {
        	printf("标记为完成\n"); 
          current_task->status = 'F'; // 标记为完成
          awaitTasks[highest_priority_index].status = 'F';
        } else if (current_task->status == 'R') {
            // 如果任务仍没有结束，则说明发生阻塞，更新最后使用时间
//            update_last_used(pages, memory_size, last_used);
        }
//
        // 检查是否所有任务都已完成
        int all_tasks_finished = 1;
        for (int i = 0; i < task_count; i++) {
            if (awaitTasks[i].status != 'F') {
            		printf("未完成 %d %c \n", i+1, comeTasks[i].status); 
                all_tasks_finished = 0;
                break;
            }
        }
        if (all_tasks_finished) {
        	  printf("自动完成%d\n", current_time); 
            break; // 所有任务完成，结束模拟
        }

        current_time++; // 更新时间片
        
        
//        // 测试用
//				if (current_time >= 200) {
//					printf("强行结束\n");
//					break;
//				} 
    }
		
		printf("完成!\n");
    return 0;
}


// 更新任务优先级并打印每个任务的优先级
void update_priority(Task tasks[], int task_count) {
    for (int i = 0; i < task_count; i++) {
        Task *task = &tasks[i];

        // 只更新已到达且未完成的任务
        if (task->arrive_time <= current_time && task->status != 'F') {
            // 如果任务正在运行，每个时间片结束后降低其优先级
            if (task->status == 'W') {
                task->priority = task->priority > 1 ? task->priority - 1 : 1; // 防止优先级降到0或以下
            }
            // 如果任务处于就绪状态，增加其优先级
            else if (task->status == 'R') {
                task->priority += 1;
            }
            // 如果任务处于阻塞状态，优先级不变
            else if (task->status == 'B') {
                // 优先级保持不变
            }
        }

//        // 打印任务的名称、优先级和状态
//        printf("任务 %s: 优先级 %d, 状态 %c\n", task->process_name, task->priority, task->status);
    }
}


// 找到优先级最高的任务
int find_highest_priority_task(Task tasks[], int task_count, int last_number) {
    int highest_priority_index = -1;
    int highest_priority = -1;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].status != 'F' && tasks[i].priority > highest_priority) {
            highest_priority = tasks[i].priority;
            highest_priority_index = i;
        }
    }
    
    if (tasks[last_number].status == 'F') {
        printf("任务 %s: 状态 %c, 优先级 %d    已结束\n", tasks[last_number].process_name, tasks[last_number].status, tasks[last_number].priority);
		}
    
    if (last_number != -1 && tasks[last_number].status != 'F' && last_number != highest_priority_index) {
    	printf("任务 %s   进入阻塞\n", tasks[last_number].process_name);
    	tasks[last_number].status = 'B';
		} 
    
    return highest_priority_index;
}


// 打印页表 
void print_page_table(PageTable *pageTable, int pageTableSize) {
    printf("页表内容：\n");
    printf("页号\t物理块号\t是否完成\n");
    for (int i = 0; i < pageTableSize; i++) {
        if (pageTable[i].page_number == 0) {
            // 假设页号为0表示页表结束
            break;
        }
        printf("%d\t%d\t\t%d\n", pageTable[i].page_number, pageTable[i].physical_block_number, pageTable[i].ifFinsih);
    }
}


//  模拟任务执行
void simulate_task_execution(Task *task, int memory_size) {
		// 切换状态
		task->status = 'W' ;
	
	 	// 找到对应的页表 
    PageTable *pageTable = pageTables[task->table_number - 1];
    
    // 依次执行页表中记录地址的程序 
    
    for (int i = 0; i < task->instruction_number; i++) {
    	// 只进行一个，且第一个未完成的 
    	if (!pageTable[i].ifFinsih) {
    		int page_number = pageTable[i].page_number; // 假设页表中存储的是页号
    	  int block_number = pageTable[i].physical_block_number; // 物理块号 
    	  
        int found = 0;
        		
        // 检查页面是否已经加载
		    for (int j = 0; j < MemoryPageNumber; j++) {
		        if (Memory[current_history_index][j] == page_number) {
		            found = 1;
		            break;
		        }
		    }
		      
		    if (!found) {
            // 页面未找到，发生缺页
            printf("缺页中断：需要页面 %d\n", page_number);
//            int current_time = i; // 假设当前时间是指令序号
            page_replacement(page_number, pageTable, i);
            
            // 打印当前Memory
						for(int i=0;i<=current_history_index;i++) {
							for(int j=0;j<MemoryPageNumber;j++) {
								printf("\t%d",Memory[i][j]);
							}
							printf("\n");
						} 
        } else {
		        // 页面原本就有，更新最后使用时间
		        last_used[page_number] = current_time;
				}
        
        // 确保拥有页面，然后进行正常操作  
        printf("页号%d,物理块号%d\n", page_number, block_number);
        // 按照页号和物理块号找寻指令
//				printf("执行指令：%s, 阻塞时长：%d\n\n", pages[page_number-1][block_number-1].instruction_name, pages[page_number-1][block_number-1].block_time);
		    
		    if (pages[page_number-1][block_number-1].block_time != 0) {
		    	// 进入阻塞
					printf("指令：%s 进入阻塞\n", pages[page_number-1][block_number-1].instruction_name);
					
					// 减少已经阻塞时间 
//					pages[page_number-1][block_number-1].block_time -=1 ; 

					// 修改当前进程状态
					task->status = 'B' ;

					// 进程切换
					
					
					
					break;
					 
				}
		    
		    task->need_time -=1 ;
		    
		    printf("执行指令：%s 完成\n", pages[page_number-1][block_number-1].instruction_name);
				pageTables[task->table_number - 1][i].ifFinsih = true;
				
				current_time += 1;
				break; 
			}

    }
}


// 打印当前内存中所有页面的最后使用时间
void print_last_used_times() {
	  printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
    printf("当前内存中所有页面的最后使用时间：\n");
    for (int i = 0; i < MemoryPageNumber; i++) {
        // 检查页面是否已分配
        if (Memory[current_history_index][i] != 0) {
            printf("页面号：%d  最后使用时间：%d\n", Memory[current_history_index][i], last_used[Memory[current_history_index][i]]);
        }
    }
    printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
}

// 执行页面置换，使用 LRU 算法
void page_replacement(int new_page, PageTable *pageTable, int index) {
		print_last_used_times();
		
    // 查找新页面是否已在内存中
    int found = 0;
    for (int j = 0; j < MemoryPageNumber; j++) {
        if (Memory[current_history_index][j] == new_page) {
            found = 1;
            break;
        }
    }

    if (!found) {
        // 新页面不在内存中，需要置换

        // 查找最久未使用的页面
        int lru_index = -1;
        int min_last_used_time = current_time; // 使用当前时间作为初始值
        for (int i = 0; i < MemoryPageNumber; i++) {
            if (last_used[Memory[current_history_index][i]] < min_last_used_time) {
                min_last_used_time = last_used[Memory[current_history_index][i]];
                lru_index = i;
            }
        }

        if (lru_index != -1) {
            // 替换最久未使用的页面
            Memory[current_history_index][lru_index] = new_page;
            last_used[new_page] = current_time; // 更新最后使用时间
       		 	printf("最久未使用的页面为：%d  最后使用时间: %d\n", Memory[current_history_index][lru_index], min_last_used_time);
            printf("LRU页面置换：页面 %d 被替换为页面 %d\n", Memory[current_history_index][lru_index], new_page);
        } else {
            // 没有找到合适的页面进行置换，可能是因为内存已满且没有页面被使用过
            printf("内存已满，无法进行页面置换\n");
        }
    } else {
        // 页面已在内存中，更新最后使用时间
        last_used[new_page] = current_time;
    }
}


// 打印任务状态
void print_task_status(Task tasks[], int task_count) {
		if (task_count > 5) {
			task_count = 5;
		} 
		printf("                                  当前各进程PCB信息                                  \n");
		printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
    for (int i = 0; i < task_count; i++) {
        printf("任务 %s: 状态 %c, 优先级 %d\n", tasks[i].process_name, tasks[i].status, tasks[i].priority);
    }
    printf("﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀﹀\n");
}


//// 打印页面状态
//void print_page_status(MemoryPage *pages[], int memory_size) {
//    for (int i = 0; i < memory_size; i++) {
//        for (int j = 0; j < 2; j++) { // 假设每个内存页面数组有两个MemoryPage
//            printf("页面 %d: 块号 %d, 指令 '%s', 阻塞时间 %d\n", i, pages[i][j].block_number, pages[i][j].instruction_name, pages[i][j].block_time);
//        }
//    }
//}


