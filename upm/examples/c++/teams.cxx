/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <signal.h>

#include "teams.hpp"
#include "upm_utilities.h"

using namespace std;

bool shouldRun = true;

void
sig_handler(int signo)
{
    if (signo == SIGINT)
        shouldRun = false;
}

int
main(int argc, char** argv)
{
    signal(SIGINT, sig_handler);

    //! [Interesting]

    cout << "Initializing..." << endl;

    // Instantiate an TEAMS instance, using A0 for temperature, and
    // 165.0 ohms for the rResistor value (for the libelium 4-20ma
    // interface)
    upm::TEAMS sensor(0, 165.0);

    // update and print available values every second
    while (shouldRun) {
        // update our values from the sensor
        sensor.update();

        // is the sensor connected? (current >= 4ma)
        cout << "Is Connected: " << sensor.isConnected() << endl;

        // print computed current on the loop.  This includes the offset,
        // if one was set by setOffsetMilliamps().
        cout << "Milliamps: " << sensor.getRawMilliamps() << endl;

        // we show both C and F for temperature
        cout << "Temperature: " << sensor.getTemperature() << " C / " << sensor.getTemperature(true)
             << " F" << endl;

        cout << endl;

        upm_delay(1);
    }

    cout << "Exiting..." << endl;

    //! [Interesting]

    return 0;
}
