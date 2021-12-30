#include <glpi_esp8266.h>

char SSID[] = "your SSID";               //network SSID
char NETKEY[] = "your password";         //network access key
char *tokenIot = "your token iot";       //token iot
char *tokenClient = "your token client"; //token client
char *assetName = "asset name";          //device name

int attempts = 50;

//Before instantiating the object using our GlpiIot class you must make the necessary internet connections so that you can make the requests.

//Instantiate the object by passing the tokenIot and the tokenClient, both available on the verdanatech portal.
GlpiIot invasion(tokenIot, tokenClient);