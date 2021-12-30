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
  String _ticketId;
  String _problemId;
  long _eventId;
  char *_assetName;
  char *serverNameon;
  char *httpsRequestData;
  String _result;
  String _message;
  int httpsResponseCode;
  String urlBase;
  String Request(String url, String requestField);

public:
  GlpiIot(char *tokenIot, char *tokenClient);

  String NewTicketIncident(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName);
  String NewTicketRequest(char *ticketName, char *categoryName, int ticketPriority, char *ticketDescription, char *assetName);
  String SolutionTicket(String ticketId, char *solutionDescription);
  String FollowupTicket(String ticketId, char *followupContent);
  String TaskTicket(String ticketId, char *taskContent, int taskState, int taskTime);
  String FilesTicket(String ticketId, char *fileName, char *fileContent);

  String NewProblem(char *problemName, char *categoryName, int problemPriority, char *problemDescription, char *assetName);
  String SolutionProblem(String problemId, char *solutionDescription);
  String FollowupProblem(String problemId, char *followupContent);
  String TaskProblem(String problemId, char *taskContent, int taskState, int taskTime);
  String FilesProblem(String problemId, char *fileName, char *fileContent);

  void ResultOfGet(int httpsResponseCode, String payload);
  void Debug(bool debug);
  void DebugConsole(int httpsResponseCode, String serverNameon, String result, String message);
  void SetEventIdInc(long eventIdInc);
  long GetEventIdInc();
  void SetEventIdReq(long eventIdReq);
  long GetEventIdReq();
  void SetEventIdPro(long eventIdPro);
  long GetEventIdPro();
};

#endif
