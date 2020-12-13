#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <string.h> 
int main(void)
{
    while(1)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        char date[64] = "";
        time_t tt = tv.tv_sec + tv.tv_usec/1e9;
        strftime(date, 64, "%Y-%m-%d %H:%M:%S", localtime(&tt));
        std::cout << "date : "<<date
                  << "      timestamp :"<<std::to_string(tv.tv_sec) + "." + std::to_string(tv.tv_usec)
                  << std::endl;
        sleep(1);
    }
    return 0;
}
/***
****  readme.txt
****  g++ -o main main.cpp
****  得到当前的时间和时间戳
****
***/

