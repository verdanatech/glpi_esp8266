#include <glpi_esp8266.h>

//As a response to the request we will have the ticket ID that must be stored in a variable, in this case, I saved it in the ticketReqId variable so that I can send it as a parameter in the other requests.

/* As parameters we will pass:
* ticket name,
* category,
* priority level,
* A brief description,
* and asset name.
*/

//opening new ticket of type request
String ticketReqId = invasion.NewTicketRequest("Change door lock", "IoT", 3, "The door lock is defective", assetName);

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);