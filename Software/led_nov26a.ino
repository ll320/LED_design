// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN 2
#define PWM_LED_OUT 11
#define PWM_MAX 255

// global variables representing "state" across all functions
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool BUTTON_PUSHED = false;
int previous_button_state = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {

   attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pushed, RISING);
   pinMode(PWM_LED_OUT, OUTPUT);
   // define output (PWM) pin connected to LED
   Serial.begin(9600);

}

// continually-running loop
// calls functions that are named as "actions"
void loop(){
    
    check_button_press();

    set_pwm_based_on_operating_mode();

    shine_led();

}

void set_pwm_based_on_operating_mode() {

    switch (operating_mode) {
        case 0:
        Serial.println('0');
            PWM_OUT = 0;
            break;
        case 1:
        Serial.println('1');
            PWM_OUT = PWM_MAX;
            break;
        case 2:
        Serial.println('2');
            PWM_OUT = (PWM_MAX/2);
            break;
        case 3:
        Serial.println('3');
            PWM_OUT = (PWM_MAX/4);
            break;
        case 4:
        Serial.println('4');
            flash_the_light();
            break;
    }

}

void button_pushed() {
    BUTTON_PUSHED = true;
}

void flash_the_light() {
    digitalWrite(PWM_LED_OUT, HIGH);
    delay(500);
    digitalWrite(PWM_LED_OUT,LOW);
    delay(500);
    
      
}

void shine_led() {
    analogWrite(PWM_LED_OUT, PWM_OUT);
}

void check_button_press() {
    if (BUTTON_PUSHED == true) {
      delay(500);
        operating_mode = operating_mode + 1;
        if (operating_mode == 5) {
            operating_mode = 0;
        }
    }

    BUTTON_PUSHED = false;
}
