#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function that reads the frequency distribution from a file
void read(double *numbers)
{
    FILE *f = fopen("distribution.txt", "r");
    if (f == NULL)
    {
        printf("Error: could not open file!\n");
        exit(1);
    }
    int i = 0;
    while (fscanf(f, "%lf", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(f);
}

// Write a function that computes the normalized frequency of each character (a histogram) in a string.

void frequency(char *string, int *numbers1)
{
    int i;
    for (i = 0; i < 26; i++)
    {
        numbers1[i] = 0;
    }
    for (i = 0; i < strlen(string); i++)
    {
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            numbers1[string[i] - 'a']++;
        }
        else if (string[i] >= 'A' && string[i] <= 'Z')
        {
            numbers1[string[i] - 'A']++;
        }
    }
}

// expected numbers of each letter in the string

void expected_numbers(double *numbers, int length)
{
    int i;
    for (i = 0; i < 26; i++)
    {
        numbers[i] = length * numbers[i]/100;
    }
}

// Write a function that computes the Chi-square distance between two histograms.

int chi_square(double *numbers, int *numbers1)
{
    double chi_square = 0;
    int i;
    for (i = 0; i < 26; i++)
    {
        if (numbers[i] != 0)
        {
            if (numbers[i] > numbers1[i])
            {
                chi_square += (numbers[i] - numbers1[i]) * (numbers[i] - numbers1[i]) / numbers[i];
            }
            else
            {
                chi_square += (numbers1[i] - numbers[i]) * (numbers1[i] - numbers[i]) / numbers[i];
            }
        }
    }
    return chi_square;
}

// decodes a string using the caesar shift algorithm

void ceasar_shift_decoder(char *s, double *numbers)
{
    int i, n;
    int min_dist = 999999999;
    int shift = 0;
    int *numbers1 = (int *)malloc(26 * sizeof(int));
    if (numbers1 == NULL)
    {
        printf("Error: memory allocation failed!\n");
        exit(1);
    }
    else {
        for (n = 1; n <= 26; n++)
        {
            for (i = 0; i < strlen(s); i++)
            {
                if (s[i] >= 'a' && s[i] <= 'z')
                {
                    s[i] = (s[i] - 'a' + 1) % 26 + 'a';
                }
                else if (s[i] >= 'A' && s[i] <= 'Z')
                {
                    s[i] = (s[i] - 'A' + 1) % 26 + 'A';
                }
            }
            frequency(s, numbers1);
            if(chi_square(numbers, numbers1) < min_dist)
            {
                min_dist = chi_square(numbers, numbers1);
                shift = n;
            }
        }
    }
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = (s[i] - 'a' + shift) % 26 + 'a';
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = (s[i] - 'A' + shift) % 26 + 'A';
        }
    }
    printf("%s\n", s);
}

// create a function that prints the menu
void print_menu()
{
    printf("1. Input a string to be decrypted\n");
    printf("2. Decode a string using the caesar's frequency algorithm\n");
    printf("0. Exit\n");
}

int main()
{
    // double *numbers = (double *)malloc(26 * sizeof(double));
    // char string[] = "Uf ime ftq nqef ar fuyqe, uf ime ftq iadef ar fuyqe, uf ime ftq msq ar iuepay, uf ime ftq msq ar raaxuetzqee, uf ime ftq qbaot ar nqxuqr, uf ime ftq qbaot ar uzodqpgxufk, uf ime ftq eqmeaz ar xustf, uf ime ftq eqmeaz ar pmdwzqee, uf ime ftq ebduzs ar tabq, uf ime ftq iuzfqd ar pqebmud.";
    // if (numbers == NULL)
    // {
    //     printf("Error: memory allocation failed!\n");
    //     exit(1);
    // }
    // else {
    //     read(numbers);
    // }
    // int *numbers1 = (int *)malloc(26 * sizeof(int));
    // if (numbers1 == NULL)
    // {
    //     printf("Error: memory allocation failed!\n");
    //     exit(1);
    // }
    // else {
    //     frequency(string, numbers1);
    // }
    // expected_numbers(numbers, strlen(string));
    // ceasar_shift_decoder(string, numbers);  
    // free(numbers);
    // free(numbers1);
    
    
    
    
    int option;
    char string[100000], c;
    double *numbers = (double *)malloc(26 * sizeof(double));
    int *numbers1 = (int *)malloc(26 * sizeof(int));
    if (numbers == NULL || numbers1 == NULL)
    {
        printf("Error: memory allocation failed!\n");
        exit(1);
    }
    else {
        read(numbers);
        do {
            print_menu();
            printf("Option: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                printf("Input string: \n");
                while ((c = getchar()) == '\n');
                ungetc(c, stdin);
                scanf("%[^\n]%*c", string);
                printf("String inputed! \n\n");
                break;
            case 2:
                frequency(string, numbers1);
                expected_numbers(numbers, strlen(string));
                printf("String decoded: \n");
                ceasar_shift_decoder(string, numbers);
                printf("\n");
                break;
            case 0:
                printf("Bye!\n");
                break;
            default:
                printf("Invalid option!\n");
                break;
            }
        } while (option != 0);
    }
    free(numbers);
    free(numbers1);
    return 0;
}