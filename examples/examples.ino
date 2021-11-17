#include <glpi_esp8266.h>

char SSID[] = "VTC";        //SSID da rede
char NETKEY[] = "#v3rD@n4"; //Chave de acesso a rede
char *token_iot = "870db0906c07b0b8dded3dc5f32fd7d5";
char *token_client = "e1d96bf3ea0419f1a22a2947bd78feb9";
char *asset_name = "PEVTCMTNB2590";

int attempts = 50;

Tickets caixaAgua("Caixa quase vazia", 1, "IoT", 5, "A caixa está com 10 litros de água", "PEVTCMTNB2590");
Tickets tempMovimento("Presença detectada", 1, "IoT", 6, "Alguém está na sala", "PEVTCMTNB2590");
Tickets temperaturaPlanta("Temperatura planta", 1, "IoT", 2, "A temperatura está muito alta", "PEVTCMTNB2590");
Problems caixaAgua1("Cano quebrou", "IoT", 6, "O cano que enche a caixa quebrou e a caixa está vazia", "PEVTCMTNB2590");

void printNetworkData()
{
  /*
 * Imprime no monitor serial os dados de conexão da rede
 */

  Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - ");
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
 * Realiza a conexão da esp8266 com a rede wifi
 */

  delay(2000); //Um pequeno atraso para conseguir pegar os dados via Serial
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, NETKEY);

  // Definindo hostname da placa para LAN
  WiFi.hostname(asset_name);

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
  wifiConect();
  printNetworkData();
  delay(4000);
  caixaAgua.new_ticket(token_iot, token_client);
  delay(2000);
  caixaAgua1.new_problem(token_iot, token_client);
  caixaAgua.task_ticket("Vamo no baldinho", 1, 4000, token_iot, token_client);
  delay(2000);
  tempMovimento.new_ticket(token_iot, token_client);
  delay(2000);
  caixaAgua.followup_ticket("Foi enviado a notificação para o síndico", token_iot, token_client);
  delay(2000);
  temperaturaPlanta.new_ticket(token_iot, token_client);
  delay(120000);
  caixaAgua.solution_ticket("A caixa foi enchida no baldinho, agora ela está cheia", token_iot, token_client);
  delay(2000);
  temperaturaPlanta.solution_ticket("A planta foi regada", token_iot, token_client);
}
void loop()
{
  // put your main code here, to run repeatedly:
}