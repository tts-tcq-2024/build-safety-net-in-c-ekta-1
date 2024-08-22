#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

#define MAX_SOUNDEX_LENGTH 4

// Helper function to get the soundex code for a letter
char getSoundexCode(char c) {
    static const char chartable[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2',
        '2', '4', '5', '5', '0', '1', '2', '6', '2', '3',
        '0', '1', '0', '2', '0', '2'
    };
    return isalpha(c) ? chartable[c - 'A'] : '0';
}

// Append soundex code to the result
void appendSoundex(char code, char prevcode, char *soundex, int *sIndex) {
    if (code != '0' && code != prevcode) {
        soundex[*sIndex] = code;
        (*sIndex)++;
    }
}

// Process the input name to fill the soundex array
void processName(const char *name, int len, char *soundex, int *sIndex) {
    char prevcode = getSoundexCode(name[0]);
    soundex[0] = toupper(name[0]);
    for (int i = 1; i < len && *sIndex < MAX_SOUNDEX_LENGTH; i++) {
        char code = getSoundexCode(name[i]);
        if (isalpha(name[i])) {
            appendSoundex(code, prevcode, soundex, sIndex);
            prevcode = code;
        }
    }
}

// Finalize the soundex code by padding with zeros
void finalizeSoundex(char *soundex) {
    int length = strlen(soundex);
    while (length < MAX_SOUNDEX_LENGTH) {
        soundex[length++] = '0';
    }
    soundex[MAX_SOUNDEX_LENGTH] = '\0';
}

// Generate the soundex code from the input name
void generateSoundex(const char *name, char *soundex) {
    int len = strlen(name);
    soundex[0] = '\0'; // Initialize the soundex array
    int sIndex = 1; // Start index for soundex array
    processName(name, len, soundex, &sIndex);
    finalizeSoundex(soundex);
}

#endif // SOUNDEX_H
