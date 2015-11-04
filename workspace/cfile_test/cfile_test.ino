
#include <LCFile.h>

LCFileClass File1;
LCFileClass File2;

char writedata[40] = {0};
char readdata[40] = {0};
unsigned char sysTime = 0;

void setup()
{
    Serial1.begin(115200);
    Serial1.print("CFile test.\r\n");
    File1.FileOpen("file1.txt");
    File2.FileOpen("file2.txt");
    File1.FileWrite("file1.txt\r\n");
    File2.FileWrite("file2.txt\r\n");
    File1.FileRead(readdata,40,0);
    Serial1.print(readdata);
    Serial1.print("\r\n");
}

void loop()
{
    unsigned char i = 10;
    unsigned long size = 0; 
    sprintf((char*)writedata, "It is time %d,Pls check!\r\n", sysTime ++);
    Serial1.print(writedata);
    File1.FileWrite(writedata);
    File1.FileSize(&size);
    Serial1.print("File1 size is ");
    Serial1.println(size);
    while(i--)
    {
        if(task_uart_key() == 1)
        {
            File2.FileDelete();
            Serial1.print("FileDelete.\r\n");
        }
        delay(100);
    }
}

unsigned int task_uart_key()
{
    String inString = "";
    unsigned int keyValue = 0;
    unsigned char bitCount = 0; 
    unsigned char dataTemp1[10] = {0};
    while(Serial1.available() > 0)
    {
            unsigned char inChar = Serial1.read();
            inString += (char)inChar;
            dataTemp1[bitCount] = inChar - '0';
            bitCount += 1;
            delay(10);
    }
    if(inString != "")
    {
            if(bitCount > 4)
            {
                Serial1.println("Key input error.");
            }
            else
            {
                    for(char i=0;i<bitCount;i++)
                    {
                            unsigned int dataTemp2 = 1;
                            for(char j=0;j<(bitCount-i-1);j++)dataTemp2 *= 10;
                            keyValue += (dataTemp1[i] * dataTemp2);
                    }   
                    Serial1.print("Key value is: ");
                    Serial1.println(keyValue); 
            }
    }
    return keyValue;   
}