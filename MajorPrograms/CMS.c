// CMS (Contact Management System) or PhoneBook

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define NAME_LENGTH 100
#define PHONE_LENGTH 15
#define EMAIL_LENGTH 100
#define FILENAME "contacts.dat"
#define GROUP_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    char phone[PHONE_LENGTH];
    char email[EMAIL_LENGTH];
    char group[GROUP_LENGTH];  // New field to categorize contacts
} Contact;

Contact contacts[MAX_CONTACTS];
int contact_count = 0;

void load_contacts();
void save_contacts();
void add_contact();
void view_contacts();
void edit_contact();
void delete_contact();
void search_contact();
void sort_contacts();
void export_contacts_to_csv();
void import_contacts_from_csv();
void filter_contacts_by_group();
void display_statistics();
void clear_buffer();
void menu();
void display_contact(Contact contact);
int get_contact_index(int id);

int main() {
    load_contacts();
    menu();
    return 0;
}

void load_contacts() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(&contact_count, sizeof(int), 1, file);
        fread(contacts, sizeof(Contact), contact_count, file);
        fclose(file);
    }
}

void save_contacts() {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(&contact_count, sizeof(int), 1, file);
        fwrite(contacts, sizeof(Contact), contact_count, file);
        fclose(file);
    }
}

void menu() {
    int choice;
    do {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Search Contact\n");
        printf("6. Sort Contacts\n");
        printf("7. Export Contacts to CSV\n");
        printf("8. Import Contacts from CSV\n");
        printf("9. Filter Contacts by Group\n");
        printf("10. Display Statistics\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice) {
            case 1: add_contact(); break;
            case 2: view_contacts(); break;
            case 3: edit_contact(); break;
            case 4: delete_contact(); break;
            case 5: search_contact(); break;
            case 6: sort_contacts(); break;
            case 7: export_contacts_to_csv(); break;
            case 8: import_contacts_from_csv(); break;
            case 9: filter_contacts_by_group(); break;
            case 10: display_statistics(); break;
            case 0: printf("Exiting...\n"); save_contacts(); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);
}

void clear_buffer() {
    while (getchar() != '\n'); // Clear input buffer
}

void add_contact() {
    if (contact_count >= MAX_CONTACTS) {
        printf("Contact limit reached! Cannot add more contacts.\n");
        return;
    }

    Contact new_contact;
    new_contact.id = contact_count + 1; // Assign ID based on current count

    printf("Enter contact name: ");
    fgets(new_contact.name, NAME_LENGTH, stdin);
    strtok(new_contact.name, "\n");  // Remove newline

    printf("Enter contact phone: ");
    fgets(new_contact.phone, PHONE_LENGTH, stdin);
    strtok(new_contact.phone, "\n");  // Remove newline

    printf("Enter contact email: ");
    fgets(new_contact.email, EMAIL_LENGTH, stdin);
    strtok(new_contact.email, "\n");  // Remove newline

    printf("Enter contact group: ");
    fgets(new_contact.group, GROUP_LENGTH, stdin);
    strtok(new_contact.group, "\n");  // Remove newline

    contacts[contact_count] = new_contact;
    contact_count++;
    printf("Contact added successfully!\n");
}

void view_contacts() {
    if (contact_count == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("\n--- Contacts ---\n");
    for (int i = 0; i < contact_count; i++) {
        display_contact(contacts[i]);
    }
}

void display_contact(Contact contact) {
    printf("ID: %d | Name: %s | Phone: %s | Email: %s | Group: %s\n", 
           contact.id, 
           contact.name, 
           contact.phone, 
           contact.email,
           contact.group);
}

int get_contact_index(int id) {
    for (int i = 0; i < contact_count; i++) {
        if (contacts[i].id == id) {
            return i;
        }
    }
    return -1; // Not found
}

void edit_contact() {
    int id;
    printf("Enter the contact ID to edit: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_contact_index(id);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    Contact *contact = &contacts[index];
    printf("Editing Contact ID: %d\n", contact->id);
    printf("Current Name: %s\n", contact->name);
    printf("Current Phone: %s\n", contact->phone);
    printf("Current Email: %s\n", contact->email);
    printf("Current Group: %s\n", contact->group);

    printf("Enter new name (or press Enter to keep current): ");
    char new_name[NAME_LENGTH];
    fgets(new_name, NAME_LENGTH, stdin);
    strtok(new_name, "\n");  // Remove newline
    if (strlen(new_name) > 0) {
        strcpy(contact->name, new_name);
    }

    printf("Enter new phone (or press Enter to keep current): ");
    char new_phone[PHONE_LENGTH];
    fgets(new_phone, PHONE_LENGTH, stdin);
    strtok(new_phone, "\n");  // Remove newline
    if (strlen(new_phone) > 0) {
        strcpy(contact->phone, new_phone);
    }

    printf("Enter new email (or press Enter to keep current): ");
    char new_email[EMAIL_LENGTH];
    fgets(new_email, EMAIL_LENGTH, stdin);
    strtok(new_email, "\n");  // Remove newline
    if (strlen(new_email) > 0) {
        strcpy(contact->email, new_email);
    }

    printf("Enter new group (or press Enter to keep current): ");
    char new_group[GROUP_LENGTH];
    fgets(new_group, GROUP_LENGTH, stdin);
    strtok(new_group, "\n");  // Remove newline
    if (strlen(new_group) > 0) {
        strcpy(contact->group, new_group);
    }

    printf("Contact updated successfully!\n");
}

void delete_contact() {
    int id;
    printf("Enter the contact ID to delete: ");
    scanf("%d", &id);
    clear_buffer();

    int index = get_contact_index(id);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }

    for (int i = index; i < contact_count - 1; i++) {
        contacts[i] = contacts[i + 1]; // Shift contacts left
    }
    contact_count--;
    printf("Contact deleted successfully!\n");
}

void search_contact() {
    char search_term[NAME_LENGTH];
    printf("Enter name or part of name to search: ");
    fgets(search_term, NAME_LENGTH, stdin);
    strtok(search_term, "\n");  // Remove newline

    printf("\n--- Search Results ---\n");
    int found = 0;
    for (int i = 0; i < contact_count; i++) {
        if (strstr(contacts[i].name, search_term) != NULL) {
            display_contact(contacts[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No contacts found with that name.\n");
    }
}

void sort_contacts() {
    for (int i = 0; i < contact_count - 1; i++) {
        for (int j = i + 1; j < contact_count; j++) {
            if (strcmp(contacts[i].name, contacts[j].name) > 0) {
                Contact temp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temp;
            }
        }
    }
    printf("Contacts sorted by name.\n");
}

void export_contacts_to_csv() {
    FILE *file = fopen("contacts.csv", "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "ID,Name,Phone,Email,Group\n");
    for (int i = 0; i < contact_count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n", 
                contacts[i].id, 
                contacts[i].name, 
                contacts[i].phone, 
                contacts[i].email,
                contacts[i].group);
    }
    fclose(file);
    printf("Contacts exported to contacts.csv successfully!\n");
}

void import_contacts_from_csv() {
    FILE *file = fopen("contacts.csv", "r");
    if (!file) {
        printf("Failed to open file for reading.\n");
        return;
    }

    char line[256];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Skip the header line (first line)
        if (line_num == 0) {
            line_num++;
            continue;
        }

        // Split the line into tokens (ID, Name, Phone, Email, Group)
        char *token = strtok(line, ",");
        if (token == NULL) continue;

        // Parse the ID (ignored because IDs will be reassigned based on contact_count)
        int id = atoi(token);

        // Get the name
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        char name[NAME_LENGTH];
        strncpy(name, token, NAME_LENGTH);

        // Get the phone
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        char phone[PHONE_LENGTH];
        strncpy(phone, token, PHONE_LENGTH);

        // Get the email
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        char email[EMAIL_LENGTH];
        strncpy(email, token, EMAIL_LENGTH);

        // Get the group
        token = strtok(NULL, "\n");
        if (token == NULL) continue;
        char group[GROUP_LENGTH];
        strncpy(group, token, GROUP_LENGTH);

        // Add contact to the list (if there's space)
        if (contact_count < MAX_CONTACTS) {
            Contact new_contact;
            new_contact.id = contact_count + 1;
            strncpy(new_contact.name, name, NAME_LENGTH);
            strncpy(new_contact.phone, phone, PHONE_LENGTH);
            strncpy(new_contact.email, email, EMAIL_LENGTH);
            strncpy(new_contact.group, group, GROUP_LENGTH);

            contacts[contact_count] = new_contact;
            contact_count++;
        } else {
            printf("Contact limit reached! Some contacts may not be imported.\n");
            break;
        }
    }

    fclose(file);
    printf("Contacts imported from contacts.csv successfully!\n");
}

void filter_contacts_by_group() {
    char group[GROUP_LENGTH];
    
    printf("Enter group name to filter: ");
    fgets(group, GROUP_LENGTH, stdin);
    strtok(group, "\n");  // Remove newline character
    
    printf("\n--- Contacts in Group: %s ---\n", group);
    int found = 0;
    
    for (int i = 0; i < contact_count; i++) {
        if (strcmp(contacts[i].group, group) == 0) {
            display_contact(contacts[i]);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No contacts found in the group \"%s\".\n", group);
    }
}

void display_statistics() {
    printf("\n--- Contact Statistics ---\n");
    printf("Total Contacts: %d\n", contact_count);
    
    // Count contacts in each group
    int group_counts[MAX_CONTACTS] = {0};
    char groups[MAX_CONTACTS][GROUP_LENGTH] = {""};
    int unique_groups = 0;
    
    for (int i = 0; i < contact_count; i++) {
        int group_found = 0;
        for (int j = 0; j < unique_groups; j++) {
            if (strcmp(contacts[i].group, groups[j]) == 0) {
                group_counts[j]++;
                group_found = 1;
                break;
            }
        }
        if (!group_found) {
            strncpy(groups[unique_groups], contacts[i].group, GROUP_LENGTH);
            group_counts[unique_groups]++;
            unique_groups++;
        }
    }
    
    for (int i = 0; i < unique_groups; i++) {
        printf("Group \"%s\": %d contact(s)\n", groups[i], group_counts[i]);
    }
}