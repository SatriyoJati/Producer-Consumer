#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#ifndef PRODUCER_H
#define PRODUCER_H


typedef struct Producer* Producer_Handle_t;
Producer_Handle_t Producer_Create(QueueHandle_t queue) ;
void Producer_Destroy(Producer_Handle_t me) ;
void Producer_Task(void *args);

#endif
