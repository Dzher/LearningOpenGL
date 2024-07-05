#ifndef __PATH_HELPER__
#define __PATH_HELPER__

#include <string>
#include <string_view>

namespace utils
{
class PathHelper
{
public:
    static std::string getRootPath(bool by_marco = true);
    static std::string getImagePath(const std::string& file_name);
    static std::string getShaderPath(const std::string& file_name);

private:
    constexpr static std::string_view kImagePath = "/share/images/";
    constexpr static std::string_view kShaderPath = "/share/shaders/";
};
}  // namespace utils

#endif