CC = g++ --std=c++11

all: a.out

a.out: main.o in_out_handler.o film.o manager.o user.o comment.o publisher.o customer.o
			${CC} main.o in_out_handler.o film.o manager.o user.o comment.o publisher.o customer.o

main.o: main.cpp in_out_handler.o film.o manager.o user.o comment.o publisher.o customer.o
			${CC} -c main.cpp

in_out_handler.o: in_out_handler.cpp in_out_handler.h
			${CC} -c in_out_handler.cpp

film.o: film.cpp film.h
			${CC} -c film.cpp

manager.o: manager.cpp manager.h
			${CC} -c manager.cpp

user.o: user.cpp user.h
			${CC} -c user.cpp

comment.o: comment.cpp comment.h
			${CC} -c comment.cpp

publisher.o: publisher.cpp publisher.h
			${CC} -c publisher.cpp

customer.o: customer.cpp customer.h
			${CC} -c customer.cpp
clean:
			rm *.o
			rm Scheduler.out