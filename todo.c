#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TASK_NAME_MAX_LENGTH 100

typedef enum {
    PENDING = 1,
    IN_PROGRESS = 2,
    COMPLETED = 3
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
void editTask(taskStruct *task, int *index);
void filterTask(taskStruct *task, int index);
int comparePriority(const void *a, const void *b);
void filterByPriority(taskStruct *task, int index);
void filterByStatus(taskStruct *task, int index);
char *getStatusString(int status);
void saveToFile(taskStruct *task, int index);
void loadDataFromFile(taskStruct **task, int *index, int *capacity);

int main() {
    int capacity = 5;
    int index = 0;
    int option = 0;
    taskStruct *task = malloc(sizeof(taskStruct) * capacity);

    loadDataFromFile(&task, &index, &capacity);

    do {
        printf("=========== Main Menu ==============\n");
        printf("1. Display tasks\n");
        printf("2. Add task\n");
        printf("3. Edit task\n");
        printf("4. Delete task\n");
        printf("5. Filter/Sort tasks\n");
        printf("6. Save tasks\n");
        printf("7. Exit\n");
       
        printf("Choose an option: ");
        scanf("%d", &option);
        
        switch(option) {
            case 1: 
                displayTasks(task, index);
                break;
            case 2:
                addTask(task, &index);
                break;
            case 3:
                editTask(task, &index);
                break;
            case 4:
                deleteTask(task, &index);
            case 5:
                filterTask(task, index);
            case 6:
                saveToFile(task, index);
        }

    } while (option != 7); 
}

void displayTasks(taskStruct *task, int index) {
    printf("=========== Task List  ==============\n");
	if (index == 0) {
		printf("No task added yet\n");
		return;
	}

    for (int i = 0; i < index; i++) {
        char *status;
        status = getStatusString(task[i].status);
        printf("%s [%s]\n", (task + i)->name, status);
    }
}

void addTask(taskStruct *task, int *index) {
    char taskName[TASK_NAME_MAX_LENGTH];
    while(getchar() != '\n');

    printf("Input your task: ");
    if (fgets(taskName, sizeof(taskName), stdin) != NULL) {
        taskName[strcspn(taskName, "\n")] = '\0';
        strcpy(task[*index].name, taskName);
        task[*index].status = PENDING;
    }

    int priority;
    printf("Input your priority: ");
    scanf(" %d", &priority);

    task[*index].priority = priority;

    (*index)++;

    printf("Task added successfully\n"); 

}

void editTask(taskStruct *task, int *index) {
    int tobeEditedTaskID;
    printf("============= Edit Task ===========\n");
    printf("Chose a task ID to edit: ");
    scanf("%d", &tobeEditedTaskID);
    
    if (tobeEditedTaskID >= *index) {
        printf("Task ID not found\n");
        return;
    }
    

    printf("1. Edit name\n");
    printf("2. Edit status\n");
    printf("1. Edit priority\n");
    
    int selectedOption;
    printf("Chose an option to edit\n");
    scanf("%d", &selectedOption);

    switch(selectedOption) {
        case 1:
            char taskName[TASK_NAME_MAX_LENGTH];
            while(getchar() != '\n');

            printf("Input your task: ");
            if (fgets(taskName, sizeof(taskName), stdin) != NULL) {
                taskName[strcspn(taskName, "\n")] = '\0';
                strcpy((*(task + tobeEditedTaskID)).name, taskName);
                //(*(task + tobeEditedTaskID)).status = PENDING;
            }
            break;
        case 2:
            int status;
            printf("Input your status: ");
            scanf("%d", &status);
            switch(status) {
                case 1:
                    (*(task + tobeEditedTaskID)).status = IN_PROGRESS;
                    break;
                case 2:
                    (*(task + tobeEditedTaskID)).status = COMPLETED;
                    break;

            }
            break;

    }
}

void deleteTask(taskStruct *task, int *index) {
    int tobeDeletedTaskID;

    printf("============ Delete Task ==============\n");
    printf("Chose a task ID to delete: ");
    scanf("%d", &tobeDeletedTaskID);
    
    if (tobeDeletedTaskID >= *index) {
        printf("Task ID not found\n");
        return;
    }
    
    for (int i = tobeDeletedTaskID; i < *index - 1; i++) {	
        if (i >=  tobeDeletedTaskID) {
			task[i] = task[i+1];			
		}	
    }

	(*index)--;
	printf("Task deleted successfully\n");
}



void filterTask(taskStruct *task, int index) {

    printf("================ Filter =================\n");
    printf("1. Filter by priority\n");
    printf("2. Filter by creation date\n");
    printf("3. Filter by status\n");

    int selectedOption;
    printf("Chose your option to filter: ");
    scanf("%d", &selectedOption);

    switch (selectedOption) {
        case 1:
            filterByPriority(task, index);
            break;
		case 2:
            break;
        case 3:
			filterByStatus(task, index);
            break;
    }

}

void filterByPriority(taskStruct *task, int index) {
    taskStruct *mytask = task;
    qsort(mytask, index, sizeof(taskStruct), comparePriority);
	
    for (int i = 0; i < index; i++) {
        printf("%s and priority: %d\n", mytask[i].name, mytask[i].priority);
    }

}

int comparePriority(const void *a, const void *b) {
    taskStruct task_a = *((taskStruct *)a);
    taskStruct task_b = *((taskStruct *)b);

	return task_b.priority - task_a.priority;
}

void filterByStatus(taskStruct *task, int index) {
	printf("================ Filter By Status =================\n");
	printf("1. Pending\n");
    printf("2. In progress\n");
    printf("3. Completed\n");
	
    printf("Chose your option: ");
	int selectedOption;
	scanf("%d", &selectedOption);

    for (int i = 0; i < index; i++) {
        if (task[i].status == selectedOption) {
            char *statusString = getStatusString(task[i].status);
            printf("%s [%s]\n", task[i].name, statusString);
        }
    }
}

char *getStatusString(int status) {
    char *statusString;
    switch(status) {
        case PENDING:
            statusString = "Pending";
            break;
        case IN_PROGRESS:
            statusString = "In Progress";
            break;
        case COMPLETED:
            statusString = "Completed";
            break;
    }

    return statusString;
}


void saveToFile(taskStruct *task, int index) {
    FILE *file_ptr = fopen("task.txt", "w");
    
    for (int i = 0; i < index; i++) {
        fprintf(file_ptr, "%s;%d;%d\n", task[i].name, task[i].priority, task[i].status);
    }

    fclose(file_ptr);
}


void loadDataFromFile(taskStruct **task, int *index, int *capacity) {
    FILE *file_ptr = fopen("task.txt", "a+");
    
    char currentTaskData[100];
    while(fgets(currentTaskData, sizeof(currentTaskData), file_ptr)) {
        if (*index == *capacity) {
            *capacity = *capacity + 5;
            taskStruct *newly_allocated_task_ptr = realloc(*task, sizeof(taskStruct) * (*capacity));
            *task = newly_allocated_task_ptr;
        }

        char *taskData = strtok(currentTaskData, ";");
        strcpy((*task)[*index].name, taskData);

		taskData = strtok(NULL, ";");
		if (taskData!= NULL) {
			(*task)[*index].priority = atoi(taskData);
		}

		taskData = strtok(NULL, ";");
        if (taskData != NULL) {
			(*task)[*index].status = atoi(taskData);
		}

        (*index)++;
    }

    fclose(file_ptr);

}
