#include <glpi_esp8266.h>

char *HOSTNAME = "verdanadeskIoT"; //Hostname do equipamento na Rede LAN
char SSID[] = "...";               //SSID da rede
char NETKEY[] = "...";             //Chave de acesso a rede

int tentativas = 50;

void printNetworkData()
{

  Serial.println();
  Serial.println("- - - - - - - -");
  Serial.println("Hostname: " + (String)HOSTNAME);

  Serial.println("Conectado em: " + (String)SSID);

  Serial.print("Meu endereço IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  // Serial.println(WiFi.macAddress());

  Serial.println("- - - - - - - -");
}

void wifiConect()
{

  /*
 * Realiza a conexão da esp8266 com a rede wifi
 */

  delay(2000); //Um pequeno atraso para conseguir pegar os dados via Serial
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, NETKEY);

  // Definindo hostname da placa para LAN
  //  WiFi.hostname(HOSTNAME);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    tentativas--;

    if (tentativas == 0)
    {
      Serial.println();
      Serial.println("Time-out. Verifique as configurações e tente novamente.");
      delay(1000);

      //while(true);
    }
  }
}

void setup(void)
{

  //inicialização da comunicação com a porta serial
  Serial.begin(115200);
  wifiConect();
  delay(2000);
  printNetworkData();
}

void loop(void)
{
}