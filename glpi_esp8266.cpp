/**
 * ---------------------------------------------------------------------
 * glpi_esp8266 - Integration library between GLPi and esp8266
 * Copyright (C) 2021 Verdanatech Soluções em TI and contributors.
 *
 * https://verdanatech.com
 *
 * ---------------------------------------------------------------------
 *
 * LICENSE
 *
 * This file is part of glpi_esp8266.
 *
 * glpi_esp8266 is free software developed and supported
 * by Verdanatech Soluções em TI and contributors
 * You can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * glpi_esp8266 is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantantability or fitness for a particular purpose.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glpi_esp8266. If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------
 */

#include "glpi_esp8266.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

String _ticketId;
String _problemId;
char *_tokenIot;
char *_tokenClient;
bool _debug;
const char *_result;
const char *_message;

int _eventIdInc;
long eventIdInc;

int _eventIdReq;
long eventIdReq;

int _eventIdPro;
long eventIdPro;

GlpiIot::GlpiIot(char *tokenIot, char *tokenClient)
{
    _tokenClient = tokenClient;
    _tokenIot = tokenIot;
    urlBase = "https://vconnector2.verdanadesk.com/api/iot/";
    _debug = false;
    _eventId = 0;
};

void GlpiIot::Debug(bool debug)
{
    _debug = debug;
};

void GlpiIot::SetEventIdInc(long eventIdInc)
{
    _eventIdInc = eventIdInc;
};

long GlpiIot::GetEventIdInc()
{
    return _eventIdInc;
};

void GlpiIot::SetEventIdReq(long eventIdReq)
{
    _eventIdReq = eventIdReq;
};

long GlpiIot::GetEventIdReq()
{
    return _eventIdReq;
};

void GlpiIot::SetEventIdPro(long eventIdPro)
{
    _eventIdPro = eventIdPro;
};

long GlpiIot::GetEventIdPro()
{
    return _eventIdPro;
};

void GlpiIot::resultOfGet(int httpsResponseCode, String payload)
{
    if (httpsResponseCode == 201 || httpsResponseCode == 200)
    {
        // Allocate JsonBuffer
        // Use arduinojson.org/assistant to compute the capacity.
        const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
        DynamicJsonBuffer jsonBuffer(capacity);

        // Parse JSON object
        JsonObject &root = jsonBuffer.parseObject(payload);
        if (!root.success())
        {
            Serial.println(F("Parsing failed!"));
            return;
        }

        // Decode JSON/Extract values
        Serial.println(F("Response:"));
        Serial.println(root["result"].as<char *>());
        Serial.println(root["message"].as<char *>());
        //Serial.println(root["data"][0].as<char*>());
        //Serial.println(root["data"][1].as<char*>());
    }
    else
    {
        Serial.println("Error in response");
    }

    //http.end();  //Close connection

    delay(5000); //GET Data at every 5 seconds
};

void GlpiIot::DebugConsole(int httpsResponseCode, String serverNameon, String result, String httpsRequestData)
{
    if (_debug == true)
    {
        if (httpsResponseCode != 201 && httpsResponseCode != 200)
        {
            Serial.println("Error - Code: " + (String)httpsResponseCode);
        }
        if (httpsResponseCode == 201 || httpsResponseCode == 200)
        {
            Serial.println("Sucess - Code: " + (String)httpsResponseCode);
        }
        Serial.println(" Url: " + (String)serverNameon);
        Serial.println(" and ID of request: ");
        //Serial.println(_result);
        //Serial.println(_message);
    }
};

String GlpiIot::Request(String url, String requestField)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = url;
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _tokenClient);
    https.addHeader("token-iot", _tokenIot);

    String httpsRequestData = requestField;
    int httpsResponseCode = https.POST(httpsRequestData);
    String payload = https.getString();
    https.end();
    this->resultOfGet(httpsResponseCode, payload);
    this->DebugConsole(httpsResponseCode, serverNameon, payload, httpsRequestData);

    return payload;
};

String GlpiIot::NewTicketIncident(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName)
{
    if (this->GetEventIdInc() == 0)
    {
        long eventIdTemp = random(2147483647);
        this->SetEventIdInc(eventIdTemp);
    }

    eventIdInc = this->GetEventIdInc();
    String url = (String)urlBase + "tickets";
    String requestField = ("ticket_name=" + (String)ticketName + "&ticket_type=1" + "&category_name=" + (String)categoryName + "&ticket_description=" + (String)ticketDescription + "&ticket_priority=" + (int)ticketPriority + "&event_id=" + (int)_eventIdInc + "&asset_name=" + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::NewTicketRequest(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName)
{
    if (this->GetEventIdReq() == 0)
    {
        long eventIdTemp = random(2147483647);
        this->SetEventIdReq(eventIdTemp);
    }

    eventIdReq = this->GetEventIdReq();
    String url = (String)urlBase + "tickets";
    String requestField = ("ticket_name=" + (String)ticketName + "&ticket_type=2" + "&category_name=" + (String)categoryName + "&ticket_description=" + (String)ticketDescription + "&ticket_priority=" + (int)ticketPriority + "&event_id=" + (int)_eventIdReq + "&asset_name=" + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::SolutionTicket(String ticketId, char *solutionDescription)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/solutions";
    String requestField = ("solution_description=" + (String)solutionDescription);
    return this->Request(url, requestField);
};

String GlpiIot::FollowupTicket(String ticketId, char *followupContent)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/followup";
    String requestField = ("followup_content=" + (String)followupContent);
    return this->Request(url, requestField);
};

String GlpiIot::TaskTicket(String ticketId, char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/tasks";
    String requestField = ("task_content=" + (String)taskContent + "&task_state=" + (int)taskState + "&task_time=" + (int)taskTime);
    return this->Request(url, requestField);
};

/*String GlpiIot::FilesTicket(String ticketId, char *fileName, char *fileContent)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)urlBase + "tickets/" + (String)ticketId + "/files";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type:", "multipart/form-data");
    https.addHeader("token-client", _tokenClient);
    https.addHeader("token-iot", _tokenIot);

    String httpsRequestData = ("document_content="(String)fileName + "&url_document=" + (String)fileContent);
    int httpsResponseCode = https.POST(httpsRequestData);
    String result = https.getString();
    https.end();
    Serial.println(result);
    return result;
};
*/

String GlpiIot::NewProblem(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName)
{
    if (this->GetEventIdPro() == 0)
    {
        long eventIdTemp = random(2147483647);
        this->SetEventIdPro(eventIdTemp);
    }

    eventIdPro = this->GetEventIdPro();
    String url = (String)urlBase + "problems";
    String requestField = ("problem_name=" + (String)problemName + "&category_name=" + (String)categoryName + "&problem_description=" + (String)problemDescription + "&problem_priority=" + (int)problemPriority + "&event_id=" + (int)_eventIdPro + "&asset_name=" + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::SolutionProblem(String problemId, char *solutionDescription)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/solutions";
    String requestField = ("solution_description=" + (String)solutionDescription);
    return this->Request(url, requestField);
};

String GlpiIot::FollowupProblem(String problemId, char *followupContent)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/followup";
    String requestField = ("followup_content=" + (String)followupContent);
    return this->Request(url, requestField);
};

String GlpiIot::TaskProblem(String problemId, char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/tasks";
    String requestField = ("task_content=" + (String)taskContent + "&task_state=" + (int)taskState + "&task_time=" + (int)taskTime);
    return this->Request(url, requestField);
};

/*String GlpiIot::FilesProblem(String problemId, char *fileName, char *fileContent)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/files";
    String requestField = ("document_content=" + (String)fileName + "&url_content=@" + (String)fileContent + "&key=url_document" + "&type=file" + "&enabled=true" + "&description=");
    return this->Request(url, requestField);
};
*/