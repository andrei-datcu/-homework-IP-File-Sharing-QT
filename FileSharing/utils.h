#pragma once

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

#define TESTFILE "test.json"
#define FILELISTPORT 8888
#define FILEPORT 9999
#define SEARCHPORT 9999
#define CHUNKSIZE 1000
#define SERVERIPADDRESS "127.0.0.1"
#define SERVERPORT 9191



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

typedef struct
{
	char userName[30];
} connectRequest;

typedef struct
{
	int valid;
	int size;
	char payload[1000];
} serverConnectResponse;
