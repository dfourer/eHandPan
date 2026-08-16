/*
 * Gestionnaire de page html
 */

#include "NetMan.h"
#include <esp_wifi.h>
#include <esp_efuse.h>

NetMan::NetMan() 
{
  _port = 80;
  _server = new AsyncWebServer(_port);
  clear();
}

NetMan::NetMan(uint16_t port) 
{
  _port = port;
  _server = new AsyncWebServer(_port);
  clear();
}

//----------------------------------------------------------------
// Outils server
//----------------------------------------------------------------
void NetMan::on(const char * uri, ArRequestHandlerFunction handlerHTML)
{
  _server->on(uri, HTTP_GET|HTTP_POST,  handlerHTML );
}


void NetMan::onNotFound(ArRequestHandlerFunction handlerHTML)
{
  _server->onNotFound(handlerHTML);
}

void NetMan::begin()
{
  _server->begin();
}

void NetMan::loop()
{
  // _server.handleClient();
}


//----------------------------------------------------------------
// Gestion du WIFI
//----------------------------------------------------------------  

/*
 * reset à 0 l'adresse IP
 */
void NetMan::resetIP(IPAddress & ip) 
{
  ip = IPAddress(0,0,0,0);
}

/*
   récupère l'adresse IP Wifi et met à jour la variable "wifi_ip"
*/
void NetMan::getWifiIP(char * wifi_ip, int l)
{
  IPAddress myIP = WiFi.localIP();
  snprintf(wifi_ip, l, "%d.%d.%d.%d", myIP[0], myIP[1], myIP[2], myIP[3]);
}

/*
   récupére la qualité du WIFI en %
*/
long NetMan::getWifiQualite()
{
  long rssi = WiFi.RSSI();
  long rssiCalc;
  if (rssi <= -100)
    rssiCalc = 0;
  else if (rssi >= -50)
    rssiCalc = 100;
  else
    rssiCalc = 2 * (rssi + 100);

  return rssiCalc;
}

#define WIFI_POWER WIFI_POWER_11dBm
/*
 * Connexion WIFi en mode STA (client)
 */
bool NetMan::connectWifiSTA(const char * ssid, const char * password, const IPAddress & ip, const IPAddress & gw, const IPAddress & masque) 
{
  bool ret=false;

  DEBUG1("connectWifiSTA()...");
  DEBUG2("  ssid: ", ssid);
  DEBUG2("  password: ", password);
//  DEBUG2("  ip:",ip.toString())
//  DEBUG2("  gw:",gw.toString())
//  DEBUG2("  masque:",masque.toString())

  WiFi.mode(WIFI_STA);
  WiFi.hostname("spacedrum");
  WiFi.begin(ssid, password);
  int nbtry = 0;
  while ( (WiFi.status() != WL_CONNECTED) && (nbtry < 16) )  {
    delay(500);
#ifdef DEBUGAPP
    Serial.print(".");
#endif
    nbtry++;
  }
  IPAddress  myIP = WiFi.localIP();
  //DEBUG2("IP address: ",myIP);
  DEBUG2("IP address: ",myIP);

  if (WiFi.status() == WL_CONNECTED) {
    ret = true;
    DEBUG1("Connexion OK");
  } else {
    DEBUG1("Connexion KO");
  }  
  return ret;
}

/*
 * Connexion WIFi en mode AP (serveur)
 */
bool NetMan::connectWifiAP(const char * ssid,const char * password, const IPAddress & ip, const IPAddress & gw, const IPAddress & masque) 
{
  bool ret=false;

  DEBUG1("connectWifiAP()...");
  DEBUG2("  ssid: ", ssid);
  DEBUG2("  password: ", password);
  DEBUG2("  ip:",ip.toString())
  DEBUG2("  gw:",gw.toString())
  DEBUG2("  masque:",masque.toString())

  WiFi.mode(WIFI_AP);
    
  WiFi.softAPConfig(ip, gw, masque);
  WiFi.hostname(ssid); 
  WiFi.softAP(ssid, password);

  wifi_config_t conf;
  esp_wifi_get_config(WIFI_IF_AP, &conf);
  // conf.ap.authmode = WIFI_AUTH_WPA2_PSK;
  conf.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
  // conf.ap.channel = 6;
  esp_wifi_set_config(WIFI_IF_AP, &conf);  

  IPAddress myIP = WiFi.softAPIP();
  DEBUG2("IP address: ",myIP);  

  return true;
}


bool NetMan::getMacAddress(uint8_t * addr) {
  esp_err_t ret = esp_wifi_get_mac(WIFI_IF_AP, addr);
  return  (ret == ESP_OK) ;

    // uint32_t value;
    // esp_efuse_read_block(ESP_EFUSE_BLK3, &value);
    // addr[0] = value >> 0;
    // addr[1] = value >> 8;
    // addr[2] = value >> 16;
    // addr[3] = value >> 24;
    // esp_efuse_read_block(ESP_EFUSE_BLK3, &value);
    // addr[4] = value >> 0;
    // addr[5] = value >> 8;
    // return true;
}



//----------------------------------------------------------------
// Outils HTMLS
//----------------------------------------------------------------  
bool NetMan::getParamByte(const String & var,byte * value, int * nbChanged)
{
  byte ret;
  bool res=false;
  if ( _request->hasParam(var) ) {
    ret = atoi( _request->getParam(var)->value().c_str() );
    if (ret != *value) {
      *nbChanged = *nbChanged +1 ;
      *value = ret;
      res=true;
    }        
  }
  return res;
}

bool NetMan::getParamString(const String & var,char * value, int * nbChanged)
{
  char *cp;
  bool res=false;
  if ( _request->hasParam(var) ) {
    cp = (char *) _request->getParam(var)->value().c_str() ;
    //DEBUG3(var, "=", cp);
    if ((strlen(cp)>0) && strcmp(cp,value) ){
      strcpy(value,cp);
      *nbChanged = *nbChanged +1 ;
      res=true;
      //DEBUG1(" -> modif");
    }
  }
  return res;

}


bool NetMan::getParamInt(const String & var,int16_t * value, int * nbChanged)
{
  int16_t ret;
  bool res=false;
  if ( _request->hasParam(var) ) {
//DEBUG2("getParamInt", var);
    ret = atoi( _request->getParam(var)->value().c_str() );
//DEBUG2("   ->val=", ret);
    if (ret != *value) {
      *nbChanged = *nbChanged +1 ;
      *value = ret;
      res=true;
    }        
  }
  return res;
}


void NetMan::clear()
{
  html = "";
}

void NetMan::add(const String & h)
{
    html += h + "\r\n";
}


void NetMan::head(const String & title)
{
    html = "<html> <head>\
    <title>" + title + "</title>\r\n\
    <meta charset='UTF-8'>\r\n\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\r\n\
    <style>\r\n\
      body { background-color: #FAFAFA; font-family: Arial; Color: #000000; min-width: max-content; }\r\n\
      h2 { Color: #0c0cd4; }\r\n\
      h3 { Color: #2E2EFE; }\r\n\
      table { border: 0; } \r\n\
      table.kb { border: 0; width: 100%; } \r\n\
      th { border: thin solid #6495ed;  padding: 2px; background-color: #D0E3FA; width:110px; } \r\n\
      td { border: thin solid #6495ed;  padding: 2px; text-align: center; background-color: #ffffff; }\r\n\
      td.vide { border: 0;  padding: 5px; text-align: center; background-color: #ffffff; }\r\n\
      td.blanche { border: thin solid #6495ed;  padding: 5px; text-align: center; background-color: #7cc7f3; }\r\n\
      td.noire { border: thin solid #6495ed;  padding: 5px; text-align: center; background-color: #4b4949; }\r\n\
      input.plage { text-align: right; margin-right: 5px; width: 4em;   } \r\n\
      #measurefirst { width: 4em;   } \r\n\
      #measurelast  { width: 4em;   } \r\n\
      #bpm { width: 4em;   } \r\n\
    </style>\r\n\
  </head>\r\n";
}

void NetMan::row(const String & h)
{
  html += "<tr>" + h + "</tr>\r\n";
}

void NetMan::cell(const String & h)
{
  html += "<td>" + h + "</td>\r\n";
}

void NetMan::cellh(const String & h)
{
  html += "<th>" + h + "</th>\r\n";
}

void NetMan::selectBegin(const String & var)
{
  html += "<select name=";
  html += var;
  html += ">\r\n";
}

void NetMan::selectEnd()
{
  html += "</select>\r\n";
}

void NetMan::selectOption(int val,int val_actuel,const String & lib)
{
  html += "<option value=";
  html += val;
  if (val==val_actuel) {
    html += " selected";
  }
  html += ">";
  html += lib;
  html += "</option>\r\n";
}

void NetMan::selectOptionStr(const String & val,const String & val_actuel,const String & lib)
{
  html += "<option value=";
  html += val;
  if (val==val_actuel) {
    html += " selected";
  }
  html += ">";
  html += lib;
  html += "</option>\r\n";
}


void NetMan::sendHTML()
{
  _request->send ( 200, "text/html", html );    
  html = "";
}