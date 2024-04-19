/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Arduino.h>
#include "br_e1_plus\br_e1_plus.h"

BR_E1_PLUS::BR_E1_PLUS BR_e1;

void setup()
{
    BR_e1.setup();
}

void loop()
{
    BR_e1.loop();
}
