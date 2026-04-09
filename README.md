Event Manager Description

The Event Manager is a simple event-driven programming library designed for embedded systems and applications where events need to be scheduled and executed at specific times. It supports event registration, scheduling, and processing, making it suitable for systems that need to react to timers, user inputs, or external triggers.

This system allows you to register events, assign handlers to them, schedule them to run at specific times, and process them in the main loop. The library is lightweight and flexible, using a singly linked list to store registered events. This allows events to be added and removed dynamically during runtime without relying on a fixed-size array.

Features:
  Event Scheduling: Allows scheduling events to be triggered at specific times.
  Event Registration: Registers events together with a user-defined callback handler and optional context data.
  Event Processing: Executes scheduled event handlers when their time comes.
  Dynamic Event Management: Supports the addition and removal of events during runtime.
  Linked List-Based Storage: Events are stored in a singly linked list, allowing flexible event management.
  Lightweight: Designed to have minimal overhead for real-time or resource-constrained systems.
  Simple Integration: Can be easily integrated into embedded applications using a polling-based main loop.

Architecture
The Event Manager consists of the following core components:

Event Structure
The Event structure defines a single event and contains the following fields:
  isScheduled – indicates whether the event is currently scheduled,
  scheduledTime – stores the time at which the event should be executed,
  onEvent – pointer to the callback function that will be executed,
  context – optional pointer to user-defined data associated with the event,
  next – pointer to the next event in the linked list.
  Event Manager Functions
  Initialization: EVENT_MANAGER_Init() initializes the event manager and clears all previously registered events.
  Event Registration: EVENT_MANAGER_RegisterEvent() registers an event together with its handler function and optional context data.
  Event Scheduling: EVENT_MANAGER_ScheduleEvent() allows a registered event to be scheduled for execution at a specified time.
  Event Processing: EVENT_MANAGER_Proc() checks all registered events and executes the handlers of those whose scheduled time has been reached.
  Event Unregistration: EVENT_MANAGER_UnregisterEvent() removes an event from the manager when it is no longer needed.

How It Works
1. Event Creation
An event object of type Event is created by the user. This object stores all information required to manage and execute the event.

2. Event Registration
The event is registered using EVENT_MANAGER_RegisterEvent(), which adds it to the internal singly linked list maintained by the event manager. During registration, the user provides:
  a pointer to the event object,
  a callback handler function,
  optional context data.

4. Scheduling the Event
Once registered, the event can be scheduled using EVENT_MANAGER_ScheduleEvent(). This function assigns the execution time to the event and marks it as scheduled.

5. Event Processing
The event manager must be periodically polled by calling EVENT_MANAGER_Proc() inside the main loop of the application. This function traverses the linked list of registered events and checks whether any scheduled event should be executed.

If the scheduled time of an event is less than or equal to the current time:
  the event is marked as no longer scheduled,
  its callback handler is called,
  the event object, scheduled time, and user context are passed to the handler.

5. Unregistering Events
If an event is no longer needed, it can be removed from the manager using EVENT_MANAGER_UnregisterEvent(). The event is then detached from the linked list and will no longer be processed.

Summary
The Event Manager provides a simple and efficient way to implement event-driven behavior in embedded systems. Its linked list-based design allows flexible runtime event management, while its polling-based processing model keeps the implementation lightweight and easy to integrate into small applications.

It is particularly useful in systems where actions must be executed at specific times without relying on a full operating system or advanced scheduling mechanisms.
