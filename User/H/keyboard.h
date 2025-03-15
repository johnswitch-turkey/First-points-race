//
// Created by osolemio on 24-12-11.
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define ON HAL_GPIO_ReadPin(KEY_R3_GPIO_Port, KEY_R3_Pin) == 1
#define OFF HAL_GPIO_ReadPin(KEY_R4_GPIO_Port, KEY_R4_Pin) == 1

void key_scan(void);

#endif //KEYBOARD_H
