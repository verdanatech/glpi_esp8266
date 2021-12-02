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

authorization::authorization(char *token_iot, char *token_client)
{
    _token_client = token_client;
    _token_iot = token_iot;
};

tickets::tickets(char *ticket_name, int ticket_type, char *category_name, int ticket_priority, char *ticket_description, char *asset_name)
{
    _ticket_name = ticket_name;
    _ticket_type = ticket_type;
    _category_name = category_name;
    _ticket_priority = ticket_priority;
    _ticket_description = ticket_description;
    _asset_name = asset_name;
    url_base = "https://vconnector2.verdanadesk.com/api/iot/";
};

String tickets::request(String url, String request_field)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String server_nameon = url;
    https.begin(client, server_nameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String https_request_data = request_field;
    int https_response_code = https.POST(https_request_data);
    String result = https.getString();
    https.end();
    Serial.println(result); //just to know if it worked
    return result;
};

void tickets::new_ticket()
{
    _event_id = random(2147483647);
    String url = (String)url_base + "tickets";
    String request_field = ("ticket_name= " + (String)_ticket_name + "&ticket_type= " + (int)_ticket_type + "&category_name= " + (String)_category_name + "&ticket_description= " + (String)_ticket_description + "&ticket_priority= " + (int)_ticket_priority + "&event_id= " + (int)_event_id + "&asset_name= " + (String)_asset_name);
    _ticket_id = this->request(url, request_field);
};

void tickets::solution_ticket(char *solution_description)
{
    String url = (String)url_base + "tickets/" + (String)_ticket_id + "/solutions";
    String request_field = ("solution_description= " + (String)solution_description);
    this->request(url, request_field);
};

void tickets::followup_ticket(char *followup_content)
{
    String url = (String)url_base + "tickets/" + (String)_ticket_id + "/followup";
    String request_field = ("followup_content= " + (String)followup_content);
    this->request(url, request_field);
};

void tickets::task_ticket(char *task_content, int task_state, int task_time)
{
    String url = (String)url_base + "tickets/" + (String)_ticket_id + "/tasks";
    String request_field = ("task_content= " + (String)task_content + "&task_state= " + (int)task_state + "&task_time= " + (int)task_time);
    this->request(url, request_field);
};

problems::problems(char *problem_name, char *category_name, int problem_priority, char *problem_description, char *asset_name)
{
    _problem_name = problem_name;
    _category_name = category_name;
    _problem_priority = problem_priority;
    _problem_description = problem_description;
    _asset_name = asset_name;
    url_base = "https://vconnector2.verdanadesk.com/api/iot/";
};

String problems::request(String url, String request_field)
{
    BearSSL::WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String server_nameon = url;
    https.begin(client, server_nameon);

    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    https.addHeader("token-client", _token_client);
    https.addHeader("token-iot", _token_iot);

    String https_request_data = request_field;
    int https_response_code = https.POST(https_request_data);
    String result = https.getString();
    https.end();
    Serial.println(result); //just to know if it worked
    return result;
};

void problems::new_problem()
{
    _event_id = random(2147483647);
    String url = (String)url_base + "problems";
    String request_field = ("problem_name= " + (String)_problem_name + "&category_name= " + (String)_category_name + "&problem_description= " + (String)_problem_description + "&problem_priority= " + (int)_problem_priority + "&event_id= " + (int)_event_id + "&asset_name= " + (String)_asset_name);
    _problem_id = this->request(url, request_field);
};

void problems::solution_problem(char *solution_description)
{
    String url = (String)url_base + "problems/" + (String)_problem_id + "/solutions";
    String request_field = ("solution_description= " + (String)solution_description);
    this->request(url, request_field);
};

void problems::followup_problem(char *followup_content)
{
    String url = (String)url_base + "problems/" + (String)_problem_id + "/followup";
    String request_field = ("followup_content= " + (String)followup_content);
    this->request(url, request_field);
};