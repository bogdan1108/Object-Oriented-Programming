#include <stdio.h>
#include <stdlib.h>

// Alice forgot her card�s PIN code.She remembers that her PIN code had 4 digits, all the digits were distinctand in decreasing order, and that the sum of these digits was 24. 
// This C program that prints, on different lines, all the PIN codes which fulfill these constraints. 

int main(int argc, char* argv[]) {
	int sum = 0;

	for (int i = 9; i >= 7; i--) {
		for (int j = i; j >= 0; j--) {
			for (int k = j; k >= 0; k--) {
				for (int l = k; l >= 0; l--) {
					if (i != j && i != k && i != l && j != k && j != l && k != l) {
						sum = i + j + k + l;
						if (sum == 24) {
							printf("%d%d%d%d\n", i, j, k, l);
						}
					}
				}
			}
		}
	}

	return 0;
}

