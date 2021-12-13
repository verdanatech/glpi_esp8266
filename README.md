# glpi_esp8266

glpi_esp8266 Consumes Verdanatech's vConnector API, thus allowing integration between IoT system with the GLPi management system.

# License

This file is part of glpi_esp8266.

glpi_esp8266 is free software developed and supported
by Verdanatech Soluções em TI and contributors
You can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

glpi_esp8266 is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantantability or fitness for a particular purpose.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with glpi_esp8266. If not, see <http://www.gnu.org/licenses/>.

---

# Dependencies

Requires import of libraries ESP8266HTTPClient.h, ESP8266WiFi.h

Be a Verdanatech GLPi user.

# Installation

1. Download the latest version from the library at https://github.com/verdanatech/glpi_esp8266 and save the file somewhere

2. In Arduino IDE, go to Sketch menu option -> Import Library -> Add Library...

3. Find the zip file you saved in the first step and choose it

4. Check if it was added successfully by opening the Sketch menu -> Import Library. 

5. You should now see glpi_esp8266 listed among the available libraries.

# Use

In normal use, the programmer creates the objects according to his project and using the library functions, makes the request to the vConnector API that makes the request to the GLPi and opens a call returning an ID that can be used for other requests.

The library only works on esp8266 boards.

See the examples for more details on how the library is used.


# Authorization


## Constructor
This is our constructor for authorization in the API, we will use the parameters below.


### Parameters

 - **tokenIot:** token generated in the customer portal in the IOT configuration tab.

 - **tokenClient:** customer token generated in the customer portal.


# Tickets


## Constructor
Here is our constructor for tickets, in it we will create our object using the parameters below.

### Parameters

 - **ticketName:** is the name that will be given to the ticket.

 - **ticketType:** here we define the ticket type. We currently use two types: type 1 is incident, type 2 is requisition.

 - **categoryName:** here is defined the category of the ticket. NOTE: the category must be existing in the GLPi system.

 - **ticketPriority:** here the priority of the ticket is defined. We use values from 1 to 6, with 1 being a very low priority level and 6 being a critical priority level.

 - **ticketDescription:** here is a brief summary of the ticket.

 - **assetName:** in this parameter, the name of the asset (device name) from which the request is being made is passed.


## Methods

### NewTicket
This method opens a new ticket.


### FollowupTicket
Using this method, you can add a follow-up to the ticket.


### Parameters

 - **followupContent:** Here is a description of the ticket follow-up.

### TaskTicket
Using this method, you can add a task to the ticket.


### Parameters

 - **taskContent:** here a description of the task is made.

 - **taskState:** here the task status is defined. We currently use 1 for a task that still needs to be done and 2 for a task that has already been done.

 - **taskTime:** in this parameter, the time required to perform the task is passed in seconds.


### SolutionTicket
With this method it is possible to add a solution to a ticket.


### Parameters

 - **solutionDescription:** here a description of the ticket solution is made.


# Problems

## Constructor
Here is our constructor for problems, in it we will create our object using the parameters below.

### Parameters

 - **problemName:** is the name that will be given to the problem.

 - **categoryName:** here is defined the category of the problem. NOTE: the category must be existing in the GLPi system.

 - **problemPriority:** here the priority of the problem is defined. We use values from 1 to 6, with 1 being a very low priority level and 6 being a critical priority level.

 - **problemDescription:** here is a brief summary of the problem.

 - **assetName:** in this parameter, the name of the asset (device name) from which the request is being made is passed.


## Methods

### NewProblem
This method performs the opening of a problem.


### FollowupProblem
By using this method, you can add follow-up to the issue.


### Parameters

 - **followupContent:** Here is a description of the issue's follow-up.


### SolutionProblem
With this method it is possible to add a solution to a problem.


### Parameters

 - **solutionDescription:** here is a description of the solution to the problem.

 ### TaskProblem
Using this method, you can add a task to the problem.


### Parameters

 - **taskContent:** here a description of the task is made.

 - **taskState:** here the task status is defined. We currently use 1 for a task that still needs to be done and 2 for a task that has already been done.

 - **taskTime:** in this parameter, the time required to perform the task is passed in seconds.

