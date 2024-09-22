#include <stdio.h>

int factorial(int num) {
    if (num == 1 || num == 0) {
        return 1;
    } else {
        return num * factorial(num - 1);
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("The factorial of %d is %d.\n", num, factorial(num));
    return 0;
}