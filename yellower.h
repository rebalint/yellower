#ifndef _FILE_NAME_H_
#define _FILE_NAME_H_
#endif

#include <filesystem>
#include <string>
#include <iostream>

//using namespace std;
namespace fs= std::filesystem;

//declare thread functions
void recolor(std::basic_string<char> imgpath, const std::string ext, float intensity, const std::vector<unsigned char>& target_rgb);