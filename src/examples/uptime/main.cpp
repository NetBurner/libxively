
/*
* This example will create a Task the perpetually sends the uptime, in seconds,
* of the current device.
*
* Before running this application, you need to
* register for a Developer Account with Xively. Once you register, you will be
* provided with an API key. Paste the API key to the define below. You will also
* need to create a new feed to get a feed id. Paste the feed id (9 digit number)
* in to the FEED_ID defined below
*/


#include <predef.h>
#include <init.h>

#include <ucos.h>
#include <ucosmcfc.h>
#include <constants.h>
#include <utils.h>

#include <xively.h>
#include <xi_helpers.h>
#include <xi_err.h>

// TODO:
// Uncomment these lines and change the values to the API_KEY and FEED_ID
// provided by Xively

// #define API_KEY     "longstring"
// #define FEED_ID     123456789

#ifndef API_KEY
#error API_KEY is not provided. See comments in main.cpp
#endif

const char * AppName="XivelyUptime";


void updateXively(void *) {
    xi_context_t* xi_context = xi_create_context(XI_TCP, API_KEY, FEED_ID);

    while (1) {
        if (xi_context != 0) {
            xi_datapoint_t uptime;

            xi_set_value_i32(&uptime, Secs);

            // Set to 0, this will set the server to use its time of rx
            uptime.timestamp.timestamp = 0;

            // Send uptime to Xively
            xi_datastream_update(xi_context, FEED_ID, "uptime", &uptime);

        }
        // Update at 30 second intervals
        OSTimeDly(30*TICKS_PER_SECOND);
    }

    xi_delete_context(xi_context); // Will never be called, since this task never ends
}


extern "C" void UserMain(void * pd) {
    init();
    iprintf("Application started\n");

    OSSimpleTaskCreatewName(updateXively,MAIN_PRIO-1,"Xively");

    while (1) {
        OSTimeDly(TICKS_PER_SECOND);
    }
}
