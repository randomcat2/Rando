#include <stdio.h>

int main() {
    int data[8];
    printf("Enter the code to be sent one by one\n");
    scanf("%d %d %d %d",&data[3],&data[5],&data[6],&data[7]);
    data[1]=data[3]^data[5]^data[7];
    data[2]=data[3]^data[6]^data[7];
    data[4]=data[5]^data[6]^data[7];
    for(int i=1;i<=7;i++)
    {
        printf("%d",data[i]);
    }
    int datarec[8];
    printf("\nEnter a received code\n");
    for(int i=1;i<=7;i++)
    {
        scanf("%d",&datarec[i]);
        
    }
    int c1=datarec[1]^datarec[3]^datarec[5]^datarec[7];
    int c2=datarec[2]^datarec[3]^datarec[6]^datarec[7];
    int c3=datarec[4]^datarec[5]^datarec[6]^datarec[7];
    int c=c3*4+c2*2+c1;
    if(c==0)
    {
        printf("the error is not there");
        
    }
    else
    {
        printf("The error is found at %d ",c);
        if(datarec[c]==0)
        {
            datarec[c]=1;
        }
        else
        {
            datarec[c]=0;
        }
    }
    printf("the correct code is \n");
    for(int i=1;i<=7;i++)
    {
        printf("%d",datarec[i]);
    }
    
    
}  