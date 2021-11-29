#include <glpi_esp8266.h>

char SSID[] = "your SSID";                //network SSID
char NETKEY[] = "your password";          //network access key
char *token_iot = "your token iot";       //token iot
char *token_client = "your token client"; //token client
char *asset_name = "asset name";          //device name

int attempts = 50;

authorization tokens(token_iot, token_client); //creating the tokens object in the authorization class to perform API authentication

tickets invasao("Cadeado danificado", 1, "IoT", 4, "O cadeado foi danificado", asset_name); //creating an object in class tickets

problems invasion("Porta danificada", "IoT", 6, "A porta principal foi danificada", asset_name); //creating an object in class problems

void printNetworkData()
{
  /*
 * Prints the network connection data on the serial monitor
 */
  Serial.println();
  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - -");
  Serial.println("Hostname: " + (String)asset_name);

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

  WiFi.hostname(asset_name); //Setting the hostname of the LAN adapter

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
  invasao.new_ticket(); //opening a ticket
  delay(3000);
  invasao.task_ticket("Verificar o cadeado que foi danificado", 1, 0); //adding a task to the ticket
  delay(3000);
  invasao.followup_ticket("O segurança foi notificado e irá se dirigir até a localização do cadeado"); //adding a follow-up to the ticket
  delay(3000);
  invasao.task_ticket("Verificar o cadeado que foi danificado", 2, 300); //again adding a task to the ticket
  delay(3000);
  invasao.solution_ticket("O cadeado foi trocado"); //adding a solution to the ticket
  delay(3000);
  invasion.new_problem(); //opening a problem
  delay(3000);
  invasion.followup_problem("O vigilante foi notificado e deverá se digigir com urgência até o imóvel"); //adding a follow-up to the problem
  delay(3000);
  invasion.followup_problem("Foi verificado sinal de arrombamento"); //again adding a follow-up to the problem
  delay(3000);
  invasion.solution_problem("Marceneiro e chaveiro realizaram o conserto da porta"); //sending a solution to the problem
}
void loop()
{
  // put your main code here, to run repeatedly:
}