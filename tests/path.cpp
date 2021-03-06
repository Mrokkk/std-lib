#include <path.hpp>
#include "yatf/include/yatf.hpp"

using namespace yacppl;

TEST(path, empty_path_is_empty_string) {
    path p;
    REQUIRE(p == "");
}

TEST(path, can_be_constructed_from_char_ptr) {
    path p1(nullptr);
    REQUIRE_FALSE(p1);
    const char *str = "/some_path/dir/file";
    path p2(str);
    REQUIRE_EQ((const char *)p2, "/some_path/dir/file");
    path p4("/");
    REQUIRE_EQ((const char *)p4, "/");
    path p5("/root/aaa/bbb/ccc");
    REQUIRE_EQ((const char *)p5, "/root/aaa/bbb/ccc");
}

TEST(path, can_be_constructed_from_other_path_by_copy) {
    path p1(nullptr);
    path p2("/root/dir/aaa/bbb");
    path p3(p1);
    REQUIRE(p1.get() == nullptr);
    REQUIRE(p3.get() == nullptr);
    path p4(p2);
    REQUIRE(p2.get() != nullptr);
    REQUIRE(p4.get() != nullptr);
    REQUIRE_EQ((const char *)p4, "/root/dir/aaa/bbb");
}

TEST(path, can_be_constructed_from_other_path_by_move) {
    path p1(nullptr);
    path p2("/root/dir/aaa/bbb");
    path p3(move(p1));
    REQUIRE(p1.get() == nullptr);
    REQUIRE(p3.get() == nullptr);
    path p4(move(p2));
    REQUIRE(p2.get() == nullptr);
    REQUIRE(p4.get() != nullptr);
    REQUIRE_EQ((const char *)p4, "/root/dir/aaa/bbb");
}

TEST(path, can_be_assigned_to_other_path) {
    path p1("/some_path");
    path p2(nullptr);
    path p3;
    p3 = p1;
    REQUIRE_EQ((const char *)p3, "/some_path");
    p3 = p2;
    REQUIRE_FALSE(p3);
    p3 = p1;
    REQUIRE_EQ((const char *)p1, "/some_path");
    // FIXME: REQUIRE(p2 == nullptr);
    REQUIRE_EQ((const char *)p3, "/some_path");
}

TEST(path, paths_can_be_appended) {
    path p1("home");
    path p2("user");
    path p3(p1 / p2);
    REQUIRE_EQ((const char *)p3, "home/user");
    p3 /= "dir";
    REQUIRE(p3 == "home/user/dir");
    p3 /= "next_dir";
    REQUIRE(p3 == "home/user/dir/next_dir");
    path p4 = p3 / "test";
    REQUIRE(p3 == "home/user/dir/next_dir");
    REQUIRE(p4 == "home/user/dir/next_dir/test");
}

TEST(path, paths_are_normalized) {
    path p;
    p = p / "root" / "////test//" / "/dir////";
    REQUIRE_EQ((const char *)p, "/root/test/dir");
    auto p2 = p / path("dir2");
    REQUIRE_EQ((const char *)p2, "/root/test/dir/dir2");
    p2 /= "//dir3////dir4/";
    REQUIRE_EQ((const char *)p2, "/root/test/dir/dir2/dir3/dir4");
    path p3("/////dir/////////");
    REQUIRE_EQ((const char *)p3, "/dir");
}

TEST(path, can_get_basename) {
    path p("/root/dir1/dir2//dir3/");
    REQUIRE_EQ((const char *)p.basename(), "dir3");
    path p2("some_dir");
    REQUIRE_EQ((const char *)p2.basename(), "some_dir");
    path p3("/");
    REQUIRE_EQ((const char *)p3.basename(), "");
    path p5("/path");
    REQUIRE_EQ((const char *)p5.basename(), "path");
}

TEST(path, can_get_dirname) {
    path p("/");
    REQUIRE_EQ((const char *)p.dirname(), "/");
    path p2("/root/dir1/dir2//dir3/");
    REQUIRE_EQ((const char *)p2.dirname(), "/root/dir1/dir2");
    path p3("root/dir1/dir2//dir3/");
    REQUIRE_EQ((const char *)p3.dirname(), "root/dir1/dir2");
    path p4("path");
    REQUIRE_EQ((const char *)p4.dirname(), "");
    path p5("/path");
    REQUIRE_EQ((const char *)p5.dirname(), "/");
}

TEST(path, can_be_iterated) {
    {
        path p("/root/dir");
        auto it = p.cbegin();
        REQUIRE_EQ((const char *)*it, "/");
        REQUIRE_EQ((*it).length(), 1u);
        ++it;
        REQUIRE_EQ((const char *)*it, "root");
        ++it;
        REQUIRE_EQ((const char *)*it, "dir");
        ++it;
        REQUIRE(it == p.cend());
    }
    {
        path p("root/dir");
        auto it = p.begin();
        REQUIRE_EQ((const char *)*it, "root");
        it++;
        REQUIRE_EQ((const char *)*it, "dir");
        it++;
        REQUIRE(it == p.end());
    }
    {
        path p("/dir1/dir2/dir3/dir4/other_dir");
        string paths[6] = {
            "/",
            "dir1",
            "dir2",
            "dir3",
            "dir4",
            "other_dir"
        };
        auto i = 0u;
        for (const auto &it : p) {
            REQUIRE_EQ((const char *)it, (const char *)paths[i]);
            ++i;
        }
    }
    {
        path p("/dir1/dir2/dir3/dir4/other_dir");
        auto it = p.begin();
        REQUIRE_EQ((const char *)*(it + 1), "dir1");
        REQUIRE_EQ((const char *)*(it + 2), "dir2");
        REQUIRE_EQ((const char *)*(it + 3), "dir3");
        REQUIRE_EQ((const char *)*(it + 4), "dir4");
        REQUIRE_EQ((const char *)*(it + 5), "other_dir");
        REQUIRE((it + 6) == p.end());
        REQUIRE((it + 7) == p.end());
        REQUIRE((it + 1024) == p.end());
    }
}

