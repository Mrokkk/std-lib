#include <path.h>
#include "yatf/include/yatf.h"

using namespace yacppl;

TEST(path_tests, empty_path_is_empty_string) {
    path p;
    REQUIRE(p == "");
    REQUIRE_EQ(p.get(), "");
}

TEST(path_tests, path_constructed_from_string_is_valid) {
    path p("/root/dir");
    REQUIRE(p == "/root/dir");
    path p2("some_dir/another_dir");
    REQUIRE(p2 == "some_dir/another_dir");
}

TEST(path_tests, paths_can_be_appended) {
    path p1("home");
    path p2("user");
    path p3(p1 / p2);
    REQUIRE(p3 == "home/user");
    p3 /= "dir";
    REQUIRE(p3 == "home/user/dir");
    p3 /= "next_dir";
    REQUIRE(p3 == "home/user/dir/next_dir");
    path p4 = p3 / "test";
    REQUIRE(p3 == "home/user/dir/next_dir");
    REQUIRE(p4 == "home/user/dir/next_dir/test");
}

TEST(path_tests, paths_are_normalized) {
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

TEST(path_tests, can_get_basename) {
    path p("/root/dir1/dir2//dir3/");
    REQUIRE_EQ(p.basename(), "dir3");
    path p2("some_dir");
    REQUIRE_EQ(p2.basename(), "some_dir");
}

