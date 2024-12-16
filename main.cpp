#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MemoryPageNumber 3 	// ���������ڴ�ҳ�� 
#define MemoryHistorySize 100 // ������������¼100�η�����ʷ

// ��ҵ�ṹ��
typedef struct Task{ 
    // ��ҵ��
    char process_name[5];    
    // ����ʱ��
    int arrive_time;
    // �������ȼ��ֶ�
    int priority; 
    // cpu��������ʱ��
		int need_time; 
    // ����״̬������ W������ R������ B����� F
    // �����״̬����ʾ�ڽ��̶����У����������ڴ� 
    char status;
    // ��������ʱ��
    int block_time; 
    // ָ������ 
    int instruction_number;
    // ҳ��� 
    int table_number; 

//    // ����ָ��
//    Task *next; 
}Task; 

// ҳ��ṹ
typedef struct PageTable{
	// ҳ��
	int page_number;
	// ��Ӧ������� 
	int physical_block_number;
	// �Ƿ�ִ����  ��ɣ� δ��� 
	bool ifFinsih; 
}PageTable; 

// �ڴ�ҳ�� 
typedef struct MemoryPage{
	// ��� 
	int block_number;
	// ָ������ 
	char instruction_name[10];
	// ����ʱ�� 
	int block_time;
}MemoryPage;


// ����������̵�����
Task tasks[5] = {
    {"T1", 0, 9, 13, 'R', 0, 13, 1},
    {"T2", 1, 34, 8, 'R', 0, 8, 2},
    {"T3", 2, 30, 14, 'R', 0, 14, 3},
    {"T4", 3, 29, 11, 'R', 0, 11, 4},
    {"T5", 4, 10, 12, 'R', 0, 12, 5}
};


// ÿ�����̵�ҳ��
PageTable pageTable1[13] = {
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

// ʮ��ҳ�� ��ģ����ڴ�����飩
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


// �����ҳ��
int Memory[MemoryHistorySize][MemoryPageNumber] = {0}; // ��ʼ������ҳ��Ϊδ����״̬
int current_history_index = 0; // ��ǰ��ʷ���� 
int current_time = 0;	// ��ǰʱ�� 

// ҳ�� 
PageTable *pageTables[5] = {pageTable1, pageTable2, pageTable3, pageTable4, pageTable5};
	
// ģ���ڴ�����飬�洢����š�ָ�����ơ�������������������������ʱ��)
MemoryPage *pages[10] = {page1, page2, page3, page4, page5, page6, page7, page8, page9, page10};

// ģ�����ִ��ָ��

// ����ȱҳ�ж�


// �����������ȼ� 
void update_priority(Task tasks[], int task_count);
// �ҵ����ȼ���ߵ�����
int find_highest_priority_task(Task tasks[], int task_count, int last_number);
// ��ӡҳ�� 
void print_page_table(PageTable *pageTable, int pageTableSize); 
// ģ������ִ��
void simulate_task_execution(Task *task, int memory_size);
// ҳ���û� 
void page_replacement(int new_page, PageTable *pageTable, int index);

// ��ӡ����״̬
void print_task_status(Task tasks[], int task_count);
// ��ӡҳ��״̬
void print_page_status(MemoryPage *pages[], int memory_size);
// �������ʹ��ʱ��
//void update_last_used(MemoryPage *pages[], int memory_size, int *last_used[], int current_time);


int find_lru_page(MemoryPage memory[][2], int size);
void simulate_scheduling(Task tasks[], PageTable *pageTables[], int task_count, MemoryPage *pages[], int memory_size);


// ��ռʽ��̬���ȼ������㷨
int main() {
		int task_count = 5;
	
	  // ��ʼ�����ʹ��ʱ������
	  int last_used[10] = {0}; // ������10��ҳ��
	  
	  int memory_size = 10; // ������10���ڴ�ҳ��
	  
	  Task comeTasks[5] = {};	// �������� 
	 	int comeTask_count = 0; // ����������
		
		int last_number= -1; // ��һ��������ȼ� 
		
		// �ȴ���(������˳�� 
		Task awaitTasks[5] = {
		    {"T1", 0, 9, 13, 'R', 0, 13, 1},
		    {"T2", 1, 34, 8, 'R', 0, 8, 2},
		    {"T3", 2, 30, 14, 'R', 0, 14, 3},
		    {"T4", 3, 29, 11, 'R', 0, 11, 4},
		    {"T5", 4, 10, 12, 'R', 0, 12, 5}
		};
		
		/*
		��Ҫ�޸� comeTasks�� awaitTasks
		Tasks��Ӧ����Ϊ�޸� 
		*/
		

    // ģ�����ϵͳ����
    while (1) {
	   		// �洢��������� 
	   		if (tasks[comeTask_count].arrive_time <= current_time && comeTask_count <= task_count) {
	   			// comeTasks���� 
	   			comeTasks[comeTask_count] = tasks[comeTask_count];
	   			printf("���񵽴�\t%s \t%c \t%d \t%d \t%d \t%d \t%d\n", 
					 comeTasks[comeTask_count].process_name, comeTasks[comeTask_count].status, comeTasks[comeTask_count].arrive_time, 
					 comeTasks[comeTask_count].priority, comeTasks[comeTask_count].need_time, comeTasks[comeTask_count].instruction_number, comeTasks[comeTask_count].table_number); 
					comeTask_count +=1 ;
				}

    	
        // �����������ȼ�
        update_priority(comeTasks, comeTask_count);

        // �ҵ����ȼ���ߵ�����
        int highest_priority_index = find_highest_priority_task(comeTasks, comeTask_count, last_number);
        if (highest_priority_index == -1) {
            // û�е������������ʱ�䵥λ
            current_time++;
            continue;
        }
        // ��ǰ���ȼ���ߵ����� 
        Task *current_task = &comeTasks[highest_priority_index];
        last_number =  highest_priority_index;
				printf("��ǰ���ȼ���ߵ�����Ϊ�� %s ���ȼ�Ϊ��%d \n", current_task->process_name, current_task->priority);

    		// �ҵ���Ӧ��ҳ�� 
    		PageTable *pageTable = pageTables[current_task->table_number - 1];
    		printf("���� %s ��ҳ�� \n", current_task->process_name);
				// ��ӡҳ�� 
				print_page_table(pageTable, current_task->instruction_number); 

        // ģ������ִ��(ִֻ��һ��) 
        simulate_task_execution(current_task, memory_size);

				// ��ӡ��Ҫʱ��
				printf("��Ҫʱ��:%d\n\n", current_task->need_time) ;
				
        // ��ӡ��ǰ����״̬
//        print_task_status(comeTasks, comeTask_count);

//        // ��ӡ��ǰҳ��״̬
//        print_page_status(pages, memory_size);
//
        // ��������Ƿ����
        if (current_task->need_time == 0) {
        	printf("���Ϊ���\n"); 
          current_task->status = 'F'; // ���Ϊ���
          awaitTasks[highest_priority_index].status = 'F';
        } else if (current_task->status == 'R') {
            // ���������û�н�������˵�������������������ʹ��ʱ��
//            update_last_used(pages, memory_size, last_used);
        }
//
        // ����Ƿ��������������
        int all_tasks_finished = 1;
        for (int i = 0; i < task_count; i++) {
            if (awaitTasks[i].status != 'F') {
            		printf("δ��� %d %c \n", i+1, awaitTasks[i].status); 
                all_tasks_finished = 0;
                break;
            }
        }
        if (all_tasks_finished) {
        	  printf("�Զ����%d\n", current_time); 
            break; // ����������ɣ�����ģ��
        }

        current_time++; // ����ʱ��Ƭ
        
        
//        // ������
//				if (current_time >= 200) {
//					printf("ǿ�н���\n");
//					break;
//				} 
    }
		
		printf("���!\n");
    return 0;
}


// �����������ȼ�����ӡÿ����������ȼ�
void update_priority(Task tasks[], int task_count) {
    for (int i = 0; i < task_count; i++) {
        Task *task = &tasks[i];

        // ֻ�����ѵ�����δ��ɵ�����
        if (task->arrive_time <= current_time && task->status != 'F') {
            // ��������������У�ÿ��ʱ��Ƭ�����󽵵������ȼ�
            if (task->status == 'W') {
                task->priority = task->priority > 1 ? task->priority - 1 : 1; // ��ֹ���ȼ�����0������
            }
            // ��������ھ���״̬�����������ȼ�
            else if (task->status == 'R') {
                task->priority += 1;
            }
            // �������������״̬�����ȼ�����
            else if (task->status == 'B') {
                // ���ȼ����ֲ���
            }
        }

        // ��ӡ��������ơ����ȼ���״̬
        printf("���� %s: ���ȼ� %d, ״̬ %c\n", task->process_name, task->priority, task->status);
    }
}


// �ҵ����ȼ���ߵ�����
int find_highest_priority_task(Task tasks[], int task_count, int last_number) {
    int highest_priority_index = -1;
    int highest_priority = -1;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].status != 'F' && tasks[i].priority > highest_priority) {
            highest_priority = tasks[i].priority;
            highest_priority_index = i;
        }
    }
    
    if (last_number != -1 && tasks[last_number].status != 'F') {
    	tasks[last_number].status = 'B';
		} 
    
    return highest_priority_index;
}


// ��ӡҳ�� 
void print_page_table(PageTable *pageTable, int pageTableSize) {
    printf("ҳ�����ݣ�\n");
    printf("ҳ��\t������\t�Ƿ����\n");
    for (int i = 0; i < pageTableSize; i++) {
        if (pageTable[i].page_number == 0) {
            // ����ҳ��Ϊ0��ʾҳ�����
            break;
        }
        printf("%d\t%d\t%d\n", pageTable[i].page_number, pageTable[i].physical_block_number, pageTable[i].ifFinsih);
    }
}


//  ģ������ִ��
void simulate_task_execution(Task *task, int memory_size) {
		// �л�״̬
		task->status = 'W' ;
	
	 	// �ҵ���Ӧ��ҳ�� 
    PageTable *pageTable = pageTables[task->table_number - 1];
    
    // ����ִ��ҳ���м�¼��ַ�ĳ��� 
    
    for (int i = 0; i < task->instruction_number; i++) {
    	// ֻ����һ�����ҵ�һ��δ��ɵ� 
    	if (!pageTable[i].ifFinsih) {
    		int page_number = pageTable[i].page_number; // ����ҳ���д洢����ҳ��
    	  int block_number = pageTable[i].physical_block_number; // ������ 
    	  
        int found = 0;
        		
        // ���ҳ���Ƿ��Ѿ�����
		    for (int j = 0; j < MemoryPageNumber; j++) {
		        if (Memory[current_history_index][j] == page_number) {
		            found = 1;
		            break;
		        }
		    }
		      
		    if (!found) {
            // ҳ��δ�ҵ�������ȱҳ
            printf("ȱҳ�жϣ���Ҫҳ�� %d\n", page_number);
//            int current_time = i; // ���赱ǰʱ����ָ�����
            page_replacement(page_number, pageTable, i);
            
            // ��ӡ��ǰMemory
						for(int i=0;i<=current_history_index;i++) {
							for(int j=0;j<MemoryPageNumber;j++) {
								printf("\t%d",Memory[i][j]);
							}
							printf("\n");
						} 
        }
        
        // ȷ��ӵ��ҳ�棬Ȼ�������������  
        printf("ҳ��%d,������%d\n", page_number, block_number);
        // ����ҳ�ź���������Ѱָ��
//				printf("ִ��ָ�%s, ����ʱ����%d\n\n", pages[page_number-1][block_number-1].instruction_name, pages[page_number-1][block_number-1].block_time);
		    
		    if (pages[page_number-1][block_number-1].block_time != 0) {
		    	// ��������
					printf("ָ�%s ��������\n", pages[page_number-1][block_number-1].instruction_name);
					
					// �����Ѿ�����ʱ�� 
//					pages[page_number-1][block_number-1].block_time -=1 ; 

					// �޸ĵ�ǰ����״̬
					task->status = 'B' ;

					// �����л�
					
					
					
					break;
					 
				}
		    
		    task->need_time -=1 ;
		    
		    printf("ִ��ָ�%s ���\n", pages[page_number-1][block_number-1].instruction_name);
				pageTables[task->table_number - 1][i].ifFinsih = true;
				
				current_time += 1;
				break; 
			}

    }
}


// ִ��ҳ���û�
// ������һ���е�û�� 
void page_replacement(int new_page, PageTable *pageTable, int index) {
	
	
	// �Ѿ����� 
//	int LRU[MemoryPageNumber] = {0,0,0}; 
	int a[3] = { Memory[current_history_index][0], Memory[current_history_index][1], Memory[current_history_index][2] };
	int count[3] = {0,0,0} ;
	int ifCount[3] = {1,1,1} ;
	
	// �Ȳ�һ�飬����ԭ����0
	for (int j = 0; j < MemoryPageNumber; j++) {
		if (Memory[current_history_index][j] == 0) {
			// ����0�����滻���ҷ���
			printf("���ȱҳ���룬��ԭ����%d����λ�÷��뵱ǰҳ�ţ�%d\n", j+1, new_page); 
			// �ȸ��ƣ����滻 
			// �����������滻����һ�У� ���ϸ�����һ�� 
			current_history_index ++ ; 
			Memory[current_history_index][0] = Memory[current_history_index-1][0];
			Memory[current_history_index][1] = Memory[current_history_index-1][1];
			Memory[current_history_index][2] = Memory[current_history_index-1][2];
			Memory[current_history_index][j] = new_page;
			

			return ;
		}
	}
	
	
	// �����ĸ�λ��������δʹ��
	for (int i = current_history_index - 1; i >= 0; i--) {
		// һ��㵹���� 
		for (int j = 0; j < MemoryPageNumber; j++) {
			if (ifCount[j] && Memory[i][j] == a[j]) {
				count[j] += 1;
			} else {
				// ���ֲ�����������ټ� 
				ifCount[j] = 0;
			} 
		}
		
		
		if (count[0] != count[1] && count[0] != count[2] && count[1] != count[2]) {
			// �ҵ����Ľ����û�
			int index = 0; 
			if (count[0] > count[1]) {
				if (count[0] > count[2]) {
					// ��һ�����
					index = 0; 
				} else {
					// ���������
					index = 2; 
				}
			}  else {
		    if (count[1] > count[2]) {
		      // �ڶ������
		      index = 1; 
		    } else {
		      // ���������
		      index = 2; 
		    }
			}
			
		
			printf("���ȱҳ�û�����ԭ����%d��λ�ã��û���ҳ�棺%d,���뵱ǰҳ�棺%d\n", index+1, Memory[current_history_index][index], new_page); 

			// �ȸ��ƣ����滻 
			// �����������滻����һ�У� ���ϸ�����һ�� 
			current_history_index ++ ; 
			Memory[current_history_index][0] = Memory[current_history_index-1][0];
			Memory[current_history_index][1] = Memory[current_history_index-1][1];
			Memory[current_history_index][2] = Memory[current_history_index-1][2];
			Memory[current_history_index][index] = new_page;
			
			return ;
		}
		
		// ������������ֲ����ˣ�����ǰ��������ʼ����
		if (ifCount[0] && ifCount[1] && ifCount[2]) {
			printf("�������� current_history_index: %d\n %d %d %d\n", current_history_index, count[0],count[1],count[2]);
			break;
		}
	}
	
	 return ;
}


//// ����ȱҳ�ж�
//void handle_page_fault(Task *task, PageTable *page_table, MemoryPage *pages[], int memory_size) {
////    int lru_index = find_lru_page(pages, memory_size, task->last_used);
//    // �����δʹ�õ�ҳ���û���ȥ�������µ�ҳ����ؽ���
//    // ������Ҫ��������ҳ����ڴ�ҳ��ľ��������ʵ��
//}
//
//

//
//// �������ʹ��ʱ��
//void update_last_used(MemoryPage *pages[], int memory_size, int *last_used[], int current_time) {
////    for (int i = 0; i < memory_size; i++) {
////        last_used[i] = current_time; // current_time��Ҫ���ⲿ���壬��ʾ��ǰ��ʱ��Ƭ
////    }
//}


// ��ӡ����״̬
void print_task_status(Task tasks[], int task_count) {
    for (int i = 0; i < task_count; i++) {
        printf("���� %s: ״̬ %c, ���ȼ� %d\n", tasks[i].process_name, tasks[i].status, tasks[i].priority);
    }
}


// ��ӡҳ��״̬
void print_page_status(MemoryPage *pages[], int memory_size) {
    for (int i = 0; i < memory_size; i++) {
        for (int j = 0; j < 2; j++) { // ����ÿ���ڴ�ҳ������������MemoryPage
            printf("ҳ�� %d: ��� %d, ָ�� '%s', ����ʱ�� %d\n", i, pages[i][j].block_number, pages[i][j].instruction_name, pages[i][j].block_time);
        }
    }
}

//// ģ�⴦��������
//void simulate_scheduling(Task tasks[], PageTable *pageTables[], int task_count, MemoryPage *pages[], int memory_size) {
//    int current_time = 0;
//    int running_index = 0; // ���н��̵�����
//
//    // ��¼ÿ���ڴ�ҳ�����һ��ʹ�õ�ʱ��
//    int last_used[10] = {0}; // ���������10���ڴ�ҳ��
//
//    while (1) {
//        update_priority(tasks, task_count, current_time); // �������ȼ�
//
//        // �ҵ����ȼ���ߵĽ���
//        int highest_priority_index = 0;
//        for (int i = 1; i < task_count; i++) {
//            if (tasks[i].priority > tasks[highest_priority_index].priority ||
//                (tasks[i].priority == tasks[highest_priority_index].priority && tasks[i].arrive_time < tasks[highest_priority_index].arrive_time)) {
//                highest_priority_index = i;
//            }
//        }
//
//        // ����Ƿ���Ҫҳ���û�
//        PageTable *current_page_table = pageTables[highest_priority_index];
//        for (int i = 0; current_page_table[i].page_number != 0; i++) {
//            int page_number = current_page_table[i].page_number;
//            int physical_block_number = current_page_table[i].physical_block_number;
//            int found = 0;
//            for (int j = 0; j < memory_size; j++) {
//                for (int k = 0; k < 2; k++) { // ����ÿ��page���鶼��2��MemoryPage
//                    if (pages[j][k].block_number == physical_block_number) {
//                        found = 1;
//                        last_used[j] = current_time; // �������ʹ��ʱ��
//                        break;
//                    }
//                }
//                if (found) break;
//            }
//            if (!found) {
//                // �ҵ����δʹ�õ�ҳ������û�
//                int lru_index = 0;
//                int min_last_used = current_time;
//                for (int k = 0; k < memory_size; k++) {
//                    if (last_used[k] < min_last_used) {
//                        lru_index = k;
//                        min_last_used = last_used[k];
//                    }
//                }
//                // ����ҳ����Ϣ
//                for (int k = 0; k < 2; k++) {
//                    if (pages[lru_index][k].block_number == 0) { // �ҵ��տ�
//                        pages[lru_index][k].block_number = physical_block_number;
//                        break;
//                    }
//                }
//                last_used[lru_index] = current_time;
//            }
//        }
//
//        printf("At time %d, Process %s is running with page table:\n", current_time, tasks[highest_priority_index].process_name);
//        for (int i = 0; current_page_table[i].page_number != 0; i++) {
//            printf("Page number: %d, Physical block: %d\n", current_page_table[i].page_number, current_page_table[i].physical_block_number);
//        }
//
//        // ģ��CPU����ʱ��
//        tasks[highest_priority_index].need_time--;
//        if (tasks[highest_priority_index].need_time == 0) {
//            tasks[highest_priority_index].status = 'F'; // ���״̬
//            break;
//        }
//
//        current_time++;
//    }
//}
//
//// ��ӡ��ǰʱ��Ƭ��״̬��������ǰ���̡��ȴ����̡�����ɽ��̺͵�ǰ���̵�ҳ�� 
//void print_current_state(Task tasks[], int task_count, MemoryPage *pages[], int memory_size) {
////    // ��ӡ��ǰ���еĽ���
////    int current_running_task_index = find_highest_priority_task(tasks, task_count);
////    printf("��ǰ���н��̣�%s\n", tasks[current_running_task_index].process_name);
////
////    // ��ӡ�ȴ��еĽ���
////    printf("�ȴ��еĽ��̣�");
////    for (int i = 0; i < task_count; i++) {
////        if (tasks[i].status == 'W') { // 'W' ��ʾ�ȴ�״̬
////            printf("%s ", tasks[i].process_name);
////        }
////    }
////    printf("\n");
////
////    // ��ӡ����ɵĽ���
////    printf("����ɵĽ��̣�");
////    for (int i = 0; i < task_count; i++) {
////        if (tasks[i].status == 'F') { // 'F' ��ʾ���״̬
////            printf("%s ", tasks[i].process_name);
////        }
////    }
////    printf("\n");
////
////    // ��ӡ��ǰ���̵�ҳ��
////    printf("��ǰ���̵�ҳ��");
////    for (int i = 0; pageTables[current_running_task_index][i].page_number != 0; i++) {
////        printf("(%d, %d) ", pageTables[current_running_task_index][i].page_number, pageTables[current_running_task_index][i].physical_block_number);
////    }
////    printf("\n");
//}
//
//
//// ��ӡҳ���û���Ϣ���������û�����ҳ������û�����ҳ�档
//void print_page_replacement_info(int page_replaced_index, MemoryPage *pages[], int memory_size) {
//    // ��ӡҳ���û���Ϣ
//    printf("ҳ���û���ҳ�� %d ���滻��\n", page_replaced_index);
//
//    // ��ӡ���û�����ҳ����Ϣ
//    for (int i = 0; i < memory_size; i++) {
//        for (int j = 0; j < 2; j++) { // ����ÿ���ڴ�ҳ������������MemoryPage
//            if (pages[i][j].block_number != 0) {
//                printf("ҳ�� %d: ��� %d, ָ������ '%s', ����ʱ�� %d\n", i, pages[i][j].block_number, pages[i][j].instruction_name, pages[i][j].block_time);
//            }
//        }
//    }
//}
//
//// ��ӡҳ���û�ͼ��չʾҳ����ʱ��ı仯
//void print_page_replacement_graph(MemoryPage *pages[], int memory_size) {
//    // ��ӡҳ���û�ͼ��չʾҳ����ʱ��ı仯
//    // �������Ҫһ�����ӵ����ݽṹ����¼ҳ����ʱ��ı仯
//    // �˴�ʡ�Ծ���ʵ�֣���Ϊ����������μ�¼ҳ����ʷ����
//} 
//
//// ��ӡ��ǰ�����ҳ����Ϣ��
//void print_currently_allocated_pages(MemoryPage *pages[], int memory_size) {
//    // ��ӡ��ǰ�����ҳ��
//    printf("��ǰ�����ҳ�棺");
//    for (int i = 0; i < memory_size; i++) {
//        for (int j = 0; j < 2; j++) { // ����ÿ���ڴ�ҳ������������MemoryPage
//            if (pages[i][j].block_number != 0) {
//                printf("ҳ�� %d: ��� %d, ָ������ '%s', ����ʱ�� %d\n", i, pages[i][j].block_number, pages[i][j].instruction_name, pages[i][j].block_time);
//            }
//        }
//    }
//}

