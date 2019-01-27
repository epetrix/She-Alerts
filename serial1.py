#!/usr/bin/python
import serial
import time
import smtplib
from keys import *

#function used to send an email with proper json format
#returns nothing, either sends email or doesn't. prints result
def sendEmail(TO, SUBJECT, TEXT):
    BODY = '\r\n'.join(['To: %s' % TO,
                    'From: %s' % gmail_sender,
                    'Subject: %s' % SUBJECT,
                    '', TEXT])
    try:
        server.sendmail(gmail_sender, [TO], BODY)
        print('email sent!')
    except:
        print('error sending mail')

def alertEMS():
    to = 'vmc12@pitt.edu'
    sub = 'Fallen Elderly Alert'
    text = 'Elder patient registered to She Alerts may need assistance from a fall at 135 N Bellefield Ave.'
    sendEmail(to, sub, text)
    
def alertPatientCare():
    to = 'svw6@pitt.edu'
    sub = 'Fallen Patient Alert'
    text = 'Your patient registered to She Alerts may need assistance from a fall at her home.'
    sendEmail(to, sub, text)
    
#authentication for gmail access
gmail_sender = 'sheAlerts@gmail.com'
gmail_passwd = PASSWD
server = smtplib.SMTP_SSL('smtp.gmail.com', 465)
server.ehlo()
server.login(gmail_sender, gmail_passwd)

board = serial.Serial("/dev/tty.usbmodem1421", 9600)

time.sleep(5)
while(1):
    signal = board.read().decode("utf-8")
    print(signal)
    if (signal == '1'):
        alertEMS()
        alertPatientCare()
board.close()
