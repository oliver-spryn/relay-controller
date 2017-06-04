/**
 *  Arduino + 8-way relay board Device Type for SmartThings
 *
 *  Author: badgermanus@gmail.com
 *  Code: https://github.com/jwsf/device-type.arduino-8-way-relay
 *
 * Copyright (C) 2014 Jonathan Wilson  <badgermanus@gmail.com>
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, 
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
 * permit persons to whom the Software is furnished to do so, subject to the following 
 * conditions: The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */ 
 
metadata {
	definition ( author: "badgermanus@gmail.com", name: "Arduino Relay Board" ) {
		capability "Polling"
		capability "Refresh"
                
		command "RelayOn1"
		command "RelayOff1"
		command "RelayOn2"
		command "RelayOff2"
		command "RelayOn3"
		command "RelayOff3"
		command "RelayOn4"
		command "RelayOff4"
		command "RelayOn5"
		command "RelayOff5"
		command "RelayOn6"
		command "RelayOff6"
	}

	tiles {
		standardTile("relay1", "device.relay1", canChangeIcon: true, canChangeBackground: true) {
			state "off", label: 'Hall Off', action: "RelayOn1", icon: "st.switches.switch.off", backgroundColor: "#ffffff", defaultState: true
			state "on", label: 'Hall On', action: "RelayOff1", icon: "st.switches.switch.on", backgroundColor: "#79b821"
		}
        
		standardTile("relay2", "device.relay2", canChangeIcon: true, canChangeBackground: true) {
			state "on", label: 'Hall On', action: "RelayOff2", icon: "st.switches.switch.on", backgroundColor: "#79b821", defaultState: true
			state "off", label: 'Hall Off', action: "RelayOn2", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
		}
        
		standardTile("relay3", "device.relay3", canChangeIcon: true, canChangeBackground: true) {
			state "off", label: 'Yard Off', action: "RelayOn3", icon: "st.switches.switch.off", backgroundColor: "#ffffff", defaultState: true
			state "on", label: 'Yard On', action: "RelayOff3", icon: "st.switches.switch.on", backgroundColor: "#79b821"
		}
        
		standardTile("relay4", "device.relay4", canChangeIcon: true, canChangeBackground: true) {
			state "on", label: 'Yard On', action: "RelayOff4", icon: "st.switches.switch.on", backgroundColor: "#79b821", defaultState: true
			state "off", label: 'Yard Off', action: "RelayOn4", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
		}
        
		standardTile("relay5", "device.relay5", canChangeIcon: true, canChangeBackground: true) {
			state "off", label: 'Walk Off', action: "RelayOn5", icon: "st.switches.switch.off", backgroundColor: "#ffffff", defaultState: true
			state "on", label: 'Walk On', action: "RelayOff5", icon: "st.switches.switch.on", backgroundColor: "#79b821"
		}
        
		standardTile("relay6", "device.relay6", canChangeIcon: true, canChangeBackground: true) {
			state "on", label: 'Walk On', action: "RelayOff6", icon: "st.switches.switch.on", backgroundColor: "#79b821", defaultState: true
			state "off", label: 'Walk Off', action: "RelayOn6", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
		}
        
		standardTile("refresh", "device.switch", inactiveLabel: false, decoration: "flat") {
			state "default", label:'', action:"refresh.refresh", icon:"st.secondary.refresh"
		}
        
		main "relay1"
		details(["relay1", "relay2", "relay3", "relay4", "relay5", "relay6", "refresh"])
	}
}

// Hall
def RelayOn1() {
	log.debug "Turning on relay 1"
	zigbee.smartShield(text: "1").format()
}

def RelayOff1() {
	log.debug "Turning off relay 1"
	zigbee.smartShield(text: "1").format()
}

def RelayOn2() {
	log.debug "Turning on relay 1"
	zigbee.smartShield(text: "0").format()
}

def RelayOff2() {
	log.debug "Turning off relay 1"
	zigbee.smartShield(text: "0").format()
}

// Lamp
def RelayOn3() {
	log.debug "Turning on relay 2"
	zigbee.smartShield(text: "3").format()
}

def RelayOff3() {
	log.debug "Turning off relay 2"
	zigbee.smartShield(text: "3").format()
}

def RelayOn4() {
	log.debug "Turning on relay 2"
	zigbee.smartShield(text: "2").format()
}

def RelayOff4() {
	log.debug "Turning off relay 2"
	zigbee.smartShield(text: "2").format()
}

// Walk
def RelayOn5() {
	log.debug "Turning on relay 3"
	zigbee.smartShield(text: "5").format()
}

def RelayOff5() {
	log.debug "Turning off relay 3"
	zigbee.smartShield(text: "5").format()
}

def RelayOn6() {
	log.debug "Turning on relay 3"
	zigbee.smartShield(text: "4").format()
}

def RelayOff6() {
	log.debug "Turning off relay 3"
	zigbee.smartShield(text: "4").format()
}

def poll() {
	log.debug "Poll - getting state of all relays"
	zigbee.smartShield(text: "e").format()
}

def refresh() {
	log.debug "Refresh - getting state of all relays"
	zigbee.smartShield(text: "e").format()
}
 
// Arduino event handlers
// =================================
 
def parse(String description) {

 	def value = zigbee.parse(description)?.text
	log.debug "Received: " + value
    
	if (value == "relayon1") { 
		createEvent (name:"relay1", value:"on", isStateChange:true)
	} else
	if (value == "relayoff1") {
	   	createEvent (name:"relay1", value:"off", isStateChange:true)
	} else
	if (value == "relayautooff1") {
	   	sendEvent (name: "alert", value: "Relay auto switchoff")
	} else
	if (value == "relayon2") {
	   	createEvent (name:"relay2", value:"on", isStateChange:true)
	} else
	if (value == "relayoff2") {
	   	createEvent (name:"relay2", value:"off", isStateChange:true)
	} else 
	if (value == "relayon3") {
	   	createEvent (name:"relay3", value:"on", isStateChange:true)
	} else
	if (value == "relayoff3") {
	   	createEvent (name:"relay3", value:"off", isStateChange:true)
	} else 
	if (value == "relayon4") {
	   	createEvent (name:"relay4", value:"on", isStateChange:true)
	} else
	if (value == "relayoff4") {
	   	createEvent (name:"relay4", value:"off", isStateChange:true)
	} else 
	if (value == "relayon5") {
	   	createEvent (name:"relay5", value:"on", isStateChange:true)
	} else
	if (value == "relayoff5") {
	   	createEvent (name:"relay5", value:"off", isStateChange:true)
	} else 
	if (value == "relayon6") {
	   	createEvent (name:"relay6", value:"on", isStateChange:true)
	} else
	if (value == "relayoff6") {
	   	createEvent (name:"relay6", value:"off", isStateChange:true)
	} else 
	if (value == "relayon7") {
	   	createEvent (name:"relay7", value:"on", isStateChange:true)
	} else
	if (value == "relayoff7") {
	   	createEvent (name:"relay7", value:"off", isStateChange:true)
	} else 
	if (value == "relayon8") {
	   	createEvent (name:"relay8", value:"on", isStateChange:true)
	} else
	if (value == "relayoff8") {
	   	createEvent (name:"relay8", value:"off", isStateChange:true)
	}
}
