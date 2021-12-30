#include <glpi_esp8266.h>

/* To add a solution to a call of type problem we need to pass the following parameters:
* problem id
* solution description
*/

//sending a solution to the problem
invasion.SolutionProblem(problemId, "Joiner and locksmith carried out the repair of the door");

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);