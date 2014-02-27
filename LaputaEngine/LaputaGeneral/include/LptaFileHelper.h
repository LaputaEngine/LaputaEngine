#ifndef _LPTAFILEHELPER_H_
#define _LPTAFILEHELPER_H_

#include <string>

namespace lpta
{
namespace helper
{

typedef enum WRITE_RESULT_TYPE
{
    SUCCESS,
    FAILURE,
} WRITE_RESULT;

// note, avoid using these for large files, mainly suitable for small file reads
// such as pixel shader programs
std::string FileRead(const std::string &filename);
WRITE_RESULT FileWrite(const std::string &filename, 
    const std::string &content, bool overwrite=false);

bool FileExists(const std::string &filename);

}
}

#endif