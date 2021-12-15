#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int empty[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
screenTouchOn0[8]={0x01,0x00,0x45,0x01,0x01,0x00,0x00,0x00},
screenTouchOn1[8]={0x01,0x00,0x4a,0x01,0x01,0x00,0x00,0x00},
screenX[8]={0x03,0x00,0x35,0x00,0x00,0x00,0x00,0x00},
screenZ[8]={0x03,0x00,0x36,0x00,0x00,0x00,0x00,0x00},
screenHandID0[8]={0x03,0x00,0x2f,0x00,0x00,0x00,0x00,0x00},
screenHandID1[8]={0x03,0x00,0x39,0x00,0x00,0x00,0x00,0x00},
screenUnlock[8]={0x03,0x00,0x39,0x00,0xff,0xff,0xff,0xff},
screenTouchOff0[8]={0x01,0x00,0x45,0x01,0x01,0x00,0x00,0x00},
screenTouchOff1[8]={0x01,0x00,0x4a,0x01,0x01,0x00,0x00,0x00},
apply[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int help(){
    printf("a");
    return 0;
}

int GetDecLen(int inInt){
    int count = 0;
    while(inInt){
        inInt /= 10;
        count++;
    }
    return count;
}

unsigned long GetHexLen(unsigned long inInt){
    unsigned long count = 0;
    while(inInt){
        inInt /= 0x10;
        count++;
    }
    return count;
}

int Readfile(char *path){
    int count = 0;
    char a;
    FILE *eventFile = fopen(path,"r");
    if(eventFile != NULL){
        while(!feof(eventFile)){
            printf("%c",fgetc(eventFile));
            count++;
        }
        if(fclose(eventFile)==EOF){
            printf( "文件关闭错误\n" );
        }
    }
    printf("\n");
    return 0;
}

int Writefile(char *path,int force){
    if(force == 0){
        FILE *openFile = fopen(path,"w");
        if(openFile != NULL) fputc('a',openFile);
        fclose(openFile);
    }else if(force == 1){
        FILE *openFile = fopen(path,"wb");
        if(openFile != NULL) fputc('a',openFile);
        fclose(openFile);
    }else printf("Can't write file!\n");
    return 0;
}

int Doubletap(){
    return 0;
}

int ForOut(char *filePath,int *inValueName){
    FILE *openFile = fopen(filePath,"ab+");
    for(int num=0;num<8;num++) fputc(empty[num],openFile);
    for(int num=0;num<8;num++) fputc(inValueName[num],openFile);
    fclose(openFile);
    return 0;
}

int DecToBin(int inInt){
    int count = 0,temp[16]={};
    while((inInt /= 2) > 0){
        temp[count] = inInt % 2;
        count++;
    }
    return 0;
}

unsigned long HexSplit(unsigned long inInt,int *inPosFunc){
    unsigned long DecCount = 0,HexCount = 0x01,splitHex[2]={0x00,0x00},hexLen;
    hexLen = GetHexLen(inInt);
    while(hexLen != 0){
        splitHex[DecCount] = inInt / HexCount % 0x100;
        HexCount *= 0x100;
        DecCount++;
        if(hexLen >= 2) hexLen -= 2;
        else hexLen--;
    }
    inPosFunc[4] = splitHex[0];
    inPosFunc[5] = splitHex[1];
    return 0;
}

int WriteRawData(char *fileLocation){
    FILE *openFile = fopen(fileLocation,"ab+");
    if(openFile != NULL){
        fclose(openFile);
        ForOut(fileLocation,screenTouchOn0);
        ForOut(fileLocation,screenTouchOn1);
        ForOut(fileLocation,screenHandID0);
        ForOut(fileLocation,screenHandID1);
        ForOut(fileLocation,screenX);
        ForOut(fileLocation,screenZ);
        ForOut(fileLocation,apply);
    }else printf("Error!\n");
    return 0;
}

unsigned long CharToDec(char * inChar){
    unsigned long outDec;
    for(unsigned long count = 1,nums = 0;nums <= strlen(inChar) - 1;count *= 10,nums++){
        if(inChar[nums] >= 48 && inChar[nums] <= 57){
            if(count == 1) outDec = inChar[nums] - 48;
            if(count > 1){
                if(inChar[nums] - 48 == 0) outDec *= 10;
                else outDec = outDec * 10 + inChar[nums] - 48;
            }
        }else{
            printf("Error 1!\n");
            exit(1);
        }
    }
    return outDec;
}

int Tap(char *fileLocation,int touchid,int x,int z){
    screenHandID0[4]=touchid;
    screenHandID0[4]=touchid;
    HexSplit(x,screenX);
    HexSplit(z,screenZ);
    WriteRawData(fileLocation);
    return 0;
}

int main(int args,char **argv){
    /*if(argv[2] != NULL){
        if(strcmp(argv[2],"tap") == 0) Tap(argv[1],CharToDec(argv[3]),CharToDec(argv[4]),CharToDec(argv[5]));
        else if(strcmp(argv[2],"doubletap") == 0) Doubletap();
        else printf("Error!\n");
    }else help();*/
    return 0;
}