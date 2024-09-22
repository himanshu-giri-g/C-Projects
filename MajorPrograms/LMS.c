// LMS (Library Management System)

// Functionalties :-

// 1. Editing and deleting books.
// 2. Viewing borrowed books by a user.
// 3. Enhancing the user interface and adding error handling.
// 4. Implementing a simple search feature for users.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 100
#define USERNAME_LENGTH 50

typedef struct 
{
    int id;
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int is_borrowed;
} Book;

typedef struct 
{
    int id;
    char username[USERNAME_LENGTH];
    int borrowed_books[MAX_BOOKS];
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
void menu();
void initialize();
void clear_buffer();

int main() {
    initialize();
    menu();
    return 0;
}

void initialize() 
{
    // Prepopulate with some books
    strcpy(library[0].title, "The Great Gatsby");
    strcpy(library[0].author, "F. Scott Fitzgerald");
    library[0].id = 1;
    library[0].is_borrowed = 0;
    book_count++;

    strcpy(library[1].title, "1984");
    strcpy(library[1].author, "George Orwell");
    library[1].id = 2;
    library[1].is_borrowed = 0;
    book_count++;

    strcpy(users[0].username, "admin");
    users[0].id = 1;
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
    new_book.id = book_count + 1;  // Assign ID based on current count
    printf("Enter book title: ");
    fgets(new_book.title, TITLE_LENGTH, stdin);
    strtok(new_book.title, "\n");  // Remove newline
    printf("Enter author name: ");
    fgets(new_book.author, AUTHOR_LENGTH, stdin);
    strtok(new_book.author, "\n");  // Remove newline
    new_book.is_borrowed = 0;  // Initially not borrowed

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
        printf("ID: %d | Title: %s | Author: %s | Borrowed: %s\n", 
                library[i].id, 
                library[i].title, 
                library[i].author, 
                library[i].is_borrowed ? "Yes" : "No");
    }
}

void search_book() 
{
    char title[TITLE_LENGTH];
    printf("Enter book title to search: ");
    fgets(title, TITLE_LENGTH, stdin);
    strtok(title, "\n");  // Remove newline

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
    int book_id;
    printf("Enter the book ID to borrow: ");
    scanf("%d", &book_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count) 
    {
        printf("Invalid book ID.\n");
        return;
    }

    if (library[book_id - 1].is_borrowed) 
    {
        printf("Book is already borrowed.\n");
    } 

    else
    {
        library[book_id - 1].is_borrowed = 1;
        printf("Book borrowed successfully!\n");
    }
}

void return_book() 
{
    int book_id;
    printf("Enter the book ID to return: ");
    scanf("%d", &book_id);
    clear_buffer();

    if (book_id <= 0 || book_id > book_count)
    {
        printf("Invalid book ID.\n");
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
    new_user.id = user_count + 1;  // Assign ID based on current count
    printf("Enter username: ");
    fgets(new_user.username, USERNAME_LENGTH, stdin);
    strtok(new_user.username, "\n");  // Remove newline
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
        printf("ID: %d | Username: %s\n", users[i].id, users[i].username);
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
    strtok(new_title, "\n");  // Remove newline

    if (strlen(new_title) > 0) 
    {
        strcpy(book->title, new_title);
    }
    
    printf("Enter new author (or press Enter to keep current): ");
    char new_author[AUTHOR_LENGTH];
    fgets(new_author, AUTHOR_LENGTH, stdin);
    strtok(new_author, "\n");  // Remove newline

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
}