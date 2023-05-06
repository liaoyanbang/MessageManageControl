#include "Mmc_Msg_Handle.h"

#include "Moudle_List.h"
#include "Msg_Queue.h"
#include "Mmc_Error.h"
#include "Mmc_Event.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

mmc_msg_handle_ctrl_t mmc_msg_handle_ctrl[MOUDLE_COUNT];

unsigned int Mmc_Msg_Handle_Create(unsigned int size,msg_moudle_t moudle)
{
    if(0 != size)
    {
        if(moudle>=MOUDLE_COUNT)
        {
            printf("moudle is none\n");
            return ERROR;
        }
        mmc_msg_handle_ctrl[moudle].mmc_msg_handle_queue = createQueue(size);
        return OK;
    }
    else
    {
        printf("size is zero\n");
        return ERROR;
    }
}

unsigned int Mmc_Msg_Handle_Free(msg_moudle_t moudle)
{

    if(moudle>=MOUDLE_COUNT)
    {
        printf("moudle is none\n");
        return ERROR;
    }
    if(mmc_msg_handle_ctrl[moudle].mmc_msg_handle_queue != NULL)
        freeQueue(mmc_msg_handle_ctrl[moudle].mmc_msg_handle_queue);
    return OK;

}

unsigned int Mmc_Msg_Handle_Send(int event_id,int parameter_1,int parameter_2,msg_moudle_t target_moudle)
{
    unsigned int ret;
    if(target_moudle >= MOUDLE_COUNT)
    {
        printf("send msg form mmc to %d moudle error\n",target_moudle);
        return ERROR;
    }

    message_t* message = (message_t*)malloc(sizeof(message_t));
    if(message == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return ERROR;
    }
    message->event_id = event_id;
    message->parameter_1 = parameter_1;
    message->parameter_2 = parameter_2;
    
    ret = enqueue(mmc_msg_handle_ctrl[target_moudle].mmc_msg_handle_queue,message);
    if(ret == OK)
    {
        printf("event_id:%d,send msg form mmc to %d moudle\n",event_id,target_moudle);
    }
    return ret;
}
unsigned int Sub_Mmc_Msg_Handle_Send(int event_id,int parameter_1,int parameter_2,msg_moudle_t from_moudle)
{
    unsigned int ret;
    message_t* message = (message_t*)malloc(sizeof(message_t));
    if(message == NULL)
    {
        printf("Error: Memory allocation failed\n");
        return ERROR;
    }
    message->event_id = event_id;
    message->parameter_1 = parameter_1;
    message->parameter_2 = parameter_2;
    ret = enqueue(mmc_msg_handle_ctrl[MOUDLE_MMC].mmc_msg_handle_queue,message);//Send to MMC
    if(ret == OK)
    {
        printf("event_id:%d,send msg form moudle %d to mmc moudle\n",event_id,from_moudle);
    }
    return ret;
}

unsigned int Mmc_Msg_Handle_Publish(message_t* message)
{
    unsigned int ret;
    Node_t* moudle_list = Mmc_GetMoudleList(message->event_id);
    Node_t* pos = moudle_list->next;//Get second node 
    //For each to send obversations msg
    while (pos != NULL) {
        //printf("%d\n",pos->moudle);
        //printf("Message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);
        ret = enqueue(mmc_msg_handle_ctrl[pos->moudle].mmc_msg_handle_queue,message);
        if(ret == ERROR)
        {
            return ret;
        }
        pos = pos->next;
    }
    return OK;
}

unsigned int Mmc_Msg_Handle_Recv(message_t **message)
{
    *message = dequeue(mmc_msg_handle_ctrl[MOUDLE_MMC].mmc_msg_handle_queue);
    if(*message == NULL)
        return ERROR;
    else
        return OK;
}
unsigned int Sub_Mmc_Msg_Handle_Recv(message_t **message,msg_moudle_t recv_moudle)
{

    *message = dequeue(mmc_msg_handle_ctrl[recv_moudle].mmc_msg_handle_queue);
    if(*message == NULL)
        return ERROR;
    else
        return OK;
}

msg_queue_t* Mmc_Msg_Handle_GetQueue(msg_moudle_t moudle)
{
    return mmc_msg_handle_ctrl[moudle].mmc_msg_handle_queue;
}

unsigned int Mmc_Msg_Handle_Init(void)
{
    unsigned int ret = 0;
    int moudle = 0;
    for(moudle = 0;moudle < MOUDLE_COUNT;moudle++)
    {
        ret = Mmc_Msg_Handle_Create(MAX_MSG_COUNT,moudle);
        if(ERROR == ret)
        {
            return ret;
        }
    }
    Mmc_Event_MoudleInit();
    return OK;
}

unsigned int Mmc_Msg_Handle_DeInit(void)
{
    unsigned int ret = 0;
    int moudle = 0;
    for(moudle = 0;moudle < MOUDLE_COUNT;moudle++)
    {
        ret = Mmc_Msg_Handle_Free(moudle);
        if(ERROR == ret)
        {
            return ret;
        }
    }
    return OK;
}

