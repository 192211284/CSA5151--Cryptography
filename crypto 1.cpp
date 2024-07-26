#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void countFrequency(const char *text, int *frequency) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        }
    }
}

void getTopLetters(int *frequency, char *topLetters, int topN) {
    int sortedFreq[26];
    for (int i = 0; i < 26; i++) {
        sortedFreq[i] = frequency[i];
    }
    for (int i = 0; i < topN; i++) {
        int maxIndex = -1;
        for (int j = 0; j < 26; j++) {
            if (maxIndex == -1 || sortedFreq[j] > sortedFreq[maxIndex]) {
                maxIndex = j;
            }
        }
        topLetters[i] = 'a' + maxIndex;
        sortedFreq[maxIndex] = -1;  // Mark as used
    }
}

void decrypt(const char *ciphertext, char *plaintext, int key) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[1024];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, 1024, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    int frequency[26] = {0};
    countFrequency(ciphertext, frequency);

    int topN;
    printf("Enter the number of top possible plaintexts: ");
    scanf("%d", &topN);

    char topLetters[26];
    getTopLetters(frequency, topLetters, topN);

    printf("Possible plaintexts:\n");
    for (int i = 0; i < topN; i++) {
        char plaintext[1024];
        int key = (topLetters[i] - 'e' + 26) % 26;
        decrypt(ciphertext, plaintext, key);
        printf("%d: %s\n", i + 1, plaintext);
    }

    return 0;
}

