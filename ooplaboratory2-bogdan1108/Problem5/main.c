#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tests.h"

void create_start_menu()
{
    printf("Welcome to the game of 24!\n");
}

void arg_h(int help) {
    if (help == 1)
        printf("Use each of the four numbers shown below exactly once, combining them somehow with the basic mathematical operators (+, -, *, /) to yiled the value of 24.\n");

}

void arg_s(int save, int **numbers, char **operators) {
    if (save == 1) {
        printf("Saved all the possible solutions in solution.txt.\n");
        FILE *f = fopen("solution.txt", "w");
        if (f == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
        for (int i = 0; i < 3188; i++) {
            fprintf(f, "%d %c %d %c %d %c %d\n", numbers[i][0], operators[i][0], numbers[i][1], operators[i][1], numbers[i][2], operators[i][2], numbers[i][3]);
        }
    }
}

void arg_e(int easy) {
    if (easy == 1)
        printf("Easy mode selected.\n");
}

void generate_the_digits_to_use_randomly(int **numbers, int *num)
{
    // generate the numbers to use randomly (numbers is dynamically allocated)
    
    int i = rand() % 3188;
    num[0] = numbers[i][0];
    num[1] = numbers[i][1];
    num[2] = numbers[i][2];
    num[3] = numbers[i][3];
    printf("The numbers to use are: %d, %d, %d, %d.\n", num[0], num[1], num[2], num[3]);
}

// function that reads the input from the user of exactly 3 operations and checks if they are valid
void readInput(char *operators)
{
    printf("Enter the three operations to be used, in order (+, -, *, /): ");
    scanf("%s", operators);
    if (strlen(operators) != 3)
    {
        printf("Error: you need to enter exactly three operators. Please retry!\n");
        readInput(operators);
    }
    // check if the operators are valid
    int i;
    for (i = 0; i < 3; i++)
    {
        if (operators[i] != '+' && operators[i] != '-' && operators[i] != '*' && operators[i] != '/')
        {
            printf("Error: you typed an invalid operator. Please retry!\n");
            readInput(operators);
        }
    }
}

// int play_again()
// {
//     char answer;
//     printf("Do you want to play again?");
//     scanf("%c", &answer);
//     if (answer == 'y')
//         return 0;
//     else
//         return 1;
// }

// Write a function generateAllCombinations that takes as parameters two dynamically allocated arrays (one for the operators and one for the operands, and fills in all the 3188 solutions). 
void generateAllCombinations(int** numbers, char** operators) {
    // write generateAllCombinations such that every possible combination of the 4 numbers and 3 operators with the result 24 is generated
double res = 0.0;
int counter = 0;
    for (int i = 1; i <= 9; i++){
        for (int j = 1; j <= 9; j++){
            for (int k = 1; k <= 9; k++){
                for (int l = 1; l <= 9; l++){
                    for (int m = 0; m <= 3; m++){
                        for (int n = 0; n <= 3; n++){
                            for (int o = 0; o <= 3; o++){
                                res = 0;
                                double nr1 = i;
                                double nr2 = j;
                                double nr3 = k;
                                double nr4 = l;
                                int op1 = m;
                                int op2 = n;
                                int op3 = o;
                                if (m == 0)
                                    op1 = '+';
                                else if (m == 1)
                                    op1 = '-';
                                else if (m == 2)
                                    op1 = '*';
                                else if (m == 3)
                                    op1 = '/';
                                if (n == 0)
                                    op2 = '+';
                                else if (n == 1)
                                    op2 = '-';
                                else if (n == 2)
                                    op2 = '*';
                                else if (n == 3)
                                    op2 = '/';
                                if (o == 0)
                                    op3 = '+';
                                else if (o == 1)
                                    op3 = '-';
                                else if (o == 2)
                                    op3 = '*';
                                else if (o == 3)
                                    op3 = '/';


                                    if (op1 == '+')
                                        res = nr1 + nr2;
                                    else if (op1 == '-')
                                        res = nr1 - nr2;
                                    else if (op1 == '*')
                                        res = nr1 * nr2;
                                    else if (op1 == '/')
                                        res = nr1 / nr2;

                                    if (op2 == '+')
                                        res = res + nr3;
                                    else if (op2 == '-')
                                        res = res - nr3;
                                    else if (op2 == '*')
                                        res = res * nr3;
                                    else if (op2 == '/')
                                        res = res / nr3;

                                    if (op3 == '+')
                                        res = res + nr4;
                                    else if (op3 == '-')
                                        res = res - nr4;
                                    else if (op3 == '*')
                                        res = res * nr4;
                                    else if (op3 == '/')
                                        res = res / nr4;

                                    const double epsilon = 0.0000001;
                                    if(24 - epsilon < res && res < 24 + epsilon){
                                        numbers[counter][0] = nr1;
                                        numbers[counter][1] = nr2;
                                        numbers[counter][2] = nr3;
                                        numbers[counter][3] = nr4;
                                        operators[counter][0] = op1;
                                        operators[counter][1] = op2;
                                        operators[counter][2] = op3;
                                        counter++;
                                        //printf("%d: %f %c %f %c %f %c %f\n",counter, nr1, op1, nr2, op2, nr3, op3, nr4);
                                    }

                            }
                        }
                    }
                }
            }
        }
    }
}

void compute(char* op, int* num) {
    double result = 0;
    if (op[0] == '+') {
        result = num[0] + num[1];
        printf("%d %c %d = %f\n", num[0], op[0], num[1], result);}
    else if (op[0] == '-') {
        result = num[0] - num[1];
        printf("%d %c %d = %f\n", num[0], op[0], num[1], result);}
    else if (op[0] == '*') {
        result = num[0] * num[1];
        printf("%d %c %d = %f\n", num[0], op[0], num[1], result);}
    else if (op[0] == '/') {
        result = num[0] / num[1];
        printf("%d %c %d = %f\n", num[0], op[0], num[1], result);}
    
    if (op[1] == '+') {
        result = result + num[2];
        printf("%f %c %d = %f\n", result, op[1], num[2], result);}
    else if (op[1] == '-') {
        result = result - num[2];
        printf("%f %c %d = %f\n", result, op[1], num[2], result);}
    else if (op[1] == '*') {
        result = result * num[2];
        printf("%f %c %d = %f\n", result, op[1], num[2], result);}
    else if (op[1] == '/') {
        result = result / num[2];
        printf("%f %c %d = %f\n", result, op[1], num[2], result);}

    if (op[2] == '+') {
        result = result + num[3];
        printf("%f %c %d = %f\n", result, op[2], num[3], result);}
    else if (op[2] == '-') {
        result = result - num[3];
        printf("%f %c %d = %f\n", result, op[2], num[3], result);}
    else if (op[2] == '*') {
        result = result * num[3];
        printf("%f %c %d = %f\n", result, op[2], num[3], result);}
    else if (op[2] == '/') {
        result = result / num[3];
        printf("%f %c %d = %f\n", result, op[2], num[3], result);}
    
    if(result == 24)
        printf("Well done! You won!\n");
    else
        printf("Sadly, You lost! :(\n)");
}

void play_again(int** numbers, char** operators, int* num, char* op) {
    int again = 0;
    printf("Do you want to play again? (1 - yes, 0 - no): ");
    scanf("%d", &again);
    if (again == 1) {
        create_start_menu();
        generateAllCombinations(numbers, operators);
        generate_the_digits_to_use_randomly(numbers, num);
        readInput(op);
        compute(op, num);
        play_again(numbers, operators, num, op);
    }
    else {
        printf("Goodbye!\n");
        exit(0);
    }

}

void play_again_easy() {
    int again = 0;
    printf("Do you want to play again? (1 - yes, 0 - no): ");
    scanf("%d", &again);
    if (again == 1) {
        int easy_numbers[7][4] = {
            {1, 1, 4, 6},
            {1, 1, 3, 8},
            {1, 2, 2, 6},
            {1, 2, 3, 4},
            {1, 1, 3, 9},
            {4, 4, 4, 6},
            {1, 8, 8, 8}
        };
        // give to the user one random option from easy_numbers
        srand(time(NULL));
        int i = rand() % 7;
        int easy_nr[4];
        easy_nr[0] = easy_numbers[i][0];
        easy_nr[1] = easy_numbers[i][1];
        easy_nr[2] = easy_numbers[i][2];
        easy_nr[3] = easy_numbers[i][3];

        printf("The numbers to use are: %d, %d, %d, %d.\n", easy_numbers[i][0], easy_numbers[i][1], easy_numbers[i][2], easy_numbers[i][3]);
        printf("The operators to use are: +, -, *, /.\n");
        printf("Please enter the operators you want to use: ");
        char op[3];
        scanf("%s", op);
        compute(op, easy_nr);
    }
    else {
        printf("Goodbye!\n");
    }
    
}

// command line arguments -h -s -e
int main(int argc, char *argv[])
{
    // initialize the command line arguments
    int save = 0;
    int easy = 0;
    int help = 0;
    int i;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help = 1;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            save = 1;
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            easy = 1;
        }
    }

    srand(time(NULL));
#if ENABLE_TESTS == 1
    run_tests(true);
#endif
    create_start_menu();
    arg_h(help);
    arg_e(easy);
    if (easy == 1) {
        int easy_numbers[7][4] = {
            {1, 1, 4, 6},
            {1, 1, 3, 8},
            {1, 2, 2, 6},
            {1, 2, 3, 4},
            {1, 1, 3, 9},
            {4, 4, 4, 6},
            {1, 8, 8, 8}
        };
        // give to the user one random option from easy_numbers
        srand(time(NULL));
        int i = rand() % 7;
        printf("The numbers to use are: %d, %d, %d, %d.\n", easy_numbers[i][0], easy_numbers[i][1], easy_numbers[i][2], easy_numbers[i][3]);
        printf("The operators to use are: +, -, *, /.\n");
        printf("Please enter the operators you want to use: ");
        char op[3];
        scanf("%s", op);
        compute(op, easy_numbers[i]);
        exit(0);
    }
    // allocate memory for the numbers and operators dynamically with calloc
    int** numbers = (int**)malloc(3188 * sizeof(int*));
    int* num = (int*)malloc(4 * sizeof(int));
	char** operators = (char**)malloc(3188 * sizeof(char*));
    char* op = (char*)malloc(3 * sizeof(char));
	if (numbers == NULL || operators == NULL || op == NULL || num == NULL) {
		printf("Failed to allocate memory");
		exit(-1);
	}

	for (int i = 0; i < 3188; i++) {

		numbers[i] = (int*)malloc(4 * sizeof(int));
		operators[i] = (char*)malloc(3 * sizeof(char));
		if (numbers[i] == NULL || operators[i] == NULL) {
			printf("Failed to allocate memory");
			exit(-1);
		}
	}

	generateAllCombinations(numbers, operators);
    generate_the_digits_to_use_randomly(numbers, num);
    arg_s(save, numbers, operators);
    readInput(op);
    compute(op, num);
    play_again(numbers, operators, num, op);
    //readInput(op);
    // free the memory for the numbers
    // free(numbers);
    for (int i = 0; i < 3188; i++) {
		free(numbers[i]);
		free(operators[i]);
	}
    free(num);
    free(op);
    free(numbers);
    free(operators);
}
