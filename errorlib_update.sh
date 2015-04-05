#!/bin/sh
if [ ! -d ./error_lib ]
then
mkdir error_lib
fi
if [ -d ./error_lib/current ]
then
rm -r -f ./error_lib/current
fi
{ git clone https://github.com/DevWurm/error_library.git ./error_lib/current/ &&
 rm -r ./error_lib/current/Binary/ &&
 rm -r ./error_lib/current/lib/ &&
 make source -C ./error_lib/current/
 cp ./error_lib/current/Binary/error.o ./error_lib/ &&
 rm -r -f ./error_lib/current
} || {
 echo "Failure at update!"
}

