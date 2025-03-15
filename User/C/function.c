#include "function.h"

static TIM_HandleTypeDef *motor_tim; // 定时器句柄
static volatile uint16_t pulse_num = 0;    // 当前脉冲计数
static volatile uint16_t pulse_limit = 0;  // 脉冲数限制
static volatile uint8_t pulse_flag = 0;    // 0: 停止, 1: 运行, 2: 完成
static volatile uint8_t direction = 1;     // 方向 (1: 正转, 0: 反转)

#define PULSE_FLAG_STOP  0
#define PULSE_FLAG_START 1
#define PULSE_FLAG_END   2



/**
 * @brief 设置脉冲频率
 * @param freq 频率 (Hz, 范围 1~50kHz)
 */
void Motor_SetPulseFreq(uint32_t freq) {
    if (freq <= 0 || freq > 50000) return; // 限制频率范围

    freq *= 2; // 每个脉冲包含高低电平，频率翻倍
    uint32_t arr = (84000000 / 1680) / freq - 1; // 预分频1440，计算自动重载值
    __HAL_TIM_SET_PRESCALER(motor_tim, 0);    // 72MHz / 1440 = 50kHz
    __HAL_TIM_SET_AUTORELOAD(motor_tim, arr);
}

/**
 * @brief 设置脉冲数量
 * @param pulse_num 脉冲数 (0表示无限脉冲)
 */
void Motor_SetPulseNum(uint16_t pulse_num) {
    if (pulse_num == 0) {
        pulse_flag = PULSE_FLAG_START; // 无限脉冲
        pulse_limit = 0;
    } else {
        pulse_num = 0; // 重置计数
        pulse_flag = PULSE_FLAG_START;
        pulse_limit = pulse_num * 2; // 每个脉冲高低电平计2次
    }
}

/**
 * @brief 启动脉冲输出
 */
void Motor_PulseStart(void) {
    if (pulse_flag == PULSE_FLAG_STOP) {
        pulse_flag = PULSE_FLAG_START;
    }
    HAL_TIM_Base_Start_IT(motor_tim); // 启动定时器中断
}

/**
 * @brief 停止脉冲输出
 */
void Motor_PulseStop(void) {
    pulse_flag = PULSE_FLAG_STOP;
    HAL_TIM_Base_Stop_IT(motor_tim);
    HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_RESET);
}

/**
 * @brief 检查脉冲是否结束
 * @return 1: 已结束, 0: 未结束
 */
uint8_t Motor_PulseIsEnd(void) {
    return (pulse_flag == PULSE_FLAG_END);
}

/**
 * @brief 设置电机方向
 * @param direction 1: 正转, 0: 反转
 */
void Motor_SetDirection(uint8_t direction) {
    HAL_GPIO_WritePin(DIR_PORT, DIR_PIN, direction ? GPIO_PIN_SET : GPIO_PIN_RESET);
    direction = direction;
}

/**
 * @brief 主控制函数
 * @param freq 频率 (Hz)
 * @param pulse_num 脉冲数
 * @param direction 方向
 */
void Motor_Control(uint32_t freq, uint16_t pulse_num, uint8_t direction) {
    Motor_SetPulseFreq(freq);
    Motor_SetPulseNum(pulse_num);
    Motor_SetDirection(direction);
    Motor_PulseStart();
}

/**
 * @brief 定时器中断回调
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == motor_tim && pulse_flag == PULSE_FLAG_START) {
        static uint8_t step_state = 0;
        step_state = !step_state;
        HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, step_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

        if (pulse_limit > 0) {
            pulse_num++;
            if (pulse_num >= pulse_limit) {
                pulse_flag = PULSE_FLAG_END;
                Motor_PulseStop();
            }
        }
    }
}
