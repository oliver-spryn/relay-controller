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

	if (message.equals("hallon"))           hall.close(message);
	else if (message.equals("halloff"))     hall.open(message);
	else if (message.equals("lampon"))      lamp.close(message);
	else if (message.equals("lampoff"))     lamp.open(message);
	else if (message.equals("walkon"))      walk.close(message);
	else if (message.equals("walkoff"))     walk.open(message);
	else if (message.equals("otheron"))     other.close(message);
	else if (message.equals("otheroff"))    other.open(message);
	else if (message.equals("reporthall"))  st.send(hall.status() == OPEN ? "hall=0;" : "hall=1;");
	else if (message.equals("reportlamp"))  st.send(lamp.status() == OPEN ? "lamp=0;" : "lamp=1;");
	else if (message.equals("reportwalk"))  st.send(walk.status() == OPEN ? "walk=0;" : "walk=1;");
	else if (message.equals("reportother")) st.send(other.status() == OPEN ? "other=0;" : "other=1;");
	else if (message.equals("allon")) {
		hall.close("hallon");
		lamp.close("lampon");
		walk.close("walkon");
		other.close("otheron");
		st.send("allon");
	}
	else if (message.equals("alloff")) {
		hall.open("halloff");
		lamp.open("lampoff");
		walk.open("walkoff");
		other.open("otheroff");
		st.send("alloff");
	}
	else if (message.equals("reportall")) {
		String ret = "";
		ret = ret + (hall.status() == OPEN ? "hall=0;" : "hall=1;");
		ret = ret + (lamp.status() == OPEN ? "lamp=0;" : "lamp=1;");
		ret = ret + (walk.status() == OPEN ? "walk=0;" : "walk=1;");
		ret = ret + (other.status() == OPEN ? "other=0;" : "other=1;");

		st.send(ret);
	}
}