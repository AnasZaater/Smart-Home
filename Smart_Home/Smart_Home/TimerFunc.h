// Wave Generation Mode
#define Normal '0'
#define PWM_Phase_Correct '1'
#define PWM_Fast '2'

// Compare Output Match Mode
#define COM_OFF '0'
#define COM_Toggle '1'
#define COM_Clear '2' //--> non-inverting - PWM
#define COM_Set '3'	 //-->  inverting - PWM

// Prescaler 
#define fclkOFF '0'
#define fclk0 '1'
#define fclk8 '2'
#define fclk64 '3'
#define fclk256 '4'
#define fclk1024 '5'

void Timer(char timerNum,char Mode,char COM,char Prescaler);
