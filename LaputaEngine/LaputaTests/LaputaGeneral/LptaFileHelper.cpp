#include <gtest/gtest.h>
#include <sys/stat.h>
#include "LaputaGeneral/include/LptaFileHelper.h"
using namespace lpta::helper;

const std::string DEFAULT_TEST_FILE = "./LptaFileHelperTest.txt";

void RemoveFile(const std::string &filename=DEFAULT_TEST_FILE)
{
    remove(filename.c_str());
}

class LptaFileHelperTest : public ::testing::Test
{
protected:
    virtual void SetUp(void)
    {
        RemoveFile();
    }
    virtual void TearDown(void)
    {
        RemoveFile();
    }       
};


TEST_F(LptaFileHelperTest, FileWrite)
{
    const std::string testContent = "hello world!";
    FileWrite(DEFAULT_TEST_FILE, testContent);
    struct stat statResult;
    ASSERT_EQ(0, stat(DEFAULT_TEST_FILE.c_str(), &statResult));
    std::string readBack = FileRead(DEFAULT_TEST_FILE);
    ASSERT_EQ(testContent, readBack);
}

TEST_F(LptaFileHelperTest, FileWrite_Overwrite)
{
    const std::string oldContent = "old stuff";
    const std::string newContent = "new stuff";
    FileWrite(DEFAULT_TEST_FILE, oldContent);
    WRITE_RESULT result  = FileWrite(DEFAULT_TEST_FILE, newContent, true);
    std::string readBack = FileRead(DEFAULT_TEST_FILE);
    ASSERT_EQ(WRITE_RESULT::SUCCESS, result);
    ASSERT_EQ(newContent, readBack);
}

TEST_F(LptaFileHelperTest, FileWrite_NoOverwrite)
{
    const std::string oldContent = "old stuff";
    const std::string newContent = "new stuff";
    FileWrite(DEFAULT_TEST_FILE, oldContent);
    WRITE_RESULT result = FileWrite(DEFAULT_TEST_FILE, oldContent, false);
    std::string readBack = FileRead(DEFAULT_TEST_FILE);
    ASSERT_EQ(WRITE_RESULT::FAILURE, result);
    ASSERT_EQ(oldContent, readBack);
}


TEST_F(LptaFileHelperTest, FileRead_Missing)
{
    std::string content = FileRead(DEFAULT_TEST_FILE);
    ASSERT_EQ(0, content.length());
    ASSERT_EQ("", content);
}


TEST_F(LptaFileHelperTest, FileExists)
{
    FileWrite(DEFAULT_TEST_FILE, "");
    ASSERT_TRUE(FileExists(DEFAULT_TEST_FILE));
}

TEST_F(LptaFileHelperTest, FileExists_Missing)
{
    ASSERT_FALSE(FileExists(DEFAULT_TEST_FILE));
}