#include "Relay.h"
#include "LED.h"
#include <SoftwareSerial.h>
#include "SmartThings.h"

//Pinout setup
#define RLY_COUNT 4
#define RLY_HALL  4
#define RLY_LAMP  5
#define RLY_WALK  6
#define RLY_OTHER 7

#define ST_LED   13
#define ST_RX    3
#define ST_TX    2

//SmartThings setup
SmartThingsCallout_t messageCallout;
SmartThings st(ST_RX, ST_TX, messageCallout);

//Relay setup
Relay hall(&st, 0, RLY_HALL);
Relay lamp(&st, 1, RLY_LAMP);
Relay walk(&st, 2, RLY_WALK);
Relay other(&st, 3, RLY_OTHER);

void setup() {

}

void loop() {
	st.run();

	hall.run();
	lamp.run();
	walk.run();
	other.run();
}

void messageCallout(String message) {
	Serial.print(message);

	if (message.equals("0"))      hall.close(message);
	else if (message.equals("1")) hall.open(message);
	else if (message.equals("2")) lamp.close(message);
	else if (message.equals("3")) lamp.open(message);
	else if (message.equals("4")) walk.close(message);
	else if (message.equals("5")) walk.open(message);
	else if (message.equals("6")) other.close(message);
	else if (message.equals("7")) other.open(message);
	else if (message.equals("a")) st.send(hall.status() == OPEN ? "hall=0;" : "hall=1;");
	else if (message.equals("b")) st.send(lamp.status() == OPEN ? "lamp=0;" : "lamp=1;");
	else if (message.equals("c")) st.send(walk.status() == OPEN ? "walk=0;" : "walk=1;");
	else if (message.equals("d")) st.send(other.status() == OPEN ? "other=0;" : "other=1;");
	else if (message.equals("8")) {
		hall.close("0");
		lamp.close("2");
		walk.close("4");
		other.close("6");
		st.send("8");
	}
	else if (message.equals("9")) {
		hall.open("1");
		lamp.open("2");
		walk.open("5");
		other.open("7");
		st.send("9");
	}
	else if (message.equals("e")) {
		String ret = "";
		ret = ret + (hall.status() == OPEN ? "hall=0;" : "hall=1;");
		ret = ret + (lamp.status() == OPEN ? "lamp=0;" : "lamp=1;");
		ret = ret + (walk.status() == OPEN ? "walk=0;" : "walk=1;");
		ret = ret + (other.status() == OPEN ? "other=0;" : "other=1;");

		st.send(ret);
	}
}
