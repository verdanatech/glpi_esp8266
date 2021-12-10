#include <glpi_esp8266.h>

char SSID[] = "your SSID";               //network SSID
char NETKEY[] = "your password";         //network access key
char *tokenIot = "your token iot";       //token iot
char *tokenClient = "your token client"; //token client
char *assetName = "asset name";          //device name

int attempts = 50;

Authorization tokens(tokenIot, tokenClient); //creating the tokens object in the authorization class to perform API authentication

Tickets invasion("Damaged padlock", 1, "IoT", 4, "The padlock has been damaged", assetName); //creating an object in class tickets

Problems housebreaking("Damaged door", "IoT", 6, "The main door has been damaged", assetName); //creating an object in class problems

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
  // put your setup code here, to run once:
  Serial.begin(115200);

  /*
 *functions to connect to the wifi network and print the network connection data on the serial monitor
 */

  wifiConect();
  printNetworkData();
  delay(4000);
  invasion.NewTicket(); //opening a ticket
  delay(3000);
  invasion.TaskTicket("Check the padlock that was damaged", 1, 0); //adding a task to the ticket
  delay(3000);
  invasion.FollowupTicket("Security has been notified and will proceed to the location of the lock"); //adding a follow-up to the ticket
  delay(3000);
  invasion.TaskTicket("Check the padlock that was damaged", 2, 300); //again adding a task to the ticket
  delay(3000);
  invasion.SolutionTicket("The padlock has been changed"); //adding a solution to the ticket
  delay(3000);
  housebreaking.NewProblem(); //opening a problem
  delay(3000);
  housebreaking.TaskProblem("Check the door", 1, 0);
  delay(3000);
  housebreaking.FollowupProblem("The security has been notified and must go to the property urgently"); //adding a follow-up to the problem
  delay(3000);
  housebreaking.FollowupProblem("Sign of burglary was verified"); //again adding a follow-up to the problem
  delay(3000);
  housebreaking.SolutionProblem("Joiner and locksmith carried out the repair of the door"); //sending a solution to the problem
}
void loop()
{
  // put your main code here, to run repeatedly:
}