#ifndef _MMC_MSG_HANDLE_H
#define _MMC_MSG_HANDLE_H

#include "Msg_Queue.h"

#define MAX_MSG_COUNT (64)

typedef struct mmc_msg_handle_ctrl
{
    msg_queue_t* mmc_msg_handle_queue;

} mmc_msg_handle_ctrl_t;

typedef enum msg_moudle
{
    MOUDLE_MMC = 0,
    MOUDLE_GUI,
    MOUDLE_TX,
    MOUDLE_XX,
    MOUDLE_KK,
    MOUDLE_COUNT,
} msg_moudle_t;

unsigned int Mmc_Msg_Handle_Init(void);
unsigned int Mmc_Msg_Handle_DeInit(void);
unsigned int Mmc_Msg_Handle_Send(int event_id,int parameter_1,int parameter_2,msg_moudle_t target_moudle);
unsigned int Sub_Mmc_Msg_Handle_Send(int event_id,int parameter_1,int parameter_2,msg_moudle_t from_moudle);
unsigned int Mmc_Msg_Handle_Publish(message_t* message);
unsigned int Mmc_Msg_Handle_Recv(message_t **message);
unsigned int Sub_Mmc_Msg_Handle_Recv(message_t **message,msg_moudle_t recv_moudle);
msg_queue_t* Mmc_Msg_Handle_GetQueue(msg_moudle_t moudle);

#endif
