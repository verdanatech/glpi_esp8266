# glpi_esp8266

glpi_esp8266 Consumes Verdanatech's vConnector API, thus allowing integration between IoT system with the GLPi management system.

# license

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
 


# dependencies

Requires import of libraries ESP8266HTTPClient.h, ESP8266WiFi.h

Be a Verdanatech GLPi user.

# Installation

Download the latest version from the library at https://github.com/verdanatech/glpi_esp8266 and save the file somewhere

In Arduino IDE, go to Sketch menu option -> Import Library -> Add Library...

Find the zip file you saved in the first step and choose it

Check if it was added successfully by opening the Sketch menu -> Import Library. You should now see glpi_esp8266 listed among the available libraries.

# Use

In normal use, the programmer creates the objects according to his project and using the library functions, makes the request to the vConnector API that makes the request to the GLPi and opens a call returning an ID that can be used for other requests.

The library only works on esp8266 boards.

See the examples for more details on how the library is used.
