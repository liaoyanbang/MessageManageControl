#include <error.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "Mmc_Msg_Handle.h"
#include "Mmc_Error.h"
#include "Msg_Queue.h"
#include "Mmc_Event.h"

void INT_handler(void)
{
    Mmc_Msg_Handle_DeInit();
}
void *thread_gui(void)
{
    message_t* message;
    unsigned int ret;
    while(1)
    {
        ret = Sub_Mmc_Msg_Handle_Recv(&message,MOUDLE_GUI);
        if(OK == ret)
        {
            printf("gui recevie message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);
            switch (message->event_id) 
            {
                case HAL_UPDATE:
                {
                    //TODO
                    break;
                }
                case HAL_WRITE:
                {
                    //TODO
                    break;
                }
            }
        }
    }
    return NULL;
}
void *thread_tx(void)
{
    message_t* message;
    unsigned int ret;
    while(1)
    {
        ret = Sub_Mmc_Msg_Handle_Recv(&message,MOUDLE_TX);
        if(OK == ret)
        {
            printf("tx recevie message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);

            switch (message->event_id) 
            {
                case HAL_UPDATE:
                {
                    //TODO
                    break;
                }
            }
        }
    }
    return NULL;
}
void *thread_send(void)
{
    unsigned int ret;
    //Send Msg
    sleep(5);
    for(int i =0;i<100;i++)
    {
        
        ret = Sub_Mmc_Msg_Handle_Send(HAL_UPDATE,2,2,MOUDLE_XX);
        if(ERROR == ret)
        {
            printf("Send mmc msg fail\n");
            return NULL;
        }
    }
    return NULL;
    sleep(3);
    ret = Sub_Mmc_Msg_Handle_Send(HAL_WRITE1,2,2,MOUDLE_KK);
    if(ERROR == ret)
    {
        printf("Send mmc msg fail\n");
        return NULL;
    }
    sleep(3);
    ret = Sub_Mmc_Msg_Handle_Send(HAL_WRITE2,2,2,MOUDLE_KK);
    if(ERROR == ret)
    {
        printf("Send mmc msg fail\n");
        return NULL;
    }
    return NULL;
}


int main() 
{
    message_t* message;
    unsigned int ret;

    ret = Mmc_Msg_Handle_Init();
    if(ERROR == ret)
    {
        printf("Create mmc msg handle fail\n");
        return ret;
    }
    //create thread to obverser their queue
    pthread_t tid1,tid2;
    ret=pthread_create(&tid1,NULL,(void*)thread_gui,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
        return -1; 
    }
    ret=pthread_create(&tid2,NULL,(void*)thread_tx,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
        return  -1; 
    }
    //create third to send obversation msg
    pthread_t tid3;
    ret=pthread_create(&tid3,NULL,(void*)thread_send,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
        return  -1; 
    }
    //signal(SIGINT,INT_handler);

    while (1) 
    {
        ret = Mmc_Msg_Handle_Recv(&message);//mmc模块接收消息
        if(OK == ret)
        {
            //printf("Message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);
            //MMC接收到事件  分发事件至其他模块
            //通过事件id来确定是哪些模块注册
            Mmc_Msg_Handle_Publish(message);
        }
    }
    return 0;
}