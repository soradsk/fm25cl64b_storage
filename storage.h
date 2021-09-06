#ifndef __STORAGE_H_
#define __STORAGE_H_

#include "fm25cl64b.h"

#define DATA_BLOCK 60
#define DATA_BLOCK_SIZE 10;
typedef struct Data_Block
{
	unsigned char block_size; // size of a block in fram 255
	unsigned int start_address; //a address in fram
	//unsigned long next_address;
}data_block;

typedef struct Storage
{
	//unsigned char data_block_key[DATA_BLOCK];
	data_block *db[DATA_BLOCK];
	unsigned char storage_size;
	unsigned int current_address; //a address in fram
}storage;

data_block *data_block_generate(unsigned int start_address,unsigned char data_size);
void storage_init();
unsigned int storage_insert(storage storage_0,void *address,unsigned char data_size);
void storage_select(storage storage_,void* address,unsigned int key);
void stroage_update(storage storage_,void** address,unsigned char data_size,unsigned int key);
#endif