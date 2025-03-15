//
// Created by osolemio on 24-12-11.
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
//
#include "keyboard.h"

#include "main.h"
#include "stm32f4xx_hal.h"

int key = 0;

void key_scan(void)
{
    HAL_GPIO_WritePin(KEY_C1_GPIO_Port, KEY_C1_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    if(HAL_GPIO_ReadPin(KEY_R1_GPIO_Port, KEY_R1_Pin) == 1) {
        key = 1;
    }
    else if(HAL_GPIO_ReadPin(KEY_R2_GPIO_Port, KEY_R2_Pin) == 1) {
        key = 2;
    }
    else if(HAL_GPIO_ReadPin(KEY_R3_GPIO_Port, KEY_R3_Pin) == 1) {
        key = 3;
    }
    else if(HAL_GPIO_ReadPin(KEY_R4_GPIO_Port, KEY_R4_Pin) == 1) {
        key = 4;
    }
    else {
        //key = 0;
    }
    HAL_GPIO_WritePin(KEY_C1_GPIO_Port, KEY_C1_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);

    HAL_GPIO_WritePin(KEY_C2_GPIO_Port, KEY_C2_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    if(HAL_GPIO_ReadPin(KEY_R1_GPIO_Port, KEY_R1_Pin) == 1) {
        key = 5;
    }
    else if(HAL_GPIO_ReadPin(KEY_R2_GPIO_Port, KEY_R2_Pin) == 1) {
        key = 6;
    }
//    else if(HAL_GPIO_ReadPin(KEY_R3_GPIO_Port, KEY_R3_Pin) == 1) {
//        key = 7;
//    }
//    else if(HAL_GPIO_ReadPin(KEY_R4_GPIO_Port, KEY_R4_Pin) == 1) {
//        key = 8;
//    }
    else {
        //key = 0;
    }
    HAL_GPIO_WritePin(KEY_C2_GPIO_Port, KEY_C2_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}
