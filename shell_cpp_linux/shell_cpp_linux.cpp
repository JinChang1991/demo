#include<stdio.h>
#include <iostream>

/*
使用popen的方式，调用linux的shell命令
*/
int main()
{
	FILE *fp = NULL;
	char data[100] = {'0'};
        std::string cmd ="scp jin@127.0.0.1:/home/jin/autobot/calibration_online/calibration_sync/image/* /home/jin/autobot/calibration_online/calibration_sync/server";
	fp = popen(cmd.c_str(), "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	while (fgets(data, sizeof(data), fp) != NULL)
	{
		printf("%s", data);
	}
	pclose(fp);
	return 0;
}
