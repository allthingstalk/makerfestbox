# Maker Fest Box
The "Box" experiment for Maker Fest, Novi Sad 2019

## How-To

### AllThingsTalk Maker
- Create a free account on [AllThingsTalk Maker](https://maker.allthingstalk.com/signup)
- Select your playground
- Click "New Device"
- Choose "Your Own Device"
- Set a name
- Click "Create Asset"
- Choose "Actuator" at the top, name it "Box" and choose the type to be "Boolean" and save
- In the top right corner, click "+ Create Pinboard" and confirm
- You should now see a button on your pinboard, which we'll later use to open up the box

### Arduino IDE
- (If not already installed) Download [Arduino IDE](https://www.arduino.cc/en/Main/Software) and open it
- Go to *File > Preferences* and in the *Additional Boards Manager URLs* paste "http://arduino.esp8266.com/stable/package_esp8266com_index.json" and click *OK*
- Go to *Tools > Board > Boards Manager* and search for "esp8266"
- Install "esp8266 by ESP8266 Community" and *Close*
- Go to *Tools > Manage Libraries*
- Search for and download "ArduinoJson" (by Benoit Blanchon) and "PubSubClient" (by Nick O'Leary)
- Download the "MakerFestBox.ino" from this repository and open it in Arduino IDE
- Edit the *WIFI_SSID*, *WIFI_PASSWORD*, *MQTT_USER* and *DEVICE_ID* accordingly (check the comments)

### Hardware
- Plug in your box via USB
- Go to *Tools > Board* and select *NodeMCU 1.0 (ESP-12E Module)*
- Go to *Tools > Port* and select the port to which the box is connected (e.g. ttyUSB0 / COM[number])
- Go to *Sketch > Upload* and wait for the upload to the board to finish
- Once done, you can go to *Tools > Serial Monitor* to get info from the box

### Final
You can now go to your pinboard and click the "Box" button and see what happens!
We'll also try to share access to boxes between ourselves and try to make the box unlock by shaking our phone, but that'll be explained live.