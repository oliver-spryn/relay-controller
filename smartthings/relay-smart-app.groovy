definition (
	name: "Arduino Message Sender",
	namespace: "Home Automation",
	author: "Oliver Spryn",
	description: "Turns Arduino controlled relays on and off based on the state of a controller switch",
	category: "Convenience",
	iconUrl: "https://s3.amazonaws.com/smartapp-icons/Meta/light_outlet.png",
	iconX2Url: "https://s3.amazonaws.com/smartapp-icons/Meta/light_outlet@2x.png"
)

preferences {
	section("Select an Arduino board") {
		input "arduino", "device.arduinoRelayBoard"
    }
    
    section("Hallway Triggering Device") {
		input "hallway", "capability.switch"
    }
    
    section("Sidewalk Triggering Device") {
		input "sidewalk", "capability.switch"
    }
    
    section("Yard Light Triggering Device") {
		input "yard", "capability.switch"
    }
}

// Subscriptions
def installed() {
	subscribe(hallway, "switch.off", hallOff)
	subscribe(hallway, "switch.on", hallOn)
    
    subscribe(sidewalk, "switch.off", sidewalkOff)
	subscribe(sidewalk, "switch.on", sidewalkOn)
    
    subscribe(yard, "switch.off", yardOff)
	subscribe(yard, "switch.on", yardOn)
}

def updated() {
	unsubscribe()
	installed() 
}

// Hallway
def hallOff(evt) {
	arduino.RelayOff1()
}

def hallOn(evt) {
	arduino.RelayOn2()
}

// Sidewalk
def sidewalkOff(evt) {
	arduino.RelayOff5()
}

def sidewalkOn(evt) {
	arduino.RelayOn6()
}

// Hallway
def yardOff(evt) {
	arduino.RelayOff3()
}

def yardOn(evt) {
	arduino.RelayOn4()
}