#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "producer.h"
#include "consumer.h"
#include "freertos/queue.h"

#include "esp_log.h"

#define TAG "Main"

void app_main(void)
{
    ESP_LOGI(TAG, "Starting the ide of thinking");

    QueueHandle_t Queue_Prod_Cons = xQueueCreate(10, sizeof(int));

    if (Queue_Prod_Cons == NULL)
    {
        ESP_LOGI(TAG,"queue not created");
    }
    else
    {
        ESP_LOGE(TAG,"queue success created");
    }

    Producer myproducer = 
    {
        .message_transmit = 0,
        .queue = NULL
    };

    Consumer myconsumer = 
    {
        .receivedMessage = 0,
        .queue = NULL
    };

    attach_producer_to_queue(&myproducer, Queue_Prod_Cons);
    attach_consumer_to_queue(&myconsumer, Queue_Prod_Cons);

    // printf("%p", myProducer);
    
    xTaskCreate(Producer_Task, "Sender1", 2000, (void *)&myproducer, 0, NULL);
    xTaskCreate(Consumer_Task, "Receiver", 2000, (void *)&myconsumer, 0, NULL);

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    ESP_LOGE(TAG,"return?");

}
