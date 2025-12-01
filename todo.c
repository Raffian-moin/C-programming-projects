#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef enum {
    PENDING = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2
} TaskStatus;

typedef struct Task {
    char name[100];
    int priority;
    TaskStatus status;
} taskStruct;

void showMenu(void);
void addTask(taskStruct *task, int *index);
void displayTasks(taskStruct *task, int *index);

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
            
        if (option == 2) {
            addTask(task, &index);
        }

    } while (option != 7);
    
    displayTasks(task, &index);
    
}

void displayTasks(taskStruct *task, int *index) {
    for (int i = 0; i < *index; i++) {
        printf("%s\n", (task+i)->name);
    }
}

void addTask(taskStruct *task, int *index) {
    strcpy((*(task + *index)).name, "Watch movie");
    (*(task + *index)).status = PENDING;
    (*index)++;
    printf("Task added successfully\n");
}
