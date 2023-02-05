//Room NO.
#define Room1 '1'
#define Room2 '2'
#define Room3 '3'
#define Room4 '4'
#define Room5 '5'

//DIR
#define LED_1_DIR DDRB
#define LED_2_DIR DDRB
#define LED_3_DIR DDRC
#define LED_4_DIR DDRC
#define LED_5_DIR DDRD

#define BUZZER_DIR DDRD

#define DIMMER_DIR DDRB

//LED Status
#define ON '1'
#define OFF '0'

//Blink Time
#define LED_BLINK_T 500

//FUNCTIONS
void LED_STAT(unsigned char status,unsigned char R_Num);
void Alarm_On ();
void DIMMER_CONTROL(unsigned char level);
void LED_START();
void BUZZER_START();
void DIMMER_Init();



//Values for mapping [Dimmer]
#define MAX 255
#define maxPercent 100

#define LEVEL0_PERCENT 0
#define LEVEL1_PERCENT 25 
#define LEVEL2_PERCENT 50
#define LEVEL3_PERCENT 75
#define LEVEL4_PERCENT 100

#define LEVEL0 '0'
#define LEVEL1 '1'
#define LEVEL2 '2'
#define LEVEL3 '3'
#define LEVEL4 '4'