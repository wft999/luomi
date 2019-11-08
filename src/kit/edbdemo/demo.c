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
	int ret = create_db("/root/temp","db01",2,colType,100,STORE_BY_COL,COMPRESS_NONE,1);
	if(ret < 0){
		printf("====create_db fail====%d\n\n",ret);
		//goto error;
	}

	void* pDb = open_db("/root/temp/db01");
	if(pDb == NULL){
		printf("====open_db fail====\n\n");
		goto error;
	}

	int count = 120;
	struct _dt{
		int e1;
		int e2;
	};

	struct _dt d;
	d.e1 = 1;
	d.e2 = 10000;

	while(count--){
		ret = put_db(pDb,(char*)&d);
		if(ret <0){
			printf("====put_db fail====%d\n\n",ret);
			goto error;
		}
		d.e1++;
		d.e2++;
		sleep(1);
		printf("====put_db count====%d\n\n",count);
	}

	int64_t fileIndex;
	printf("====input fileIndex=====\n");
	while(scanf("%ld",&fileIndex) > 0)
		query_db(pDb,fileIndex);

	close_db(pDb);


error:
	printf("====demo end====\n\n");
	return getchar();
}
