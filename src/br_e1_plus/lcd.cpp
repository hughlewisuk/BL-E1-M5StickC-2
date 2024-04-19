/**
 * @file test_lcd.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "br_e1_plus.h"

namespace BR_E1_PLUS
{

    void BR_E1_PLUS::Displaybuff()
    {
        Disbuff->pushSprite(0, 0);
    }

    void BR_E1_PLUS::ColorBar()
    {
        float color_r, color_g, color_b;

        color_r = 0;
        color_g = 0;
        color_b = 255;

        for (int i = 0; i < 384; i = i + 4)
        {
            if (i < 128)
            {
                color_r = i * 2;
                color_g = 0;
                color_b = 255 - (i * 2);
            }
            else if ((i >= 128) && (i < 256))
            {
                color_r = 255 - ((i - 128) * 2);
                color_g = (i - 128) * 2;
                color_b = 0;
            }
            else if ((i >= 256) && (i < 384))
            {
                color_r = 0;
                color_g = 255 - ((i - 256) * 2);
                ;
                color_b = (i - 256) * 2;
                ;
            }
            Disbuff->fillRect(0, 0, 240, 135,
                              Disbuff->color565(color_r, color_g, color_b));
            Displaybuff();
        }

        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                color_r = 0;
                color_g = 0;
                color_b = 0;
                break;
            case 1:
                color_r = 255;
                color_g = 0;
                color_b = 0;
                break;
            case 2:
                color_r = 0;
                color_g = 255;
                color_b = 0;
                break;
            case 3:
                color_r = 0;
                color_g = 0;
                color_b = 255;
                break;
            }
            for (int n = 0; n < 240; n++)
            {
                color_r = (color_r < 255) ? color_r + 1.0625 : 255U;
                color_g = (color_g < 255) ? color_g + 1.0625 : 255U;
                color_b = (color_b < 255) ? color_b + 1.0625 : 255U;
                Disbuff->drawLine(n, i * 33.75, n, (i + 1) * 33.75,
                                  Disbuff->color565(color_r, color_g, color_b));
            }
        }
        Displaybuff();
        delay(500);

        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                color_r = 255;
                color_g = 255;
                color_b = 255;
                break;
            case 1:
                color_r = 255;
                color_g = 0;
                color_b = 0;
                break;
            case 2:
                color_r = 0;
                color_g = 255;
                color_b = 0;
                break;
            case 3:
                color_r = 0;
                color_g = 0;
                color_b = 255;
                break;
            }
            for (int n = 0; n < 240; n++)
            {
                color_r = (color_r > 2) ? color_r - 1.0625 : 0U;
                color_g = (color_g > 2) ? color_g - 1.0625 : 0U;
                color_b = (color_b > 2) ? color_b - 1.0625 : 0U;
                Disbuff->drawLine(239 - n, i * 33.75, 239 - n, (i + 1) * 33.75,
                                  Disbuff->color565(color_r, color_g, color_b));
            }
        }
        Displaybuff();
        delay(500);
    }

    void BR_E1_PLUS::frame_test()
    {
        display->fillScreen(TFT_BLACK);
        display->drawRect(0, 0, display->width(), display->height(), TFT_GREEN);
        display->drawRect(1, 1, display->width() - 2, display->height() - 2, TFT_GREEN);
        display->drawLine(0, 0, display->width(), display->height(), TFT_GREEN);
        display->drawLine(0, display->height(), display->width(), 0, TFT_GREEN);
        displayUpdate();

        waitNext();
    }

    void BR_E1_PLUS::color_test()
    {
        std::vector<int> color_list = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_BLACK, TFT_WHITE};
        for (auto i : color_list)
        {
            display->fillScreen(i);
            displayUpdate();
            waitNext();
        }
    }

    void BR_E1_PLUS::lcd_init()
    {
        lcd.begin();
        lcd.setRotation(3);
        // lcd.setBrightness(255);

        // lcd.setBrightness(200);

        // lcd.fillScreen(TFT_RED);
        // while (1);
        // lcd.setTextColor(TFT_WHITE, TFT_RED);
        // lcd.setTextSize(3);
        // uint8_t bbb = 0;
        // while (1) {
        //     printf("%d\n", bbb);
        //     lcd.setBrightness(bbb);
        //     lcd.setCursor(10, 10);
        //     lcd.printf("%d    ", bbb);
        //     bbb++;
        //     delay(20);
        // }

        /* Full scren sprite */
        Disbuff = new LGFX_Sprite(&lcd);
        Disbuff->createSprite(lcd.width(), lcd.height());
    }

    void BR_E1_PLUS::lcd_test()
    {
        // ColorBar();

        frame_test();
        color_test();

        // ColorBar();
    }

    void BR_E1_PLUS::set_init_screen(bool do_pair)
    {
        display->fillRect(0, 0, 240, 135, (negatif?TFT_BLACK:TFT_WHITE));
        
        display->setTextSize(2);
        display->setFreeFont(font_name);
        display->drawString(name, 120 - (display->textWidth(name)/2.0), 20 +  font_name->glyph->height); 
        
        if(do_pair)
        {
            display->setTextSize(1);
            display->setFreeFont(font_text);
            display->drawString("Pairing in progress", 120 - (display->textWidth("Pairing in progress")/2.0), 95); 
        }

        display->pushSprite(0,0);
    }

    void BR_E1_PLUS::set_address(String address_str)
    {
        address = address_str;
        address.toUpperCase();
    }

    void BR_E1_PLUS::set_main_menu_screen( void )
    {
        display->fillRect(0, 0, 240, 135, (negatif?TFT_BLACK:TFT_WHITE));

        display->setFreeFont(font_text);
        display->setTextSize(1);
        display->drawString(address, 120 - (display->textWidth(address)/2.0), 5);
        display->drawLine(0, 28, 240, 28, (negatif?TFT_WHITE:TFT_BLACK));
        display->drawString(status, 120 - (display->textWidth(status)/2.0), 112);
        display->drawLine(0, 107, 240, 107, (negatif?TFT_WHITE:TFT_BLACK));

        display->drawString(timertext, 20, 35);
        float v_bat = (float)analogReadMilliVolts(38) * 2 / 1000;
        display->drawFloat( v_bat, 1, 190, 35);
        display->drawString("v", 220, 35);
         
        display->setFreeFont(font_titles);
        display->drawFloat(float(displaydelay)/1000.0, 1, 20, 60);



        display->pushSprite(0,0);
    }

}
