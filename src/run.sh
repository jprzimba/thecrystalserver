#!/bin/bash

#The crystal server run script

echo "The crystal server run script"
VERSION="1.0"

case "$1" in
  --help|-h)
      echo >&2 "Usage $0 <options>"
      echo >&2 " Where options are:"
      echo >&2 " -h|--help|start|stop|restart|kill|--version";
      if [ -f crystalserver ];
      then
        ./crystalserver --help
      fi
      ;;
   start|s)
     if [ -f crystalserver ];
     then
        echo >&2 "Running The crystal server v$VERSION"
        ./crystalserver
        echo >&2 "Exited with code $?"
      else
         echo >&2 "Could not start The crystal server"
      fi
     ;;
   restart)
     echo "Restarting..."
     killall -9 crystalserver
     if [ -f crystalserver ];
     then
        ./crystalserver
		echo >&2 "Exited with code $?"
     else
        echo >&2 "Failed"
     fi
     ;;
   stop|kill)
     killall -9 crystalserver
     ;;
   --version)
     echo "v$VERSION"
     exit
     ;;
   *)
      echo >&2 "Usage $0 <options>"
      echo >&2 " Where options are:"
      echo >&2 " -h|--help|start|stop|restart|kill";
      ;;
esac
