#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_DESC_LENGTH 256
#define MAX_TAG_LENGTH 50
#define MAX_TAGS 5

typedef struct {
    int id;
    char title[MAX_TITLE_LENGTH];
    char description[MAX_DESC_LENGTH];
    int is_completed;
    int priority; // 1 (High), 2 (Medium), 3 (Low)
    char tags[MAX_TAGS][MAX_TAG_LENGTH];
    char due_date[11]; // Format: YYYY-MM-DD
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void add_task();
void view_tasks();
void edit_task();
void delete_task();
void complete_task();
void set_task_priority();
void set_due_date();
void view_task_by_priority();
void filter_tasks_by_tag();
void overdue_tasks();
void menu();
void clear_buffer();
void display_task(Task task);
int validate_date(const char* date);
int is_task_overdue(const char* due_date);

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- Task Management System ---\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Edit Task\n");
        printf("4. Delete Task\n");
        printf("5. Complete Task\n");
        printf("6. Set Task Priority\n");
        printf("7. Set Task Due Date\n");
        printf("8. View Tasks by Priority\n");
        printf("9. Filter Tasks by Tag\n");
        printf("10. View Overdue Tasks\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice) {
            case 1: add_task(); break;
            case 2: view_tasks(); break;
            case 3: edit_task(); break;
            case 4: delete_task(); break;
            case 5: complete_task(); break;
            case 6: set_task_priority(); break;
            case 7: set_due_date(); break;
            case 8: view_task_by_priority(); break;
            case 9: filter_tasks_by_tag(); break;
            case 10: overdue_tasks(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);
}

void clear_buffer() {
    while (getchar() != '\n'); // Clear input buffer
}

void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Task limit reached! Cannot add more tasks.\n");
        return;
    }

    Task new_task;
    new_task.id = task_count + 1;
    printf("Enter task title: ");
    fgets(new_task.title, MAX_TITLE_LENGTH, stdin);
    strtok(new_task.title, "\n");

    printf("Enter task description: ");
    fgets(new_task.description, MAX_DESC_LENGTH, stdin);
    strtok(new_task.description, "\n");

    new_task.is_completed = 0; // Initially not completed
    new_task.priority = 3; // Default priority (Low)
    strcpy(new_task.due_date, "N/A"); // No due date initially

    // Enter tags
    printf("Enter up to %d tags (comma-separated): ", MAX_TAGS);
    char tag_input[256];
    fgets(tag_input, 256, stdin);
    strtok(tag_input, "\n");

    char *tag_token = strtok(tag_input, ",");
    int tag_count = 0;
    while (tag_token != NULL && tag_count < MAX_TAGS) {
        strncpy(new_task.tags[tag_count], tag_token, MAX_TAG_LENGTH);
        tag_token = strtok(NULL, ",");
        tag_count++;
    }

    tasks[task_count] = new_task;
    task_count++;
    printf("Task added successfully!\n");
}

void view_tasks() {
    if (task_count == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- Tasks ---\n");
    for (int i = 0; i < task_count; i++) {
        display_task(tasks[i]);
    }
}

void display_task(Task task) {
    printf("ID: %d | Title: %s | Description: %s | Status: %s | Priority: %d | Due Date: %s | Tags: ",
           task.id,
           task.title,
           task.description,
           task.is_completed ? "Completed" : "Pending",
           task.priority,
           task.due_date);
    for (int i = 0; i < MAX_TAGS && strlen(task.tags[i]) > 0; i++) {
        printf("%s ", task.tags[i]);
    }
    printf("\n");
}

void edit_task() {
    int task_id;
    printf("Enter the task ID to edit: ");
    scanf("%d", &task_id);
    clear_buffer();

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    Task *task = &tasks[task_id - 1];
    printf("Editing Task ID: %d\n", task->id);
    printf("Current Title: %s\n", task->title);
    printf("Current Description: %s\n", task->description);

    printf("Enter new title (or press Enter to keep current): ");
    char new_title[MAX_TITLE_LENGTH];
    fgets(new_title, MAX_TITLE_LENGTH, stdin);
    strtok(new_title, "\n");
    if (strlen(new_title) > 0) {
        strcpy(task->title, new_title);
    }

    printf("Enter new description (or press Enter to keep current): ");
    char new_description[MAX_DESC_LENGTH];
    fgets(new_description, MAX_DESC_LENGTH, stdin);
    strtok(new_description, "\n");
    if (strlen(new_description) > 0) {
        strcpy(task->description, new_description);
    }

    printf("Task updated successfully!\n");
}

void delete_task() {
    int task_id;
    printf("Enter the task ID to delete: ");
    scanf("%d", &task_id);
    clear_buffer();

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    for (int i = task_id - 1; i < task_count - 1; i++) {
        tasks[i] = tasks[i + 1]; // Shift tasks left
    }
    task_count--;
    printf("Task deleted successfully!\n");
}

void complete_task() {
    int task_id;
    printf("Enter the task ID to mark as completed: ");
    scanf("%d", &task_id);
    clear_buffer();

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    tasks[task_id - 1].is_completed = 1;
    printf("Task ID %d marked as completed!\n", task_id);
}

void set_task_priority() {
    int task_id, priority;
    printf("Enter the task ID to set priority: ");
    scanf("%d", &task_id);
    clear_buffer();

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    printf("Enter priority (1: High, 2: Medium, 3: Low): ");
    scanf("%d", &priority);
    clear_buffer();

    if (priority < 1 || priority > 3) {
        printf("Invalid priority. Please try again.\n");
        return;
    }

    tasks[task_id - 1].priority = priority;
    printf("Priority for Task ID %d updated successfully!\n", task_id);
}

void set_due_date() {
    int task_id;
    printf("Enter the task ID to set due date: ");
    scanf("%d", &task_id);
    clear_buffer();

    if (task_id <= 0 || task_id > task_count) {
        printf("Invalid task ID.\n");
        return;
    }

    printf("Enter due date (YYYY-MM-DD): ");
    char due_date[11];
    fgets(due_date, 11, stdin);
    strtok(due_date, "\n");

    if (!validate_date(due_date)) {
        printf("Invalid date format. Please try again.\n");
        return;
    }

    strcpy(tasks[task_id - 1].due_date, due_date);
    printf("Due date for Task ID %d updated successfully!\n", task_id);
}

int validate_date(const char* date) {
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') {
        return 0;
    }
    return 1;
}

void view_task_by_priority() {
    int priority;
    printf("Enter priority to filter (1: High, 2: Medium, 3: Low): ");
    scanf("%d", &priority);
    clear_buffer();

    if (priority < 1 || priority > 3) {
        printf("Invalid priority. Please try again.\n");
        return;
    }

    printf("\n--- Tasks with Priority %d ---\n", priority);
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].priority == priority) {
            display_task(tasks[i]);
        }
    }
}

void filter_tasks_by_tag() {
    char tag[MAX_TAG_LENGTH];
    printf("Enter tag to filter tasks: ");
    fgets(tag, MAX_TAG_LENGTH, stdin);
    strtok(tag, "\n");

    printf("\n--- Tasks with Tag: %s ---\n", tag);
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        for (int j = 0; j < MAX_TAGS; j++) {
            if (strcmp(tasks[i].tags[j], tag) == 0) {
                display_task(tasks[i]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No tasks found with the tag \"%s\".\n", tag);
    }
}

void overdue_tasks() {
    printf("\n--- Overdue Tasks ---\n");
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (strcmp(tasks[i].due_date, "N/A") != 0 && is_task_overdue(tasks[i].due_date)) {
            display_task(tasks[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No overdue tasks.\n");
    }
}

int is_task_overdue(const char* due_date) 
{
    // Current date
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);
    char today[11];
    snprintf(today, sizeof(today), "%04d-%02d-%02d", current_date.tm_year + 1900, current_date.tm_mon + 1, current_date.tm_mday);

    return strcmp(today, due_date) > 0;
}
