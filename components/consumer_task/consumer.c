#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "consumer.h"



struct Consumer
{
    int receivedMessage;
    QueueHandle_t queue;
};


Consumer_Handle_t Consumer_Create(QueueHandle_t queue)
{
    Consumer_Handle_t instance = (Consumer_Handle_t) malloc(1*sizeof(struct Consumer));
    if(instance == NULL)
    {
        printf("failed to create instance consumer\n");
    }
    instance->queue = queue;
    printf("Producer created");
    return instance;
}

void Consumer_Destroy(Consumer_Handle_t me)
{
    free(me);
}

void Consumer_Task(void * args)
{
    Consumer_Handle_t consumerHandle = (Consumer_Handle_t) args;
    BaseType_t xStatus_Received;

    const TickType_t xFrequency_send = pdMS_TO_TICKS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency_send);
        if (uxQueueMessagesWaiting(consumerHandle->queue) != 0)
        {
            printf("Queue should have been empty!\r\n");
        }

        xStatus_Received = xQueueReceive(consumerHandle->queue, &(consumerHandle->receivedMessage) , 0);
        if (xStatus_Received == pdPASS)
        {
            printf("success received\n");
        }
        else
        {
            printf("Queue is empty\n");
        }
        
    }
}