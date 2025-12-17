#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Global Memory Variable
double memory = 0.0;

// Displays the calculator menu
void show_menu() {
    printf("\n--- ADVANCED CALCULATOR (With Memory Support) ---\n");
    printf("Current Memory Value (M): %.2lf\n", memory);
    printf("----------------------------------------\n");
    printf("Basic Operations (Two Numbers):\n");
    printf("  + : Addition\t  - : Subtraction\n");
    printf("  * : Multiplication\t  / : Division\n");
    printf("Scientific Operations (Single Number):\n");
    printf("  S : Square Root\t  L : Logarithm (ln)\t G : Sinus (degrees)\n");
    printf("  P : Power (Two Numbers: base exponent)\n");
    printf("Memory Operations:\n");
    printf("  M+ : Add Result to Memory\t M- : Subtract Result from Memory\n");
    printf("  MC : Clear Memory\t MR : Recall Memory (Use R instead of number)\n");
    printf("Other:\n");
    printf("  Q : Quit\t  ? : Show Menu\n");
    printf("----------------------------------------\n");
}

// Clears input buffer and fixes invalid input
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Main Calculator Logic
void calculator() {
    char operation;
    double number1, number2, result;
    int requires_single_number = 0;

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    show_menu();

    while (1) {
        printf("\nSelect operation (M: %.2lf): ", memory);

        if (scanf(" %c", &operation) != 1) {
            printf("Error: Invalid operation input.\n");
            clear_buffer();
            continue;
        }

        if (operation == 'Q' || operation == 'q') {
            printf("Exiting calculator.\n");
            break;
        }
        if (operation == '?') {
            show_menu();
            continue;
        }

        if (operation == 'M' || operation == 'm') {
            char next_char;
            if (scanf("%c", &next_char) == 1 && (next_char == 'C' || next_char == 'c')) {
                memory = 0.0;
                printf("Memory cleared (MC). New memory value: %.2lf\n", memory);
                continue;
            } else {
                printf("Error: Invalid memory command. Use MC.\n");
                clear_buffer();
                continue;
            }
        }

        if (operation == 'S' || operation == 's' ||
            operation == 'G' || operation == 'g' ||
            operation == 'L' || operation == 'l') {
            requires_single_number = 1;
        } else if (operation == '+' || operation == '-' ||
                   operation == '*' || operation == '/' ||
                   operation == 'P' || operation == 'p') {
            requires_single_number = 0;
        } else {
            printf("Error: Unknown operation! Please enter a valid operation (or ?).\n");
            clear_buffer();
            continue;
        }

        if (requires_single_number) {
            printf("Enter a number (R for MR): ");
            if (scanf("%lf", &number1) != 1) {
                char mr_check;
                if (scanf(" %c", &mr_check) == 1 && (mr_check == 'R' || mr_check == 'r')) {
                    number1 = memory;
                    printf("-> Using %.2lf from memory (MR).\n", memory);
                } else {
                    printf("Error: Invalid number input.\n");
                    clear_buffer();
                    continue;
                }
            }
        } else {
            printf("Enter two numbers (R for MR): ");

            if (scanf("%lf", &number1) != 1) {
                char mr_check1;
                if (scanf(" %c", &mr_check1) == 1 && (mr_check1 == 'R' || mr_check1 == 'r')) {
                    number1 = memory;
                    printf("-> Using %.2lf from memory (Number 1).\n", memory);
                } else {
                    printf("Error: Invalid input for number 1.\n");
                    clear_buffer();
                    continue;
                }
            }

            if (scanf("%lf", &number2) != 1) {
                char mr_check2;
                if (scanf(" %c", &mr_check2) == 1 && (mr_check2 == 'R' || mr_check2 == 'r')) {
                    number2 = memory;
                    printf("-> Using %.2lf from memory (Number 2).\n", memory);
                } else {
                    printf("Error: Invalid input for number 2.\n");
                    clear_buffer();
                    continue;
                }
            }
        }

        result = 0.0;
        int calculation_successful = 1;

        switch (operation) {
            case '+': printf("%.2lf + %.2lf ", number1, number2); result = number1 + number2; break;
            case '-': printf("%.2lf - %.2lf ", number1, number2); result = number1 - number2; break;
            case '*': printf("%.2lf * %.2lf ", number1, number2); result = number1 * number2; break;
            case '/':
                if (number2 != 0) {
                    printf("%.2lf / %.2lf ", number1, number2);
                    result = number1 / number2;
                } else {
                    printf("Error: Division by zero is undefined.\n");
                    calculation_successful = 0;
                }
                break;
            case 'P': case 'p':
                printf("%.2lf ^ %.2lf ", number1, number2);
                result = pow(number1, number2);
                break;
            case 'S': case 's':
                if (number1 >= 0) {
                    printf("sqrt(%.2lf) ", number1);
                    result = sqrt(number1);
                } else {
                    printf("Error: Square root of a negative number.\n");
                    calculation_successful = 0;
                }
                break;
            case 'G': case 'g':
                printf("sin(%.2lf) ", number1);
                result = sin(number1 * M_PI / 180.0);
                break;
            case 'L': case 'l':
                if (number1 > 0) {
                    printf("ln(%.2lf) ", number1);
                    result = log(number1);
                } else {
                    printf("Error: Logarithm requires a positive number.\n");
                    calculation_successful = 0;
                }
                break;
        }

        if (calculation_successful) {
            printf("= %.4lf\n", result);

            printf("Memory operation (M+/M-/h): ");
            char memory_command;
            if (scanf(" %c", &memory_command) == 1) {
                if (memory_command == 'M') {
                    char op;
                    if (scanf("%c", &op) == 1) {
                        if (op == '+') {
                            memory += result;
                            printf("-> Result (%.4lf) added to memory (M+). New memory: %.2lf\n", result, memory);
                        } else if (op == '-') {
                            memory -= result;
                            printf("-> Result (%.4lf) subtracted from memory (M-). New memory: %.2lf\n", result, memory);
                        } else {
                            printf("-> Memory operation canceled.\n");
                        }
                    } else {
                        printf("-> Memory operation canceled.\n");
                    }
                } else {
                    printf("-> Memory operation canceled.\n");
                }
            }
            clear_buffer();
        }
    }
}

int main() {
    calculator();
    return 0;
}
