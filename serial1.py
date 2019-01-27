#!/usr/bin/python
import serial
import time
import smtplib
from keys import *

#function used to send an email in order to alert of errors found
#err is the specified error message based on the issue
#returns nothing, either sends email or doesn't.
def sendEmail():
    TO = 'vmc12@pitt.edu'
    SUBJECT = 'Patient Alert'
    TEXT = 'Your patient may have fallen down :('
    BODY = '\r\n'.join(['To: %s' % TO,
                    'From: %s' % gmail_sender,
                    'Subject: %s' % SUBJECT,
                    '', TEXT])
    try:
        server.sendmail(gmail_sender, [TO], BODY)
        print('email sent!')
    except:
        print('error sending mail')

#authentication for gmail access
gmail_sender = 'sheAlerts@gmail.com'
gmail_passwd = PASSWD
server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
server.ehlo()
server.login(gmail_sender, gmail_passwd)

board = serial.Serial("/dev/tty.usbmodem1411", 9600)

time.sleep(5)
while(1):
    signal = board.read().decode("utf-8")
    print(signal)
    if (signal == '1'):
        sendEmail()
    time.sleep(1)
board.close()
