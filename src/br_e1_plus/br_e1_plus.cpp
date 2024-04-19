/**
 * @file test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-05-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "CanonBLERemote.h"
#include "TimeLapse_Management.h"
#include "br_e1_plus.h"


String name_remote = "BR-M5";
CanonBLERemote canon_ble(name_remote);
TimeLapse timelapse(400);

enum RemoteMode {Settings, Shooting, Video}current_mode;



namespace BR_E1_PLUS
{

    void BR_E1_PLUS::hardware_init()
    {
        /* Hold pwr pin */
        gpio_reset_pin((gpio_num_t)POWER_HOLD_PIN);
        pinMode(POWER_HOLD_PIN, OUTPUT);
        digitalWrite(POWER_HOLD_PIN, HIGH);

        Wire1.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    }

    void BR_E1_PLUS::power_off()
    {
        rtc_init();
        display->fillScreen(TFT_BLACK);
        displayUpdate();

        while ((!btnPWR.read()))
        {
            delay(100);
        }

        delay(200);

        printf("power off\n");
        digitalWrite(POWER_HOLD_PIN, 0);
        delay(10000);

        while (1)
        {
            delay(1000);
        }
    }

    void BR_E1_PLUS::setup()
    {
        hardware_init();
        key_init();
        lcd_init();


        rtc_init();
        canon_ble.init();

        bool do_pair = !btnA.read();

        if( !do_pair )
            do_pair = ( canon_ble.getPairedAddress() == BLEAddress(""));

        set_init_screen(do_pair);
    
        
        delay(500);
        // Pairing
        if(do_pair){
            // pair() function should be called only when you want to pair with the new camera. 
            // After paired, the pair() function should not be called.
            while(!canon_ble.pair(10));
            {
                Serial.println("Pairing...");
            }

        }
        delay(500);
        Serial.println("Setup Done");
        
        set_address("Not connected");
        current_mode = Video;
        timertext = "Restart (secs):";
        status = "Start Video";
        displaydelay = timelapse.get_interval();
        set_main_menu_screen();
        // lcd_init();
        //imu_init();
        //mic_init();
        //ble_init();
    }

    void BR_E1_PLUS::loop()
    {
        // rtc_wakeup_test();
        bool bConnectionState = m_bConnectionState;
        m_bConnectionState = canon_ble.isConnected();
        if( bConnectionState != m_bConnectionState )
        {
            if( m_bConnectionState )
                set_address(canon_ble.getPairedAddressString());
            else
            {
                set_address("Not connected");
                canon_ble.forceCameraConnection();
            }
            set_main_menu_screen();
        }

        if( !m_bConnectionState )
            canon_ble.forceCameraConnection();

        if( timelapse.IsRunning())
        {
            displaydelay = timelapse.get_time_to_go();
            status = "Time to Go";
            set_main_menu_screen();
        }
        //imu_test();
        //rtc_test();
        switch (current_mode)
        {
        case Settings:
            if(btnBLong.released())
            {
                current_mode = Shooting;
                status = (timelapse.get_interval()==0)?"Ready for single shot":"Ready for timelapse";
                displaydelay = timelapse.get_interval();
                timertext = "Interval (secs):";
                set_main_menu_screen();
            }
            else
            {
                update_settings();
            }
            break;
        
        case Shooting:
            if(btnBLong.released())
            {
                current_mode = Video;
                status = "Start Video";
                displaydelay = timelapse.get_interval();
                timertext = "Restart (secs):";
                timelapse.set_interval(0);
                set_main_menu_screen();
            }
            else
            {
                update_shooting();
            }
            break;
        case Video:
            if(btnBLong.released())
            {
                current_mode = Settings;
                status = "Setting interval";
                displaydelay = timelapse.get_interval();
                timertext = "Interval (secs):";
                timelapse.set_interval(0);
                set_main_menu_screen();
            }
            else
            {
                update_video();
            }
            break;

        default:
            break;
        }
        delay(10);
    }

    void BR_E1_PLUS::update_video()
    {
        // Update timelapse
        if (timelapse.TimeLapse_Trigger())
        {
            canon_ble.video();
            delay( 200 );
            canon_ble.video();
        }

        // Remote control
        if( timelapse.get_interval() == 0 ) //Single shots
        {
            if (btnA.released() /*&& !btnB.released()*/)
            {
                 if(!canon_ble.video())
                    status =  "Video Failed";
                else
                    status = "Video started";
                set_main_menu_screen();
                timelapse.set_interval((30 * 60000)-2000); //29 mins 58secs
                timelapse.Launch();
            }
        }
        else // Timelapses
        {
            // Stop or start timelapse
            if (btnA.released())
            {
                displaydelay = 0;
                status =  "Start Video";
                timelapse.Stop();
                timelapse.set_interval(0);
                set_main_menu_screen();
            }
        }
    }


    void BR_E1_PLUS::update_shooting()
    {
        // Update timelapse
        if (timelapse.TimeLapse_Trigger())
        {
            Serial.println("Trigger timelapse");
            if(!canon_ble.trigger())
            {
                Serial.println("Trigger Failed");
            }
        }

        // Remote control
        if (timelapse.get_interval() == 0) //Single shots
        {
            if (btnA.released() /*&& !btnB.released()*/)
            {
                Serial.println("Single shot");
                if(!canon_ble.trigger())
//                if(!canon_ble.video())
                    status =  "Trigger Failed";
                else
                    status = "Trigger Shutter";
                set_main_menu_screen();
            }
        }
        else // Timelapses
        {
            // Stop or start timelapse
            if (btnA.released())
            {
                if (timelapse.Recording_OnOFF())
                    status =  "Shooting timelapse";
                else
                    status =  "Ready for timelapse";
               set_main_menu_screen();
            }
        }
    }

    void BR_E1_PLUS::update_settings()
    {
        if (btnA.released())
        {
            timelapse.TimeLapse_decDelay();
            displaydelay = timelapse.get_interval();
            set_main_menu_screen();
        }
        if (btnB.released() && !btnBLong.released())
        {
            timelapse.TimeLapse_incDelay();
            displaydelay = timelapse.get_interval();
            set_main_menu_screen();
        }
    }



}
