#include <gtest/gtest.h>
#include "Soundex.h"

// Helper function to compare Soundex results
void testSoundex(const char* name, const char* expected) {
    char result[MAX_SOUNDEX_LENGTH + 1];
    generateSoundex(name, result);
    ASSERT_STREQ(result, expected);
}

// Test for a basic Soundex code
TEST(SoundexTestsuite, BasicSoundexCode) {
    testSoundex("Example", "E251");
}

// Test for handling and ignoring non-alphabetic characters
TEST(SoundexTestsuite, IgnoresNonAlphabeticCharacters) {
    testSoundex("A1B2C3", "A123");
}

// Test for an empty input
TEST(SoundexTestsuite, HandlesEmptyInput) {
    testSoundex("", "0000");
}

// Test for single character input
TEST(SoundexTestsuite, HandlesSingleCharacterInput) {
    testSoundex("A", "A000");
    testSoundex("B", "B000");
}

// Test for handling input with different delimiters and special characters
TEST(SoundexTestsuite, HandlesSpecialCharacters) {
    testSoundex("O'Neil", "O543");
    testSoundex("De La Cruz", "D042");
}

// Test for names with multiple identical consecutive letters
TEST(SoundexTestsuite, HandlesConsecutiveIdenticalLetters) {
    testSoundex("MCC", "M020");
}

// Test for long names
TEST(SoundexTestsuite, HandlesLongNames) {
    testSoundex("Pneumonoultramicroscopicsilicovolcanoconiosis", "P554");
}
