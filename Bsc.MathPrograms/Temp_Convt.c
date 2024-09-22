#include <stdio.h>

// Function to convert Celsius to Kelvin
float celsius_to_kelvin(float temp) {
    return temp + 273.0;
}

// Function to convert Kelvin to Celsius
float kelvin_to_celsius(float temp) {
    return temp - 273.0;
}

int main() {
    int option;
    float temp;

    printf("---WELCOME TO TEMPERATURE CONVERTER---\n");
    printf("1. Celsius to Kelvin\n2. Kelvin to Celsius\n");

    printf("Choose any one option: ");
    scanf("%d", &option);

    if (option == 1) {
        printf("Enter temperature to be converted (in Celsius): ");
        scanf("%f", &temp);
        printf("The temperature in Kelvin for the given temperature is: %.2f K\n", celsius_to_kelvin(temp));
    } else if (option == 2) {
        printf("Enter temperature to be converted (in Kelvin): ");
        scanf("%f", &temp);
        printf("The temperature in Celsius for the given temperature is: %.2f C\n", kelvin_to_celsius(temp));
    } else {
        printf("ERROR! Please choose a valid option.\n");
    }

    return 0;
}