all:
	g++ -std=c++0x -Wall -O3 -o server main.cpp socket.cpp http-message.cpp http-request.cpp http-response.cpp http-utility.cpp http-server.cpp mime-type-chooser.cpp utility.cpp