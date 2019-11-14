#include <stdio.h>
#include <stdlib.h>
#include "os.h"

#include "db.h"
#include <tscompression.h>
#include <tchecksum.h>

extern int gColTypeSize[];
extern char* gColTypeFormat[];
int (*gTaosCompFunc[])(const char *const input, int inputSize, const int elements, char *const output, int outputSize,
                   char algorithm, char *const buffer, int bufferSize) = {
                                          tsCompressBool,
                                          tsCompressTinyint,
                                          tsCompressSmallint,
                                          tsCompressInt,
                                          tsCompressBigint,
                                          tsCompressFloat,
                                          tsCompressDouble,
                                          tsCompressString,
                                          tsCompressTimestamp,
                                          tsCompressString};

int (*gTaosDecompFunc[])(const char *const input, int compressedSize, const int elements, char *const output,
                     int outputSize, char algorithm, char *const buffer, int bufferSize) = {
                                                            tsDecompressBool,
                                                            tsDecompressTinyint,
                                                            tsDecompressSmallint,
                                                            tsDecompressInt,
                                                            tsDecompressBigint,
                                                            tsDecompressFloat,
                                                            tsDecompressDouble,
                                                            tsDecompressString,
                                                            tsDecompressTimestamp,
                                                            tsDecompressString};

int compressNone(const void* handle,INDEX* const pIndex){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		gErrorCode = 3;
		return -1;
	}

	int inputCount =  pDb->pLogHead->curRowCount;
	int outSize = pDb->pLogHead->maxColSize * inputCount + sizeof(TSCKSUM);
	char* pOutput = malloc(outSize);
	if(pOutput == NULL){
		logError("compressNone","pOutput == NULL");
		return -2;
	}

	int totalSize = 0;
	char* pInput = (char*)pDb->pLogData;
	for(int i = 0; i < pDb->pLogHead->colCount; i++){
		COL_TYPE type = pDb->pLogHead->colType[i];
		int colSize = gColTypeSize[type];
		int size = colSize*inputCount;
		memcpy(pOutput, pInput, size);

		size += sizeof(TSCKSUM);
		taosCalcChecksumAppend(0, (uint8_t*)pOutput, size);

		write(pDb->recordFd, pOutput, size);

		pInput += colSize * pDb->pLogHead->cacheSize;
		totalSize += size;
		pIndex->colLens[i] = size;
	}
	free(pOutput);

	return totalSize;
}

int decompressNone(const void* handle,const char* const pInput,const INDEX* const pIndex,int col,char* pOutput, int outSize){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		return -1;
	}

	COL_TYPE type = pDb->pLogHead->colType[col];
	int colSize = gColTypeSize[type];

	memcpy(pOutput,pInput,colSize * pIndex->rowCount);

	return 0;
}


int compressTaosOneStep(const void* handle,INDEX* const pIndex){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		return -1;
	}

	int inputCount =  pDb->pLogHead->curRowCount;
	int outSize = pDb->pLogHead->maxColSize * inputCount  + sizeof(TSCKSUM);
	char* pOutput = malloc(outSize);
	if(pOutput == NULL){
		logError("compressTaosOneStep","pOutput == NULL");
		return -2;
	}

	int totalSize = 0;
	char* pInput = (char*)pDb->pLogData;
	for(int i = 0; i < pDb->pLogHead->colCount; i++){
		COL_TYPE type = pDb->pLogHead->colType[i];
		int colSize = gColTypeSize[type];
		int size = gTaosCompFunc[type](pInput,colSize*inputCount,inputCount,pOutput,outSize, ONE_STAGE_COMP,NULL, 0);
		size += sizeof(TSCKSUM);
		taosCalcChecksumAppend(0, (uint8_t*)pOutput, size);
		write(pDb->recordFd, pOutput, size);

		pInput += colSize * pDb->pLogHead->cacheSize;
		totalSize += size;
		pIndex->colLens[i] = size;
	}
	free(pOutput);

	return totalSize;
}

int decompressTaosOneStep(const void* handle,const char* const pInput,const INDEX* const pIndex,int col,char* pOutput, int outSize){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		return -1;
	}

	COL_TYPE type = pDb->pLogHead->colType[col];
	int colSize = gColTypeSize[type];

	int size = gTaosDecompFunc[type](pInput,pIndex->colLens[col] - sizeof(TSCKSUM),pIndex->rowCount,pOutput,outSize, ONE_STAGE_COMP,NULL, 0);
	if(size != colSize * pIndex->rowCount){
		logError("compressTaosOneStep","size != colSize * pIndex->count");
		return -3;
	}

	return 0;
}

int compressTaosTwoStep(const void* handle,INDEX* const pIndex){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		gErrorCode = 3;
		return -1;
	}

	return 0;
}

int decompressTaosTwoStep(const void* handle,const char* const pInput,const INDEX* const pIndex,int col,char* pOutput, int outSize){
	return 0;
}

int decompressZlib(const void* handle,const char* const pInput,const INDEX* const pIndex,int col,char* pOutput, int outSize){
	return 0;
}


int compressZlib(const void* handle,INDEX* const pIndex){
	DB* pDb = (DB*)handle;
	if(pDb == NULL || pDb->signature != handle){
		gErrorCode = 3;
		return -1;
	}

	return 0;
}

