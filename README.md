# rip_router

## Router table, brodcasting entries and updating them based on informations from other routers.

### how to compile:
>go to src folder and use `make` command

#### how to start router:
>`./router`
and write information about available interfaces and routers which are connected directly.
```c
2
10.0.1.1/8 distance 3
192.168.5.43/24 distance 2
```

#### how to clean compiled files:
>You can use `make clean` command.

#### how to clean compiled files and delete executable file:
>You can use `make distclean` command.
