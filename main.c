#include "hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "prcm.h"
#include "rom_map.h"
#include "utils.h"
#include "gpio_if.h"
#include "pin_mux_config.h"

static const unsigned char ExtLedUCPin = 7;
static unsigned int extLedPort;
static unsigned char extLedPin;

#if defined (ccs)
	extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
	extern uVectorEntry __vector_table;
#endif

void SYS_Init (void)
{
#if defined (ccs)
	MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
	MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif

	MAP_IntMasterEnable ();
	MAP_IntEnable (FAULT_SYSTICK);

	PRCMCC3200MCUInit();
}

/*
 * main.c
 */
int main(void) {
	
	SYS_Init();

	PinMuxConfig ();

	GPIO_IF_GetPortNPin(ExtLedUCPin,&extLedPort,&extLedPin);

	while (true)
	{
        MAP_UtilsDelay(8000000);
        GPIO_IF_Set(ExtLedUCPin,extLedPort,extLedPin,1);
        MAP_UtilsDelay(800000);
        GPIO_IF_Set(ExtLedUCPin,extLedPort,extLedPin,0);
	}

	return 0;
}
