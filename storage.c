#include "storage.h"

#define FRAM_BLOCK sizeof(char)
storage STORAGE;

data_block* data_block_generate(unsigned int start_address,unsigned char data_size)
{
	data_block* temp = (data_block*)malloc(sizeof(data_block));
	temp->block_size = data_size;
	temp->start_address = start_address;
	return temp;
}

void storage_init()
{
	STORAGE.current_address = 0;
	STORAGE.storage_size = 0;
}

unsigned int storage_insert(storage storage_,void **address,unsigned char data_size)
{
	unsigned char i;
	unsigned int key;
	char *address_;
	unsigned char data_number = data_size/FRAM_BLOCK;
	key = ++STORAGE.storage_size;
	address_ = *address;
	for(i = 0; i < data_number; i++)
	{
		FramWriteByte(STORAGE.current_address + i, *(address_ + i));
	}
	STORAGE.db[STORAGE.storage_size]  = data_block_generate(STORAGE.current_address, data_number);
	STORAGE.current_address = STORAGE.current_address + data_number;
	return key;
}

void storage_select(storage storage_,void** address,unsigned int key)
{
	unsigned char i;
	data_block* db;
	char c;
	char *address_;
	db = STORAGE.db[key];
	address_ = *address;
	for(i = 0; i < db->block_size; i++)
	{
		//*(address + i) = FramReadByte(db->start_address + i);
		c = FramReadByte(db->start_address + i); //address
		memcpy((address_ + i), &c, FRAM_BLOCK);
	}
}

void stroage_update(storage storage_,void** address,unsigned char data_size,unsigned int key)
{
	unsigned char i;
	data_block* db;
	char * address_;
	unsigned char data_number = data_size/FRAM_BLOCK;
	address_ = *address;
	db = STORAGE.db[key];
	for(i = 0; i < db->block_size; i++)
	{
		FramWriteByte(db->start_address + i,*(address_ + i));
	}
}

/*
void stroage_delete(storage storage_,unsigned char key)
{
	
}
*/