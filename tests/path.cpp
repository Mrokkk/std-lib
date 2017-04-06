#include <path.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(path_tests, empty_path_is_empty_string) {
    path p;
    REQUIRE(p == "");
}

TEST(path_tests, path_constructed_from_string_is_valid) {
    path p("/root/dir");
    REQUIRE(p == "/root/dir");
}

TEST(path_tests, can_be_appended) {
    path p;
    p = p / "root" / "////test//" / "/dir////";
    //REQUIRE_EQ(p.operator const char *(), "/root/test/dir");
    REQUIRE(p == "/root/test/dir");
    auto p2 = p / path("dir2");
    REQUIRE(p2 == "/root/test/dir/dir2");
}

