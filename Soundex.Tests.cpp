#include <gtest/gtest.h>
#include "Soundex.h"

void testSoundex(const char* name, const char* expected) {
    char result[MAX_SOUNDEX_LENGTH + 1];
    generateSoundex(name, result);
    ASSERT_STREQ(result, expected);
}

TEST(SoundexTestsuite, BasicSoundexCode) {
    testSoundex("Example", "E251");
}

TEST(SoundexTestsuite, IgnoresNonAlphabeticCharacters) {
    testSoundex("A1B2C3", "A123");
}

TEST(SoundexTestsuite, HandlesEmptyInput) {
    testSoundex("", "0000");
}

TEST(SoundexTestsuite, HandlesSingleCharacterInput) {
    testSoundex("A", "A000");
    testSoundex("B", "B000");
}

TEST(SoundexTestsuite, HandlesSpecialCharacters) {
    testSoundex("O'Neil", "O543");
    testSoundex("De La Cruz", "D042");
}

TEST(SoundexTestsuite, HandlesConsecutiveIdenticalLetters) {
    testSoundex("MCC", "M020");
}

TEST(SoundexTestsuite, HandlesLongNames) {
    testSoundex("Pneumonoultramicroscopicsilicovolcanoconiosis", "P554");
}
