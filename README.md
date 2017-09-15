# tlping

## What is tlping ?

It is a command-line tool which imitates the well-known ping program but tlping uses the UDP protocol and Echo service (port 7) instead. tlping works currently under Windows.

## How to install it ?

1. Unzip the archive
2. Copy-Paste tlping.exe in "C:\Users\<your windows username>\"

## How to use it ?

1. Open the windows console (cmd.exe)
2. Use the following command to execute the program :

```shell
tlping [-h display the help (what you currently read)] [-c=<count> number of ping to execute] [-s=<size> size of the payload (aka data carried by a packet)]
	[-i=<time in second> interval between each ping request] [-t=<time in millisecond> timeout (if no response is received after this time elapsed, tlping stops)] [IP Address]
```