#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

#define MAX_SOUNDEX_LENGTH 4

// Function to get Soundex code for a given character
char getSoundexCode(char c) {
    c = toupper(c);
    static const char chartable[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2',
        '2', '4', '5', '5', '0', '1', '2', '6', '2', '3',
        '0', '1', '0', '2', '0', '2'
    };
    return isalpha(c) ? chartable[c - 'A'] : '0';
}

// Function to update Soundex array based on name and its length
void updateSoundexArray(const char *name, int len, char *soundex) {
    int sIndex = 1;
    char prevcode = getSoundexCode(name[0]);
    soundex[0] = toupper(name[0]);

    for (int i = 1; i < len && sIndex < MAX_SOUNDEX_LENGTH; i++) {
        char code = getSoundexCode(name[i]);
        if (code != '0' && code != prevcode) {
            soundex[sIndex++] = code;
            prevcode = code;
        }
    }
    soundex[sIndex] = '\0';
}

// Function to finalize Soundex code to ensure it has exactly 4 characters
void finalizeSoundex(char *soundex) {
    int len = strlen(soundex);
    while (len < MAX_SOUNDEX_LENGTH) {
        soundex[len++] = '0';
    }
    soundex[MAX_SOUNDEX_LENGTH] = '\0';
}

// Main function to generate Soundex code
void generateSoundex(const char *name, char *soundex) {
    if (name == NULL || *name == '\0') {
        strcpy(soundex, "0000");
        return;
    }
    int len = strlen(name);
    soundex[0] = '\0';
    updateSoundexArray(name, len, soundex);
    finalizeSoundex(soundex);
}

#endif // SOUNDEX_H
