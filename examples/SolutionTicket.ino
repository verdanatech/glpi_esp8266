#include <glpi_esp8266.h>

/* To add a solution to a call of type ticket we need to pass the following parameters:
* ticket id
* solution description
*/

//adding a solution to the ticket
invasion.SolutionTicket(ticketIncId, "The padlock has been changed");

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);