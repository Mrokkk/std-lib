//
// Created by maciek on 14.06.16.
//

#include <boost/test/unit_test.hpp>
#include <Move.h>
#include <String.h>

BOOST_AUTO_TEST_SUITE(StringTests)

    BOOST_AUTO_TEST_CASE(canCreateEmptyString)
    {
        String string;
        BOOST_CHECK_EQUAL(string.isEmpty(), true);
        BOOST_CHECK_EQUAL(string.size(), 0);
    }

    BOOST_AUTO_TEST_CASE(canCreateValidString)
    {
        String string("Example");
        BOOST_CHECK_EQUAL(string.size(), 7);
        BOOST_CHECK_EQUAL(string.isEmpty(), false);
    }

    BOOST_AUTO_TEST_CASE(canAccessCharacters)
    {
        String string("Example");
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[3], 'm');
        BOOST_CHECK_EQUAL(string[6], 'e');
    }

    BOOST_AUTO_TEST_CASE(canModifyCharacters)
    {
        String string("Example");
        string[2] = 'r';
        string[3] = 'n';
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[2], 'r');
        BOOST_CHECK_EQUAL(string[3], 'n');
        BOOST_CHECK_EQUAL(string[6], 'e');
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByCopy)
    {
        String string1("Example String");
        String string2(string1);
        BOOST_CHECK_EQUAL(string1.size(), 14);
        BOOST_CHECK_EQUAL(string2.size(), 14);
        BOOST_CHECK_EQUAL(string1[0], string2[0]);
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByTempValue)
    {
        String string1(String("Example String"));
        BOOST_CHECK_EQUAL(string1.size(), 14);
        BOOST_CHECK_EQUAL(string1[0], 'E');
        BOOST_CHECK_EQUAL(string1[7], ' ');
        BOOST_CHECK_EQUAL(string1[13], 'g');
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByMove)
    {
        String string("Example String");
        String string1(move<String>(string));
        BOOST_CHECK_EQUAL(string1.size(), 14);
        BOOST_CHECK_EQUAL(string1[0], 'E');
        BOOST_CHECK_EQUAL(string1[7], ' ');
        BOOST_CHECK_EQUAL(string1[13], 'g');
    }

    BOOST_AUTO_TEST_CASE(canBeConstructedByString)
    {
        String string(String("Example"));
        BOOST_CHECK_EQUAL(string.size(), 7);
        BOOST_CHECK_EQUAL(string.isEmpty(), false);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[3], 'm');
        BOOST_CHECK_EQUAL(string[6], 'e');
    }

    BOOST_AUTO_TEST_CASE(canBeCopied)
    {
        String string1("Example 1");
        String string2("Example 2");
        string2 = string1;
        BOOST_CHECK_EQUAL(string2.size(), 9);
        BOOST_CHECK_EQUAL(string2.isEmpty(), false);
        BOOST_CHECK_EQUAL(string2[0], 'E');
        BOOST_CHECK_EQUAL(string2[3], 'm');
        BOOST_CHECK_EQUAL(string2[8], '1');
    }

    BOOST_AUTO_TEST_CASE(canCastToCString)
    {
        String string = "Example";
        char *c_string = string;
        BOOST_CHECK_EQUAL(c_string == string, true);
    }

    BOOST_AUTO_TEST_CASE(canBeComparedWithString)
    {
        String string1 = "Example";
        String string2 = "Example";
        String string3 = "Exampl";
        BOOST_CHECK_EQUAL(string1 == string2, true);
        BOOST_CHECK_EQUAL(string1 == string3, false);
        BOOST_CHECK_EQUAL(string1 != string2, false);
        BOOST_CHECK_EQUAL(string1 != string3, true);
    }

    BOOST_AUTO_TEST_CASE(canBeComparedWithCString)
    {
        String string1 = "Example";
        BOOST_CHECK_EQUAL(string1 == "Example", true);
        BOOST_CHECK_EQUAL(string1 == "Example1", false);
        BOOST_CHECK_EQUAL(string1 != "Example", false);
        BOOST_CHECK_EQUAL(string1 != "Example1", true);
    }

    BOOST_AUTO_TEST_CASE(canAppendCString)
    {
        String string;
        string.append("Example 1");
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[5], 'l');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], 0);
        string.append("Example 2");
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[5], 'l');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], 'E');
        BOOST_CHECK_EQUAL(string[14], 'l');
        BOOST_CHECK_EQUAL(string[17], '2');
        BOOST_CHECK_EQUAL(string[18], 0);
        string.append("Example3");
        BOOST_CHECK_EQUAL(string[18], 'E');
        BOOST_CHECK_EQUAL(string[19], 'x');
        BOOST_CHECK_EQUAL(string[25], '3');
        BOOST_CHECK_EQUAL(string[26], 0);
    }

    BOOST_AUTO_TEST_CASE(canAppendString)
    {
        String string;
        String example1("Example 1");
        String example3("Example3");
        string.append(example1);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[5], 'l');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], 0);
        string.append(String("Example 2"));
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[5], 'l');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], 'E');
        BOOST_CHECK_EQUAL(string[14], 'l');
        BOOST_CHECK_EQUAL(string[17], '2');
        BOOST_CHECK_EQUAL(string[18], 0);
        string.append(example3);
        BOOST_CHECK_EQUAL(string[18], 'E');
        BOOST_CHECK_EQUAL(string[19], 'x');
        BOOST_CHECK_EQUAL(string[25], '3');
        BOOST_CHECK_EQUAL(string[26], 0);
    }

    BOOST_AUTO_TEST_CASE(canAppendInt)
    {
        String string("Example");
        string.append(-1);
        BOOST_CHECK_EQUAL(string.size(), 9);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[4], 'p');
        BOOST_CHECK_EQUAL(string[7], '-');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], '\0');
    }

    BOOST_AUTO_TEST_CASE(canAppendUnsignedInt)
    {
        String string("Example");
        unsigned int number = 432;
        string.append(number);
        BOOST_CHECK_EQUAL(string.size(), 10);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[4], 'p');
        BOOST_CHECK_EQUAL(string[7], '4');
        BOOST_CHECK_EQUAL(string[8], '3');
        BOOST_CHECK_EQUAL(string[9], '2');
        BOOST_CHECK_EQUAL(string[10], '\0');
    }

    BOOST_AUTO_TEST_CASE(canAppendAddress)
    {
        String string;
        void *address = (void *) 0xff34;
        string.append(address);
        BOOST_CHECK_EQUAL(string.size(), 6);
        BOOST_CHECK_EQUAL(string[0], '0');
        BOOST_CHECK_EQUAL(string[1], 'x');
        BOOST_CHECK_EQUAL(string[2], 'f');
        BOOST_CHECK_EQUAL(string[5], '4');
    }

    BOOST_AUTO_TEST_CASE(canFormatCStrings)
    {
        String string;
        string << "Example" <<  " 1";
        BOOST_CHECK_EQUAL(string.size(), 9);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[3], 'm');
        BOOST_CHECK_EQUAL(string[6], 'e');
        BOOST_CHECK_EQUAL(string[8], '1');
        BOOST_CHECK_EQUAL(string[9], '\0');
    }

    BOOST_AUTO_TEST_CASE(canFormatStrings)
    {
        String string;
        String example1("Example 1"), example2("Example 2");
        string << example1 << example2;
        BOOST_CHECK_EQUAL(string.size(), 18);
        BOOST_CHECK_EQUAL(string[0], 'E');
        BOOST_CHECK_EQUAL(string[3], 'm');
        BOOST_CHECK_EQUAL(string[6], 'e');
        BOOST_CHECK_EQUAL(string[17], '2');
        BOOST_CHECK_EQUAL(string[18], '\0');
    }

BOOST_AUTO_TEST_SUITE_END()