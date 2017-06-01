#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int BCD2String(char *pcBCDData, int iBCDDataLen, char *strDigitBuf, int iBufLen);
int String2BCD(char *strDigitData, int strDigitDataLen, char *pcBCDBuf, int iBCDBufLen);


// 主函数
int main()
{
    int  iRetVal = 0;
    char szBCDData[3] = {0x75, 0x39};
    char szDigitBuf[10] = {0};

    iRetVal = BCD2String(szBCDData, strlen(szBCDData), szDigitBuf, sizeof(szDigitBuf));
    if (iRetVal != 0)
    {
       printf("exec BCD2String failed!\n");
       return -1;
    }

    printf("szDigitBuf=%s!\n", szDigitBuf);

    iRetVal = String2BCD("19", 2, szBCDData, 1);
    if (iRetVal != 0)
    {
	printf("exec String2BCD failed!\n");
        return -1;
    }

    printf("szBCDData=%x!\n", szBCDData[0]);

    memset(szDigitBuf, 0x00, sizeof(szDigitBuf));
    iRetVal = BCD2String(szBCDData, 1, szDigitBuf, 2);
    if (iRetVal != 0)
    {
	printf("exec BCD2String failed!\n");
        return -1;
    }

    printf("szDigitBuf=%s!\n", szDigitBuf);

    return 0;
}



// 将8421BCD码转换为十进制数字串
int BCD2String(char *pcBCDData, int iBCDDataLen, char *strDigitBuf, int iBufLen)
{
    int  iPosFlag = 0;
    char cBCD     = 0;

    if (pcBCDData==NULL || strDigitBuf==NULL)
    {
        printf("BCD2String: pcBCDData==NULL || strDigitBuf==NULL!\n");
        return -1;
    }
	
    if (2 * iBCDDataLen > iBufLen)
    {
        printf("BCD2String: 2 * iBCDDataLen(%d) > iBufLen(%d)!\n", iBCDDataLen, iBufLen);
        return -1;
    }
	
    for (iPosFlag = 0; iPosFlag < iBCDDataLen; iPosFlag++)
    {
        cBCD = (pcBCDData[iPosFlag] >> 4);
        if (0x0f == cBCD)
        {
            break;
        }
        strDigitBuf[2 * iPosFlag] = cBCD + '0';
        if (!isdigit(strDigitBuf[2 * iPosFlag]))
        {
            printf("BCD2String: strDigitBuf[2 * %d] is not digit!\n", iPosFlag);
            return -2;
        }

        cBCD = (pcBCDData[iPosFlag] & 0x0f);
        if (0x0f == cBCD)
        {
            break;
        }
        strDigitBuf[2 * iPosFlag + 1] = cBCD + '0';
        if (!isdigit(strDigitBuf[2 * iPosFlag + 1]))
        {
            printf("BCD2String: strDigitBuf[2 * %d + 1] is not digit!\n", iPosFlag);
            return -2;
        }
    }
    
    return 0;
}


// 将十进制数字串转换为8421BCD码
int String2BCD(char *strDigitData, int strDigitDataLen, char *pcBCDBuf, int iBCDBufLen)
{
    int  iPosFlag = 0;

    if (strDigitData==NULL || pcBCDBuf==NULL)
    {
        printf("String2BCD: strDigitData==NULL || pcBCDBuf==NULL!\n");
        return -1;
    }
	
    if (strDigitDataLen > 2 * iBCDBufLen)
    {
        printf("String2BCD: strDigitDataLen(%d) > 2 * iBCDBufLen(%d)!\n", strDigitDataLen, iBCDBufLen);
        return -1;
    }
	
    for (iPosFlag = 0; iPosFlag < strDigitDataLen; iPosFlag+=2)
    {
        if (!isdigit(strDigitData[iPosFlag]))
        {
            printf("String2BCD: strDigitData[%d] is not digit!\n", iPosFlag);
            return -2;
        }
        pcBCDBuf[iPosFlag / 2] = strDigitData[iPosFlag] - '0';
		
        pcBCDBuf[iPosFlag / 2] <<= 4;

        if ((iPosFlag + 1 >= strDigitDataLen))
        {
            break;
        }
        if (!isdigit(strDigitData[iPosFlag + 1]))
        {
            printf("String2BCD: isdigit(strDigitData[%d + 1] is not digit!\n", iPosFlag);
            return -2;
        }
        pcBCDBuf[iPosFlag / 2] += strDigitData[iPosFlag + 1] - '0';
    }
    
    return 0;
}
