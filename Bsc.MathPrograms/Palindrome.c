#include <stdio.h>
#include <string.h>

int main() {
    char str_n[100];
    printf("Enter a word: ");
    fgets(str_n, sizeof(str_n), stdin);
    str_n[strcspn(str_n, "\n")] = 0; // remove the newline character

    int len = strlen(str_n);
    int i;
    int is_palindrome = 1;

    for (i = 0; i < len / 2; i++) {
        if (str_n[i] != str_n[len - i - 1]) {
            is_palindrome = 0;
            break;
        }
    }

    if (is_palindrome) {
        printf("The word %s is a Palindrome.\n", str_n);
    } else {
        printf("The word %s is not a Palindrome.\n", str_n);
    }

    return 0;
}