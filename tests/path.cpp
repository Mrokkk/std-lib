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

TEST(path_tests, paths_can_be_appended) {
    path p1("home");
    path p2("user");
    path p3(p1 / p2);
    REQUIRE(p3 == "home/user");
    p3 /= "dir";
    REQUIRE(p3 == "home/user/dir");
}

TEST(path_tests, removes_trailing_slash_when_appending) {
    path p;
    p = p / "root" / "////test//" / "/dir////";
    REQUIRE(p == "/root/test/dir");
    auto p2 = p / path("dir2");
    REQUIRE(p2 == "/root/test/dir/dir2");
    p2 /= "//dir3////dir4/";
    REQUIRE(p2 == "/root/test/dir/dir2/dir3/dir4");
    path p3("/////dir/////////");
    REQUIRE(p3 == "/dir");
}

