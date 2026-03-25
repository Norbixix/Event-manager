#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// Maximum number of events handled by the event manager
#define MAX_NUMBER_OF_EVENTS 10

// Table of Event handles
static Event* events[MAX_NUMBER_OF_EVENTS];


void EVENT_MANAGER_Init(void) {
    memset(events, 0, sizeof(events));
}

bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
	if(event == NULL || onEvent == NULL)
	{
		return false;
	}
	
	for(uint8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if(events[i] == event){
			event->isScheduled = false;
			event->scheduledTime = 0;
			event->onEvent = onEvent;
			event->context = context;
			events[i] = event;
			return true;
		}
	}

	for(uint8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if(events[i] == NULL)
		{
			event->isScheduled = false;
			event->scheduledTime = 0;
			event->onEvent = onEvent;
			event->context = context;
			events[i] = event;
			return true;
		}
	}
	return false;
}


void EVENT_MANAGER_UnregisterEvent(Event* event) {
	if(event == NULL)
	{
		return;
	}

	for(uint8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if(events[i] == event)
		{
			events[i] = NULL;
			event->isScheduled = false;
			event->scheduledTime = 0;
			event->onEvent = NULL;
			event->context = NULL;
			return;
		}
	}
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
	if(event == NULL )
	{
		return false;
	}

		for(uint8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		if(events[i] == event)
		{
			event->isScheduled = true;
			event->scheduledTime = time;
			return true;
		}
	}
	return false;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {
	for(uint8_t i = 0; i < MAX_NUMBER_OF_EVENTS; i++)
	{
		Event* event = events[i];

		if(event != NULL && event->isScheduled && event->scheduledTime <= currentTime)
		{
			uint64_t scheduledTime = event->scheduledTime;
			OnEventHandler onEvent = event->onEvent;
			void* context = event ->context;

			event->isScheduled = false;

			if(onEvent != NULL)
			{
				onEvent(event, scheduledTime, context);
			}
		}
	}
}
