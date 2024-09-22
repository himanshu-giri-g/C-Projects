#include <stdio.h>
#include <math.h>

int main() {
    int a, sum = 0, temp, remainder, n = 0;

    printf("Enter a Number: ");
    scanf("%d", &a);

    temp = a;

    // Count the number of digits
    while (temp != 0) {
        temp /= 10;
        n++;
    }

    temp = a;

    // Calculate the sum of the digits powered by the number of digits
    while (temp != 0) {
        remainder = temp % 10;
        sum += pow(remainder, n);
        temp /= 10;
    }

    if (sum == a) {
        printf("The No. %d is an Armstrong Number.\n", a);
    } else {
        printf("The No. %d is not an Armstrong Number.\n", a);
    }

    return 0;
}