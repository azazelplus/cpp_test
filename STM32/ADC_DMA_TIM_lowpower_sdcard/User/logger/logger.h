// data_logger.h
#ifndef __DATA_LOGGER_H
#define __DATA_LOGGER_H

#include "ff.h"
#include <stdint.h>

// 数据记录器状态
typedef enum {
    LOGGER_UNINIT = 0,
    LOGGER_READY,
    LOGGER_WRITING,
    LOGGER_ERROR
} LoggerState;

// 数据记录器初始化
LoggerState logger_init(void);

// 记录ADC数据
void log_adc_value(float adc_value);

// 关闭记录器
void logger_close(void);

#endif // __DATA_LOGGER_H
