all:
	$(CC) cpu_full_load.c -lpthread -o cpu_load_test