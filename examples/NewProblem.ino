#include <glpi_esp8266.h>

//As a response to the request we will have the problem ID that must be stored in a variable, in this case, I saved it in the problemId variable so that I can send it as a parameter in the other requests.

/* As parameters we will pass:
* problem name,
* category,
* priority level,
* A brief description,
* and asset name.
*/

//opening a problem
String problemId = invasion.NewProblem("Damaged door", "IoT", 6, "The main door has been damaged", assetName);

//In order for the request information to be shown on the serial monitor, we need to activate debug mode.

//To activate debug mode we must call the object instantiated in the GlpiIot class and the Debug function, which accepts boolean values.

//activating debug mode
invasion.Debug(true);