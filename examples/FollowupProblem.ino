#include <glpi_esp8266.h>

/* To add a follow-up to a call, we need to pass the following parameters:
* problem id
* follow-up description
*/

//adding a follow-up to the problem
invasion.FollowupProblem(problemId, "The security has been notified and must go to the property urgently");

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);