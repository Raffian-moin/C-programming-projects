#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TASK_NAME_MAX_LENGTH 100

typedef enum {
    PENDING = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2
} TaskStatus;

typedef struct Task {
    char name[TASK_NAME_MAX_LENGTH];
    int priority;
    TaskStatus status;
} taskStruct;

void showMenu(void);
void addTask(taskStruct *task, int *index);
void displayTasks(taskStruct *task, int index);
void deleteTask(taskStruct *task, int *index);

int main() {
    taskStruct *task = malloc(sizeof(taskStruct) * 10);
    int index = 0;
    int option = 0;

    do {
        printf("=========== Main Menu ==============\n");
        printf("1. Display tasks\n");
        printf("2. Add task\n");
        printf("3. Edit task\n");
        printf("4. Delete task\n");
        printf("5. Filter/Sort tasks\n");
        printf("6. Save tasks\n");
        printf("7. Exit\n");
       
        printf("Choose an option: \n");
        scanf("%d", &option);
        
        switch(option) {
            case 1: 
                displayTasks(task, index);
                break;
            case 2:
                addTask(task, &index);
                break;
            case 3:
                //Todo
                //editTask(void)
                break;
            case 4:
                deleteTask(task, &index);
        }

    } while (option != 7);
    
    //displayTasks(task, &index);
    
}

void displayTasks(taskStruct *task, int index) {
    for (int i = 0; i < index; i++) {
        char status[20];

        switch((task + i)->status) {
            case PENDING:
                strcpy(status, "Pending");
                break;
            case IN_PROGRESS:
                strcpy(status, "In progress");
                break;
            case COMPLETED:
                strcpy(status, "Completed");
                break;
        }
        /*
        if ((task + i)->status == PENDING) {
            strcpy(status, "pending");
        }
        */
        printf("%s [%s]\n", (task + i)->name, status);
    }
}

void addTask(taskStruct *task, int *index) {
    char taskName[TASK_NAME_MAX_LENGTH];
    while(getchar() != '\n');

    printf("Input your task: ");
    if (fgets(taskName, sizeof(taskName), stdin) != NULL) {
        taskName[strcspn(taskName, "\n")] = '\0';
        strcpy((*(task + *index)).name, taskName);
        (*(task + *index)).status = PENDING;
    }

    int priority;
    printf("Input your priority: ");
    scanf(" %d", &priority);

    (*(task + *index)).priority = priority;

    (*index)++;

    printf("Task added successfully\n"); 

}

void deleteTask(taskStruct *task, int *index) {
    int tobeDeletedTaskID;
    printf("Chose a task ID to delete: ");
    scanf("%d", &tobeDeletedTaskID);

    for (int i = tobeDeletedTaskID; i < *index - 1; i++) {	
        if (i >=  tobeDeletedTaskID) {
			task[i] = task[i+1];			
		}	
    }

	(*index)--;
	printf("Task deleted successfully\n");
}
