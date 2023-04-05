# stm32f4-lwip-pppos

# DISPOSITIVO:
 - Microcontrollore + Modulo 4G
 - Connettività TCP/IP usando PPPoS
 - Fisico: UART
 
# PIATTAFORMA:
 - STM32 F4 DISCOVERY - MB997-B-00(02)
 - NEXUS/4G ATQ1 - Isolando il modulo EC25-EUX
   FW dedicato che accende il modulo in modalità EVB
	e mette i segnali MODEM in ingresso alta impedenza
 - DEBUGGER ST-Link + SWO

# FIRMWARE:
 - FreeRTOS
 - LwIP per PPPoS
 - SDK CubeMX (librerie ST)

# TOOL
 - Gerber Viewer: gerbv - http://gerbv.geda-project.org/
 - STM32 CubeIDE
 