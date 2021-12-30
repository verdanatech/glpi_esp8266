#include <glpi_esp8266.h>

/* To send a task to GLPi we need to pass the following parameters:
* problem id
* task description
* task status (can be 1 or 2) 1 for tasks that need to be done and 2 for tasks already done
* and the time to perform the task (time is passed in seconds)
*/

//adding a task to the problem

//To send a task to a problem, I used the variable that takes the problem id as a parameter.
invasion.TaskProblem(problemId, "Check the door", 1, 0);

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);