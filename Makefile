GXX = /usr/bin/g++
objects = main.o connection.o session.o room.o paticipant.o

server : $(objects)
	$(GXX) -o server $(objects) -lboost_system -lboost_thread

main.o : main.cpp Connection.hpp
	$(GXX) -c main.cpp

connection.o : Connection.cpp Connection.hpp Session.hpp
	$(GXX) -c -o connection.o  Connection.cpp

session.o : Session.cpp Session.hpp Room.hpp
	$(GXX) -c -o session.o Session.cpp

room.o : Room.cpp Room.hpp Paticipant.hpp
	$(GXX) -c -o room.o Room.cpp

paticipant.o : Paticipant.cpp Paticipant.hpp chat_message.hpp
	$(GXX) -c -o paticipant.o Paticipant.cpp

clean :
	rm server $(objects)
