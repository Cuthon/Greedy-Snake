#pragma once
#include <graphics.h>
#include <map>
#include <string>

class drawer
{
private:
    static drawer* _instance;
    drawer();
    
public:
    static drawer* GetInstance();
    void loadImgs();
    std::map<std::string, IMAGE> imgMap;
};

void transparentimage(int x, int y, IMAGE& img);
