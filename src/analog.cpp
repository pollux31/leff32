#include "analog.h"
#include "led.h"

#define ADC2_4_PIN 13

#define DEFAULT_LEVEL 2300  // no noise value
#define NOISE 150           // noise value

ExponentialFilter ADCfilter(50, 0);

// handle to tasks
TaskHandle_t hTaskAnalog;

// define tasks 
void TaskAnalog(void *pvParameters);

void SetupAnalog()
{
    // Create the default task
    xTaskCreatePinnedToCore(
        TaskAnalog,
        "Analog",
        2048,       //stack size
        NULL,       // Task parameter
        3,          // Task priority from 0 (lowest) to 3
        &hTaskAnalog, // Created task handle return value (TaskHandle_t xHandle or NULL)
        1           // Display need to run in Core 1 !!!
    );

}

/*--------------------------------------------------*/
/*                       Tasks                      */
/*--------------------------------------------------*/

//---------------------------------------------------------------
void TaskAnalog(void *pvParameters)
{
    
    int min = 4095;
    int max = 0;
    int level = 0;

    while (1)
    {
        int reading = analogRead(ADC2_4_PIN);
        
        if (reading < min)
        {
            min = reading;
            Serial.printf("min: %d, max: %d, delta: %d\n", min, max, max - min);
        }
        if (reading > max)
        {
            max = reading;
            Serial.printf("min: %d, max: %d, delta: %d\n", min, max, max - min);
        }   

        // Read the ADC value
        reading = abs(reading - DEFAULT_LEVEL);
        //reading = (reading > NOISE) ? reading : 0;
        ADCfilter.Filter(reading);
        level = ADCfilter.Current();
        SetLedLevel(level);
        //Serial.printf("Reading: %d, Level: %d\n", reading, level);
        
        //float voltage = ((float)reading / 4095.0) * 5;
        //Serial.printf("ADC2_4_PIN: %d, voltage: %f\n", reading, voltage);

        // Wait 100 ms
        vTaskDelay(100 / portTICK_PERIOD_MS);

    } // End infinit loop
}

