#include <gtest/gtest.h>
#include <Move.h>
#include <String.h>

TEST(StringTests, canCreateEmptyString) {
    String string;
    EXPECT_EQ(string.isEmpty(), true);
    EXPECT_EQ(string.size(), 0);
}

TEST(StringTests, canCreateValidString) {
    String string("Example");
    EXPECT_EQ(string.size(), 7);
    EXPECT_EQ(string.isEmpty(), false);
}

TEST(StringTests, canAccessCharacters) {
    String string("Example");
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[3], 'm');
    EXPECT_EQ(string[6], 'e');
}

TEST(StringTests, canModifyCharacters) {
    String string("Example");
    string[2] = 'r';
    string[3] = 'n';
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[2], 'r');
    EXPECT_EQ(string[3], 'n');
    EXPECT_EQ(string[6], 'e');
}

TEST(StringTests, canBeConstructedByCopy) {
    String string1("Example String");
    String string2(string1);
    EXPECT_EQ(string1.size(), 14);
    EXPECT_EQ(string2.size(), 14);
    EXPECT_EQ(string1[0], string2[0]);
}

TEST(StringTests, canBeConstructedByTempValue) {
    String string1(String("Example String"));
    EXPECT_EQ(string1.size(), 14);
    EXPECT_EQ(string1[0], 'E');
    EXPECT_EQ(string1[7], ' ');
    EXPECT_EQ(string1[13], 'g');
}

TEST(StringTests, canBeConstructedByMove) {
    String string("Example String");
    String string1(move<String>(string));
    EXPECT_EQ(string1.size(), 14);
    EXPECT_EQ(string1[0], 'E');
    EXPECT_EQ(string1[7], ' ');
    EXPECT_EQ(string1[13], 'g');
}

TEST(StringTests, canBeConstructedByString) {
    String string(String("Example"));
    EXPECT_EQ(string.size(), 7);
    EXPECT_EQ(string.isEmpty(), false);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[3], 'm');
    EXPECT_EQ(string[6], 'e');
}

TEST(StringTests, canBeCopied) {
    String string1("Example 1");
    String string2("Example 2");
    string2 = string1;
    EXPECT_EQ(string2.size(), 9);
    EXPECT_EQ(string2.isEmpty(), false);
    EXPECT_EQ(string2[0], 'E');
    EXPECT_EQ(string2[3], 'm');
    EXPECT_EQ(string2[8], '1');
}

TEST(StringTests, canCastToCString) {
    String string = "Example";
    char *c_string = string;
    EXPECT_EQ(c_string == string, true);
}

TEST(StringTests, canBeComparedWithString) {
    String string1 = "Example";
    String string2 = "Example";
    String string3 = "Exampl";
    EXPECT_EQ(string1 == string2, true);
    EXPECT_EQ(string1 == string3, false);
    EXPECT_EQ(string1 != string2, false);
    EXPECT_EQ(string1 != string3, true);
}

TEST(StringTests, canBeComparedWithCString) {
    String string1 = "Example";
    EXPECT_EQ(string1 == "Example", true);
    EXPECT_EQ(string1 == "Example1", false);
    EXPECT_EQ(string1 != "Example", false);
    EXPECT_EQ(string1 != "Example1", true);
}

TEST(StringTests, canAppendCString) {
    String string;
    string.append("Example 1");
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[5], 'l');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], 0);
    string.append("Example 2");
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[5], 'l');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], 'E');
    EXPECT_EQ(string[14], 'l');
    EXPECT_EQ(string[17], '2');
    EXPECT_EQ(string[18], 0);
    string.append("Example3");
    EXPECT_EQ(string[18], 'E');
    EXPECT_EQ(string[19], 'x');
    EXPECT_EQ(string[25], '3');
    EXPECT_EQ(string[26], 0);
}

TEST(StringTests, canAppendString) {
    String string;
    String example1("Example 1");
    String example3("Example3");
    string.append(example1);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[5], 'l');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], 0);
    string.append(String("Example 2"));
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[5], 'l');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], 'E');
    EXPECT_EQ(string[14], 'l');
    EXPECT_EQ(string[17], '2');
    EXPECT_EQ(string[18], 0);
    string.append(example3);
    EXPECT_EQ(string[18], 'E');
    EXPECT_EQ(string[19], 'x');
    EXPECT_EQ(string[25], '3');
    EXPECT_EQ(string[26], 0);
}

TEST(StringTests, canAppendInt) {
    String string("Example");
    string.append(-1);
    EXPECT_EQ(string.size(), 9);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[4], 'p');
    EXPECT_EQ(string[7], '-');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], '\0');
}

TEST(StringTests, canAppendUnsignedInt) {
    String string("Example");
    unsigned int number = 432;
    string.append(number);
    EXPECT_EQ(string.size(), 10);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[4], 'p');
    EXPECT_EQ(string[7], '4');
    EXPECT_EQ(string[8], '3');
    EXPECT_EQ(string[9], '2');
    EXPECT_EQ(string[10], '\0');
}

TEST(StringTests, canAppendAddress) {
    String string;
    void *address = (void *) 0xff34;
    string.append(address);
    EXPECT_EQ(string.size(), 6);
    EXPECT_EQ(string[0], '0');
    EXPECT_EQ(string[1], 'x');
    EXPECT_EQ(string[2], 'f');
    EXPECT_EQ(string[5], '4');
}

TEST(StringTests, canFormatCStrings) {
    String string;
    string << "Example" << " 1";
    EXPECT_EQ(string.size(), 9);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[3], 'm');
    EXPECT_EQ(string[6], 'e');
    EXPECT_EQ(string[8], '1');
    EXPECT_EQ(string[9], '\0');
}

TEST(StringTests, canFormatStrings) {
    String string;
    String example1("Example 1"), example2("Example 2");
    string << example1 << example2;
    EXPECT_EQ(string.size(), 18);
    EXPECT_EQ(string[0], 'E');
    EXPECT_EQ(string[3], 'm');
    EXPECT_EQ(string[6], 'e');
    EXPECT_EQ(string[17], '2');
    EXPECT_EQ(string[18], '\0');
}
