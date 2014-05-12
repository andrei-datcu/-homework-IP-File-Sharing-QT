#pragma once


typedef struct
{
	int type;
	int size;
	char payload[1024];
} request;

