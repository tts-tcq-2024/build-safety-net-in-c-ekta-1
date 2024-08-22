#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <ctype.h>
#include <string.h>

#define MAX_SOUNDEX_LENGTH 4

char getSoundexCode(char c) {
    c = toupper(c);
    static const char chartable[] = {
        '0', '1', '2', '3', '0', '1', '2', '0', '0', '2',
        '2', '4', '5', '5', '0', '1', '2', '6', '2', '3',
        '0', '1', '0', '2', '0', '2'
    };
    if (isalpha(c)) {
        return chartable[c - 'A'];
    }
    return '0';
}

void appendSoundex(char code, char prevcode, char *soundex, int *sIndex) {
    if (code != '0' && code != prevcode) {
        soundex[*sIndex] = code;
        (*sIndex)++;
    }
}

void updateSoundexArray(const char *name, int len, char *soundex) {
    int sIndex = 1;
    char prevcode = getSoundexCode(name[0]);
    soundex[0] = toupper(name[0]);

    for (int i = 1; i < len && sIndex < MAX_SOUNDEX_LENGTH; i++) {
        char code = getSoundexCode(name[i]);
        appendSoundex(code, prevcode, soundex, &sIndex);
        prevcode = code;
    }
    soundex[sIndex] = '\0';
}

void finalizeSoundex(char *soundex) {
    int length = strlen(soundex);
    while (length < MAX_SOUNDEX_LENGTH) {
        soundex[length++] = '0';
    }
    soundex[MAX_SOUNDEX_LENGTH] = '\0';
}

void generateSoundex(const char *name, char *soundex) {
    int len = strlen(name);
    soundex[0] = '\0';
    updateSoundexArray(name, len, soundex);
    finalizeSoundex(soundex);
}

#endif // SOUNDEX_H
