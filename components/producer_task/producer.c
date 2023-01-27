#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "producer.h"


struct Producer
{
    int message;
    QueueHandle_t queue;
};

Producer_Handle_t Producer_Create(QueueHandle_t queue)
{
    Producer_Handle_t instance = (Producer_Handle_t) malloc(1*sizeof(struct Producer)); 
    if (instance == NULL)
    {
        printf("failed to create instance producer");
    }
    instance->queue = queue;
    printf("Producer created");

    return instance ;
}

void Producer_Destroy(Producer_Handle_t me)
{
    free(me);
}

void Producer_Task ( void * args)
{
    Producer_Handle_t producerHandle = (Producer_Handle_t) args;
    BaseType_t xStatus_send;
    producerHandle -> message = 9;
    const TickType_t xFrequency_send = pdMS_TO_TICKS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    BaseType_t xWasDelayed;

    for(;;)
    {
        // vTaskDelayUntil(&xLastWakeTime, xFrequency_send);

        printf("Test sender\n");
        // vTaskDelay(pdMS_TO_TICKS(1000));

        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency_send);

        if (xWasDelayed == pdTRUE)
        {
            printf("Yes it is delayed\n");
        }
        else 
        {
            printf("Sorry the delay doesnt work\n");
        }
        xStatus_send = xQueueSend(producerHandle->queue, &(producerHandle->message), 0);
        if (xStatus_send == pdPASS)
        {
            printf("success input to queue\n");
        }
        else if (xStatus_send == pdFAIL)
        {
            printf("Queue is full\n");
        }
        
    }
}