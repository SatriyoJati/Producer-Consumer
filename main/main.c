#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "producer.h"
#include "consumer.h"
#include "freertos/queue.h"

void app_main(void)
{
    printf("Starting the ide of thinking\n");

    QueueHandle_t Queue_Prod_Cons = xQueueCreate(10, sizeof(int));

    if (Queue_Prod_Cons == NULL)
    {
        printf("queue not created\n");
    }
    else
    {
        printf("success created\n");
    }

    Producer_Handle_t myProducer = Producer_Create(Queue_Prod_Cons);
    Consumer_Handle_t myConsumer = Consumer_Create(Queue_Prod_Cons);


    // printf("%p", myProducer);
    
    xTaskCreate(Producer_Task, "Sender1", 2000, (void *) myProducer, 1, NULL);
    xTaskCreate(Consumer_Task, "Receiver", 2000, (void *) myProducer, 1, NULL);

    TickType_t xLastWakeTime;
    BaseType_t status;
    for(;;)
    {
        status = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));

    }

    Producer_Destroy(myProducer);
    Consumer_Destroy(myConsumer);
}
