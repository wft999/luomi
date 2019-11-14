/*
 * Copyright (c) 2019 Luomi, Inc.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>

#include <time.h>
#include <db.h>

int main(int argc, char *argv[]) {
	COL_TYPE colType[] = {COL_TYPE_INT,COL_TYPE_INT};
	int ret = create_db("/root/temp","compressNone",2,colType,1200,STORE_BY_COL,COMPRESS_NONE,1);
	if(ret < 0){
		printf("====create_db:compressNone fail====%d\n\n",ret);
	}

	ret = create_db("/root/temp","compressTaos1",2,colType,1200,STORE_BY_COL,COMPRESS_TAOS_ONE_STEP,1);
	if(ret < 0){
		printf("====create_db:compressTaos1 fail====%d\n\n",ret);
	}

	void* pDbNone = open_db("/root/temp/compressNone");
	if(pDbNone == NULL){
		printf("====open_db:compressNone fail====\n\n");
		goto error;
	}

	void* pDbTaos1 = open_db("/root/temp/compressTaos1");
	if(pDbTaos1 == NULL){
		printf("====open_db:compressTaos1 fail====\n\n");
		goto error;
	}

	int count = 1000000;
	struct _dt{
		int e1;
		int e2;
	};

	struct _dt d;
	d.e1 = 1;
	d.e2 = 10000;

	while(count--){
		ret = put_db(pDbNone,(char*)&d);
		if(ret <0){
			printf("====put_db fail====%d\n\n",ret);
			goto error;
		}
		ret = put_db(pDbTaos1,(char*)&d);
		if(ret <0){
			printf("====put_db fail====%d\n\n",ret);
			goto error;
		}
		d.e1++;
		d.e2++;
		sleep(1);
		printf("====put_db count====%d\n\n",count);
	}

/*
	int64_t fileIndex;
	printf("====input fileIndex=====\n");
	while(scanf("%lld",&fileIndex) > 0)
		readFromFile(pDb,fileIndex);
*/

error:
	close_db(pDbNone);
	close_db(pDbTaos1);
	printf("====demo end====\n\n");
	return getchar();
}
