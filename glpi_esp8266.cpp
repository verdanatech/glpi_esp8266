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
long _eventId;
char *_tokenIot;
char *_tokenClient;

Authorization::Authorization(char *tokenIot, char *tokenClient)
{
    _tokenClient = tokenClient;
    _tokenIot = tokenIot;
};

Tickets::Tickets(char *ticketName, int ticketType, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName)
{
    _ticketName = ticketName;
    _ticketType = ticketType;
    _categoryName = categoryName;
    _ticketPriority = ticketPriority;
    _ticketDescription = ticketDescription;
    _assetName = assetName;
    urlBase = "https://vconnector2.verdanadesk.com/api/iot/";
};

String Tickets::Request(String url, String requestField)
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
    Serial.println(result); //just to know if it worked
    return result;
};

void Tickets::NewTicket()
{
    _eventId = random(2147483647);
    String url = (String)urlBase + "tickets";
    String requestField = ("ticket_name= " + (String)_ticketName + "&ticket_type= " + (int)_ticketType + "&category_name= " + (String)_categoryName + "&ticket_description= " + (String)_ticketDescription + "&ticket_priority= " + (int)_ticketPriority + "&event_id= " + (int)_eventId + "&asset_name= " + (String)_assetName);
    _ticketId = this->Request(url, requestField);
};

void Tickets::SolutionTicket(char *solutionDescription)
{
    String url = (String)urlBase + "tickets/" + (String)_ticketId + "/solutions";
    String requestField = ("solution_description= " + (String)solutionDescription);
    this->Request(url, requestField);
};

void Tickets::FollowupTicket(char *followupContent)
{
    String url = (String)urlBase + "tickets/" + (String)_ticketId + "/followup";
    String requestField = ("followup_content= " + (String)followupContent);
    this->Request(url, requestField);
};

void Tickets::TaskTicket(char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "tickets/" + (String)_ticketId + "/tasks";
    String requestField = ("task_content= " + (String)taskContent + "&task_state= " + (int)taskState + "&task_time= " + (int)taskTime);
    this->Request(url, requestField);
};

Problems::Problems(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName)
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
    Serial.println(result); //just to know if it worked
    return result;
};

void Problems::NewProblem()
{
    _eventId = random(2147483647);
    String url = (String)urlBase + "problems";
    String requestField = ("problem_name= " + (String)_problemName + "&category_name= " + (String)_categoryName + "&problem_description= " + (String)_problemDescription + "&problem_priority= " + (int)_problemPriority + "&event_id= " + (int)_eventId + "&asset_name= " + (String)_assetName);
    _problemId = this->Request(url, requestField);
};

void Problems::SolutionProblem(char *solutionDescription)
{
    String url = (String)urlBase + "problems/" + (String)_problemId + "/solutions";
    String requestField = ("solution_description= " + (String)solutionDescription);
    this->Request(url, requestField);
};

void Problems::FollowupProblem(char *followupContent)
{
    String url = (String)urlBase + "problems/" + (String)_problemId + "/followup";
    String requestField = ("followup_content= " + (String)followupContent);
    this->Request(url, requestField);
};

void Problems::TaskProblem(char *taskContent, int taskState, int taskTime)
{
    String url = (String)urlBase + "problems/" + (String)_problemId + "/tasks";
    String requestField = ("task_content= " + (String)taskContent + "&task_state= " + (int)taskState + "&task_time= " + (int)taskTime);
    this->Request(url, requestField);
};