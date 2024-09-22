// EMS (Employee Management System)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    float base_salary;
    int years_of_service;
    float bonus;
    float total_salary;
} Employee;

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

void add_employee();
void view_employees();
void edit_employee();
void delete_employee();
void calculate_salary(Employee *emp);
void assign_department();
void search_employee();
void save_employees_to_file();
void load_employees_from_file();
void sort_employees();
void calculate_bonus(Employee *emp);
void clear_buffer();
void menu();
void display_employee(Employee emp);
void calculate_total_salary(Employee *emp);
int get_employee_index(int id);

int main() {
    load_employees_from_file();
    menu();
    save_employees_to_file();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- Employee Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Edit Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Assign Department\n");
        printf("6. Search Employee\n");
        printf("7. Sort Employees\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice) {
            case 1: add_employee(); break;
            case 2: view_employees(); break;
            case 3: edit_employee(); break;
            case 4: delete_employee(); break;
            case 5: assign_department(); break;
            case 6: search_employee(); break;
            case 7: sort_employees(); break;
            case 0: printf("Exiting...\n"); save_employees_to_file(); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);
}

void clear_buffer() {
    while (getchar() != '\n'); // Clear input buffer
}

void add_employee() {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("Employee limit reached! Cannot add more employees.\n");
        return;
    }

    Employee new_employee;
    new_employee.id = employee_count + 1;

    printf("Enter employee name: ");
    fgets(new_employee.name, MAX_NAME_LENGTH, stdin);
    strtok(new_employee.name, "\n");

    printf("Enter department: ");
    fgets(new_employee.department, MAX_DEPT_LENGTH, stdin);
    strtok(new_employee.department, "\n");

    printf("Enter base salary: ");
    scanf("%f", &new_employee.base_salary);
    clear_buffer();

    printf("Enter years of service: ");
    scanf("%d", &new_employee.years_of_service);
    clear_buffer();

    calculate_salary(&new_employee);

    employees[employee_count] = new_employee;
    employee_count++;

    printf("Employee added successfully!\n");
}

void view_employees() {
    if (employee_count == 0) {
        printf("No employees available.\n");
        return;
    }

    printf("\n--- Employees ---\n");
    for (int i = 0; i < employee_count; i++) {
        display_employee(employees[i]);
    }
}

void display_employee(Employee emp) {
    printf("ID: %d | Name: %s | Department: %s | Base Salary: %.2f | Years of Service: %d | Bonus: %.2f | Total Salary: %.2f\n", 
           emp.id, 
           emp.name, 
           emp.department, 
           emp.base_salary, 
           emp.years_of_service, 
           emp.bonus,
           emp.total_salary);
}

void edit_employee() {
    int id;
    printf("Enter the employee ID to edit: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_employee_index(id);
    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    Employee *emp = &employees[index];
    printf("Editing Employee ID: %d\n", emp->id);
    printf("Current Name: %s\n", emp->name);
    printf("Current Department: %s\n", emp->department);
    printf("Current Base Salary: %.2f\n", emp->base_salary);
    printf("Current Years of Service: %d\n", emp->years_of_service);

    printf("Enter new name (or press Enter to keep current): ");
    char new_name[MAX_NAME_LENGTH];
    fgets(new_name, MAX_NAME_LENGTH, stdin);
    strtok(new_name, "\n");
    if (strlen(new_name) > 0) {
        strcpy(emp->name, new_name);
    }

    printf("Enter new department (or press Enter to keep current): ");
    char new_department[MAX_DEPT_LENGTH];
    fgets(new_department, MAX_DEPT_LENGTH, stdin);
    strtok(new_department, "\n");
    if (strlen(new_department) > 0) {
        strcpy(emp->department, new_department);
    }

    printf("Enter new base salary (or press Enter to keep current): ");
    char new_salary_input[20];
    fgets(new_salary_input, 20, stdin);
    if (strlen(new_salary_input) > 1) {
        emp->base_salary = atof(new_salary_input);
    }

    printf("Enter new years of service (or press Enter to keep current): ");
    char new_service_input[10];
    fgets(new_service_input, 10, stdin);
    if (strlen(new_service_input) > 1) {
        emp->years_of_service = atoi(new_service_input);
    }

    calculate_salary(emp);
    printf("Employee updated successfully!\n");
}

void delete_employee() {
    int id;
    printf("Enter the employee ID to delete: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_employee_index(id);
    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    for (int i = index; i < employee_count - 1; i++) {
        employees[i] = employees[i + 1]; // Shift employees left
    }
    employee_count--;
    printf("Employee deleted successfully!\n");
}

void assign_department() {
    int id;
    printf("Enter the employee ID to assign department: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_employee_index(id);
    if (index == -1) {
        printf("Employee not found.\n");
        return;
    }

    Employee *emp = &employees[index];
    printf("Enter new department: ");
    fgets(emp->department, MAX_DEPT_LENGTH, stdin);
    strtok(emp->department, "\n");

    printf("Department assigned successfully!\n");
}

void calculate_salary(Employee *emp) {
    calculate_bonus(emp);
    calculate_total_salary(emp);
}

void calculate_bonus(Employee *emp) {
    if (emp->years_of_service > 10) {
        emp->bonus = emp->base_salary * 0.10; // 10% bonus for more than 10 years
    } else if (emp->years_of_service > 5) {
        emp->bonus = emp->base_salary * 0.05; // 5% bonus for more than 5 years
    } else {
        emp->bonus = 0;
    }
}

void calculate_total_salary(Employee *emp) {
    emp->total_salary = emp->base_salary + emp->bonus;
}

void search_employee() {
    int choice;
    printf("\nSearch Employee by: \n");
    printf("1. Name\n2. ID\n3. Department\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_buffer();

    if (choice == 1) {
        char name[MAX_NAME_LENGTH];
        printf("Enter name to search: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        strtok(name, "\n");

        printf("\n--- Search Results ---\n");
        int found = 0;
        for (int i = 0; i < employee_count; i++) {
            if (strstr(employees[i].name, name) != NULL) {
                display_employee(employees[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No employees found with that name.\n");
        }
    } else if (choice == 2) {
        int id;
        printf("Enter ID to search: ");
        scanf("%d", &id);
        clear_buffer();

        int index = get_employee_index(id);
        if (index != -1) {
            display_employee(employees[index]);
        } else {
            printf("Employee not found.\n");
        }
    } else if (choice == 3) {
        char department[MAX_DEPT_LENGTH];
        printf("Enter department to search: ");
        fgets(department, MAX_DEPT_LENGTH, stdin);
        strtok(department, "\n");

        printf("\n--- Search Results ---\n");
        int found = 0;
        for (int i = 0; i < employee_count; i++) {
            if (strstr(employees[i].department, department) != NULL) {
                display_employee(employees[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No employees found in that department.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
}

void sort_employees() {
    int choice;
    printf("\nSort Employees by: \n");
    printf("1. Name\n2. Salary\n3. Department\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_buffer();

    for (int i = 0; i < employee_count - 1; i++) {
        for (int j = i + 1; j < employee_count; j++) {
            int swap = 0;

            if (choice == 1 && strcmp(employees[i].name, employees[j].name) > 0) {
                swap = 1;
            } else if (choice == 2 && employees[i].total_salary < employees[j].total_salary) {
                swap = 1;
            } else if (choice == 3 && strcmp(employees[i].department, employees[j].department) > 0) {
                swap = 1;
            }

            if (swap) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }

    printf("Employees sorted successfully!\n");
}

void save_employees_to_file() {
    FILE *file = fopen("employees.dat", "wb");
    if (!file) {
        printf("Failed to open file for saving.\n");
        return;
    }

    fwrite(&employee_count, sizeof(int), 1, file);
    fwrite(employees, sizeof(Employee), employee_count, file);
    fclose(file);
    printf("Employees saved to file.\n");
}

void load_employees_from_file() {
    FILE *file = fopen("employees.dat", "rb");
    if (!file) {
        printf("No saved employee data found.\n");
        return;
    }

    fread(&employee_count, sizeof(int), 1, file);
    fread(employees, sizeof(Employee), employee_count, file);
    fclose(file);
    printf("Employees loaded from file.\n");
}

int get_employee_index(int id) {
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}
