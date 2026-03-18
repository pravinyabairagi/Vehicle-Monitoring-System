all:
		gcc main.c speed.c seatbelt.c -o ecu_project -lpthread

run:
	./project

clean:
	rm -f project log.txt
