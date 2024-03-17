#define ARDUINO_RUNNING_CORE 1

#include "main.h"
#include "n31-40.xbm"
#include "analog.h"

// define tasks 
void TaskMain(void *pvParameters);

// Definition
SSD1306Wire display = SSD1306Wire(0x3c, SDA, SCL);

// handle to tasks
TaskHandle_t hTaskMain;

void splash()
{
    // splash screen
    display.setContrast(255);
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.clear();
    display.drawXbm((128 - n31_width) / 2, 1, n31_width, n31_height, n31_bits);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 45, "- Nicot31 -");
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.display();
}

//----------------------------------------------------------------------------
// the setup function runs once when you press reset or power the board
//----------------------------------------------------------------------------
void setup()
{
    // initialize serial communication at 115200 bits per second:
    Serial.begin(115200);

    // Init the display
    display.init();
    Wire.setClock(400000);

    // show the splash screen
    splash();
    Serial.println("\n");

    // Analog setup
    SetupAnalog();

    // Create the default task
    xTaskCreatePinnedToCore(
        TaskMain,
        "Main",
        4096,       //stack size
        NULL,       // Task parameter
        3,          // Task priority from 0 (lowest) to 3
        &hTaskMain, // Created task handle return value (TaskHandle_t xHandle or NULL)
        1           // Display need to run in Core 1 !!!
    );

    // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
    // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*                       Tasks                      */
/*--------------------------------------------------*/

//---------------------------------------------------------------
void TaskMain(void *pvParameters) // This is a task.
{
    int state = 0;

    while (1)
    {


        // Wait 1000ms
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    } // End infinit loop
}
