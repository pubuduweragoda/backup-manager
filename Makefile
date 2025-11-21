CC = gcc
OBJ = main.o luks.o disk_manage.o
TARGET = backup_manager

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) -lcryptsetup

main.o: main.c
	$(CC) -c main.c

luks.o: luks.c luks.h
	$(CC) -c luks.c

disk_manage.o: disk_manage.c disk_manage.h
	$(CC) -c disk_manage.c

clean: 
	rm -f $(OBJ) $(TARGET) 
