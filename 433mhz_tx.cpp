#include <cstring> 
#include <wiringPi.h>

#define TXpin  3
#define RETRANSMIT  3

int tOneHigh = 250;
int tOneLow = 250; 

int tZeroHigh = 250;
int tZeroLow = 1250;

int tSyncHigh = 250;
int tSyncLow = 2500;

int tPauseHigh = 250;
int tPauseLow = 10000;

char *On   = "1010100101101001010101100101011001010101010101010110100101010101";
char *Off  = "1010100101101001010101100101011001010101010101010110101001010101";

void sendZero() {
  digitalWrite(TXpin, HIGH);
  delayMicroseconds(tZeroHigh);
  digitalWrite(TXpin, LOW);
  delayMicroseconds(tZeroLow);
}

void sendOne() {
  digitalWrite(TXpin, HIGH);
  delayMicroseconds(tOneHigh);
  digitalWrite(TXpin, LOW);
  delayMicroseconds(tOneLow);
}

void sendCode(char *str, int len) {
  char *p = str;
  int i = 0;
  while (i <= len) {
    if (*p == '0') {
      sendZero();
    }
    if (*p == '1') {
      sendOne();
    }
    p++;
    i++;
  }
}

void sendSync() {
  digitalWrite(TXpin, HIGH);
  delayMicroseconds(tSyncHigh);
  digitalWrite(TXpin, LOW);
  delayMicroseconds(tSyncLow);
}

void sendPause() {
  digitalWrite(TXpin, HIGH);
  delayMicroseconds(tPauseHigh);
  digitalWrite(TXpin, LOW);
  delayMicroseconds(tPauseLow);
}

void sendPacket(char *pkt) {
  sendSync();
  sendCode(pkt, strlen(pkt));
  sendPause();
}

void sendPackets(char *pkt) {
  for (int i = 0; i < RETRANSMIT; i++) {
    sendPacket(pkt);
  }
}

int main (void) {
  wiringPiSetup() ;
  pinMode(TXpin, OUTPUT);
  sendPackets(On);
  delay(4000);
  sendPackets(Off);
  return 0;
}

