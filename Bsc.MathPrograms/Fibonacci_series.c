#include <stdio.h>

int main() {
    int n = 10;
    int num1 = 0;
    int num2 = 1;
    int next_number = num2;
    int count = 1;

    while (count <= n) {
        printf("%d ", next_number);
        count++;
        num1 = num2;
        num2 = next_number;
        next_number = num1 + num2;
    }
    printf("\n");
    return 0;
}