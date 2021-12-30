#include <glpi_esp8266.h>

/* To add a follow-up to a call, we need to pass the following parameters:
* ticket id
* follow-up description
*/

//adding a follow-up to the ticket
invasion.FollowupTicket(ticketIncId, "Security has been notified and will proceed to the location of the lock");

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);