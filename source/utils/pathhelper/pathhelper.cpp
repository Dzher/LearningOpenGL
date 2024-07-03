#include "pathhelper.h"
#include <filesystem>
#include <iostream>
#include <string>
#include "config.h"

using namespace utils;

std::string PathHelper::getRootPath(bool by_marco)
{
    if (by_marco)
    {
        const char* project_root_path = PROJECT_ROOT;
        if (project_root_path)
        {
            return std::string(project_root_path);
        }
        else
        {
            std::cerr << "PROJECT_ROOT environment variable is not set" << std::endl;
            return "";
        }
    }
    else
    {
        // Get Root Path by Relative Path
        std::filesystem::path project_root_path =
            std::filesystem::current_path().parent_path().parent_path().parent_path();
        if (project_root_path.empty())
        {
            std::cerr << "Error Project Root Path" << std::endl;
            return "";
        }
        return project_root_path.generic_string();
    }
}

std::string PathHelper::getImagePath(const std::string& file_name)
{
    std::string image_path = getRootPath() + kImagePath.data() + file_name;
    if (!std::filesystem::exists(image_path))
    {
        std::cout << "Image path you find does not exist: " << image_path << std::endl;
        return "";
    }
    return image_path;
}

std::string PathHelper::getShaderPath(const std::string& file_name)
{
    std::string shader_path = getRootPath() + kShaderPath.data() + file_name;
    if (!std::filesystem::exists(shader_path))
    {
        std::cout << "Shader path you find does not exist: " << shader_path << std::endl;
        return "";
    }
    return shader_path;
}