#pragma once

#define TESTFILE "test.json"
#define FILELISTPORT 8888
#define FILEPORT 9999
#define SEARCHPORT 9999
#define CHUNKSIZE 1000



typedef struct
{
	int type;
	int size;
	char payload[1024];
} request;

typedef struct
{
	int fileID;
	int size;
	char payload[30];
} fileRequest;

