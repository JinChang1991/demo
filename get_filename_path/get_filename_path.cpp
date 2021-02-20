#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <libgen.h>
#include <string>
#include <algorithm>
int main() 
{
    //相对路径转换为绝对路径
    std::string file_path="./get_filename_path.cpp";
    char record_file_path_and_name[PATH_MAX];
    realpath(file_path.c_str(), record_file_path_and_name);
    std::cout << "file_path:"<< record_file_path_and_name << std::endl;

    std::string full_name = "/home/jin/Desktop/get_filename_path.cpp";
    //std::string str = record_file_path_and_name;
    //分离文件的绝对路径、文件名称、文件名
    std::string pattern = "/";
    auto result = std::find_end(full_name.begin(), full_name.end(), pattern.begin(), pattern.end());
    std::string dirName = "";
    std::string fileName = "";
    std::string fileBaseName = "";
    if (result != full_name.end()) 
    {
        dirName = full_name.substr(0, std::distance(full_name.begin(), result) + 1);
        std::cout << dirName << "\n";
        fileName = full_name.substr(std::distance(full_name.begin(), result) + 1);
        std::cout << fileName << "\n";
        fileBaseName = fileName.substr(0, fileName.size() - 4);
        std::cout << fileBaseName << "\n";
    }
    //在绝对路径下添加一个文件夹
    std::string sub_path = dirName + "meta";
    std::cout << "sub_path:" << sub_path << "\n";


    return 0;
}