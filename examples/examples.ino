#include <glpi_esp8266.h>

char SSID[] = "your SSID";               //network SSID
char NETKEY[] = "your password";         //network access key
char *tokenIot = "your token iot";       //token iot
char *tokenClient = "your token client"; //token client
char *assetName = "asset name";          //device name

int attempts = 50;

//creating the tokens object in the authorization class to perform API authentication
GlpiIot invasion(tokenIot, tokenClient);

void printNetworkData()
{
  /*
 * Prints the network connection data on the serial monitor
 */
  Serial.println();
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - -");
  Serial.println("Hostname: " + (String)assetName);

  Serial.println("Connected in: " + (String)SSID);

  Serial.print("My address IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - ");
}

void wifiConect()
{

  /*
 * Connect the esp8266 to the wifi network
 */

  delay(2000); //A slight delay to get the data via Serial
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, NETKEY);

  WiFi.hostname(assetName); //Setting the hostname of the LAN adapter

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    attempts--;

    if (attempts == 0)
    {
      Serial.println();
      Serial.println("Time-out. Check your settings and try again.");
      delay(1000);

      //while(true);
    }
  }
}

void setup(void)
{
  Serial.begin(115200);

  /*
 *functions to connect to the wifi network and print the network connection data on the serial monitor
 */

  wifiConect();
  printNetworkData();
  delay(2000);

  //activating debug mode
  invasion.Debug(true);

  //setting the event id for opening the new ticket of type incident
  invasion.SetEventIdInc(908);

  //setting the event id for opening the new ticket of type request
  invasion.SetEventIdReq(564);

  //setting the event id for opening the new ticket of type problem
  invasion.SetEventIdPro(7654);

  //opening new ticket of type incident
  String ticketIncId = invasion.NewTicketIncident("Damaged padlock", "IoT", 5, "The padlock has been damaged", assetName);

  //opening new ticket of type request
  String ticketReqId = invasion.NewTicketRequest("Change door lock", "IoT", 3, "The door lock is defective", assetName);

  //adding a task to the ticket
  invasion.TaskTicket(ticketIncId, "Check the padlock that was damaged", 1, 0);

  //adding a follow-up to the ticket
  invasion.FollowupTicket(ticketIncId, "Security has been notified and will proceed to the location of the lock");

  //again adding a task to the ticket
  invasion.TaskTicket(ticketIncId, "Check the padlock that was damaged", 2, 300);

  //adding a solution to the ticket
  invasion.SolutionTicket(ticketIncId, "The padlock has been changed");

  //opening a problem
  String problemId = invasion.NewProblem("Damaged door", "IoT", 6, "The main door has been damaged", assetName);

  //adding a task to the problem
  invasion.TaskProblem(problemId, "Check the door", 1, 0);

  //adding a follow-up to the problem
  invasion.FollowupProblem(problemId, "The security has been notified and must go to the property urgently");

  //again adding a follow-up to the problem
  invasion.FollowupProblem(problemId, "Sign of burglary was verified");

  //sending a solution to the problem
  invasion.SolutionProblem(problemId, "Joiner and locksmith carried out the repair of the door");
}

void loop()
{
  // put your main code here, to run repeatedly:
}