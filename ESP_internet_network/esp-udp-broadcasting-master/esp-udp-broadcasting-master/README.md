# ESP32 Projects
ESP32 Project: UDP Broadcasting Auto Discovery using Arduino and Python.

I wanted an easy way to get the ESP32 sending data to other apps and projects with minimum setup and configuration.
I am busy investigating mDNS ( Multicast DNS ) to discover devices but wanted to try this method first.

I have made a youtube video showing this project: https://youtu.be/PQ27j8WAP8Q

It broadcasts on the deafult 255.255.255.255 UDP Broadcast address on Port 2255, but this can be changed.

Steps to get it working:

1) Change the wifi ssid and password in the ESP main.cpp
2) Upload the ESP code to your ESP32
3) Run main.py

This is part of bigger projects that will use this form of communication to make other interesting ESP32 / 8266 Projects.

The next project is to create a DIY sound mixer that can set the sound level of individual apps on windows, almost like the GoXLR Mini.
This will be useful to streamers for instance where they can control the sound level of apps like spotify and games on a per app basis.
It will also change speaker and mic volumes.

If you need help or have project suggestions leave a comment on the youtube video.
