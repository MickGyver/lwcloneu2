
#ifndef LEDWIZ_H__INCLUDED
#define LEDWIZ_H__INCLUDED


#if defined(_MSC_VER)

#define LWZCALL __cdecl		// this is what the 'original' ledwiz.dll uses
#define LWZCALLBACK __stdcall

#if (_MSC_VER >= 1600) // starting with VisualStudio 2010 stdint.h is available
#include <stdint.h>
#else
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#endif

#else

#include <stdint.h>
#define LWZCALL
#define LWZCALLBACK

#endif


#ifdef __cplusplus
extern "C" {
#endif


#define LWZ_MAX_DEVICES 16

typedef enum {
	LWZ_REASON_ADD     = 1,
	LWZ_REASON_DELETE  = 2,
} LWZ_NOTIFY_REASON;


typedef int32_t LWZHANDLE;


typedef struct {
	LWZHANDLE handles[LWZ_MAX_DEVICES];
	int32_t numdevices;
} LWZDEVICELIST;


/************************************************************************************************************************
LWZ_SBA - All Outputs State plus Global Pulse Speed
*************************************************************************************************************************
handle is an idetifier for a specific LED-WIZ device
Values bank0, bank1, bank2, and bank3 equal 8-bit representations of on/off states for banks 1-4. 
Value globalPulseSpeed equals Global Pulse Speed setting (1 through 7).
************************************************************************************************************************/

void LWZCALL LWZ_SBA(
	LWZHANDLE hlwz, 
	unsigned int bank0, 
	unsigned int bank1,
	unsigned int bank2,
	unsigned int bank3,
	unsigned int globalPulseSpeed);


/************************************************************************************************************************
LWZ_PBA - All Outputs Profile Settings (Most Efficient): 
*************************************************************************************************************************
handle is an idetifier for a specific LED-WIZ device
Each of the 32 parameters coincide with outputs 1-32. A value of 1 to 48 sets the brightness of each LED using PWM. 
A value of 129-132 indicates an automated pulse mode as follows:
129 = Ramp Up / Ramp Down
130 = On / Off
131 = On / Ramp Down
132 = Ramp Up / On
The speed is contolled by the Global Pulse Speed parameter.
************************************************************************************************************************/

void LWZCALL LWZ_PBA(LWZHANDLE hlwz, uint8_t const *pmode32bytes);


/************************************************************************************************************************
LWZ_REGISTER - Register device for plug and play
*************************************************************************************************************************
This must be called with the hwnd that an application uses to process windows messages. 
This associates a device with a window message queue so the your application can be notified of plug/unplug events.
In order to unregister, call with hwnd == NULL.
You have to unregister if the library was manually loaded and then is going to be freed with FreeLibrary() while
the window still exists.
************************************************************************************************************************/

void LWZCALL LWZ_REGISTER(LWZHANDLE hlwz, HWND hwnd);


/************************************************************************************************************************
LWZ_SET_NOTIFY - Set notifcation mechanisms for plug/unplug events
LWZ_SET_NOTIFY_EX - same as LWZ_SET_NOTIFY, but provides a user defined pointer in the callback
*************************************************************************************************************************
Set a notification callback for plug/unplug events. 
It searches for all connected LED-WIZ devices and then calls the notify callback for it.
The callback will come back directly from this call or later from the windows procedure thread of the caller,
that is as long as you do your stuff from the same windows procedure there will be no need for thread synchronization. 
At the same time the notification procedure is called, the LWZDEVICELIST
will be updated with any new device handles that are required.
This function is also used to set a pointer to your applications device list. 
************************************************************************************************************************/

typedef void (LWZCALLBACK * LWZNOTIFYPROC)(int32_t reason, LWZHANDLE hlwz);
typedef void (LWZCALLBACK * LWZNOTIFYPROC_EX)(void *puser, int32_t reason, LWZHANDLE hlwz);

void LWZCALL LWZ_SET_NOTIFY(LWZNOTIFYPROC notify_callback, LWZDEVICELIST *plist);
void LWZCALL LWZ_SET_NOTIFY_EX(LWZNOTIFYPROC_EX notify_ex_callback, void *puser, LWZDEVICELIST *plist);


/************************************************************************************************************************
LWZ_RAWWRITE - write raw data to the device
*************************************************************************************************************************
return number of bytes written.
************************************************************************************************************************/

uint32_t LWZ_RAWWRITE(LWZHANDLE hlwz, uint8_t const *pdata, uint32_t ndata);

/************************************************************************************************************************
LWZ_RAWREAD - read raw data from the device
*************************************************************************************************************************
return number of bytes read.
************************************************************************************************************************/

uint32_t LWZ_RAWREAD(LWZHANDLE hlwz, uint8_t *pdata, uint32_t ndata);


#ifdef __cplusplus
}
#endif

#endif
