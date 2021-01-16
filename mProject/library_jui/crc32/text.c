#include <stdio.h>
struct crc32Handle
{
    unsigned int m_crcTable[256];
    unsigned char m_inputReverse;
    unsigned char m_resultReflected;
    unsigned int m_poly;
    unsigned int m_initVal;
    unsigned int m_finalXor;
};
void constructCRCHandle(struct crc32Handle *obj,unsigned int poly,unsigned int initVal,unsigned int finalXor,unsigned char inputRev,unsigned char resultRev);
unsigned char reverse8bits(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}
unsigned int reverse32bits(unsigned int x)
{
    x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
    x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
    x = ((x >> 4) & 0x0f0f0f0fu) | ((x & 0x0f0f0f0fu) << 4);
    x = ((x >> 8) & 0x00ff00ffu) | ((x & 0x00ff00ffu) << 8);
    x = ((x >> 16) & 0xffffu) | ((x & 0xffffu) << 16);
    return x;
}
void CalculateCrcTable_CRC32(struct crc32Handle *obj)
{ 
    int divident=0;
    unsigned int curByte=0;
    unsigned char bit=0;
    unsigned int polynomial = obj->m_poly;
    for (divident = 0; divident < 256; divident++) /* iterate over all possible input byte values 0 - 255 */
    {
        curByte= (unsigned int)(divident << 24); /* move divident byte into MSB of 32Bit CRC */
        for (bit = 0; bit < 8; bit++)
        {
            if ((curByte & 0x80000000) != 0)
            {
                curByte <<= 1;
                curByte ^= polynomial;
            }
            else
            {
                curByte <<= 1;
            }
        }
        
        obj->m_crcTable[divident] = curByte;
    }
}
 
unsigned int Compute_CRC32(struct crc32Handle *obj,const void* dat,int size)
{
    const unsigned char *b = dat;
    int index=0; 
    unsigned int curByte=0;
    unsigned char pos =0;
    unsigned int crc = obj->m_initVal; /* CRC is set to specified initial value */
    for(index=0;index<size;index++)
    {
        /* reflect input byte if specified, otherwise input byte is taken as it is */
        if(obj->m_inputReverse==1)
        {
            curByte =reverse8bits(b[index]);
        }
        else
        {
            curByte = b[index];
        }

        /* XOR-in next input byte into MSB of crc and get this MSB, that's our new intermediate divident */
        pos = (unsigned char)((crc ^ (curByte << 24)) >> 24);
        /* Shift out the MSB used for division per lookuptable and XOR with the remainder */
        crc = (unsigned int)((crc << 8) ^ (unsigned int)(obj->m_crcTable[pos]));
    }
    /* reflect result crc if specified, otherwise calculated crc value is taken as it is */
    if(obj->m_resultReflected==1)
    {
        crc = reverse32bits(crc);
    }
    else
    {
        /* do nothing */
    } 
    /* Xor the crc value with specified final XOR value before returning */
    return (unsigned int)(crc ^ obj->m_finalXor);
}

void constructCRCHandle(struct crc32Handle *obj,unsigned int poly,unsigned int initVal,unsigned int finalXor,unsigned char inputRev,unsigned char resultRev)
{
    obj->m_poly = poly;
    obj->m_initVal = initVal;
    obj->m_finalXor = finalXor;
    obj->m_inputReverse = inputRev;
    obj->m_resultReflected = resultRev;
    CalculateCrcTable_CRC32(obj);
}
int main(int argc,char **argv)
{
    char dat[10]="chalearm";
    unsigned int resultCrc =0;
    struct crc32Handle crcH1;
    constructCRCHandle(&crcH1,0x01920192,0xFFFFFFFE,0xFFFFFFFE,1,1);
    resultCrc =Compute_CRC32(&crcH1,dat,8);
    printf("Crc poly : %08x result : %08x\n",crcH1.m_poly,resultCrc);
    return 0;
}
