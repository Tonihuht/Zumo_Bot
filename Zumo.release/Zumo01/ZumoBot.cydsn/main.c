#include <project.h>
#include <stdio.h>
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "I2C_made.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "IR.h"
#include "Ambient.h"
#include "Beep.h"

int rread(void);

int main()
{
    struct sensors_ ref;
    struct sensors_ dig;
    CyGlobalIntEnable; 
    UART_1_Start();
    ADC_Battery_Start(); 
    sensor_isr_StartEx(sensor_isr_handler);
    
    reflectance_start();
    IR_led_Write(1);
    int16 adcresult =0;
    motor_start();
    
    //Luodaan muuttujat pysähtymeselle ja napille
    int stop = 0;
    int button = SW1_Read();
    //Laittaa ledin päälle 
    BatteryLed_Write(1);
    //Odottaa käyttäjän napin painallusta
    while(button == 1) {
        button = SW1_Read();    
    }
    //Viivalle ajo ja ...
    reflectance_read(&ref);
    while(ref.l3 < 20000 || ref.l1 < 20000 || ref.r3 < 20000 || ref.r1 < 20000){
        motor_forward(100,1);
        reflectance_read(&ref);
    }
    for(;;)
    {
        //... sille pysähtyminen
        motor_forward(0,1);
        //Odottaa käyttäjän kaukosäätimen napin painallusta liikkeelle lähtö varten
        get_IR();
        //Ajo ohjelma alkaa
        while(1) {
            
            reflectance_read(&ref);
            
            //Jyrkkä vasen
            while(ref.l3 >= 9000) {
                motor_turn(10,255,1);
                reflectance_read(&ref);
                //Hätäkäännös, jyrkempi vasen jos robotti tippuu radalta
                while (ref.l3 < 9000 && ref.l1 < 8000 && ref.r3 < 11000 && ref.r1 < 9000){
                    motor_turn(6,255,1);
                    reflectance_read(&ref);
                }
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Jyrkkä Oikea
            while(ref.r3 >= 11000) {
                motor_turn(255,10,1);
                reflectance_read(&ref);
                //Hätäkäännös, jyrkempi oikea jos robotti tippuu radalta
                while (ref.l3 < 9000 && ref.l1 < 8000 && ref.r3 < 11000 && ref.r1 < 9000){
                    motor_turn(255,6,1);
                    reflectance_read (&ref);
                }
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            //Semi jyrkkä vasen 1
            while(ref.l3 >= 9000 && ref.l1 >= 8000){
                motor_turn(65,255,1);
                reflectance_read(&ref);
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Semi jyrkkä oikea 1
            while(ref.r3 >= 11000 && ref.r1 >= 9000){
                motor_turn(255,65,1);
                reflectance_read(&ref);
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Semi jyrkkä vasen 2
            while(ref.l3 >= 9000 && ref.l1 >= 8000 && ref.r1 >= 9000){
                motor_turn(55,255,1);
                reflectance_read(&ref);
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Semi jyrkkä oikea 2
            while(ref.r3 >= 11000 && ref.r1 >= 9000 && ref.l1 >= 8000){
                motor_turn(255,55,1);
                reflectance_read(&ref);
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Suoraan
            while(ref.r1 >= 9000 && ref.l1 >= 8000 && ref.r3 < 11000 && ref.l3 < 9000) {
                motor_forward(255,0); 
                reflectance_read(&ref);
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Loiva oikea
            while(ref.r1 >= 9000) {
                motor_turn(255,200,0);
                reflectance_read(&ref);
                //Loivan vasemman tippuessa radalta niin että kaikki sensorit näkevät valkoista, pieni korjausliike jotta päätään takaisin radalle
                while(ref.l3 < 9000 && ref.l1 < 8000 && ref.r1 < 9000 && ref.r3 < 11000){
                    motor_turn(255,120,0);
                    reflectance_read(&ref);
                }
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
            
            //Loiva vasen
            while(ref.l1 >= 8000) {
                motor_turn(200,255,0);
                reflectance_read(&ref);
                //Loivan oikean tippuessa radalta niin että kaikki sensorit näkevät valkoista, pieni korjausliike jotta päätään takaisin radalle
                while(ref.l3 < 9000 && ref.l1 < 8000 && ref.r1 < 9000 && ref.r3 < 11000){
                    motor_turn(120,255,0);
                    reflectance_read(&ref);
                }
                //Tarkistaa jos kaikki sensorit mustalla ja lisää stop muuttujaan yhden, jos stop enemmän kuin 2 niin pysäyttää mootorit
                if(ref.l3 >= 20000 && ref.l1 >= 20000 && ref.r3 >= 20000 && ref.r1 >= 20000) {
                    stop++; 
                    if(stop>2){
                        motor_stop();
                    }
                    CyDelay(50);
                }
            }
        }
    }
 }   

#if 0
int rread(void)
{
    SC0_SetDriveMode(PIN_DM_STRONG);
    SC0_Write(1);
    CyDelayUs(10);
    SC0_SetDriveMode(PIN_DM_DIG_HIZ);
    Timer_1_Start();
    uint16_t start = Timer_1_ReadCounter();
    uint16_t end = 0;
    while(!(Timer_1_ReadStatusRegister() & Timer_1_STATUS_TC)) {
        if(SC0_Read() == 0 && end == 0) {
            end = Timer_1_ReadCounter();
        }
    }
    Timer_1_Stop();
    
    return (start - end);
}
#endif

/* Don't remove the functions below */
int _write(int file, char *ptr, int len)
{
    (void)file; /* Parameter is not used, suppress unused argument warning */
	int n;
	for(n = 0; n < len; n++) {
        if(*ptr == '\n') UART_1_PutChar('\r');
		UART_1_PutChar(*ptr++);
	}
	return len;
}

int _read (int file, char *ptr, int count)
{
    int chs = 0;
    char ch;
 
    (void)file; /* Parameter is not used, suppress unused argument warning */
    while(count > 0) {
        ch = UART_1_GetChar();
        if(ch != 0) {
            UART_1_PutChar(ch);
            chs++;
            if(ch == '\r') {
                ch = '\n';
                UART_1_PutChar(ch);
            }
            *ptr++ = ch;
            count--;
            if(ch == '\n') break;
        }
    }
    return chs;
}
/* [] END OF FILE */
