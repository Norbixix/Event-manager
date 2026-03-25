# Event-manager
The Event Manager is a simple event-driven programming library designed for embedded systems and applications where events need to be scheduled and executed at specific times.
It supports event registration, scheduling, and processing, making it ideal for use in systems that need to react to various events occurring at different times, such as timers, user inputs, or external triggers.

This system allows you to register events, assign handlers to them, schedule them to run at specific times, and process them in a main loop. The library is lightweight and flexible, supporting up to 10 events simultaneously.

Features
Event Scheduling: Allows scheduling events to be triggered at specific times.
Event Registration: Registers events along with a user-defined callback handler and optional context data.
Event Processing: Executes the scheduled events' handlers when their time comes.
Dynamic Event Management: Supports the addition and removal of events dynamically.
Multiple Event Support: Can handle up to 10 events at once, suitable for small embedded systems.
Lightweight: Designed to have minimal overhead for real-time or resource-constrained systems.
Architecture

The Event Manager consists of the following core components:

1. Event Structure: Defines the event, including its scheduled time, status (scheduled or not), event handler, and context data.

2. Event Manager Functions:
- Initialization: EVENT_MANAGER_Init() initializes the event manager and clears any previous event data.
- Event Registration: EVENT_MANAGER_RegisterEvent() registers an event with a handler function and optional context.
- Event Scheduling: EVENT_MANAGER_ScheduleEvent() allows you to schedule an event at a specific time.
- Event Processing: EVENT_MANAGER_Proc() checks whether the event's scheduled time has arrived and executes its handler if it has.
- Event Unregistration: EVENT_MANAGER_UnregisterEvent() allows you to unregister an event when it is no longer needed.

3. How It Works
Event Creation: Create an event object of type Event that holds the necessary information about the event.
Event Registration: Register the event using EVENT_MANAGER_RegisterEvent(), providing a handler function that will be called when the event is triggered, and optionally some context data.
Scheduling the Event: Schedule the event using EVENT_MANAGER_ScheduleEvent(), specifying the time the event should be triggered.
Event Handling: The event manager must periodically be polled by calling EVENT_MANAGER_Proc() in the main loop of your program. This function checks for events that need to be executed and triggers their corresponding handlers.
Unregistering Events: If an event is no longer needed, it can be unregistered with EVENT_MANAGER_UnregisterEvent().
