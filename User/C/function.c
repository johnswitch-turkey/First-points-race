#include "function.h"

static TIM_HandleTypeDef *motor_tim; // ��ʱ�����
static volatile uint16_t pulse_num = 0;    // ��ǰ�������
static volatile uint16_t pulse_limit = 0;  // ����������
static volatile uint8_t pulse_flag = 0;    // 0: ֹͣ, 1: ����, 2: ���
static volatile uint8_t direction = 1;     // ���� (1: ��ת, 0: ��ת)

#define PULSE_FLAG_STOP  0
#define PULSE_FLAG_START 1
#define PULSE_FLAG_END   2



/**
 * @brief ��������Ƶ��
 * @param freq Ƶ�� (Hz, ��Χ 1~50kHz)
 */
void Motor_SetPulseFreq(uint32_t freq) {
    if (freq <= 0 || freq > 50000) return; // ����Ƶ�ʷ�Χ

    freq *= 2; // ÿ����������ߵ͵�ƽ��Ƶ�ʷ���
    uint32_t arr = (84000000 / 1680) / freq - 1; // Ԥ��Ƶ1440�������Զ�����ֵ
    __HAL_TIM_SET_PRESCALER(motor_tim, 0);    // 72MHz / 1440 = 50kHz
    __HAL_TIM_SET_AUTORELOAD(motor_tim, arr);
}

/**
 * @brief ������������
 * @param pulse_num ������ (0��ʾ��������)
 */
void Motor_SetPulseNum(uint16_t pulse_num) {
    if (pulse_num == 0) {
        pulse_flag = PULSE_FLAG_START; // ��������
        pulse_limit = 0;
    } else {
        pulse_num = 0; // ���ü���
        pulse_flag = PULSE_FLAG_START;
        pulse_limit = pulse_num * 2; // ÿ������ߵ͵�ƽ��2��
    }
}

/**
 * @brief �����������
 */
void Motor_PulseStart(void) {
    if (pulse_flag == PULSE_FLAG_STOP) {
        pulse_flag = PULSE_FLAG_START;
    }
    HAL_TIM_Base_Start_IT(motor_tim); // ������ʱ���ж�
}

/**
 * @brief ֹͣ�������
 */
void Motor_PulseStop(void) {
    pulse_flag = PULSE_FLAG_STOP;
    HAL_TIM_Base_Stop_IT(motor_tim);
    HAL_GPIO_WritePin(STEP_PORT, STEP_PIN, GPIO_PIN_RESET);
}

/**
 * @brief ��������Ƿ����
 * @return 1: �ѽ���, 0: δ����
 */
uint8_t Motor_PulseIsEnd(void) {
    return (pulse_flag == PULSE_FLAG_END);
}

/**
 * @brief ���õ������
 * @param direction 1: ��ת, 0: ��ת
 */
void Motor_SetDirection(uint8_t direction) {
    HAL_GPIO_WritePin(DIR_PORT, DIR_PIN, direction ? GPIO_PIN_SET : GPIO_PIN_RESET);
    direction = direction;
}

/**
 * @brief �����ƺ���
 * @param freq Ƶ�� (Hz)
 * @param pulse_num ������
 * @param direction ����
 */
void Motor_Control(uint32_t freq, uint16_t pulse_num, uint8_t direction) {
    Motor_SetPulseFreq(freq);
    Motor_SetPulseNum(pulse_num);
    Motor_SetDirection(direction);
    Motor_PulseStart();
}

/**
 * @brief ��ʱ���жϻص�
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
