//SMS (Student Management System)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 100
#define MAX_COURSE_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char course[MAX_COURSE_LENGTH];
    int age;
    float grade;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void add_student();
void view_students();
void edit_student();
void delete_student();
void search_student();
void save_students_to_file();
void load_students_from_file();
void sort_students();
void calculate_average_grade();
void find_highest_grade_student();
void find_lowest_grade_student();
void list_students_by_age();
void list_students_by_grade();
void export_students_to_csv();
void import_students_from_csv();
void display_help();
void clear_buffer();
void menu();
void display_student(Student student);
int get_student_index(int id);

int main() {
    load_students_from_file();
    menu();
    save_students_to_file();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Edit Student\n");
        printf("4. Delete Student\n");
        printf("5. Search Student\n");
        printf("6. Sort Students\n");
        printf("7. Calculate Average Grade\n");
        printf("8. Find Student with Highest Grade\n");
        printf("9. Find Student with Lowest Grade\n");
        printf("10. List Students by Age\n");
        printf("11. List Students by Grade Range\n");
        printf("12. Export Students to CSV\n");
        printf("13. Import Students from CSV\n");
        printf("14. Display Help\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice) {
            case 1: add_student(); break;
            case 2: view_students(); break;
            case 3: edit_student(); break;
            case 4: delete_student(); break;
            case 5: search_student(); break;
            case 6: sort_students(); break;
            case 7: calculate_average_grade(); break;
            case 8: find_highest_grade_student(); break;
            case 9: find_lowest_grade_student(); break;
            case 10: list_students_by_age(); break;
            case 11: list_students_by_grade(); break;
            case 12: export_students_to_csv(); break;
            case 13: import_students_from_csv(); break;
            case 14: display_help(); break;
            case 0: printf("Exiting...\n"); save_students_to_file(); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);
}

void clear_buffer() {
    while (getchar() != '\n'); // Clear input buffer
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Student limit reached! Cannot add more students.\n");
        return;
    }

    Student new_student;
    new_student.id = student_count + 1;

    printf("Enter student name: ");
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    strtok(new_student.name, "\n");

    printf("Enter course: ");
    fgets(new_student.course, MAX_COURSE_LENGTH, stdin);
    strtok(new_student.course, "\n");

    printf("Enter age: ");
    scanf("%d", &new_student.age);
    clear_buffer();

    printf("Enter grade: ");
    scanf("%f", &new_student.grade);
    clear_buffer();

    students[student_count] = new_student;
    student_count++;

    printf("Student added successfully!\n");
}

void view_students() {
    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }

    printf("\n--- Students ---\n");
    for (int i = 0; i < student_count; i++) {
        display_student(students[i]);
    }
}

void display_student(Student student) {
    printf("ID: %d | Name: %s | Course: %s | Age: %d | Grade: %.2f\n", 
           student.id, 
           student.name, 
           student.course, 
           student.age, 
           student.grade);
}

void edit_student() {
    int id;
    printf("Enter the student ID to edit: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_student_index(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    Student *student = &students[index];
    printf("Editing Student ID: %d\n", student->id);
    printf("Current Name: %s\n", student->name);
    printf("Current Course: %s\n", student->course);
    printf("Current Age: %d\n", student->age);
    printf("Current Grade: %.2f\n", student->grade);

    printf("Enter new name (or press Enter to keep current): ");
    char new_name[MAX_NAME_LENGTH];
    fgets(new_name, MAX_NAME_LENGTH, stdin);
    strtok(new_name, "\n");
    if (strlen(new_name) > 0) {
        strcpy(student->name, new_name);
    }

    printf("Enter new course (or press Enter to keep current): ");
    char new_course[MAX_COURSE_LENGTH];
    fgets(new_course, MAX_COURSE_LENGTH, stdin);
    strtok(new_course, "\n");
    if (strlen(new_course) > 0) {
        strcpy(student->course, new_course);
    }

    printf("Enter new age (or press Enter to keep current): ");
    char new_age_input[20];
    fgets(new_age_input, 20, stdin);
    if (strlen(new_age_input) > 1) {
        student->age = atoi(new_age_input);
    }

    printf("Enter new grade (or press Enter to keep current): ");
    char new_grade_input[10];
    fgets(new_grade_input, 10, stdin);
    if (strlen(new_grade_input) > 1) {
        student->grade = atof(new_grade_input);
    }

    printf("Student updated successfully!\n");
}

void delete_student() {
    int id;
    printf("Enter the student ID to delete: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_student_index(id);
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1]; // Shift students left
    }
    student_count--;
    printf("Student deleted successfully!\n");
}

void search_student() {
    int choice;
    printf("\nSearch Student by: \n");
    printf("1. Name\n2. ID\n3. Course\n");
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
        for (int i = 0; i < student_count; i++) {
            if (strstr(students[i].name, name) != NULL) {
                display_student(students[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No students found with that name.\n");
        }
    } else if (choice == 2) {
        int id;
        printf("Enter ID to search: ");
        scanf("%d", &id);
        clear_buffer();

        int index = get_student_index(id);
        if (index != -1) {
            display_student(students[index]);
        } else {
            printf("Student not found.\n");
        }
    } else if (choice == 3) {
        char course[MAX_COURSE_LENGTH];
        printf("Enter course to search: ");
        fgets(course, MAX_COURSE_LENGTH, stdin);
        strtok(course, "\n");

        printf("\n--- Search Results ---\n");
        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (strstr(students[i].course, course) != NULL) {
                display_student(students[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("No students found in that course.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
}

void sort_students() {
    int choice;
    printf("\nSort Students by: \n");
    printf("1. Name\n2. Grade\n3. Course\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_buffer();

    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            int swap = 0;

            if (choice == 1 && strcmp(students[i].name, students[j].name) > 0) {
                swap = 1;
            } else if (choice == 2 && students[i].grade < students[j].grade) {
                swap = 1;
            } else if (choice == 3 && strcmp(students[i].course, students[j].course) > 0) {
                swap = 1;
            }

            if (swap) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("Students sorted successfully!\n");
}

void calculate_average_grade() {
    if (student_count == 0) {
        printf("No students available to calculate average grade.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < student_count; i++) {
        total += students[i].grade;
    }
    float average = total / student_count;
    printf("Average Grade: %.2f\n", average);
}

void find_highest_grade_student() {
    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }

    int highest_index = 0;
    for (int i = 1; i < student_count; i++) {
        if (students[i].grade > students[highest_index].grade) {
            highest_index = i;
        }
    }
    printf("Student with Highest Grade:\n");
    display_student(students[highest_index]);
}

void find_lowest_grade_student() {
    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }

    int lowest_index = 0;
    for (int i = 1; i < student_count; i++) {
        if (students[i].grade < students[lowest_index].grade) {
            lowest_index = i;
        }
    }
    printf("Student with Lowest Grade:\n");
    display_student(students[lowest_index]);
}

void list_students_by_age() {
    int min_age, max_age;
    printf("Enter minimum age: ");
    scanf("%d", &min_age);
    printf("Enter maximum age: ");
    scanf("%d", &max_age);
    clear_buffer();

    printf("\n--- Students in Age Range (%d - %d) ---\n", min_age, max_age);
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (students[i].age >= min_age && students[i].age <= max_age) {
            display_student(students[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in that age range.\n");
    }
}

void list_students_by_grade() {
    float min_grade, max_grade;
    printf("Enter minimum grade: ");
    scanf("%f", &min_grade);
    printf("Enter maximum grade: ");
    scanf("%f", &max_grade);
    clear_buffer();

    printf("\n--- Students in Grade Range (%.2f - %.2f) ---\n", min_grade, max_grade);
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (students[i].grade >= min_grade && students[i].grade <= max_grade) {
            display_student(students[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in that grade range.\n");
    }
}

void export_students_to_csv() {
    FILE *file = fopen("students.csv", "w");
    if (!file) {
        printf("Failed to open file for exporting.\n");
        return;
    }

    fprintf(file, "ID,Name,Course,Age,Grade\n");
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%d,%s,%s,%d,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].course,
                students[i].age,
                students[i].grade);
    }
    fclose(file);
    printf("Students exported to students.csv successfully!\n");
}

void import_students_from_csv() {
    FILE *file = fopen("students.csv", "r");
    if (!file) {
        printf("Failed to open file for importing.\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip header line
    while (fgets(line, sizeof(line), file)) {
        if (student_count >= MAX_STUDENTS) {
            printf("Student limit reached! Cannot import more students.\n");
            break;
        }

        Student new_student;
        sscanf(line, "%d,%[^,],%[^,],%d,%f",
               &new_student.id,
               new_student.name,
               new_student.course,
               &new_student.age,
               &new_student.grade);

        students[student_count] = new_student;
        student_count++;
    }
    fclose(file);
    printf("Students imported successfully from students.csv!\n");
}

void display_help() {
    printf("\n--- Help ---\n");
    printf("1. Add Student: Enter student details to add a new student.\n");
    printf("2. View Students: Display a list of all students.\n");
    printf("3. Edit Student: Modify details of an existing student.\n");
    printf("4. Delete Student: Remove a student from the system.\n");
    printf("5. Search Student: Find students by name, ID, or course.\n");
    printf("6. Sort Students: Organize students based on name, grade, or course.\n");
    printf("7. Calculate Average Grade: Display the average grade of all students.\n");
    printf("8. Find Student with Highest Grade: Display the student with the highest grade.\n");
    printf("9. Find Student with Lowest Grade: Display the student with the lowest grade.\n");
    printf("10. List Students by Age: Display students within a specified age range.\n");
    printf("11. List Students by Grade Range: Display students within a specified grade range.\n");
    printf("12. Export Students to CSV: Save student data to a CSV file.\n");
    printf("13. Import Students from CSV: Load student data from a CSV file.\n");
    printf("14. Display Help: Show this help information.\n");
    printf("0. Exit: Exit the program and save data.\n");
}

void save_students_to_file() {
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        printf("Failed to open file for saving.\n");
        return;
    }

    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Students saved to file.\n");
}

void load_students_from_file() {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("No saved student data found.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Students loaded from file.\n");
}

int get_student_index(int id) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            return i;
        }
    }
    return -1; // Student not found
}
