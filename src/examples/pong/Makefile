

PONGHOST_OBJ=main_host.o pong_host.o ball.o ball_host_callback.o player.o player_host_callback.o timer.o


all: ponghost

%.o:%.cpp
	g++ -c -o $@ $^

ponghost: $(PONGHOST_OBJ)
	g++ -o $@ $^ -lpieces -lOpenThreads -lpthread

clean:
	rm *.o ponghost
