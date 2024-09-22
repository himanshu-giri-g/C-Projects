#include <stdio.h>

int main() {
    int P; // Principal Amount
    float R; // Rate of Interest
    int T; // Time Period

    printf("Enter Principal Amount (in ₹): ");
    scanf("%d", &P);

    printf("Enter Rate of Interest (in %%): ");
    scanf("%f", &R);

    printf("Enter Time Period (in years): ");
    scanf("%d", &T);

    float SI = (P * R * T) / 100.0; // Simple Interest

    printf("Simple Interest for the given amount is: Rs.%f\n", SI);

    return 0;
}