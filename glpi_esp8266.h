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

#ifndef glpi_esp

#define glpi_esp

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class Tickets
{

private:
  char *_ticket_name;
  int _ticket_type;
  char *_category_name;
  int _ticket_priority;
  char *_ticket_description;
  long _event_id;
  char *_asset_name;
  String _ticket_id;
  char *server_nameon;
  char *https_request_data;
  int https_response_code;
  String url_base;

public:
  Tickets(char *ticket_name, int ticket_type, char *category_name, int ticket_priority, char *ticket_description, char *asset_name);
  void NewTicket();
  void SolutionTicket(char *solution_description);
  void FollowupTicket(char *followup_content);
  void TaskTicket(char *task_content, int task_state, int task_time);
  String Request(String url, String request_field);
};

// authorization
class Authorization
{
public:
  char *token_iot = 0;
  char *token_client = 0;

  Authorization(char *token_iot, char *token_client);
};

class Problems
{

private:
  char *_problem_name;
  char *_category_name;
  int _problem_priority;
  char *_problem_description;
  int _event_id;
  char *_asset_name;
  String _problem_id;
  char *server_nameon;
  char *https_request_data;
  int https_response_code;
  String url_base;

public:
  Problems(char *problem_name, char *category_name, int problem_priority, char *problem_description, char *asset_name);
  void NewProblem();
  void SolutionProblem(char *solution_description);
  void FollowupProblem(char *followup_content);
  String Request(String url, String request_field);
};

#endif
