#include "event_manager.h"
#include <stddef.h>
#include <stdbool.h>

// Table of Event handles
static Event* head = NULL;

void EVENT_MANAGER_Init(void) {
    head = NULL;
}


bool EVENT_MANAGER_RegisterEvent(Event* event, OnEventHandler onEvent, void* context) {
	if(event == NULL || onEvent == NULL)
	{
		return false;
	}
	
	Event* current = head;

	if(current == NULL)
	{
		head = event;
		event->next = NULL;
	}
	else
	{
		while(current->next != NULL)
		{
			current = current->next;
		}

		current->next = event;
		event->next = NULL;
	}

	event->isScheduled = false;
	event->scheduledTime = 0;
	event->onEvent = onEvent;
	event->context = context;
	
	return true;
}


void EVENT_MANAGER_UnregisterEvent(Event* event) {
	if(event == NULL)
	{
		return;
	}

	Event* current = head;
	Event* previous = NULL;

	while(current != NULL)
	{
		if(current == event)
		{
			if(previous == NULL)
			{
				head = current->next;
			}
			else
			{
				previous->next = current->next;
			}
		}
		previous = current;
		current = current->next;
	}
}


bool EVENT_MANAGER_ScheduleEvent(Event* event, uint64_t time) {
	if(event == NULL)
	{
		return false;
	}

	Event* current = head;

	while(current != NULL)
	{
		if(current == event)
		{
			event->isScheduled = true;
			event->scheduledTime = time;
			return true;
		}
		current = current->next;
	}
	return false;
}


void EVENT_MANAGER_Proc(uint64_t currentTime) {

	Event* current = head;

	while(current != NULL)
	{
		if(current != NULL && current->isScheduled && current->scheduledTime <= currentTime)
		{
			uint64_t scheduledTime = current->scheduledTime;
			OnEventHandler onEvent = current->onEvent;
			void* context = current ->context;
			current->isScheduled = false;

			if(onEvent != NULL)
			{
				onEvent(current, scheduledTime, context);
			}
		}
		current = current->next;
	}
}
