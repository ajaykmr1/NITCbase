#include "StaticBuffer.h"

unsigned char StaticBuffer::blocks[BUFFER_CAPACITY][BLOCK_SIZE];
struct BufferMetaInfo StaticBuffer::metainfo[BUFFER_CAPACITY];

StaticBuffer::StaticBuffer()
{

    // initialise all blocks as free
    for (int bufferIndex = 0; bufferIndex < BUFFER_CAPACITY; bufferIndex++)
    {
        metainfo[bufferIndex].free = true;
    }
}

StaticBuffer::~StaticBuffer() {}

int StaticBuffer::getFreeBuffer(int blockNum)
{
    if (blockNum < 0 || blockNum > DISK_BLOCKS)
    {
        return E_OUTOFBOUND;
    }
    int allocatedBuffer = BUFFER_CAPACITY;

    for (int bufferIndex = 0; bufferIndex < BUFFER_CAPACITY; bufferIndex++)
    {
        if (metainfo[bufferIndex].free == true)
        {
            allocatedBuffer = bufferIndex;
            break;
        }
    }

    if (allocatedBuffer == BUFFER_CAPACITY)
        return FAILURE;

    metainfo[allocatedBuffer].free = false;
    metainfo[allocatedBuffer].blockNum = blockNum;

    return allocatedBuffer;
}

/* Get the buffer index where a particular block is stored
   or E_BLOCKNOTINBUFFER otherwise
*/
int StaticBuffer::getBufferNum(int blockNum)
{

    if (blockNum < 0 || blockNum > DISK_BLOCKS)
        return E_OUTOFBOUND;

    // find and return the bufferIndex which corresponds to blockNum (check metainfo)
    for (int bufferIndex = 0; bufferIndex < BUFFER_CAPACITY; bufferIndex++)
    {
        if (metainfo[bufferIndex].free == false && metainfo[bufferIndex].blockNum == blockNum)
        {
            return bufferIndex;
        }
    }

    // if block is not in the buffer
    return E_BLOCKNOTINBUFFER;
}