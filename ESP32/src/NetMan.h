#ifndef HTMLMan_h
#define HTMLMan_h

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "tools.h"

//typedef void handler_html_t (AsyncWebServerRequest *request);

class NetMan 
{
  private:
    uint16_t _port;

  public:
    AsyncWebServer  * _server;
    AsyncWebServerRequest * _request;
    String html;

    NetMan();
    NetMan(uint16_t port);

    //----------------------------------------------------------------
    // Outils server
    //----------------------------------------------------------------
    void on(const char * uri, ArRequestHandlerFunction handlerHTML);
    void onNotFound(ArRequestHandlerFunction handlerHTML);
    void begin();
    void loop();

    //----------------------------------------------------------------
    //   Gestion du WIFI
    //----------------------------------------------------------------
    void resetIP(IPAddress & ip);
    void getWifiIP(char * wifi_ip, int l);
    long getWifiQualite();
    bool connectWifiSTA(const char * ssid, const char * password, const IPAddress & ip, const IPAddress & gw, const IPAddress & masque) ;
    bool connectWifiAP(const char * ssid, const char * password, const IPAddress & ip, const IPAddress & gw, const IPAddress & masque);
    bool getMacAddress(uint8_t * addr);


    //----------------------------------------------------------------
    // Outils HTMLS
    //----------------------------------------------------------------
    bool getParamByte(const String & var,byte * value, int * nbChanged);
    bool getParamString(const String & var,char * value, int * nbChanged);
    bool getParamInt(const String & var,int16_t * value, int * nbChanged);

    void clear();
    void add(const String & h);
    void head(const String & title);
    void row(const String & h);
    void cellh(const String & h);
    void cell(const String & h);
//    void inputText(const String & name, const String & value, byte size, );
    void selectBegin(const String & var);
    void selectEnd();
    void selectOption(int val,int val_actuel,const String & lib);
    void selectOptionStr(const String & val,const String & val_actuel,const String & lib);

    void sendHTML();
};


#endif