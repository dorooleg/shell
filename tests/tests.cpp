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
    ASSERT_EQ(env.get_value("HA"), "");
    env.set_value("HA", "VA");
    ASSERT_EQ("VA", env.get_value("HA"));
}
 
TEST(Preprocessor, SubstituteTest)
{
    Environment env;
    env.set_value("ABA", "VA");
    std::string str("echo $ABA $ $V vas");
    Preprocessor::substitute_variables(env, str);
    ASSERT_EQ("echo VA   vas", str);
}

TEST(Preprocessor, SusbstituteNumbers)
{
    Environment env;
    std::string line("x=skmfds");
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("x=skmfds", line);

    line = "echo $x";
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("echo skmfds", line);

    line = "x=12";
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("x=12", line);

    line = "echo $x";
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("echo 12", line);
}

TEST(Preprocessor, SusbstituteSingleQuotes)
{
    Environment env;
    std::string line("x=\'skmfds\'");
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("x=\'skmfds\'", line);
    ASSERT_EQ(env.get_value("x"), "skmfds");
}

TEST(Preprocessor, SusbstituteDoubleQuotes)
{
    Environment env;
    std::string line("x=\"skmfds\"");
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("x=\"skmfds\"", line);
    ASSERT_EQ(env.get_value("x"), "skmfds");
}

TEST(Preprocessor, SusbstituteNameWithNumbers)
{
    Environment env;
    std::string line("x12=skmfds");
    Preprocessor::update_environment(env, line);
    ASSERT_EQ(env.get_value("x12"), "skmfds");
}

TEST(Preprocessor, SubstituteSingleQuotes)
{
    Environment env;
    std::string line("x=a");
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("x=a", line);

    line = "echo '123$x'";
    Preprocessor::update_environment(env, line);
    Preprocessor::substitute_variables(env, line);
    ASSERT_EQ("echo '123$x'", line);
}

TEST(Preprocessor, UpdateEvironment)
{
    Environment env;
    std::string str("ABA=V");
    Preprocessor::update_environment(env, str);
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
    static bool flag = false;
    static std::string path;
    if (!flag)
    {
        #define PATH_MAX 10000
        char result[ PATH_MAX ];
        readlink( "/proc/self/exe", result, PATH_MAX );
        auto found = std::string(result).find_last_of("/");
        path = std::string(result).substr(0,found) + "/";
        flag = true;
        #undef PATH_MAX
    }
    return path;
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

static std::string echo(const std::string& args)
{
    return exec((getexepath() + "echo " + args).c_str());
}

TEST(Echo, Empty)
{
   ASSERT_EQ("\n", echo(""));
}

TEST(Echo, Single)
{
   ASSERT_EQ("ssd \n", echo("ssd"));
}

TEST(Echo, Double)
{
   ASSERT_EQ("ssd validate \n", echo("ssd validate"));
}

static std::string pwd(const std::string& args)
{
    return exec((getexepath() + "pwd " + args).c_str());
}

TEST(Pwd, Simple)
{
    std::string path = getexepath(); 
    if (!path.empty())
    {
        path.pop_back();
    }
    std::string result_pwd = pwd("");
    if (!result_pwd.empty())
    {
        result_pwd.pop_back();
        result_pwd += "/bin";
    }
    ASSERT_EQ(path, result_pwd);
}

static std::string cat(const std::string& args)
{
    return exec((getexepath() + "cat " + args).c_str());
}

TEST(Cat, Signle)
{
   ASSERT_EQ("abra\nkada\nbara\n", cat(getexepath() + "../tests/test"));
}

TEST(Cat, Double)
{
   ASSERT_EQ("abra\nkada\nbara\nABRA\nKaDa\nBaRa\n", cat(getexepath() + "../tests/test " + getexepath() + "../tests/test_i"));
}

static std::string wc(const std::string& args)
{
    return exec((getexepath() + "wc " + args).c_str());
}

TEST(Wc, Simple)
{
   ASSERT_EQ("3 3 15 /home/oleg/shell/bin/../tests/test\n3 3 15 /home/oleg/shell/bin/../tests/test_i\n", wc(getexepath() + "../tests/test " + getexepath() + "../tests/test_i"));
}


 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
