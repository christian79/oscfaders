from OSC import OSCServer,OSCClient, OSCMessage
import types
import serial

server = OSCServer( ("192.168.1.105", 8000) )
client = OSCClient()
client.connect( ("192.168.1.103", 9000) )
arduino = serial.Serial('/dev/cu.usbmodem621', 115200)

#waits for slider change
def handle_timeout(self):
    print ("Timeout")

server.handle_timeout = types.MethodType(handle_timeout, server)

# function to do the work. path refers to the fader name, args refers to the value of the slider
def fader_callback(path, tags, args, source):
    global fader1Feedback
    if path=="/1/fader1":
        fader1Feedback = int(args[0])
        msg = OSCMessage("/1/label1")
        msg.insert(0, fader1Feedback)
        print "Fader 1 %i" % fader1Feedback
        arduino.write('X')
        arduino.write('\n')
        arduino.write(fader1Feedback)
        arduino.write('\n')
        client.send(msg)

        
def fader2_callback(path, tags, args, source):
    global fader2Feedback
    if path=="/1/fader2":
        fader2Feedback = int(args[0])
        msg = OSCMessage("/1/label2")
        msg.insert(0, fader2Feedback)
        print "Fader 2 %i" % fader2Feedback
        arduino.write('Y')
        arduino.write('\n')
        arduino.write(fader2Feedback)
        arduino.write('\n')
        client.send(msg)

#execute


    
server.addMsgHandler( "/1/fader1", fader_callback)
server.addMsgHandler( "/1/fader2", fader2_callback)

while True:
    server.handle_request()

arduino.close()
server.close()
