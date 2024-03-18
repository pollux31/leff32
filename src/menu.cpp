#include <arduino.h>
#include "menu.h"

// Store the menu number
int menuNumber = 0;

// handle to tasks
TaskHandle_t hTaskMenu;

// define tasks 
void TaskMenu(void *pvParameters);


// structure of the menu
typedef struct
{
    const char *text;   // Text for the entry
    void (*function)();  // Function to call that returns the number of the next menu
}  MenuEntryType;

// structure of the list of menu
typedef struct
{
    MenuEntryType *entries; // Text for the entry
    int nbItems;            // Number of items
} MenuType;


// List of Menu functions
extern void DisplayConfigMenu(); 
extern void DisplayNetworkMenu(); 


MenuEntryType menuConfig[] = {
    {"Réseau", DisplayNetworkMenu},
    {"Niveaux Audio", NULL},
};

MenuEntryType menuReseau[] = {
    {"Option 11", NULL},
    {"Option 12", NULL},
    {"Option 13", NULL},
    {"Retour", DisplayConfigMenu},
};

MenuType menuList[] = {
    {menuConfig, sizeof(menuConfig) / sizeof(MenuEntryType)},   // Menu 0
    {menuReseau, sizeof(menuReseau) / sizeof(MenuEntryType)},   // Menu 1
};


void SetupMenu()
{
    // Create the task
    xTaskCreatePinnedToCore(
        TaskMenu,
        "Menu",
        4096,       //stack size
        NULL,       // Task parameter
        3,          // Task priority from 0 (lowest) to 3
        &hTaskMenu, // Created task handle return value (TaskHandle_t xHandle or NULL)
        1           // Display need to run in Core 1 !!!
    );

}

/*--------------------------------------------------*/
/*                       Tasks                      */
/*--------------------------------------------------*/

//---------------------------------------------------------------
void TaskMenu(void *pvParameters)
{
    while (1)
    {
        displayMenu();
        vTaskDelay(100 / portTICK_PERIOD_MS);

    } // End infinit loop
}




// Diplay the menu and return the number of the net Menu
void displayMenu() {
    char rep;
    int choice;
    int nbItems = 0;
    int nbMenu = sizeof(menuList) / sizeof(MenuEntryType);

    if ((menuNumber < 0) or (menuNumber >= nbMenu)) {
        Serial.printf("\nNuméro de Menu invalide : %d\n", menuNumber);
    } else {
        // display the menu
        MenuEntryType *menu = menuList[menuNumber].entries;    // The menu
        nbItems = menuList[menuNumber].nbItems;            // Number of items
        
        Serial.println();
        for (int j = 0; j < nbItems; j++) {
            Serial.printf("%d. %s\n", j, menu[j].text);
        }
   
        // get the choice
        Serial.print("Veuillez saisir votre choix: ");
        do {
            // loop if timeout
            Serial.readBytes(&rep, 1);
            choice = rep - '0';
        } while (choice < 0);
        
        if (choice > nbItems) {
            Serial.printf("\nChoix invalide : %d\n", choice);
        } else {
            Serial.printf("%d\n", choice);
            if (menu[choice].function != NULL) {
                menu[choice].function();
            } 
        }
    }
}

void DisplayConfigMenu() {
    menuNumber = 0;
}

void DisplayNetworkMenu() {
    menuNumber = 1;
} 
