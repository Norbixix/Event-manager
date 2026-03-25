#include "event_manager.h"
#include "event_manager.c"
#include <stdio.h>
// EXAMPLE.C - Example usage of the Event Manager

// Example event handler function
void MyEventHandler(struct Event* event, uint64_t scheduledTime, void* context) {
    // This function will be called when the event is triggered
    printf("Event triggered at time: %llu\n", scheduledTime);
}

int main() {
    // Initialize the event manager
    EVENT_MANAGER_Init();

    // Create a new event
    Event myEvent;

    // Register the event with a callback function and context (NULL in this case)
    if (EVENT_MANAGER_RegisterEvent(&myEvent, MyEventHandler, NULL)) {
        printf("Event registered successfully.\n");
    }

    // Schedule the event to be triggered at time 1000
    if (EVENT_MANAGER_ScheduleEvent(&myEvent, 1000)) {
        printf("Event scheduled at time 1000.\n");
    }

    // Main loop: process events and trigger handlers if needed
    while (1) {
        uint64_t currentTime = get_current_time(); // Get the current time from your system
        EVENT_MANAGER_Proc(currentTime); // Process events
    }

    return 0;
}