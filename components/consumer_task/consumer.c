#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "consumer.h"

#include "esp_log.h"

#define TAG "Consumer"

void attach_consumer_to_queue(Consumer * consumer , QueueHandle_t queue )
{
    consumer->queue = queue;
}


void Consumer_Task(void * args)
{
    Consumer * consumerHandle = (Consumer *) args;
    BaseType_t xStatus_Received;

    const TickType_t xFrequency_send = pdMS_TO_TICKS(500);
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;)
    {
        vTaskDelayUntil(&xLastWakeTime, xFrequency_send);
        if (uxQueueMessagesWaiting(consumerHandle->queue) != 0)
        {
            ESP_LOGI(TAG, "Queue should have been empty!");
        }

        xStatus_Received = xQueueReceive(consumerHandle->queue, &(consumerHandle->receivedMessage) , 1000);
        if (xStatus_Received == pdPASS)
        {
            ESP_LOGI(TAG, "success received\n");
        }
        else
        {
            ESP_LOGE(TAG, "Queue is empty");
        }
        
    }
}