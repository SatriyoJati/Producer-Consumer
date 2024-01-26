#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "producer.h"

#include "esp_log.h"

#define PRODUCER "Producer"

void attach_producer_to_queue(Producer * producer_intance,  QueueHandle_t queue){
    producer_intance->queue = queue;
}

void Producer_Task ( void * args)
{
    Producer * producerHandle = (Producer *) args;

    BaseType_t xStatus_send;
    producerHandle -> message_transmit = 9;
    const TickType_t xFrequency_send = pdMS_TO_TICKS(300);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    BaseType_t xWasDelayed;

    for(;;)
    {
        // vTaskDelayUntil(&xLastWakeTime, xFrequency_send);

        ESP_LOGI(PRODUCER, "Test sender\n");
        // vTaskDelay(pdMS_TO_TICKS(1000));

        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, xFrequency_send);

        if (xWasDelayed == pdTRUE)
        {
            ESP_LOGI(PRODUCER,"Yes it is delayed\n");
        }
        else 
        {
            ESP_LOGE(PRODUCER,"Sorry the delay doesnt work\n");
        }

        xStatus_send = xQueueSend(producerHandle->queue, &(producerHandle->message_transmit), 0);
        if (xStatus_send == pdPASS)
        {
            ESP_LOGI(PRODUCER,"success input to queue\n");
        }
        else if (xStatus_send == pdFAIL)
        {
            ESP_LOGE(PRODUCER,"Queue is full\n");
        }
        
    }
}