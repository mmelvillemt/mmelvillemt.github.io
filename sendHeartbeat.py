import sys
import time
import serial
import hashlib
import hmac
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad


def encrypt(msg, key, password):
    """
    Encrypts a message using AES encryption with the provided key and password.

    Parameters:
        msg: the message to be encrypted (string)
        key: the encryption key (bytes)
        password: the password to be used in the encryption (string)

    Returns:
        The encrypted message with start and end tags (bytes)
    """

    # Pads the message with extra characters in the case of lost data
    blocks = AES.block_size
    padMsg = pad(msg.encode('utf-8'), blocks)

    # Encrypts the message
    cipher = AES.new(key, AES.MODE_ECB)
    encodeMsg = cipher.encrypt(padMsg)

    # Hashes the message
    sha256Hash = hmac.new(password.encode('utf-8'), encodeMsg, hashlib.sha256)
    hashedMessage = sha256Hash.hexdigest()

    # Adds start and end tags to the message
    startTag = "sTag".encode('utf-8')
    endTag = "eTag".encode('utf-8')
    return startTag + encodeMsg + hashedMessage.encode('utf-8') + endTag


def main():
    # Counter for while loop
    i = 0

    # Change later
    key = b'\x99\xf3L\xeb\xc6`\xb1\x84\xfb\xddd\x1f\xa7\xff!+=\x06r\x17\xf7w1B\x97@\xcd\xbb\x9du\xf3/'
    password = "Ilovex88soMuch"

    # Default serial antenna baud rate
    baudRate = 57600
    outputPort = 'COM3'

    # TODO: Look into utility of parity
    outputSerial = serial.Serial(outputPort, baudRate, parity=serial.PARITY_NONE,
                                 stopbits=serial.STOPBITS_ONE, xonxoff=False,
                                 rtscts=False, dsrdtr=False)
    if not outputSerial.is_open:
        print("Port is closed, attempting to open...")
        outputSerial.open()

    # Continuously sends messages to drone
    while i < 100000:
        i += 1
        msg = str(i + 1).zfill(7) + ":go"
        encodeMsg = encrypt(msg, key, password)

        print("Message: ", msg)
        #print("Encoded Message", encodeMsg)
        #print("Byte Size of Encoded Message: ", sys.getsizeof(encodeMsg))

        outputSerial.write(encodeMsg)
        time.sleep(0.1)


if __name__ == "__main__":
    main()