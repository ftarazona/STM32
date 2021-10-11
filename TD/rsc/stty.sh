#!/bin/sh
stty -F /dev/ttyACM0 2400 raw -echo -echoe -echok -crtscts clocal
