<a name="aDZbJ"></a>

# What

这是一个消息事件订阅发布的应用框架，用于模块之间通信并且达到解耦的目的，通过mmc作为消息中转站，实现模块与模块事件消息通信只需要订阅事件id即可。<br />This is an application framework for message event subscription publishing, which is used for communication between modules and achieves the purpose of decoupling, through MMC as a message broker, to achieve module and module event message communication only need to subscribe to event IDs.
<a name="LO3a3"></a>

# Start

pull and run build.sh<br />result:

```c
event_id:1,send msg form moudle 3 to mmc moudle
tx : Message:1 2 2
gui : Message:1 2 2
event_id:3,send msg form moudle 4 to mmc moudle
tx : Message:3 2 2
gui : Message:3 2 2
event_id:4,send msg form moudle 4 to mmc moudle
event_id:5,send msg form moudle 2 to mmc moudle
gui : Message:4 2 2
gui : Message:5 2 2
tx : Message:4 2 2
tx : Message:5 2 2
```

Then you can use it
<a name="VWW6a"></a>

# How

1. Add Msg Moudle

<Mmc_Msg_Handle.h>

```c
typedef enum msg_moudle
{
    MOUDLE_MMC = 0,
    //TODO
    MOUDLE_GUI,
    MOUDLE_TX,
    MOUDLE_XX,
    MOUDLE_KK,
    //TODO END
    MOUDLE_COUNT,
} msg_moudle_t;
```

Add modules that you'll use

2. Add Event

<Mmc_Event.h>

```c
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
```

Add events that will occur in your program

3. Subscribe Event

<Mmc_Event.c>

```c
//SubscribeEvent
    //TODO
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

    //TODO END
```

First parameter is Moudle which you want to obverser the second parameter event

4. Create the thread or process to be the mmc to publish the event

<main.c>

```c
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
```

5. Create the thread or process to obverser the event

<main.c>

```c
void *thread_gui(void)
{
    message_t* message;
    unsigned int ret;
    while(1)
    {
        ret = Sub_Mmc_Msg_Handle_Recv(&message,MOUDLE_GUI);
        if(OK == ret)
        {
            printf("gui : Message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);
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
            printf("tx : Message:%d %d %d\n",message->event_id,message->parameter_1,message->parameter_2);

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

pthread_t tid1,tid2,tid3;
//create thread to obverser their queue
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
```

6. Create thread or process to simulate event triggering

<mian.c>

```c
void *thread_send(void)
{
    unsigned int ret;
    //Send Msg
    sleep(1);
    ret = Sub_Mmc_Msg_Handle_Send(HAL_UPDATE,2,2,MOUDLE_XX);
    if(ERROR == ret)
    {
        printf("Send mmc msg fail\n");
        return NULL;
    }
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
    ret = Sub_Mmc_Msg_Handle_Send(HAL_WRITE3,2,2,MOUDLE_TX);
    if(ERROR == ret)
    {
        printf("Send mmc msg fail\n");
        return NULL;
    }
    return NULL;
}

//create third to send obversation msg
pthread_t tid3;
ret=pthread_create(&tid3,NULL,(void*)thread_send,NULL);
if(ret)
{
    printf("create pthread error!\n");
    return  -1; 
}

```

7. If you use it at RTOS,you can replace threads with tasks
