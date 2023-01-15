# MiniTalk


This project is about creating a client/server application in which the client can write messages to a server,
which in turn will display the messages on its standard output.

## Copile code

    make

## Usage Server

Start the server and get PID to send to client, the client will use this PID to send message beteween them.

    ./server

This command will start server and print PID of process.

## Usage Client

Start the client and send PID to server, the client will use this PID to send message beteween them.

    ./client <PID> "MESSSAGE"


## Example

    ./server
    ./client 12345 "Message do you want show in server!