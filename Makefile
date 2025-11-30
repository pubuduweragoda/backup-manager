CC = gcc
OBJ = main.o luks.o disk_manage.o system_info.o
TARGET = backup_manager
CFLAGS = -lcryptsetup 

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

main.o: main.c
	$(CC) -c main.c

luks.o: luks.c luks.h
	$(CC) -c luks.c

disk_manage.o: disk_manage.c disk_manage.h
	$(CC) -c disk_manage.c

system_info.o: system_info.c system_info.h
	$(CC) -c system_info.c

clean: 
	rm -f $(OBJ) $(TARGET) 
