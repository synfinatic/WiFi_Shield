
#ifndef __WIFLY_H__
#define __WIFLY_H__

#include <Arduino.h>
#include <Stream.h>

#define DEFAULT_WAIT_RESPONSE_TIME      1000        // 1000ms
#define DEFAULT_BAUDRATE                9600
#define MAX_CMD_LEN                     32
#define MAX_TRY_JOIN                    3

// Auth Modes for Network Authentication
// See WiFly manual for details
#define WIFLY_AUTH_OPEN        0    // Open (default)  
#define WIFLY_AUTH_WEP         1    // WEP-128
#define WIFLY_AUTH_WPA1        2    // WPA1
#define WIFLY_AUTH_WPA1_2      3    // Mixed-mode WPA1 and WPA2-PSK
#define WIFLY_AUTH_WPA2_PSK    4    // WPA2-PSK
#define WIFLY_AUTH_ADHOC       6    // Ad-hoc, join any Ad-hoc network

#include <AnySerial.h>

class WiFly : public AnySerial
{
public:
    WiFly(AnySerial &);
    WiFly(AnySerial *);

    size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

    static WiFly *getInstance() {
        return instance;
    }

    boolean init();
    boolean reset();
    boolean save();
    boolean reboot();

    boolean join(const char *ssid);
    boolean join(const char *ssid, const char *phrase, int auth = WIFLY_AUTH_OPEN);
    boolean isAssociated();
    boolean isAssociated(const char *ssid);
    boolean leave();

    boolean connect(const char *host, uint16_t port, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    boolean connect(unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);

    boolean staticIP(const char *ip, const char *mask, const char *gateway);

    int send(const char *data, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    int send(const uint8_t *data, int len, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    int receive(uint8_t *buf, int len, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);

    boolean ask(const char *q, const char *a, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);
    boolean sendCommand(const char *cmd, const char *ack = NULL, unsigned int timeout = DEFAULT_WAIT_RESPONSE_TIME);

    boolean commandMode();
    boolean dataMode();

    void clear();

    float version();

private:
    static WiFly  *instance;

    AnySerial serial;

    boolean command_mode;
    boolean associated;
    uint8_t dhcp;
    uint8_t error_count;

};

#endif // __WIFLY_H__

