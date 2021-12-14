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

String _ticketId;
String _problemId;
long eventId;
char *_tokenIot;
char *_tokenClient;
bool _debug;

GlpiIot::GlpiIot(char *tokenIot, char *tokenClient)
{
    _tokenClient = tokenClient;
    _tokenIot = tokenIot;
    urlBase = "https://vconnector2.verdanadesk.com/api/iot/";
    _debug = false;
};

void GlpiIot::Debug(bool debug)
{
    _debug = debug;
};

void GlpiIot::DebugConsole(int httpsResponseCode, String serverNameon, String result)
{
    if (_debug == true)
    {
        if (httpsResponseCode != 201)
        {
            Serial.print("Error - Code: " + (String)httpsResponseCode);
        }
        if (httpsResponseCode == 201)
            Serial.print("Sucess - Code: " + (String)httpsResponseCode);
    }
    //Serial.println(httpsResponseCode);
    Serial.print(" Url: " + (String)serverNameon);
    Serial.println(" Result: " + (String)result);
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
    String result = https.getString();
    https.end();
    this->DebugConsole(httpsResponseCode, serverNameon, result);

    return result;
};

String GlpiIot::NewTicketIncident(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName)
{
    eventId = random(2147483647);
    String url = (String)urlBase + "tickets";
    String requestField = ("ticket_name= " + (String)ticketName + "&ticket_type=1" + "&category_name= " + (String)categoryName + "&ticket_description= " + (String)ticketDescription + "&ticket_priority= " + (int)ticketPriority + "&event_id= " + (int)eventId + "&asset_name= " + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::NewTicketRequest(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName)
{
    eventId = random(2147483647);
    String url = (String)urlBase + "tickets";
    String requestField = ("ticket_name= " + (String)ticketName + "&ticket_type=2" + "&category_name= " + (String)categoryName + "&ticket_description= " + (String)ticketDescription + "&ticket_priority= " + (int)ticketPriority + "&event_id= " + (int)eventId + "&asset_name= " + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::SolutionTicket(String ticketId, char *solutionDescription)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/solutions";
    String requestField = ("solution_description= " + (String)solutionDescription);
    return this->Request(url, requestField);
};

String GlpiIot::FollowupTicket(String ticketId, char *followupContent)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/followup";
    String requestField = ("followup_content= " + (String)followupContent);
    return this->Request(url, requestField);
};

String GlpiIot::TaskTicket(String ticketId, char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/tasks";
    String requestField = ("task_content= " + (String)taskContent + "&task_state= " + (int)taskState + "&task_time= " + (int)taskTime);
    return this->Request(url, requestField);
};

String GlpiIot::FilesTicket(String ticketId, char *fileName, char *fileContent)
{
    String url = (String)urlBase + "tickets/" + (String)ticketId + "/files";
    String requestField = ("document_content= " + (String)fileName + "&url_document= " + (String)fileContent);
    return this->Request(url, requestField);
};

/*Problems::Problems(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName)
{
    _problemName = problemName;
    _categoryName = categoryName;
    _problemPriority = problemPriority;
    _problemDescription = problemDescription;
    _assetName = assetName;
    urlBase = "https://vconnector2.verdanadesk.com/api/iot/";
};

String Problems::Request(String url, String requestField)
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
    String result = https.getString();
    https.end();

    if (_debug == false)
    {
        Serial.println(result);
    }

    return result;
};
*/

String GlpiIot::NewProblem(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName)
{
    eventId = random(2147483647);
    String url = (String)urlBase + "problems";
    String requestField = ("problem_name= " + (String)problemName + "&category_name= " + (String)categoryName + "&problem_description= " + (String)problemDescription + "&problem_priority= " + (int)problemPriority + "&event_id= " + (int)eventId + "&asset_name= " + (String)assetName);
    return this->Request(url, requestField);
};

String GlpiIot::SolutionProblem(String problemId, char *solutionDescription)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/solutions";
    String requestField = ("solution_description= " + (String)solutionDescription);
    return this->Request(url, requestField);
};

String GlpiIot::FollowupProblem(String problemId, char *followupContent)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/followup";
    String requestField = ("followup_content= " + (String)followupContent);
    return this->Request(url, requestField);
};

String GlpiIot::TaskProblem(String problemId, char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "problems/" + (String)problemId + "/tasks";
    String requestField = ("task_content= " + (String)taskContent + "&task_state= " + (int)taskState + "&task_time= " + (int)taskTime);
    return this->Request(url, requestField);
};
