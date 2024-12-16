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

// ȫ�����飬��¼ÿ��ҳ�����һ�α����ʵ�ʱ��
int last_used[10] = {0}; // ������10��ҳ��

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
/**
 * ��ǰ������������������������ 
 * �޸ĳ�ΪLRU 
 */
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
	   		if (tasks[comeTask_count].arrive_time <= current_time && comeTask_count < task_count) {
	   			// comeTasks���� 
	   			comeTasks[comeTask_count] = tasks[comeTask_count];
	   			printf("\t\t\t���񵽴�\n");
	   			printf("�������������������������������������������\n");
	   			printf("\t%s \t%c \t%d \t%d \t%d \t%d \t%d\n", 
					 comeTasks[comeTask_count].process_name, comeTasks[comeTask_count].status, comeTasks[comeTask_count].arrive_time, 
					 comeTasks[comeTask_count].priority, comeTasks[comeTask_count].need_time, comeTasks[comeTask_count].instruction_number, comeTasks[comeTask_count].table_number); 
					printf("�������������������������������������������\n");
					comeTask_count +=1 ;
				}

    	
        // �����������ȼ�
        update_priority(comeTasks, comeTask_count);
        
        // ��ӡ��ǰ����״̬
        print_task_status(comeTasks, comeTask_count);

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
				printf("��ǰ���ȼ���ߵ�����Ϊ�� %s ���ȼ�Ϊ��%d   ִ�и�����\n\n", current_task->process_name, current_task->priority);
				printf("�������������������������������������������\n");

    		// �ҵ���Ӧ��ҳ�� 
    		PageTable *pageTable = pageTables[current_task->table_number - 1];
    		printf("���� %s ��ҳ�� \n", current_task->process_name);
    		
				// ��ӡҳ�� 
				print_page_table(pageTable, current_task->instruction_number); 
				
				
        // ģ������ִ��(ִֻ��һ��) 
        simulate_task_execution(current_task, memory_size);

				// ��ӡ��Ҫʱ��
				printf("��Ҫʱ��:%d\n\n", current_task->need_time) ;

//        // ��ӡ��ǰҳ��״̬
//        print_page_status(pages, memory_size);

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
            		printf("δ��� %d %c \n", i+1, comeTasks[i].status); 
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

//        // ��ӡ��������ơ����ȼ���״̬
//        printf("���� %s: ���ȼ� %d, ״̬ %c\n", task->process_name, task->priority, task->status);
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
    
    if (tasks[last_number].status == 'F') {
        printf("���� %s: ״̬ %c, ���ȼ� %d    �ѽ���\n", tasks[last_number].process_name, tasks[last_number].status, tasks[last_number].priority);
		}
    
    if (last_number != -1 && tasks[last_number].status != 'F' && last_number != highest_priority_index) {
    	printf("���� %s   ��������\n", tasks[last_number].process_name);
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
        printf("%d\t%d\t\t%d\n", pageTable[i].page_number, pageTable[i].physical_block_number, pageTable[i].ifFinsih);
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
        } else {
		        // ҳ��ԭ�����У��������ʹ��ʱ��
		        last_used[page_number] = current_time;
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


// ��ӡ��ǰ�ڴ�������ҳ������ʹ��ʱ��
void print_last_used_times() {
	  printf("�������������������������������������������\n");
    printf("��ǰ�ڴ�������ҳ������ʹ��ʱ�䣺\n");
    for (int i = 0; i < MemoryPageNumber; i++) {
        // ���ҳ���Ƿ��ѷ���
        if (Memory[current_history_index][i] != 0) {
            printf("ҳ��ţ�%d  ���ʹ��ʱ�䣺%d\n", Memory[current_history_index][i], last_used[Memory[current_history_index][i]]);
        }
    }
    printf("�������������������������������������������\n");
}

// ִ��ҳ���û���ʹ�� LRU �㷨
void page_replacement(int new_page, PageTable *pageTable, int index) {
		print_last_used_times();
		
    // ������ҳ���Ƿ������ڴ���
    int found = 0;
    for (int j = 0; j < MemoryPageNumber; j++) {
        if (Memory[current_history_index][j] == new_page) {
            found = 1;
            break;
        }
    }

    if (!found) {
        // ��ҳ�治���ڴ��У���Ҫ�û�

        // �������δʹ�õ�ҳ��
        int lru_index = -1;
        int min_last_used_time = current_time; // ʹ�õ�ǰʱ����Ϊ��ʼֵ
        for (int i = 0; i < MemoryPageNumber; i++) {
            if (last_used[Memory[current_history_index][i]] < min_last_used_time) {
                min_last_used_time = last_used[Memory[current_history_index][i]];
                lru_index = i;
            }
        }

        if (lru_index != -1) {
            // �滻���δʹ�õ�ҳ��
            Memory[current_history_index][lru_index] = new_page;
            last_used[new_page] = current_time; // �������ʹ��ʱ��
       		 	printf("���δʹ�õ�ҳ��Ϊ��%d  ���ʹ��ʱ��: %d\n", Memory[current_history_index][lru_index], min_last_used_time);
            printf("LRUҳ���û���ҳ�� %d ���滻Ϊҳ�� %d\n", Memory[current_history_index][lru_index], new_page);
        } else {
            // û���ҵ����ʵ�ҳ������û�����������Ϊ�ڴ�������û��ҳ�汻ʹ�ù�
            printf("�ڴ��������޷�����ҳ���û�\n");
        }
    } else {
        // ҳ�������ڴ��У��������ʹ��ʱ��
        last_used[new_page] = current_time;
    }
}


// ��ӡ����״̬
void print_task_status(Task tasks[], int task_count) {
		if (task_count > 5) {
			task_count = 5;
		} 
		printf("                                  ��ǰ������PCB��Ϣ                                  \n");
		printf("�������������������������������������������\n");
    for (int i = 0; i < task_count; i++) {
        printf("���� %s: ״̬ %c, ���ȼ� %d\n", tasks[i].process_name, tasks[i].status, tasks[i].priority);
    }
    printf("�������������������������������������������\n");
}


//// ��ӡҳ��״̬
//void print_page_status(MemoryPage *pages[], int memory_size) {
//    for (int i = 0; i < memory_size; i++) {
//        for (int j = 0; j < 2; j++) { // ����ÿ���ڴ�ҳ������������MemoryPage
//            printf("ҳ�� %d: ��� %d, ָ�� '%s', ����ʱ�� %d\n", i, pages[i][j].block_number, pages[i][j].instruction_name, pages[i][j].block_time);
//        }
//    }
//}


