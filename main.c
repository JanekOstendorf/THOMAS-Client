/*
 * CLIENT
 */

/** INCLUDES **/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <linux/ioctl.h>
#include <linux/joystick.h>

/** DEFINES **/
#define JOY_DEV "/dev/input/js0"
#define NO_POWER_ZONE 10

#define DEBUG 0

int left = 0, right = 0, end = 0;
int rs232 = 0;


/**
 * Hauptfunktion
 * @return 
 */
int main(void) {

	int joy_fd, axis[4] = {1,2,3,-4}, num_of_axis = 0, num_of_buttons = 0;
	char button[9] = {}, name_of_joystick[80];
	struct js_event js;

	if((joy_fd = open(JOY_DEV, O_RDONLY | O_NDELAY)) == -1) {
		printf("Konnte Joystick nicht oeffnen!\n");
		return -1;
	}

	ioctl(joy_fd, JSIOCGAXES, &num_of_axis);
	ioctl(joy_fd, JSIOCGBUTTONS, &num_of_buttons);
	ioctl(joy_fd, JSIOCGNAME(80), &name_of_joystick);

	if(DEBUG)
            printf(
                    "Joystick gefunden: %s\n\t%d Axen\n\t%d Buttons\n\n",
                    name_of_joystick,
                    num_of_axis,
                    num_of_buttons
            );

	fcntl(joy_fd, F_SETFL, O_NONBLOCK); // use non-blocking mode 
        
	while(1)
	{

		// read the joystick state
		read(joy_fd, &js, sizeof(struct js_event));

		// see what to do with the event
		switch(js.type & ~JS_EVENT_INIT)
		{
			case JS_EVENT_AXIS:
				axis[js.number] = js.value;
				break;
			case JS_EVENT_BUTTON:
				button[js.number] = js.value;
				break;
		}
                
                // Abbruch?
		if(button[6] != 0) { 
                    
                    
                    break;
                    
		}
                
                socket_send_js(axis, button);
                
                usleep(5000);
       
        
	} // while
    
} // main

