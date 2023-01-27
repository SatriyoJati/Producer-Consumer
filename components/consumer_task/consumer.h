#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#ifndef CONSUMER_H
#define CONSUMER_H

typedef struct Consumer *Consumer_Handle_t;

Consumer_Handle_t Consumer_Create(QueueHandle_t queue);
void Consumer_Destroy(Consumer_Handle_t me) ;
void Consumer_Task(void *args);

#endif