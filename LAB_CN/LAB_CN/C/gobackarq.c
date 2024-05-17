#include<stdio.h>
int main()
{
int windowsize, sent=0, ack, i;

printf("enter the window size:");
scanf("%d",&windowsize);
while(1)
{
for(i=0;i<windowsize;i++)
{
printf("frame %d has been transmiited\n",sent);
sent++;
if(sent==windowsize)
break;
}
printf("\nplease enter the last ack recevied\n");
scanf("%d",&ack);
if(ack==windowsize)
break;
else
sent=ack;
}
return 0;
}
