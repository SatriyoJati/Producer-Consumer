#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#ifndef CONSUMER_H
#define CONSUMER_H

typedef struct consumer
{
    int receivedMessage;
    QueueHandle_t queue;
}Consumer;

void attach_consumer_to_queue(Consumer * consumer , QueueHandle_t queue);

void Consumer_Task(void *args);

#endif