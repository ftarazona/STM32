#!/bin/sh
stty -F /dev/ttyACM0 9600 raw -echo -echoe -echok -crtscts clocal
