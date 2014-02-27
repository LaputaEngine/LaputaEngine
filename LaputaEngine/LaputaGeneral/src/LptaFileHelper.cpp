#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include "LptaFileHelper.h"

#define STAT_FILE_FAILURE -1

namespace lpta
{
namespace helper
{

// solution based on answer from SO
std::string FileRead(const std::string &filename)
{
    std::string content = "";
    std::ifstream ifs(filename, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    if (ifs) {
        unsigned int fileSize = static_cast<unsigned int>(ifs.tellg());
        ifs.seekg(0, std::ifstream::beg);
        char *buffer = new char[fileSize];
        ifs.read(buffer, fileSize);
        ifs.close();
        content = std::string(buffer, fileSize);
        delete[] buffer;
    }
    else {
        // log error
    }
    return content;
}

WRITE_RESULT FileWrite(const std::string &filename, 
    const std::string &content, bool overwrite)
{
    if (!overwrite && FileExists(filename)) {
        // log error
        return WRITE_RESULT::FAILURE;
    }
    std::ofstream ofs(filename, std::ifstream::out);

    ofs << content;
    ofs.close();
    return WRITE_RESULT::SUCCESS;
}

bool FileExists(const std::string &filename)
{
    struct stat result;
    return stat(filename.c_str(), &result) != STAT_FILE_FAILURE;
}

}
}