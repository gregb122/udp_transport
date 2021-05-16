# udp_transport

## UDP client wchich implement sliding window protocol for file download

### how to compile:
>go to src folder and use `make` command

#### how to start router:
> ./transport <server_ip> <port> <file_name> <size_to_download>

for example:
```c
./transport 192.168.56.101 40001 output 10000002
```

#### how to clean compiled files:
>You can use `make clean` command.

#### how to clean compiled files and delete executable file:
>You can use `make distclean` command.
