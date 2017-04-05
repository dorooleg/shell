#include <gtest/gtest.h>
#include <array>
#include <memory>
#include <string>
#include <unistd.h> 
#include "../src/Preprocessor.h"
#include "../src/Environment.h"
 
TEST(EnvironmentTest, SimpleTest)
{
    Environment env;
    assert(env.get_value("HA") == "");
    env.set_value("HA", "VA");
    ASSERT_EQ("VA", env.get_value("HA"));
}
 
TEST(Preprocessor, SubstituteTest)
{
    Environment env;
    env.set_value("ABA", "VA");
    Preprocessor preprocessor;
    std::string str("echo $ABA $ $V vas");
    preprocessor.substitute_variables(env, str);
    ASSERT_EQ("echo VA   vas", str);
}

TEST(Preprocessor, UpdateEvironment)
{
    Environment env;
    Preprocessor preprocessor;
    std::string str("ABA=V");
    preprocessor.update_environment(env, str);
    ASSERT_EQ("V", env.get_value("ABA"));
}

static std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }

    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
        {
            result += buffer.data();
        }
    }
    return result;
}

static std::string getexepath()
{
    #define PATH_MAX 10000
    char result[ PATH_MAX ];
    readlink( "/proc/self/exe", result, PATH_MAX );
    auto found = std::string(result).find_last_of("/");
    return std::string(result).substr(0,found) + "/";
    #undef PATH_MAX
}

static std::string grep(const std::string& args, const std::string& test_file)
{
    return exec((getexepath() + "grep " + args + " " +  getexepath() + "../tests/" + test_file).c_str());
}


TEST(Grep, SimpleTest)
{
   ASSERT_EQ("abra\n", grep("ab", "test"));
   ASSERT_EQ("bara\n", grep("bar", "test"));
   ASSERT_EQ("", grep("\"^a$\"", "test"));
}

TEST(Grep, KeyI)
{
   ASSERT_EQ("abra\n", grep("-i ab", "test_i"));
   ASSERT_EQ("bara\n", grep("-i bar", "test_i"));
   ASSERT_EQ("", grep("-i \"^a$\"", "test_i"));
}

TEST(Grep, KeyW)
{
   ASSERT_EQ("abra to\n", grep("-w abra", "test_w"));
   ASSERT_EQ("", grep("-w fal", "test_w"));
}

TEST(Grep, KeyA)
{
   ASSERT_EQ("abra\nkada\nbara\n", grep("-A 3 ab", "test"));
   ASSERT_EQ("bara\n", grep("-A 3 bar", "test"));
}
 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
