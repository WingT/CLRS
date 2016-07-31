/*
 * test.c
 *
 *  Created on: 2016年1月21日
 *      Author: wing
 */
#include<stdio.h>
#include<time.h>
int main(void)
{
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow=localtime(&now);
	printf("%d",timenow->tm_hour);
	return 0;
}

