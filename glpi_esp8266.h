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

class GlpiIot
{

private:
  //tickets
  String _ticketId;

  //problems
  String _problemId;

  //geral
  long _eventId;
  char *_assetName;
  char *serverNameon;
  char *httpsRequestData;
  int httpsResponseCode;
  String urlBase;
  String Request(String url, String requestField);

public:
  GlpiIot(char *tokenIot, char *tokenClient);

  //tickets
  String NewTicketIncident(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName);
  String NewTicketRequest(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName);
  String SolutionTicket(String ticketId, char *solutionDescription);
  String FollowupTicket(String ticketId, char *followupContent);
  String TaskTicket(String ticketId, char *taskContent, int taskState, int taskTime);
  String FilesTicket(String ticketId, char *fileName, char *fileContent);

  //problems

  String NewProblem(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName);
  String SolutionProblem(String problemId, char *solutionDescription);
  String FollowupProblem(String problemId, char *followupContent);
  String TaskProblem(String problemId, char *taskContent, int taskState, int taskTime);
  String FilesProblem(String problemId, char *fileName, char *fileContent);

  //geral
  void Debug(bool debug);
  void DebugConsole(int httpsResponseCode, String serverNameon, String result);
};

// authorization
/*class Authorization
{
public:
  char *tokenIot = 0;
  char *tokenClient = 0;

  Authorization(char *tokenIot, char *tokenClient);
};

class Debug
{
public:
  Debug(bool debug);
};

class Problems
{

private:
  char *_problemName;
  char *_categoryName;
  int _problemPriority;
  char *_problemDescription;
  int _eventId;
  char *_assetName;
  String _problemId;
  char *serverNameon;
  char *httpsRequestData;
  int httpsResponseCode;
  String urlBase;
  String Request(String url, String requestField);

public:
  Problems(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName);
  void NewProblem();
  void SolutionProblem(char *solutionDescription);
  void FollowupProblem(char *followupContent);
  void TaskProblem(char *taskContent, int taskState, int taskTime);
  void FilesProblem(char *fileName, char *fileContent);
};
*/

#endif
