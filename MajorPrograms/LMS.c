#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100
#define USERNAME_LENGTH 50
#define MAX_BORROW_LIMIT 5
#define MAX_HISTORY 50

typedef struct 
{
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int is_borrowed;
    int reserved_by;
} Book;

typedef struct 
{
    int id;
    char username[USERNAME_LENGTH];
    int borrowed_books[MAX_BOOKS];
    int borrow_count;
    float fines_due;
    int borrowed_history[MAX_HISTORY];
    int history_count;
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];

int book_count = 0;
int user_count = 0;

void add_book();
void list_books();
void search_book();
void borrow_book();
void return_book();
void add_user();
void list_users();
void edit_book();
void delete_book();
void view_borrowed_books();
void reserve_book();
void cancel_reservation();
void apply_fine(int user_id, float fine_amount);
void pay_fine();
void view_fines();
void view_borrow_history();
void save_data();
void load_data();
void menu();
void initialize();
void clear_buffer();

int main() {
    initialize();
    load_data();
    menu();
    save_data();
    return 0;
}

void initialize() 
{
    // Prepopulate with some books and users
    strcpy(library[0].title, "The Great Gatsby");
    strcpy(library[0].author, "F. Scott Fitzgerald");
    library[0].id = 1;
    library[0].is_borrowed = 0;
    library[0].reserved_by = -1;
    book_count++;

    strcpy(library[1].title, "1984");
    strcpy(library[1].author, "George Orwell");
    library[1].id = 2;
    library[1].is_borrowed = 0;
    library[1].reserved_by = -1;
    book_count++;

    strcpy(users[0].username, "admin");
    users[0].id = 1;
    users[0].fines_due = 0.0;
    users[0].borrow_count = 0;
    users[0].history_count = 0;
    memset(users[0].borrowed_books, 0, sizeof(users[0].borrowed_books));
    user_count++;
}

void menu() 
{
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Search Book\n");
        printf("4. Borrow Book\n");
        printf("5. Return Book\n");
        printf("6. Add User\n");
        printf("7. List Users\n");
        printf("8. Edit Book\n");
        printf("9. Delete Book\n");
        printf("10. View Borrowed Books\n");
        printf("11. Reserve Book\n");
        printf("12. Cancel Reservation\n");
        printf("13. Apply Fine\n");
        printf("14. Pay Fine\n");
        printf("15. View Fines\n");
        printf("16. View Borrow History\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clear_buffer();
        
        switch (choice) 
        {
            case 1: add_book(); break;
            case 2: list_books(); break;
            case 3: search_book(); break;
            case 4: borrow_book(); break;
            case 5: return_book(); break;
            case 6: add_user(); break;
            case 7: list_users(); break;
            case 8: edit_book(); break;
            case 9: delete_book(); break;
            case 10: view_borrowed_books(); break;
            case 11: reserve_book(); break;
            case 12: cancel_reservation(); break;
            case 13: 
                {
                    int user_id;
                    float fine;
                    printf("Enter user ID to apply fine: ");
                    scanf("%d", &user_id);
                    printf("Enter fine amount: ");
                    scanf("%f", &fine);
                    apply_fine(user_id, fine);
                    break;
                }
            case 14: pay_fine(); break;
            case 15: view_fines(); break;
            case 16: view_borrow_history(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);
}

void clear_buffer() 
{
    while (getchar() != '\n'); // Clear input buffer
}

void add_book() 
{
    if (book_count >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }

    Book new_book;
    new_book.id = book_count + 1;
    printf("Enter book title: ");
    fgets(new_book.title, TITLE_LENGTH, stdin);
    strtok(new_book.title, "\n");
    printf("Enter author name: ");
    fgets(new_book.author, AUTHOR_LENGTH, stdin);
    strtok(new_book.author, "\n");
    new_book.is_borrowed = 0;
    new_book.reserved_by = -1;

    library[book_count] = new_book;
    book_count++;
    printf("Book added successfully!\n");
}

void list_books() 
{
    if (book_count == 0) 
    {
        printf("No books available.\n");
        return;
    }
    printf("\nBooks in Library:\n");
    for (int i = 0; i < book_count; i++) 
    {
        printf("ID: %d | Title: %s | Author: %s | Borrowed: %s | Reserved By: %d\n", 
                library[i].id, 
                library[i].title, 
                library[i].author, 
                library[i].is_borrowed ? "Yes" : "No",
                library[i].reserved_by == -1 ? 0 : library[i].reserved_by);
    }
}

void search_book() 
{
    char title[TITLE_LENGTH];
    printf("Enter book title to search: ");
    fgets(title, TITLE_LENGTH, stdin);
    strtok(title, "\n");

    for (int i = 0; i < book_count; i++) 
    {
        if (strstr(library[i].title, title) != NULL) 
        {
            printf("Found: ID: %d | Title: %s | Author: %s | Borrowed: %s\n", 
                   library[i].id, 
                   library[i].title, 
                   library[i].author, 
                   library[i].is_borrowed ? "Yes" : "No");
            return;
        }
    }
    printf("Book not found.\n");
}

void borrow_book() 
{
    int book_id, user_id;
    printf("Enter the book ID to borrow: ");
    scanf("%d", &book_id);
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count || user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid book or user ID.\n");
        return;
    }

    if (library[book_id - 1].is_borrowed) 
    {
        printf("Book is already borrowed.\n");
    } 
    else if (users[user_id - 1].borrow_count >= MAX_BORROW_LIMIT) 
    {
        printf("You cannot borrow more than %d books.\n", MAX_BORROW_LIMIT);
    } 
    else 
    {
        library[book_id - 1].is_borrowed = 1;
        users[user_id - 1].borrowed_books[users[user_id - 1].borrow_count] = book_id;
        users[user_id - 1].borrow_count++;
        users[user_id - 1].borrowed_history[users[user_id - 1].history_count++] = book_id;
        printf("Book borrowed successfully!\n");
    }
}

void return_book() 
{
    int book_id, user_id;
    printf("Enter the book ID to return: ");
    scanf("%d", &book_id);
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count || user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid book or user ID.\n");
        return;
    }

    if (!library[book_id - 1].is_borrowed) 
    {
        printf("Book is not borrowed.\n");
    } 
    else 
    {
        library[book_id - 1].is_borrowed = 0;
        printf("Book returned successfully!\n");
    }
}

void add_user() 
{
    if (user_count >= MAX_USERS) 
    {
        printf("User limit reached!\n");
        return;
    }

    User new_user;
    new_user.id = user_count + 1;
    printf("Enter username: ");
    fgets(new_user.username, USERNAME_LENGTH, stdin);
    strtok(new_user.username, "\n");
    new_user.borrow_count = 0;
    new_user.history_count = 0;
    new_user.fines_due = 0.0;
    memset(new_user.borrowed_books, 0, sizeof(new_user.borrowed_books));

    users[user_count] = new_user;
    user_count++;
    printf("User added successfully!\n");
}

void list_users() 
{
    if (user_count == 0) 
    {
        printf("No users available.\n");
        return;
    }

    printf("\nUsers in System:\n");

    for (int i = 0; i < user_count; i++) 
    {
        printf("ID: %d | Username: %s | Fines Due: %.2f\n", 
               users[i].id, users[i].username, users[i].fines_due);
    }
}

void edit_book() 
{
    int book_id;
    printf("Enter the book ID to edit: ");
    scanf("%d", &book_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count) 
    {
        printf("Invalid book ID.\n");
        return;
    }

    Book *book = &library[book_id - 1];
    printf("Editing Book ID: %d\n", book->id);
    printf("Current Title: %s\n", book->title);
    printf("Current Author: %s\n", book->author);
    printf("Enter new title (or press Enter to keep current): ");
    char new_title[TITLE_LENGTH];
    fgets(new_title, TITLE_LENGTH, stdin);
    strtok(new_title, "\n");

    if (strlen(new_title) > 0) 
    {
        strcpy(book->title, new_title);
    }
    
    printf("Enter new author (or press Enter to keep current): ");
    char new_author[AUTHOR_LENGTH];
    fgets(new_author, AUTHOR_LENGTH, stdin);
    strtok(new_author, "\n");

    if (strlen(new_author) > 0) 
    {
        strcpy(book->author, new_author);
    }

    printf("Book updated successfully!\n");
}

void delete_book() 
{
    int book_id;
    printf("Enter the book ID to delete: ");
    scanf("%d", &book_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count) 
    {
        printf("Invalid book ID.\n");
        return;
    }

    for (int i = book_id - 1; i < book_count - 1; i++) 
    {
        library[i] = library[i + 1]; // Shift books left
    }
    
    book_count--;
    printf("Book deleted successfully!\n");
}

void view_borrowed_books() 
{
    int user_id;
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid user ID.\n");
        return;
    }

    printf("\nBorrowed Books by User ID: %d\n", user_id);
    User *user = &users[user_id - 1];

    for (int i = 0; i < user->borrow_count; i++) 
    {
        int book_id = user->borrowed_books[i];
        printf("ID: %d | Title: %s\n", book_id, library[book_id - 1].title);
    }
}

void reserve_book() 
{
    int book_id, user_id;
    printf("Enter the book ID to reserve: ");
    scanf("%d", &book_id);
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count || user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid book or user ID.\n");
        return;
    }

    if (library[book_id - 1].reserved_by == -1) 
    {
        library[book_id - 1].reserved_by = user_id;
        printf("Book reserved successfully!\n");
    } 
    else 
    {
        printf("Book is already reserved.\n");
    }
}

void cancel_reservation() 
{
    int book_id, user_id;
    printf("Enter the book ID to cancel reservation: ");
    scanf("%d", &book_id);
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count || user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid book or user ID.\n");
        return;
    }

    if (library[book_id - 1].reserved_by == user_id) 
    {
        library[book_id - 1].reserved_by = -1;
        printf("Reservation cancelled successfully.\n");
    } 
    else 
    {
        printf("You have not reserved this book.\n");
    }
}

void apply_fine(int user_id, float fine_amount) 
{
    if (user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid user ID.\n");
        return;
    }

    users[user_id - 1].fines_due += fine_amount;
    printf("Fine of %.2f applied to User ID: %d\n", fine_amount, user_id);
}

void pay_fine() 
{
    int user_id;
    float payment;
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid user ID.\n");
        return;
    }

    printf("Enter payment amount: ");
    scanf("%f", &payment);
    clear_buffer();

    if (payment > users[user_id - 1].fines_due) 
    {
        printf("Payment exceeds fine amount!\n");
    } 
    else 
    {
        users[user_id - 1].fines_due -= payment;
        printf("Payment successful!\n");
    }
}

void view_fines() 
{
    int user_id;
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid user ID.\n");
        return;
    }

    printf("Total Fines Due: %.2f\n", users[user_id - 1].fines_due);
}

void view_borrow_history() 
{
    int user_id;
    printf("Enter your user ID: ");
    scanf("%d", &user_id);
    clear_buffer();

    if (user_id <= 0 || user_id > user_count) 
    {
        printf("Invalid user ID.\n");
        return;
    }

    printf("Borrow History for User ID: %d\n", user_id);
    User *user = &users[user_id - 1];
    
    for (int i = 0; i < user->history_count; i++) 
    {
        int book_id = user->borrowed_history[i];
        printf("Book ID: %d | Title: %s\n", book_id, library[book_id - 1].title);
    }
}

void save_data() 
{
    // Save data to a file (if implemented)
    printf("Saving data...\n");
    // Implement file saving logic here
}

void load_data() 
{
    // Load data from a file (if implemented)
    printf("Loading data...\n");
    // Implement file loading logic here
}
