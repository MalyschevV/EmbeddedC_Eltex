#include<stdio.h>

int main(){
  
    int a = 0xDDCCBBAA;
    unsigned char c;
    int shift = 0;
    int k = 0x00EE0000;
    int result = 0x00000000;
    
    for(int i = 0; i < sizeof(int); i++){
        c = ((a >> shift) & 0xFF);
        printf("%d byte of a = %x\n", i+1, c);
        if(i != sizeof(int)-2){
        result = result + (a & (0x000000FF << shift));
        }
        else{
            result = result + (k & (0x000000FF << shift));
        }
        shift = shift + 8;        
    } 
    printf("changed 3 byte of a: %x\n", result);
}