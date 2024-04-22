import math
import time
import argparse
import threading
import serial
import hashlib
import hmac
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
from dronekit import connect, VehicleMode, LocationGlobalRelative
from pymavlink import mavutil

parser = argparse.ArgumentParser()
parser.add_argument('--connect', default='127.0.0.1:14650')
args = parser.parse_args()

# Connect to the vehicle
print 'Connecting to vehicle on: %s' % args.connect
vehicle = connect(args.connect, baud=921600, wait_ready=True)


def arm():
    """
     Arms drone once we have GPS lock and passed safety check and changes to guided mode.

     Args:
     N/A

     Returns:
     N/A
    """
    print "Basic pre-arm checks"
    # Don't let the user try to arm until autopilot is ready
    while not vehicle.is_armable:
        print "Waiting for vehicle to initialise..."
        time.sleep(1)
    print "Arming motors"

    # Copter should enter GUIDED mode for autonomous flight
    vehicle.mode = VehicleMode("GUIDED")
    vehicle.armed = True

    while not vehicle.armed:
        print " Waiting for arming..."
        time.sleep(1)

    print "Armed!"

def decrypt(msg, key):
    """
    Decrypts a message using the provided key.

    Args:
    msg: The encrypted message to be decrypted.
    key: The key used for decryption.

    Returns:
    The decrypted message as a UTF-8 encoded string.
    """

    blocks = AES.block_size
    cipher = AES.new(key, AES.MODE_ECB)

    # Decode message
    decodeMsg = cipher.decrypt(msg)
    unpadMsg = unpad(decodeMsg, blocks)

    return unpadMsg.decode('utf-8')

#The limp home time is the amount of time the drone can not receive an authentic message before it limps home
limpHomeTime = 1.5
def authenticate(encryptMsg, password, hashMsg):
    """
    Authenticates the message by comparing the hash of the encrypted message and the provided hash.

    Parameters:
    encryptMsg (bytes): The encrypted message to be authenticated.
    password (str): The password to be used in the authentication process.
    hashMsg (bytes): The hash of the message to be compared with the hash of the encrypted message.

    Returns:
    bool: True if the message is authenticated, False otherwise.
    """

    global count
    key = b'\x99\xf3L\xeb\xc6`\xb1\x84\xfb\xddd\x1f\xa7\xff!+=\x06r\x17\xf7w1B\x97@\xcd\xbb\x9du\xf3/'

    sha256Hash = hmac.new(password.encode('utf-8'), encryptMsg, hashlib.sha256)

    if hashMsg.decode('utf-8') == sha256Hash.hexdigest():
        decodeMsg = decrypt(encryptMsg, key)
    else:
        print "Message not validated, hash does not match"
        return False  # If hashes don't match, then return false about message authenticated

    splitMsg = decodeMsg.split(':')
    msgNum = int(splitMsg[0])
    msgStatus = splitMsg[1]

    print "Decoded Message: ", decodeMsg
    print "Here"

    if msgNum > count and msgStatus == "go":
        count = msgNum
        return True
    else:
        print "Error, either non-increasing msgNum or msgStatus != go"
        print "MsgNum:", msgNum
        print "msgStatus:", msgStatus
        print "Count: ", count
        return False

def run_heartbeat(status):
    try:
        # TODO Change hashing password before competition.
        password = "Ilovex88soMuch"
        #inputPort DEPENDENT ON SYSTEM RUNNING CODE, CHECK INPUT PORT
        inputPort = '/dev/ttyUSB0'

        # Default serial antenna baud rate, DO NOT CHANGE
        baudRate = 57600

        inputSerial = serial.Serial(inputPort, baudRate, parity=serial.PARITY_NONE,
                                    stopbits=serial.STOPBITS_ONE, xonxoff=False,
                                    rtscts=False, dsrdtr=False, timeout=0.09)
        startTime = time.time()
        receiveBuffer = b''
        startTag = "sTag".encode('utf-8')
        endTag = "eTag".encode('utf-8')

        while True:
            #Read the serial buffer
            receiveBuffer += inputSerial.read(4096)

            #Find the indexes of start and end tags
            startIndex = receiveBuffer.find(startTag)
            endIndex = receiveBuffer.find(endTag)
            nextStartIndex = receiveBuffer[startIndex + 4:].find(startTag)

            print "Current Elapsed Time"
            print(time.time() - startTime)

            if nextStartIndex != -1:
                nextStartIndex += 4 + startIndex

            print "Debugging: ", startIndex, endIndex, nextStartIndex

            if (startIndex == -1 or endIndex == -1) or (nextStartIndex != -1 and nextStartIndex < endIndex):
                endTime = time.time()
                elapsedTime = endTime - startTime

                if nextStartIndex != -1 and nextStartIndex < endIndex:
                    receiveBuffer = receiveBuffer[nextStartIndex:]

                if elapsedTime > limpHomeTime:
                    # Limp Home Sequence
                    print "Limped Home"
                    status["status"] = "bad"
                    while inputSerial.read():
                        # Do nothing
                        continue

                    break
                continue

        # At this point, we have identified a start index & end index
        # Checking total message length to ensure valid
        if (endIndex - startIndex) != 84:
            # Message is not correct length, either too long or too short
            # Discard message and restart loop
            receiveBuffer = receiveBuffer[endIndex + 4:]
            continue

        #Sets what was between the 1 start and end tag (if it is the correct length) to be the
        #received message.
        fullReceivedMsg = receiveBuffer[startIndex:endIndex + 4]
        fullReceivedMsg = fullReceivedMsg[4:-4]

        #Splits the received message into the 1st half that contains the encrypted message
        #and the 2nd have that contains the hash
        encryptMsg = fullReceivedMsg[:-64]
        hashMsg = fullReceivedMsg[-64:]

        receiveBuffer = receiveBuffer[endIndex + 4:]
        print receiveBuffer

        #Calculates the time elapsed since the last heartbeat
        endTime = time.time()
        elapsedTime = endTime - startTime

        if elapsedTime > limpHomeTime:
            # Limp Home
            print "Limped Home"
            status["status"] = "bad"

            while inputSerial.read():
                continue
            return

        #Checks if the message is authentic
        elif authenticate(encryptMsg, password, hashMsg):
            print "Good Message, Timer Reset"
            startTime = time.time()

    except Exception:
        print "Error occured, Limping home(Catch block)"
        status["status"] = "bad"


def main():
    # time.sleep(10)
    status = {"status": "go"}
    thread1 = threading.Thread(target=run_heartbeat, args=[status])

    thread1.start()
    time.sleep(2)  # Guarantees we have established heartbeat connection

    if status["status"] == "go":
        arm()

    # 921600 is the baud rate that you have set in the mission planner or qgc

    # List of waypoints
    height = 1
    wp0 = LocationGlobalRelative(42.2944411352563, -83.7104572355747, height)
    wp1 = LocationGlobalRelative(42.2945254560634, -83.7103861570358, height)
    wp2 = LocationGlobalRelative(42.2944371672155, -83.7103874981403, height)
    wp3 = LocationGlobalRelative(42.294333998068, -83.7103807926178, height)
    wp4 = LocationGlobalRelative(42.2943587983593, -83.7104585766792, height)
    wp5 = LocationGlobalRelative(42.2944351831951, -83.7105390429497, height)
    wp6 = LocationGlobalRelative(42.2944857756977, 83.7104558944702, height)
    wps = [wp0, wp1, wp2, wp3, wp4, wp5, wp6]

    waypointTolerance = 2
    heightTolerance = 0.1

    if status["status"] == "go":
        vehicle.simple_takeoff(height)

    while abs(height - vehicle.location.global_relative_frame.alt) >= heightTolerance:
        time.sleep(0.09)
        if status["status"] != "go":
            # Exit and Limp home

    vehicle.simple_goto(wps[1]) # Goes to waypoint 1
    while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[1]) >= waypointTolerance:
        time.sleep(0.09)
        if status["status"] != "go":
            break

    for i in range(2, 7):
        vehicle.simple_goto(wps[i])
        while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[i]) >= waypointTolerance:
            time.sleep(0.09)
            if status["status"] != "go":
                break

    vehicle.simple_goto(wps[1]) # Waypoint 1, after one loop
    while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[1]) >= waypointTolerance:
        time.sleep(0.09)
        if status["status"] != "go":
            break

    for i in range(2, 6):
        vehicle.simple_goto(wps[i])
        while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[i]) >= waypointTolerance:
            time.sleep(0.09)
            if status["status"] != "go":
                break

    vehicle.simple_land() # TODO: Delay until land
    # TODO: Drop package

    vehicle.simple_takeoff(height)
    while abs(height - vehicle.location.global_relative_frame.alt) >= heightTolerance:
        time.sleep(0.09)
        if status["status"] != "go":
            # Exit and Limp home

    for i in range(4, 0, -1):
        vehicle.simple_goto(wps[i]) # We end up back at waypoint 1
        while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[i]) >= waypointTolerance:
            time.sleep(0.09)
            if status["status"] != "go":
                break

    for i in range(6, -1, -1):
        vehicle.simple_goto(wps[i])
        while vehicle.get_distance_metres(vehicle.location.global_relative_frame, wps[i]) >= waypointTolerance:
            time.sleep(0.09)
            if status["status"] != "go":
                break

    vehicle.simple_land()
    # TODO: What do we do after landing?

    # If we get here, we have been hacked or completed the mission
    if status["status"] != "go":
        vehicle.mode = VehicleMode("RTL")
        time.sleep(20)
        vehicle.mode = VehicleMode("Brake")
        print "Limped Home"
    else:
        vehicle.simple_land()
        time.sleep(10)
        vehicle.mode = VehicleMode("Brake")
        print "Landed: Mission Complete"

    # Close thread 1
    thread1.join()

    # Close vehicle object
    vehicle.close()


if __name__ == "__main__":
    main()

