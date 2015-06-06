/**
 *  Smart Yard Controller
 *	powered by Particle
 *
 *  Author: @dome
 *  Big credit to: juano23@gmail.com
 *  Date: 2014-01-23
 */
 
 preferences {
    input("deviceId", "text", title: "Device ID")
    input("token", "text", title: "Access Token")
}
 
metadata {

	definition (name: "Smart Yard Controller", author: "dome") {
    	capability "Switch"
        capability "Valve"
/*		capability "Alarm"
		capability "Water Sensor"
		capability "Temperature Measurement"
*/
}


	tiles {
		standardTile("switch", "device.switch", width: 1, height: 1, canChangeIcon: true) {
			state "on", label: '${name}', action: "switch.off", icon: "st.switches.switch.on", backgroundColor: "#79b821"
			state "off", label: '${name}', action: "switch.on", icon: "st.switches.switch.off", backgroundColor: "#ffffff"
		}
		standardTile("valve", "device.valve", width: 1, height: 1, canChangeIcon: true) {
			state "open", label: '${name}', action: "switch.off", icon: "st.valves.water.open", backgroundColor: "#53a7c0"
			state "closed", label: '${name}', action: "switch.on", icon: "st.valves.water.closed", backgroundColor: "#ffffff"
		}


		main "valve"
		details "valve","switch"
	}
}

def parse(String description) {
  if(message == "switch.on") {
    sendEvent(name: "switch", value: "on")
    descriptionText = "${device.displayName} is switched on"        
  }
}
    


def on() {
	put '1'
    sendEvent(name: "switch", value: "on")
    sendEvent(name: "valve", value: "open")
	descriptionText = "${device.displayName} has begun watering"        

}

def off() {
	put '0'
    sendEvent(name: "switch", value: "off")
    sendEvent(name: "valve", value: "closed")
	descriptionText = "${device.displayName} has stopped watering"        
}

private put(syc) {
    //Spark Core API Call
	httpPost(
		uri: "https://api.spark.io/v1/devices/${deviceId}/syccommand",
        body: [access_token: token, command: syc],  
	) {response -> log.debug (response.data)}
}
