#ifndef _EVENT_H
#define _EVENT_H

#include "Moudle_List.h"

typedef enum Events
{
    //TODO
    ERROR_EVENT,
    HAL_UPDATE,
    HAL_WRITE,
    HAL_WRITE1,
    HAL_WRITE2,
    HAL_WRITE3,
    //TODO END
    EVENTS_COUNT,
} Events_t;


typedef struct Event_Moudle
{
    Node_t* moudle_list;
    Events_t event_id;
} Event_Moudle_t;

void Mmc_Event_MoudleInit(void);
Node_t* Mmc_GetMoudleList(int event_id);


#endif
