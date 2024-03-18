#include "analog.h"

int vref = 1100;

// handle to tasks
TaskHandle_t hTaskAnalog;

// define tasks 
void TaskAnalog(void *pvParameters);


void SetupAnalog()
{
    /*
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_2, (adc_atten_t)ADC2_CHANNEL_4, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
    //Check type of calibration value used to characterize ADC
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
        vref = adc_chars.vref;
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
    } else {
        Serial.println("Default Vref: 1100mV");
    }
    */

    // Create the default task
    xTaskCreatePinnedToCore(
        TaskAnalog,
        "Analog",
        4096,       //stack size
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
    while (1)
    {
        uint16_t v = analogRead(ADC2_4_PIN);
        float voltage = ((float)v / 4095.0) * 5;
        // Serial.printf("ADC2_4_PIN: %d, voltage: %f\n", v, voltage);

        // Wait 1000ms
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    } // End infinit loop
}
