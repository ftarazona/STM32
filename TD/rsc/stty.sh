#!/bin/sh
stty -F /dev/ttyACM0 115200 raw -echo -echoe -echok -crtscts clocal
