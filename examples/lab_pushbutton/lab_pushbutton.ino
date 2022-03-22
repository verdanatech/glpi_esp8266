#include <glpi_esp8266.h>

char SSID[] = "";               //network SSID
char NETKEY[] = "";             //network access key
char *tokenIot = "";            //your token iot
char *tokenClient = "";         //your token client
char *assetName = "";          //device name

int attempts = 50;

const int openTicket = D0;      //button in pin D0
const int followUp = D1;        //button in pin D1
const int task = D2;            //button in pin D2
const int solution = D4;        //button in pin D4
String ticketIncId;

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

void setup(void){

  Serial.begin(115200);

  pinMode(openTicket, INPUT);
  pinMode(followUp, INPUT);
  pinMode(task, INPUT);
  pinMode(solution, INPUT);

  /*
 *functions to connect to the wifi network and print the network connection data on the serial monitor
 */

  wifiConect();
  printNetworkData();
  delay(2000);

  //activating debug mode
  invasion.Debug(true);

}

void loop(){

   if (digitalRead(openTicket) == HIGH) { //If the button is pressed (HIGH)
  
      ticketIncId = invasion.NewTicketIncident("Damaged padlock", "IoT", 5, "The padlock was damaged", assetName); //opening an incident type ticket
        
  };

  if (digitalRead(followUp) == HIGH) { //If the button is pressed (HIGH)

    invasion.FollowupTicket(ticketIncId, "Security has been notified and will proceed to the lock location"); //adding a follow up on the ticket
     
  };

  if (digitalRead(task) == HIGH) { //If the button is pressed (HIGH)

    invasion.TaskTicket(ticketIncId, "Check the padlock that was damaged", 1, 0); //adding a task in the ticket
  
  };

  if (digitalRead(solution) == HIGH) { //If the button is pressed (HIGH)

    invasion.SolutionTicket(ticketIncId, "The padlock has been changed"); //adding a solution to the ticket

  };
}