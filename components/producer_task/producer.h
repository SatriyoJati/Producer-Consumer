#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#ifndef PRODUCER_H
#define PRODUCER_H


typedef struct producer {
    int message_transmit;
    QueueHandle_t queue;
} Producer;

void attach_producer_to_queue(Producer * producer_intance,  QueueHandle_t queue);

void Producer_Task(void *args);

#endif
