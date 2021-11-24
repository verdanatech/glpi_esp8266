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

String _ticket_id;
String _problem_id;
long _event_id;
char *_token_iot;
char *_token_client;

Authorization::Authorization(char *token_iot, char *token_client)
{
    _token_client = token_client;
    _token_iot = token_iot;
};

Tickets::Tickets(char *ticket_name, int ticket_type, char *category_name, int ticket_priority, char *ticket_description, char *asset_name)
{
    _ticket_name = ticket_name;
    _ticket_type = ticket_type;
    _category_name = category_name;
    _ticket_priority = ticket_priority;
    _ticket_description = ticket_description;
    _asset_name = asset_name;
    _url_base = "https://vconnector2.verdanadesk.com/api/iot/";
};

void Tickets::new_ticket()
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    _event_id = random(2147483647);
    HTTPClient https;
    String serverNameon = (String)_url_base + "tickets";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("ticket_name= " + (String)_ticket_name + "&ticket_type= " + (int)_ticket_type + "&category_name= " + (String)_category_name + "&ticket_description= " + (String)_ticket_description + "&ticket_priority= " + (int)_ticket_priority + "&event_id= " + (int)_event_id + "&asset_name= " + (String)_asset_name);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String ticket_id = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);
        _ticket_id = ticket_id;

        if (httpsResponseCode = 201)
        {

            Serial.println("The ID of ticket is: " + (String)ticket_id);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

void Tickets::solution_ticket(char *solution_description)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)_url_base + "tickets/" + (String)_ticket_id + "/solutions";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("solution_description= " + (String)solution_description);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String requestData = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);

        if (httpsResponseCode = 201)
        {

            Serial.println("The ticket with ID " + (String)_ticket_id + " was solved");
            Serial.println("The ID of solution the ticket is: " + (String)requestData);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

void Tickets::followup_ticket(char *followup_content)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)_url_base + "tickets/" + (String)_ticket_id + "/followup";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("followup_content= " + (String)followup_content);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String requestData = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);

        if (httpsResponseCode = 201)
        {

            Serial.println("a new follow-up has been added to the ticket id: " + (String)_ticket_id);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

void Tickets::task_ticket(char *task_content, int task_state, int task_time)

{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)_url_base + "tickets/" + (String)_ticket_id + "/tasks";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("task_content= " + (String)task_content + "&task_state= " + (int)task_state + "&task_time= " + (int)task_time);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String requestData = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);

        if (httpsResponseCode = 201)
        {

            Serial.println("a new task has been added to the ticket id: " + (String)_ticket_id);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

Problems::Problems(char *problem_name, char *category_name, int problem_priority, char *problem_description, char *asset_name)
{
    _problem_name = problem_name;
    _category_name = category_name;
    _problem_priority = problem_priority;
    _problem_description = problem_description;
    _asset_name = asset_name;
    _url_base = "https://vconnector2.verdanadesk.com/api/iot/";
};

void Problems::new_problem()
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    _event_id = random(2147483647);
    HTTPClient https;
    String serverNameon = (String)_url_base + "problems";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("problem_name= " + (String)_problem_name + "&category_name= " + (String)_category_name + "&problem_description= " + (String)_problem_description + "&problem_priority= " + (int)_problem_priority + "&event_id= " + (int)_event_id + "&asset_name= " + (String)_asset_name);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String problem_id = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);
        _problem_id = problem_id;

        if (httpsResponseCode = 201)
        {

            Serial.println("The ID of problem is: " + (String)problem_id);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

void Problems::solution_problem(char *solution_description)

{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)_url_base + "problems/" + (String)_problem_id + "/solutions";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("solution_description= " + (String)solution_description);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String requestData = https.getString();
        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);

        if (httpsResponseCode = 201)
        {

            Serial.println("The problem with ID " + (String)_problem_id + " was solved");
            Serial.println("The ID of solution the problem is: " + (String)requestData);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};

void Problems::followup_problem(char *followup_content)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String serverNameon = (String)_url_base + "problems/" + (String)_problem_id + "/followup";
    https.begin(client, serverNameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String httpsRequestData = ("followup_content= " + (String)followup_content);
    int httpsResponseCode = https.POST(httpsRequestData);

    if (httpsResponseCode > 0)
    {

        String requestData = https.getString();

        Serial.println("The code of sending POST is: " + (String)httpsResponseCode);

        if (httpsResponseCode = 201)
        {

            Serial.println("a new follow-up has been added to the problem id: " + (String)_problem_id);
        }
    }
    else
    {

        Serial.print("Error on sending POST: ");
        Serial.println(httpsResponseCode);
    }

    https.end();
};