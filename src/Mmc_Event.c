#include "Mmc_Event.h"
#include "Moudle_List.h"
#include "Mmc_Msg_Handle.h"

#include <stdio.h>
#include <stdlib.h>


Event_Moudle_t event_moudle[EVENTS_COUNT];

void Mmc_SubscribeEvent(msg_moudle_t moudle,Events_t event_id)
{
    //TODO
    //模块订阅消息
    event_moudle[event_id].event_id = event_id;
    insert_node(event_moudle[event_id].moudle_list,moudle);
}

void Mmc_Event_MoudleInit(void)
{
    for(int i = 0;i<EVENTS_COUNT;i++)
    {
        event_moudle[i].event_id = i;
        event_moudle[i].moudle_list = create_list(0);
    }

    //SubscribeEvent
    Mmc_SubscribeEvent(MOUDLE_GUI,HAL_UPDATE);
    Mmc_SubscribeEvent(MOUDLE_GUI,HAL_WRITE);
    Mmc_SubscribeEvent(MOUDLE_GUI,HAL_WRITE1);
    Mmc_SubscribeEvent(MOUDLE_GUI,HAL_WRITE2);
    Mmc_SubscribeEvent(MOUDLE_GUI,HAL_WRITE3);

    Mmc_SubscribeEvent(MOUDLE_TX,HAL_UPDATE);
    Mmc_SubscribeEvent(MOUDLE_TX,HAL_WRITE1);
    Mmc_SubscribeEvent(MOUDLE_TX,HAL_WRITE2);
    Mmc_SubscribeEvent(MOUDLE_TX,HAL_WRITE3);

    Mmc_SubscribeEvent(MOUDLE_KK,HAL_UPDATE);
    Mmc_SubscribeEvent(MOUDLE_KK,HAL_WRITE1);
    Mmc_SubscribeEvent(MOUDLE_KK,HAL_WRITE2);
    Mmc_SubscribeEvent(MOUDLE_KK,HAL_WRITE3);

    Mmc_SubscribeEvent(MOUDLE_XX,HAL_UPDATE);
    Mmc_SubscribeEvent(MOUDLE_XX,HAL_WRITE1);
    Mmc_SubscribeEvent(MOUDLE_XX,HAL_WRITE2);
    Mmc_SubscribeEvent(MOUDLE_XX,HAL_WRITE3);

    //...

}

Node_t* Mmc_GetMoudleList(int event_id)
{
    return event_moudle[event_id].moudle_list;
}
