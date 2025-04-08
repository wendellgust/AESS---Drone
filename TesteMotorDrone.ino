#include <Arduino.h>
#include "hardware/pwm.h"

const uint pwmPin = 15;  // Change to your desired GPIO (e.g., 15, 16, etc.)
int speed=0;
int i;

uint slice_num, channel;

void setup() {
    // Initialize Serial for debugging (optional)
    Serial.begin(115200);
    delay(4000); // Wait for serial to stabilize
    
    // Configure PWM using Pico SDK
    gpio_set_function(pwmPin, GPIO_FUNC_PWM);  // Set GPIO to PWM function
    
    slice_num = pwm_gpio_to_slice_num(pwmPin);  // Get PWM slice
    channel = pwm_gpio_to_channel(pwmPin);      // Get channel (A or B)
    
    // Calculate for 50Hz:
    // System clock = 125MHz (125,000,000 Hz)
    // PWM frequency = sys_clock / (divider * wrap)
    // For 50Hz: 125,000,000 / (100 * 25000) = 50Hz
    pwm_set_clkdiv(slice_num, 100.0f);  // Clock divider (100.0 = slower clock)
    pwm_set_wrap(slice_num, 25000 - 1); // Wrap value (25000 cycles)
    
    // Set duty cycle (5% = 1250/25000, 1000 us)
    pwm_set_chan_level(slice_num, channel, 1250);  
    
    Serial.println("Sending 1000 us pulse");

    // Enable PWM
    pwm_set_enabled(slice_num, true);

    delay(4000);

    Serial.println("Sending 2000 us pulse");
    
    pwm_set_chan_level(slice_num, channel, 2500);

    delay(500);

    pwm_set_chan_level(slice_num, channel, 1400);

    delay(3000);
}

void loop() {
    for(i=1400; i<=2500;i+=11){
        pwm_set_chan_level(slice_num, channel, i);
        Serial.print("Duty: "); Serial.println(i);
        delay(150);
    }
    pwm_set_chan_level(slice_num, channel, 1250);
    // You can adjust duty cycle dynamically here if needed
    // Example: pwm_set_chan_level(slice_num, channel, new_duty_value);
    delay(20000);

}