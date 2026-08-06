//=======================================================================================================================
//
/// @file web.cpp
/// 
/// Body file for web management: Handle web pages 
/// 
/// @author Eric GENOTELLE
/// @date 2024
///
//=======================================================================================================================

#include "netman.h"
// #include "SPIFFS.h"
#include "img/imgstart.h"
#include "img/imgstop.h"
#include "img/imgplus.h"
#include "img/imgminus.h"
#include "img/imgreset.h"
#include "img/imgmetronome.h"
#include "img/favicon.h"

#include <ElegantOTA.h>

#include "config.h"
#include "sound.h"
#include "global.h"
#include "device.h"
#include "web.h"
#include "global.h"

NetMan nm;
char msg[200];

char panID[50];

//------------------------------------------------------------------------------------------------------------------------
/// @brief  Handle ROOT HTML page
/// @param request 
void _handleRoot(AsyncWebServerRequest *request) 
{
  nm._request = request;
  String ligne;

  DEBUG1("----------------------");
  DEBUG1("_handleRoot()");

  // --------------------------
  // Affichage de la page HTML
  // --------------------------
  nm.clear();
  nm.head( String(APPLI_NAME) );
  nm.add("<script>");
  nm.add("var idChange=-1;");
  nm.add("var playing=0;");
  nm.add("function doAction(action,arg1) {");
//  nm.add( "  alert(action);");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  var tmp = '&idChange='+idChange;" );
  nm.add( "  if (action=='bpm') {");
  nm.add( "    tmp = '&arg1=' + document.getElementById('bpm').value;");
  nm.add( "  } else if ( action=='volclic') {");
  nm.add( "    tmp = '&arg1=' + document.getElementById('volclictxt').value;");
  nm.add( "  } else if ( action=='decompte') {");
  nm.add( "    tmp = '&arg1=' + document.getElementById('decomptetxt').value;");
  nm.add( "  } else if ( action=='measurefirst') {");
  nm.add( "    tmp = '&arg1=' + document.getElementById('measurefirst').value;");
  nm.add( "  } else if ( action=='measurelast') {");
  nm.add( "    tmp = '&arg1=' + document.getElementById('measurelast').value;");
  nm.add( "  } else if ( action=='withsound') {");
  nm.add( "    tmp = '&arg1=' + (document.getElementById('withsound').checked ? '1' : '0' );");
  nm.add( "  } else if ( action=='modetuto') {");
  nm.add( "    tmp = '&arg1=' + (document.getElementById('modetuto').checked ? '1' : '0' );");
  nm.add( "  } else if ( action=='loop') {");
  nm.add( "    tmp = '&arg1=' + (document.getElementById('loop').checked ? '1' : '0' );");
  nm.add( "  } else if ( action=='clic') {");
  nm.add( "    tmp = '&arg1=' + (document.getElementById('clic').checked ? '0' : '1' );");
  nm.add( "  } else {");
  nm.add( "    tmp = '&arg1=' + arg1");
  nm.add( "  }" );
  nm.add( "  var uri = 'rest?action=' + action + tmp;" );
  nm.add( "  xhttp.open('GET', uri, true);");
  nm.add( "  xhttp.send(); ");
  nm.add( "}" );
  
  //document.getElementById('bpm').value = document.getElementById('bpm').value + 1;
  nm.add( "" );
  nm.add( "function incValue(champ,val) {");
  nm.add( "  var v = parseInt( document.getElementById(champ).value );" );
  nm.add( "  const valMin = parseInt( document.getElementById(champ).min );" );
  nm.add( "  const valMax = parseInt( document.getElementById(champ).max );" );
  nm.add( "  v = v + val;" );
  nm.add( "  if (v>valMax) { v = valMax; }" );
  nm.add( "  if (v<valMin) { v = valMin; } " );
  nm.add( "  document.getElementById(champ).value = v.toString(); " );
  nm.add( "}");
  nm.add( "" );

  nm.add( "function start_stop() {");
  nm.add( "  if ( playing == 1) {");
  nm.add( "    doAction('stop',''); ");
  nm.add( "  } else {" );
  nm.add( "    doAction('play',''); ");
  nm.add( "  }" );
  nm.add( "}" );
  
  nm.add( "function checkActivation() {");
  nm.add( "  if (document.getElementById('filename').innerHTML=='' ) {");
  nm.add( "   document.getElementById('tsong').style.display='none';");
  nm.add( "  } else {" );
  nm.add( "   document.getElementById('tsong').style.display='block';");
  nm.add( "  }" );
  nm.add( "  if ( playing == 1) {");
  nm.add( "   document.getElementById('play').src='/stop.png';");
  nm.add( "   document.getElementById('modetuto').disabled=true;");
  nm.add( "   document.getElementById('bpm').disabled=true;");
  nm.add( "   document.getElementById('bpmdec').disabled=true;");
  nm.add( "   document.getElementById('bpminc').disabled=true;");
  nm.add( "   document.getElementById('resetbpm').disabled=true;");
  nm.add( "   document.getElementById('trunning').style.display='block';");
  nm.add( "  } else {" );
  nm.add( "   document.getElementById('play').src='/start.png';");
  nm.add( "   document.getElementById('modetuto').disabled=false;");
  nm.add( "   document.getElementById('bpm').disabled=false;");
  nm.add( "   document.getElementById('bpmdec').disabled=false;");
  nm.add( "   document.getElementById('bpminc').disabled=false;");
  nm.add( "   document.getElementById('resetbpm').disabled=false;");
  nm.add( "   document.getElementById('trunning').style.display='none';");
  nm.add( "  }" );
  nm.add( "}" );

  nm.add( "function getServerData() {");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "      const obj = JSON.parse(this.responseText);");
  nm.add( "      const idChangeNew = obj.idchange;");
  nm.add( "      document.getElementById('msg').innerHTML = obj.msg;");
  nm.add( "      if (idChange != idChangeNew) {");
  nm.add( "        const activeElement = document.activeElement;");
  nm.add( "        playing  = obj.playing;");
  nm.add( "        document.getElementById('filename').innerHTML = obj.filename;");
  nm.add( "        document.getElementById('bpmbase').innerHTML = obj.bpmbase;");
  nm.add( "        document.getElementById('keysign').innerHTML = obj.keysign;");
  nm.add( "        document.getElementById('timesign').innerHTML = obj.timesign;");
  nm.add( "        document.getElementById('modetuto').checked = (obj.modetuto==1);");
  nm.add( "        if (activeElement.id!='bpm') document.getElementById('bpm').value = obj.bpm;");
  nm.add( "        document.getElementById('volclictxt').textContent = obj.volclic;");
  nm.add( "        document.getElementById('volclicinput').value = obj.volclic;");
  nm.add( "        document.getElementById('decomptetxt').textContent = obj.decompte;");
  nm.add( "        document.getElementById('decompteinput').value = obj.decompte;");
  nm.add( "        document.getElementById('version').innerHTML = obj.version;");
  nm.add( "        document.getElementById('measurefirst').min = '1';");
  nm.add( "        document.getElementById('measurefirst').max = obj.measurelast;");
  nm.add( "        if (activeElement.id!='measurefirst')  document.getElementById('measurefirst').value = obj.measurefirst;");
  nm.add( "        document.getElementById('measurelast').min = obj.measurefirst;");
  nm.add( "        document.getElementById('measurelast').max = obj.nbmeasures;");
  nm.add( "        if (activeElement.id!='measurelast')  document.getElementById('measurelast').value = obj.measurelast;");
  nm.add( "        document.getElementById('withsound').checked = (obj.withsound==1) ;");
  nm.add( "        document.getElementById('loop').checked = (obj.loop==1) ;");
  nm.add( "        document.getElementById('clic').checked = (obj.clic==0) ;");
  nm.add( "        checkActivation();");
  nm.add( "      }" );
  nm.add( "      if (playing==1) {");
  nm.add( "        document.getElementById('curmeasure').innerHTML =  obj.curmeasure;");
nm.add( "        document.getElementById('curnote').innerHTML =  obj.curnote;");
  nm.add( "        document.getElementById('progression').value = obj.progression;");
  nm.add( "      }" );
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  xhttp.open('GET', '/rest?action=info', true);");
  nm.add( "  xhttp.send(); ");
  nm.add( " }" );

  nm.add( " function redirectFile() {");
  nm.add( "  document.getElementById('formFile').target = 'iframeFile'; ");
  nm.add( "  document.getElementById('formFile').submit(); ");
  nm.add( " }");

  nm.add("</script>");

  nm.add("<body>");
  nm.add( "<h2>" + String(APPLI_NAME) + " - Contrôle</h2>");
  nm.add( "<p><b><span id='msg'></b><p>");

nm.add("<div><iframe id='iframeFile' name='iframeFile' src=''  style='position: absolute;width:0;height:0;border:0;'></iframe></div>");

  nm.add( "<table id='tgeneral'>");
  // nm.add( "<tr><th>Volume</th>");
  // nm.add( "  <td><input id='volgeninput' type='range' min='0' max='100' step=1 disabled value='0'/><output id='volgentxt'></output></td></tr>"); 
  nm.add( "<tr><th> MORCEAU </th>"); 

  nm.add(" <td><form id=formFile method='POST' action='/upload' enctype='multipart/form-data'>");
  nm.add("<div id='main'><input type='file' id='filemidi' accept='audio/midi,audio/x-midi,.mid,.midi' name='filemidi' onchange='redirectFile()'/>");
//  nm.add("<input type='button' name='action' value='Upload' onclick='redirectFile()'/>");
//  nm.add("<iframe id='iframeFile' name='iframeFile' src=''></iframe>  </div></form>");
  nm.add("</div></form>");

  nm.add("<p> <button onclick=\" doAction('loaddemo','');  \"  id='loaddemo' > DEMO </button> </td></tr>");

  nm.add( "<tr><th> METRONOME </th>"); 
  nm.add("  <td><input id='bpm' type='number' min='" + String(conf.BPM_MIN) + "' max='" + String(conf.BPM_MAX) + "' step=1 value='30'/>");
  nm.add("<button onclick=\" incValue('bpm',-1);  doAction('bpm','');  \"  id='bpmdec' > <img src='/minus.png' style='height:17;' > </button>");
  nm.add("<button onclick=\"  incValue('bpm',1);  doAction('bpm','');  \"  id='bpminc' > <img src='/plus.png' style='height:17;' > </button>");
  nm.add("<button onclick=\" doAction('resetbpm','');  \"  id='resetbpm' > <img src='/reset.png' style='height:17;' > </button>");
  nm.add("<button onclick=\" doAction('metronome','');  \"  id='metronome' > <img src='/metronome.png' style='height:17;' > </button>");
  nm.add( " <br>Volume: <input id='volclicinput' type='range' min='1' max='100' step=1 value='30'/><output id='volclictxt'></output>");
  nm.add( " &nbsp;</td></tr>"); 
 
  nm.add( "</table><p>");

  nm.add( "<table id='tsong'>"); 

  nm.row( "<th> TITRE </th>      <td> <span id='filename'></span></td>" );
  nm.row( "<th> INFO </th>       <td> <span id='keysign'></span>&nbsp;&nbsp;&nbsp;<span id='timesign'></span> &nbsp;&nbsp;&nbsp;   <span id='bpmbase'></span> bpm </td>" );
 
  nm.add( "<tr><th> SEQUENCER </th>    <td>   <input id='withsound' type='checkbox' /> <label for='withsound'> AUDIO </label> &nbsp;   <input id='modetuto' type='checkbox' /> <label for='modetuto'> MODE TUTO </label> &nbsp;   ");
  nm.add( "<p><input id='loop' type='checkbox' /> <label for='loop'> BOUCLE </label> &nbsp;  MES. <input id='measurefirst' name='measurefirst' type='number' min='1' max='100' required step=1 value='1'/> à <input id='measurelast' name='measurelast' type='number' min='1' max='100' required step=1 value='100'/> ");
  nm.add( "<p style='text-align:center'><img src='/start.png' onclick=\" start_stop();\" id='play'>");
//  nm.add( "<img src='/stop.png'  onclick=\" doAction('stop',''); \" id='stop'></p>");
  nm.add( "</td></tr>" );

  nm.add( "<tr><th> CLIC </th>  <td> <input id='clic' type='checkbox' /> <label for='clic'> MUET </label> &nbsp;");
  nm.add( " <br>Décompte: <input id='decompteinput' type='range' min='0' max='2' step=1 value='1'/><output id='decomptetxt'></output> MES.");
  nm.add( " &nbsp;</td></tr>"); 
  
//  nm.row( "<th>Mesures</th> <td> De <input id='measurefirst' name='measurefirst' type='number' min='1' max='100' required step=1 value='1'/> à <input id='measurelast' name='measurelast' type='number' min='1' max='100' required step=1 value='100'/> </td>" );

  // nm.add( "<tr><th>Commandes</th><td>"); 
//  nm.add("  <button onclick=\" doAction('learn','');  \"  id='learn' >Apprentissage</button>");
  // nm.add("</td></tr>");
  nm.add( "</table><p>");


  nm.add( "<table id='trunning'>"); 
  nm.row( "<th> Mesure en cours</th> <td> <div id='curmeasure'/></td>" );
  nm.row( "<th> Note en cours</th> <td>   <div id='curnote'/></td>" );
  nm.row( "<th>Avancement</th>       <td> <progress id='progression' value=\"\" max=\"100\"></progress></td>" );
  nm.add( "</table><p>");

  
#ifdef UNDO
  // ----------------------------------------
  // list of notes/sounds 
  nm.add( "<p><table><tr>"); 
  for (int i=0; i < NB_PIEZZO; i++) {
    nm.add("<td><button onclick=\" doAction('playnote','" + String(i) + "');  \"  id='playnote' >" + String(sounds[i].noteName) + "</button></td>");
  }
  nm.add( "</tr></table>");
#endif


#ifdef WEB_KEYBOARD
  // ----------------------------------------
  // Keyboard
  // ----------------------------------------
  nm.add( "<p><table class='kb'><tr>"); 
  nm.add( "<tr>"); 
  nm.add ( "  <td class='vide'> &nbsp; </td>");
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','1');\"  id='playnote'> A# </button> </td>" );
  nm.add ( "  <td class='vide' colspan=2> &nbsp; </td>");
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','4');\"  id='playnote'> C# </button> </td>" );
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','6');\"  id='playnote'> D# </button> </td>" );
  nm.add ( "  <td class='vide' colspan=2> &nbsp; </td>");
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','9');\"  id='playnote'> F# </button> </td>" );
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','11');\" id='playnote'> G# </button> </td>" );
  nm.add ( "  <td colspan=2 class='noire'> <button onclick=\"doAction('playnote','13');\" id='playnote'> A# </button> </td>" );
  nm.add( "</tr>"); 
  nm.add( "<tr>"); 
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','0');\"  id='playnote'> A </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','2');\"  id='playnote'> B </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','3');\"  id='playnote'> C </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','5');\"  id='playnote'> D </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','7');\"  id='playnote'> E </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','8');\" id='playnote'> F </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','10');\" id='playnote'> G </button> </td>" );
  nm.add ( "  <td colspan=2 class='blanche'> <button onclick=\"doAction('playnote','12');\" id='playnote'> A </button> </td>" );
  nm.add ( "  <td class='vide'> &nbsp; </td>");
  nm.add( "</tr>"); 
  nm.add( "</tr></table>");
#endif 
//  nm.add("<p> style='font-size:80%;'><a href='/piezzo'>Config Seuil piezzo</a>  <a href='/update'>Update firmware</a> </p>");
  nm.add("<button onclick=\"javascript:window.location.href='/piezzo' \"  id='seuil' > Config Seuil piezzo </button> ");
  nm.add("<button onclick=\"javascript:window.location.href='/update'  \"  id='update' > Update firmware </button> </p>");
  nm.add( "<p style='font-size:70%;'>Version:<span id='version'/> ");

  // ----------------------------------------
  // Javascript - en fin de page
  // ----------------------------------------
  nm.add( "<script>");
  nm.add("");
  // nm.add( "const bpmtxt = document.querySelector('#bpmtxt');"  );
  // nm.add( "const bpminput = document.querySelector('#bpminput');" );
  // nm.add( "bpmtxt.textContent = bpminput.value;") ;
  // nm.add( "bpminput.addEventListener('input', (event) => {  bpmtxt.textContent = event.target.value; }); ") ;
  // nm.add( "bpminput.addEventListener('change', (event) => {  doAction('bpm',event.target.value); }); ") ;
  // nm.add("");
  nm.add( "const bpm = document.getElementById('bpm'); ") ;
  nm.add( "bpm.addEventListener('change', (event) => { incValue('bpm',0); doAction('bpm',event.target.value);});  ") ;
  nm.add("");
  // nm.add( "const volgentxt = document.querySelector('#volgentxt');"  );
  // nm.add( "const volgeninput = document.querySelector('#volgeninput');" );
  // nm.add( "volgentxt.textContent = volgeninput.value;") ;  
  // nm.add( "volgeninput.addEventListener('input', (event) => {  volgentxt.textContent = event.target.value; }); ") ;
  // nm.add( "volgeninput.addEventListener('mouseup', (event) => {  doAction('volgen',event.target.value); }); ") ;
  // nm.add("");
  nm.add( "const volclictxt = document.getElementById('volclictxt');"  );
  nm.add( "const volclicinput = document.getElementById('volclicinput');" );
  nm.add( "volclictxt.textContent = volclicinput.value;") ;  
  nm.add( "volclicinput.addEventListener('input', (event) => {  volclictxt.textContent = event.target.value; }); ") ;
  nm.add( "volclicinput.addEventListener('change', (event) => {  doAction('volclic',event.target.value); }); ") ;
  nm.add("");
  nm.add( "const decomptetxt = document.getElementById('decomptetxt');"  );
  nm.add( "const decompteinput = document.getElementById('decompteinput');" );
  nm.add( "decomptetxt.textContent = decompteinput.value;") ;  
  nm.add( "decompteinput.addEventListener('input', (event) => {  decomptetxt.textContent = event.target.value; }); ") ;
  nm.add( "decompteinput.addEventListener('change', (event) => {  doAction('decompte',event.target.value); }); ") ;
  nm.add("");
  nm.add( "const measurefirst = document.getElementById('measurefirst'); ") ;
  nm.add( "const measurelast = document.getElementById('measurelast');  ") ;
  nm.add( "measurefirst.addEventListener('change', (event) => { incValue('measurefirst',0); measurelast.min = event.target.value; doAction('measurefirst',event.target.value);});  ") ;
  nm.add( "measurelast.addEventListener('change', (event) => { incValue('measurelast',0); measurefirst.max = event.target.value; doAction('measurelast',event.target.value);});  ") ;
  nm.add("");
  nm.add( "const withsound = document.getElementById('withsound'); ") ;
  nm.add( "const loop = document.getElementById('loop');  ") ;
  nm.add( "const clic = document.getElementById('clic');  ") ;
  nm.add( "withsound.addEventListener('input', (event) => { doAction('withsound',event.target.value);});  ") ;
  nm.add( "loop.addEventListener('input', (event) => { doAction('loop',event.target.value);});  ") ;
  nm.add( "clic.addEventListener('input', (event) => { doAction('clic',event.target.value);});  ") ;
  nm.add("");
  nm.add( "const modetuto = document.getElementById('modetuto'); ") ;
  nm.add( "modetuto.addEventListener('input', (event) => { doAction('modetuto',event.target.value);});  ") ;
  nm.add("");
  nm.add( "setInterval(function() {getServerData();}, " + String(DELAY_LOOP_WEBPARAM) + ");");
  nm.add( "" );
  nm.add( "</script>");
  nm.add("</body>");
  nm.add("</html>");
  nm.sendHTML();
}


void __displayConfigSound(int i) 
{
  nm.add( "<tr><th>" + String(sounds[i].noteName) + "</th>  ");
  nm.add( "  <td><input id='threshold" + String(i) + "' type='number' min='1' max='4095' required class='plage' value='"  + sounds[i].threshold + "'/> ");
  nm.add("<button onclick=\" incValue('threshold" + String(i) + "',-50);  changeThreshold( " + String(i) + " );  \"  id='thresholddec" + String(i) + "' > - </button>");
  nm.add("<button onclick=\"  incValue('threshold" + String(i) + "',50);  changeThreshold( " + String(i) + " );  \"  id='thresholdinc" + String(i) + "' > + </button>");

  nm.add("</td>  </tr>"); 
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief  Handle configuration HTML page
/// @param request 
void _handleConfig(AsyncWebServerRequest *request, bool modeUser) 
{
  nm._request = request;
  String ligne;

  DEBUG1("----------------------");
  DEBUG2("_handleConfig()",modeUser);

  // --------------------------
  // Affichage de la page HTML
  // --------------------------
  nm.clear();
  if (modeUser) {
    nm.head(String (APPLI_NAME) + " - Sensibilité piezzo");
  }  else {
    nm.head(String (APPLI_NAME) + " - Paramétrage");
  }
  nm.add("<script>");
  nm.add( "" );

  nm.add( "function sleep(ms) {");
//  nm.add( "  return new Promise(resolve => setTimeout(resolve, ms));");
  nm.add( "  return ;");
  nm.add( "}");
  
  nm.add( "function incValue(champ,val) {");
  nm.add( "  var v = parseInt( document.getElementById(champ).value );" );
  nm.add( "  const valMin = parseInt( document.getElementById(champ).min );" );
  nm.add( "  const valMax = parseInt( document.getElementById(champ).max );" );
  nm.add( "  v = v + val;" );
  nm.add( "  if (v>valMax) { v = valMax; }" );
  nm.add( "  if (v<valMin) { v = valMin; } " );
  nm.add( "  document.getElementById(champ).value = v.toString(); " );
  nm.add( "}");
  nm.add( "" );
  
  nm.add("function changeThreshold(note) {");
//  nm.add( "  alert(action);");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  var uri = '/rest?action=threshold&arg1=' + note + '&arg2=' +  document.getElementById('threshold' + note +'').value;" );
  nm.add( "  xhttp.open('GET', uri, true);");
  nm.add( "  xhttp.send(); ");
  nm.add( "}" );
  nm.add( "" );

  nm.add("function changeThresholdA() {");
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo < 8) {
      nm.add( "    document.getElementById('threshold" + String(i) + "').value = document.getElementById('thresholdA').value; "  );
      nm.add( "    changeThreshold(" + String(i) + ");" );
    }
  }
  nm.add( "}" );
  nm.add( "" );


  nm.add("function changeThresholdB() {");
  for (int i=0; i<NB_PIEZZO; i++) {
    if (sounds[i].PINpiezzo >= 8) {
      nm.add( "    document.getElementById('threshold" + String(i) + "').value = document.getElementById('thresholdB').value; "  );
      nm.add( "    changeThreshold(" + String(i) + ");" );
    }
  }
  nm.add( "}" );
  nm.add( "" );

  nm.add("function doAction(action,arg1) {");
//  nm.add( "  alert(doAction);");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  var uri = '/rest?action=' + action + '&arg1=' + arg1 ;" );
  nm.add( "  xhttp.open('GET', uri, true);");
  nm.add( "  xhttp.send(); ");
  nm.add( "}" );
  nm.add( "" );
  nm.add("</script>");

  nm.add("<body>");
  if (modeUser) {

    nm.add( "<h2>" + String(APPLI_NAME) + " Configuration</h2>");

    nm.add( "<table>");
  
    nm.row( "<td>&nbsp;</td> <th>Seuil déclenchement</th> ");


    nm.row( "<tr><td colspan=2 class='blanche'>Grand Saladier - A</td>  ");
    nm.add( "<tr><td class='blanche'><b>Toutes notes</b></td>  ");
    nm.add( "  <td><input id='thresholdA' type='number' min='1' max='4095' required class='plage' value='"  +  String(PIEZZO_THRESHOLD_DEF) + "'/> ");
    nm.add("   <button onclick=\" incValue('thresholdA',-50);  changeThresholdA();  \"  id='thresholdAdec' > - </button>");
    nm.add("  <button onclick=\"  incValue('thresholdA',50);  changeThresholdA();  \"  id='thresholdAinc' > + </button>");
    nm.add("</td>  </tr>"); 
    for (int i=0; i<NB_PIEZZO; i++) {
      if (sounds[i].PINpiezzo < 8) {
        __displayConfigSound(i);
      }
    }
    nm.row( "<td colspan=2>  <button onclick=\" doAction('saveconfig','');  \"  id='saveconfig' > Enregistrer </button> </td>");

    nm.row( "<td colspan=2> &nbsp;</td>  ");

    nm.row( "<td colspan=2 class='blanche'>Petit Saladier - B</td>  ");
    nm.add( "<tr><td class='blanche'><b>Toutes notes</b></td>  ");
    nm.add( "  <td><input id='thresholdB' type='number' min='1' max='4095' required class='plage' value='"  +  String(PIEZZO_THRESHOLD_DEF) + "'/> ");
    nm.add("   <button onclick=\" incValue('thresholdB',-50);  changeThresholdB();  \"  id='thresholdBdec' > - </button>");
    nm.add("  <button onclick=\"  incValue('thresholdB',50);  changeThresholdB();  \"  id='thresholdBinc' > + </button>");
    nm.add("</td>  </tr>"); 
    for (int i=0; i<NB_PIEZZO; i++) {
      if (sounds[i].PINpiezzo >= 8) {
        __displayConfigSound(i);
      }
    }
    nm.row( "<td colspan=2>  <button onclick=\" doAction('saveconfig','');  \"  id='saveconfig' > Enregistrer </button> </td>");

    nm.add( "</table>");
    nm.add("<p> ");
    nm.add(" <button onclick=\" doAction('resetconfig',''); sleep(1000); window.location.href='/piezzo';  \"  id='resetconfig' > Restaurer Config Usine</button> ");
    nm.add(" <button onclick=\" doAction('reboot','');  \"  id='reboot' > Reboot </button> ");
    nm.add("<p><button onclick=\"javascript:window.location.href='/' \"  id='home' > Accueil </button> ");
    } else {

 
      nm.add( "");
      nm.add( "<p><table id='tparam'>");

      nm.row( "<td class='blanche'>Paramètre</td> <td class='blanche'>Description</td>  <th>Valeur</th>  <td class='blanche'>Usine</td>  <td class='blanche'>Min</td> <td class='blanche'>Max</td>");
      for (int i=0; i<nbParameters; i++) {
        nm.row( "<td>" + parameters[i].name + "</td>"
          + "<td>" + parameters[i].description + "</td> <td><input id='" 
          + parameters[i].name + "' type='number' min='" + parameters[i].min + "' max='" + parameters[i].max 
          + "' required class='plage' step=" +  parameters[i].step + " value='" +  String( *(parameters[i].pValue) ) 
          + "'/></td>   <td>" + String(parameters[i].def) + "</td>" +
          + "<td>" + String(parameters[i].min) + "</td>" +
          + "<td>" + String(parameters[i].max) + "</td>" );
      }
      nm.add( "</table>");
      nm.add("<p> ");
      nm.add(" <button onclick=\" doAction('saveconfig','');  \"  id='saveconfig' > Enregistrer </button>");
      nm.add(" <button onclick=\" doAction('resetconfig',''); sleep(1000); window.location.href='/config';  \"  id='resetconfig' > Restaurer Config Usine</button> ");
      nm.add(" <button onclick=\" doAction('reboot','');  \"  id='reboot' > Reboot </button> ");
      nm.add("<p><button onclick=\"javascript:window.location.href='/' \"  id='home' > Accueil </button> ");
    }

  // ----------------------------------------
  // Javascript - end of page
  // ----------------------------------------
  nm.add( "<script>");
  nm.add("");
  if (modeUser) {
      for (int i=0; i<NB_PIEZZO; i++) {
      nm.add( "document.getElementById('threshold" + String(i) + "').addEventListener('change', (event) => { changeThreshold(" + String(i) + ");});  ") ;
    }
    nm.add( "document.getElementById('thresholdA').addEventListener('change', (event) => { changeThresholdA();});  ") ;
    nm.add( "document.getElementById('thresholdB').addEventListener('change', (event) => { changeThresholdB();});  ") ;
  } else {
    for (int i=0; i<nbParameters; i++) {
      nm.add( "document.getElementById('" + parameters[i].name + "').addEventListener('change', (event) => { doAction('" + parameters[i].name + "',event.target.value);});  ") ;
    }
  }
  nm.add( "" );
  nm.add( "</script>");
  nm.add("</body>");
  nm.add("</html>");
  nm.sendHTML();
}

void _handleConfigUser(AsyncWebServerRequest *request) 
{
  _handleConfig(request,true);
}

void _handleConfigAdmin(AsyncWebServerRequest *request) 
{
  _handleConfig(request,false);
}

//------------------------------------------------------------------------------------------------------------------------
/// @brief Check if current HTTP parameter <paramHTTP> is egal to parameter <paramName>. if so, get the value and save in <addrValue>. If no value, get default value <defaultValue>
/// @param paramHTTP current HTTP parameter
/// @param paramName parameter
/// @param addrValue where to save the value 
/// @param defaultValue default value if no value
/// @return true if found, false if not.
bool _checkParamSongInt(const char *paramHTTP, const char * paramName, int16_t * addrValue, int16_t defaultValue)
{
  if ( ! strcmp(paramHTTP,paramName) )  {
    song.idChange++;
    nm.add( "ok" );
    int nbChanged=0;

    int16_t temp = defaultValue;
    nm.getParamInt("arg1",&temp,&nbChanged);
    *addrValue = temp;
    DEBUG3("checkParamSongInt",paramName, temp);
    nm.sendHTML();    
    return true;
  } 
  return false;
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief HANDLE web to manage actions requested by ROOT page
/// @param request 
void _handleRest(AsyncWebServerRequest *request) 
{
//  DEBUG1("_handleRest()");

  String ligne;

  nm._request = request;
  char value[255];
  int nbChanged=0;
  bool res=false;
  bool actionDone=false;
  int16_t idChangeClient;
  int16_t tmpInt;

  nm.getParamString("action",value,&nbChanged);
  nm.clear();

  //-----------------------------------------------
  // play a note
  if ( _checkParamSongInt(value, "playnote", &tmpInt , 0) ) {
    touchNote( tmpInt , 100);
    return;
  }

  //-----------------------------------------------
  // Get INFO in Json format
  if ( (!actionDone)  && (!strcmp(value,"info")) ) {
    actionDone = true;
    res = true;
    idChangeClient = -1;
    ligne = String("{");
    ligne += " \"idchange\":\"" + String(song.idChange) + "\",";
    ligne += " \"msg\":\"" + String(song.lastMsg) + "\",";
    if ( idChangeClient != song.idChange ) {
      ligne += " \"filename\":\"" + String(song.filename) + "\",";
      ligne += " \"nbnotes\":" + String(song.nbNotes) + ",";
      ligne += " \"nbmeasures\":" + String(song.nbMeasures) + ",";
      ligne += " \"clic\":" + String(song.withClic) + ",";
      ligne += " \"volclic\":" + String(song.volumeClic) + ",";
      ligne += " \"decompte\":" + String(song.decompte) + ",";
      ligne += " \"loop\":" + String(song.loop) + ",";
      ligne += " \"withsound\":" + String(song.withSound) + ",";
      ligne += " \"bpm\":" + String(song.bpm) + ",";
      ligne += " \"bpmbase\":" + String(song.bpmBase) + ",";
      ligne += " \"keysign\":\"" + String(song.keySignature) + "\",";
      ligne += " \"timesign\":\"" + String(song.timeSignatureNom) + "/" +  String(song.timeSignatureDenom) + "\",";
      ligne += " \"volgen\":" + String(conf.volumeGen) + ",";
      ligne += " \"playing\":" + String(song.playing) + ",";
      ligne += " \"measurefirst\":" + String(song.measureFirst) + ",";
      ligne += " \"measurelast\":" + String(song.measureLast) + ",";
      ligne += " \"double\":" + String(song.doubleNotes) + ",";
      ligne += " \"decompte\":" + String(song.decompte) + ",";
      ligne += " \"metronome\":" + String(song.metronome) + ",";
      ligne += " \"version\":\"" + String(PROGRAMME_VERSION) + " - "+ String(PROGRAMME_DATE) + " - " + String(PROGRAMME_TIME) + " - ID:" + panID + " - Son:" + String(BANKNAME) ;
  #ifdef MIDI_SEND
      ligne += " avec MIDI";
  #endif
      ligne += "\",";
      if ( song.modeAuto ) {
        ligne += " \"modetuto\":\"0\",";
      } else {
        ligne += " \"modetuto\":\"1\",";
      }
    }

    if (song.playing) {
      if (song.doubleNotes) {
          ligne += " \"curnote\":\"" + String( sounds[  song.lNotes[song.noteCur].idxSound ].noteName ) + " + " +  String( sounds[  song.lNotes[song.noteCur+1].idxSound ].noteName ) + "\",";
      } else {
        ligne += " \"curnote\":\"" + String( sounds[  song.lNotes[song.noteCur].idxSound ].noteName ) + "\",";
      }
      ligne += " \"curmeasure\":" + String( song.lNotes[song.noteCur].measure ) + ",";
      ligne += " \"progression\":\"" + String(  (int)( (song.lNotes[song.noteCur].measure - song.measureFirst) * 100 / (song.measureLast-song.measureFirst+1)  ) ) + "\",";
    }
    ligne += " \"last\":1"; 
    ligne += "}";
    nm.add( ligne );
    nm.sendHTML();    
    return;
  }     

  //-----------------------------------------------
  // Start song 
  if ( _checkParamSongInt(value, "play", &tmpInt , 0) ) {
//    song.modeAuto = true;
    startSong();
    return; 
  }

  //-----------------------------------------------
  // withsound
  if ( _checkParamSongInt(value, "modetuto", &tmpInt, 0) ) {
    song.modeAuto = (tmpInt==0);
    DEBUG2("modeAuto",song.modeAuto ?"ON":"OFF")
    return;
  }
  
  //-----------------------------------------------
  // Stop playing stop
  if ( _checkParamSongInt(value, "stop", &tmpInt , 0) ) {
    stopSong();
    return;
  }     

  //-----------------------------------------------
  // change BPM
  if ( _checkParamSongInt(value, "bpm", &song.bpm , song.bpm) ) {
    if (song.nbNotes>0)
      computeSongTime(true);
    return;
  }     

  //-----------------------------------------------
  // reset BPM
  if ( _checkParamSongInt(value, "resetbpm", &tmpInt , 0) ) {
    song.bpm = song.bpmBase;
    if (song.nbNotes>0)
      computeSongTime(true);
    return;
  } 

  //-----------------------------------------------
  // change general volume
  if ( _checkParamSongInt(value, "volgen", &conf.volumeGen , conf.volumeGen) ) {
    return;
  }

  //-----------------------------------------------
  // change measure first
  if ( _checkParamSongInt(value, "measurefirst", &song.measureFirst, 0) ) {
    return;
  }

  //-----------------------------------------------
  // change measure last
  if ( _checkParamSongInt(value, "measurelast", &song.measureLast, 0) ) {
    return;
  }

  //-----------------------------------------------
  // withsound
  if ( _checkParamSongInt(value, "withsound", &tmpInt, 0) ) {
    song.withSound = tmpInt;
    return;
  }
  
  //-----------------------------------------------
  // loop
  if ( _checkParamSongInt(value, "loop", &tmpInt, 0) ) {
    song.loop = tmpInt;
    return;
  }

  //-----------------------------------------------
  // loop
  if ( _checkParamSongInt(value, "clic", &tmpInt, 0) ) {
    song.withClic = tmpInt;
    return;
  }

  //-----------------------------------------------
  // loop
  if ( _checkParamSongInt(value, "decompte", &tmpInt, 0) ) {
    song.decompte = tmpInt;
    return;
  }


  //-----------------------------------------------
  // change clic volume
  if ( _checkParamSongInt(value, "volclic", &tmpInt , song.volumeClic) ) {
    song.volumeClic = tmpInt;
    return;
  }

  
  //-----------------------------------------------
  // metronome
  if ( _checkParamSongInt(value, "metronome", &tmpInt , 0) ) {
    if ( song.playing ) 
      return;
    if ( song.metronome ) {
      stopMetronome();
    } else {
      startMetronome();
    }
    return;
  }

  //-----------------------------------------------
  // toggle led gauche
  if ( _checkParamSongInt(value, "ledl", &tmpInt , 0) ) {
    DEBUG2("ledl",tmpInt);
    displayLED(tmpInt,  ! sounds[tmpInt].ledLeftOn , HandLeft) ;
    return;
  }

  //-----------------------------------------------
  // toggle led droite
  if ( _checkParamSongInt(value, "ledr", &tmpInt , 0) ) {
    DEBUG2("ledl",tmpInt);
    displayLED(tmpInt,  ! sounds[tmpInt].ledRightOn , HandRight) ;
    return;
  }

  
  //-----------------------------------------------
  // All piezo Thresholds
  //-----------------------------------------------
  if ( (!actionDone)  && (!strcmp(value,"threshold") ) ) {
    song.idChange++;
    actionDone = true;
    res = true;
    int16_t note;
    int16_t threshold;
    nm.getParamInt("arg1",&note,&nbChanged);
    nm.getParamInt("arg2",&threshold,&nbChanged);
    DEBUG3("threshold",note,threshold);
    nm.add( "ok" );
    
    if ( (note>=0) && (note<NB_PIEZZO) ) {
      sounds[note].threshold = threshold;
    }
    return;
  }     

  //-----------------------------------------------
  // Check all parameters
  //-----------------------------------------------
  for (int i=0; i<nbParameters; i++ ) {
    if ( _checkParamSongInt(value, parameters[i].name.c_str(), &tmpInt , 0) ) {
      DEBUG2(parameters[i].name,tmpInt);
      *(parameters[i].pValue) = tmpInt;
      if ( parameters[i].name == "ADC_DB" )  {
        DEBUG2("analogSetPinAttenuation",conf.ADC_DB);
        analogSetPinAttenuation(PIN_MUX_VAL,(adc_attenuation_t)conf.ADC_DB);
      }
      return;
    }    
  }


  //-----------------------------------------------
  // Load demo song
   if ( _checkParamSongInt(value, "loaddemo", &tmpInt, 0) ) {
    loadSong(demoMidi,demoMidiLen);
    strcpy(song.filename,"DEMO");
    return;
  }


  //-----------------------------------------------
  // Save config in EEPROM
  if ( _checkParamSongInt(value, "saveconfig", &tmpInt, 0) ) {
    saveConfigEEPROM();
    return;
  }

  //-----------------------------------------------
  // Reset config in EEPROM
  if ( _checkParamSongInt(value, "resetconfig", &tmpInt, 0) ) {
    resetConfigEEPROM();
    return;
  }     

  //-----------------------------------------------
  // REBOOT ESP
  if ( _checkParamSongInt(value, "reboot", &tmpInt, 0) ) {
    ESP.restart();
    return;
  }     

  //-----------------------------------------------
  // Get log of piezzohit
  if ( _checkParamSongInt(value, "logpiezzo", &tmpInt, 0) ) {
    ligne = String("{");
    int id=0;
  DEBUG2("!! logPiezzoPos",logPiezzoPos);
    for (uint8_t i=logPiezzoPos; i<NB_LOG_PIEZZO; i++) {
      ligne += " \"ts_" + String(id) + "\":\"" + String(logPiezzo[i].ts) + "\","; 
      if (logPiezzo[i].ts>0) {
        ligne += " \"idxSound_" + String(id) + "\":\"" + String(logPiezzo[i].idxSound) + "\","; 
        ligne += " \"note_" + String(id) + "\":\"" + String( sounds[logPiezzo[i].idxSound].noteName ) + "\","; 
        ligne += " \"value_" + String(id) + "\":\"" + String(logPiezzo[i].value) + "\","; 
      } else {
        ligne += " \"idxSound_" + String(id) + "\":\"\","; 
        ligne += " \"note_" + String(id) + "\":\"\","; 
        ligne += " \"value_" + String(id) + "\":\"\","; 
      }
      id++;
    }
    for (uint8_t i=0; i<logPiezzoPos; i++) {
      ligne += " \"ts_" + String(id) + "\":\"" + String(logPiezzo[i].ts) + "\","; 
      if (logPiezzo[i].ts>0) {
        ligne += " \"idxSound_" + String(id) + "\":\"" + String(logPiezzo[i].idxSound) + "\","; 
        ligne += " \"note_" + String(id) + "\":\"" + String( sounds[logPiezzo[i].idxSound].noteName ) + "\","; 
        ligne += " \"value_" + String(id) + "\":\"" + String(logPiezzo[i].value) + "\","; 
      } else {
        ligne += " \"idxSound_" + String(id) + "\":\"\","; 
        ligne += " \"note_" + String(id) + "\":\"\","; 
        ligne += " \"value_" + String(id) + "\":\"\","; 
      }
      id++;
    }
    ligne += " \"last\":\"1\""; 
    ligne += "}";
    nm.add( ligne );
    nm.sendHTML();    
    return;
  }     

}


//------------------------------------------------------------------------------------------------------------------------
/// @brief Handle FileUpload
/// @param request   AsyncWebServerRequest
/// @param filename  uploaded filename
/// @param index 
/// @param data 
/// @param len 
/// @param final 
//  @note https://github.com/smford/esp32-asyncwebserver-fileupload-example/blob/master/example-01/example-01.ino
void _handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) 
{
  DEBUG1("_handleUpload");
  static size_t taille=0;
  static char _filename[100];
  
  if (!index) {
    DEBUG1(_filename);
    fileMidiLen = 0;
    taille = 0;
    msg[0] = 0;
    snprintf( _filename, sizeof(_filename) -1, "%s", filename.c_str() ) ;
    DEBUG2("filename",_filename)
  }

  if (len) {
    taille += len;

    // check if size is OK
    if ( taille > FILE_MIDI_MAX_SIZE ) {
      fileMidiLen = 0;
    } else {
      DEBUG2("copy",len);
      memcpy( fileMidi + fileMidiLen , data, len);
      fileMidiLen += len;
    }
  }

  if (final) {
    DEBUG1("upload final");
    song.idChange++;
    // check if MIDI file is OK
    if (fileMidiLen==0) {
      sprintf(msg,"Taille du fichier trop grande >=%d octets (max=%d octets)", taille, FILE_MIDI_MAX_SIZE );
      DEBUG1(msg);
      initiateSong();
    } else {
      // Try to load the song
      loadSong(fileMidi,fileMidiLen);
      strcpy(song.filename,_filename);
      if (song.nbNotes==0) {
        sprintf(msg,"Ce n'est pas un fichier MIDI" );
        DEBUG1(msg);
        initiateSong();
      } else {
        DEBUG1("Song loaded.");
      }
    }
    // DefaultHeaders::Instance().addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    // DefaultHeaders::Instance().addHeader("Pragma", "no-cache");
    // DefaultHeaders::Instance().addHeader("Expires", "0");
    //request->redirect("/");
    // String html = "BOU!!";
 

      //AsyncWebServerResponse *response = request->beginResponse(200, "text/html", html.c_str(), html.length());

     uint8_t RHTML[20];
     sprintf((char*)RHTML,"OK");
     AsyncWebServerResponse *response = request->beginResponse(200, "text/html", RHTML, sizeof(RHTML));
     request->send(response);

    // DEBUG1("request->send()...");
    //request->send(200, "text/plain", "File Uploaded !");
    //DEBUG1("request->send().");
    // request->send ( 200, "text/html", html );   
  }
}


//------------------------------------------------------------------------------------------------------------------------
/// @brief HANDLE web to enter in test mode
/// @param request 
void _handleTest(AsyncWebServerRequest *request) 
{

  nm._request = request;
  String ligne;

  DEBUG1("----------------------");
  DEBUG1("_handleTestMode()");
  conf.testMode = true;

  // --------------------------
  // Affichage de la page HTML
  // --------------------------
  nm.clear();
  nm.head( String(APPLI_NAME) + String("  - Test") );
  nm.add("<script>");
  nm.add("function doAction(action,arg1) {");
//  nm.add( "  alert(action + ' , ' + arg1 );");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  var uri = '/rest?action=' + action + '&arg1= ' + arg1;" );
  nm.add( "  xhttp.open('GET', uri, true);");
  nm.add( "  xhttp.send(); ");
  nm.add( "}" );

  nm.add( "function getServerData() {");
  nm.add( "  var xhttp = new XMLHttpRequest();");
  nm.add( "  xhttp.onreadystatechange = function() {");
  nm.add( "    if (this.readyState == 4 && this.status == 200) {");
  nm.add( "      const obj = JSON.parse(this.responseText);");

  for (int i=0; i < NB_LOG_PIEZZO; i++) {
    nm.add( "        document.getElementById('ts_" + String(i) + "').innerHTML = obj.ts_" + String(i) + ";");
    nm.add( "        document.getElementById('note_" + String(i) + "').innerHTML = obj.note_" + String(i) + ";");
    nm.add( "        document.getElementById('value_" + String(i) + "').innerHTML = obj.value_" + String(i) + ";");
  }
  nm.add( "    }" );
  nm.add( "  };" );
  nm.add( "  xhttp.open('GET', '/rest?action=logpiezzo', true);");
  nm.add( "  xhttp.send(); ");
  nm.add( " }" );
  nm.add("</script>");
  nm.add( "" );
  nm.add( "" );
  nm.add( "<table id='tled'>"); 
  nm.row( "<td> &nbsp; </td> <th> LED Gauche </td> <th> LED Droite </td>" );
  String id;
  for (int i=0; i < NB_PIEZZO; i++ ) {
    nm.add( "<tr><th> " + String(sounds[i].noteName) + "</th>" ); 
    nm.add("  <td> <input id='" + String("ledl_") + String(i) + "' type='checkbox' /> </td>");
    nm.add("  <td> <input id='" + String("ledr_") + String(i) + "' type='checkbox' /> </td>");
    nm.add("</tr>");
  }
  nm.add( "</table>"); 

  nm.add( "<table id='tlog'>"); 
  nm.row( "<td> &nbsp; </td> <th> TimeStamp</th> <th>Note</th> <th>Value</th>" );
  for (int i=0; i < NB_LOG_PIEZZO; i++ ) {
    nm.add( "<tr><th> " + String(i+1) + "</th>" ); 
    nm.add("  <td> <div id='ts_" + String(i) + "'/> </td> ");
    nm.add("  <td> <div id='note_" + String(i) + "'/> </td> ");
    nm.add("  <td> <div id='value_" + String(i) + "'/> </td> ");
    nm.add("</tr>");
  }
  nm.add( "</table>"); 

  //nm.row( "<th> Mode </th>           <td> <div id='mode'/></td>" );

  // ----------------------------------------
  // Javascript - en fin de page
  // ----------------------------------------
  nm.add( "<script>");
  nm.add("");
  for (int i=0; i < NB_PIEZZO; i++ ) {
    nm.add( "document.getElementById('" + String("ledl_") + String(i) + "').addEventListener('input', (event) => { doAction('ledl'," + String(i) + ");});  ") ;
    nm.add( "document.getElementById('" + String("ledr_") + String(i) + "').addEventListener('input', (event) => { doAction('ledr'," + String(i) + ");});  ") ;
  }

  nm.add( "setInterval(function() {getServerData();},1000);");
  nm.add( "" );
  nm.add( "</script>");
  
  nm.add("</body>");
  nm.add("</html>");
  nm.sendHTML();
}


const String & displayParam(const String & name, const  String & val) {
  return String("<th>") + name + "</th><td>" + val + "</td>";
}

const String & displayParam(const String & name, int16_t val) {
  return displayParam(name, String(val));
}

const String & displayParam(const String & name, unsigned long val) {
  return displayParam(name,String(val));
}

const String & displayParam(const String & name, bool val) {
  return displayParam(name, val ? "VRAI" : "FAUX" );
}


///------------------------------------------------------------------------------------------------------------------------
/// @brief HANDLE web to DEBUG
/// @param request 
void _handleDebug(AsyncWebServerRequest *request) 
{

  nm._request = request;

  DEBUG1("----------------------");
  DEBUG1("_handleDebug()");

  nm.clear();
  nm.head( String(APPLI_NAME) + String("  - DEBUG") );
  nm.add( "" );
  nm.add( "<table id='tsong'>"); 
  nm.row( "<th> Param</td> <th> Valeur </th>" );

  nm.row( "<th> playing </th> <td> " +  String(song.playing ? "Vrai" : "Faux") + "</td>" ); 
  nm.row( "<th> modeAuto </th> <td> " +  String(song.modeAuto ? "Vrai" : "Faux") + "</td>" ); 
  nm.row( "<th> doubleNotes </th> <td> " + String(song.doubleNotes) + "</td>" ); 
  nm.row( "<th> noteCur </th> <td> " + String(song.noteCur) + "</td>" ); 
  nm.row( "<th> measureCur </th> <td> " + String(song.measureCur) + "</td>" ); 
  nm.row( "<th> nextClicMs </th> <td> " + String(song.nextClicMs) + "</td>" ); 
  nm.row( "<th> clicCurBeat </th> <td> " + String(song.clicCurBeat) + "</td>" ); 
  nm.row( "<th> nbNotes </th> <td> " + String(song.nbNotes) + "</td>" ); 
  nm.row( "<th> nbMeasures </th> <td> " + String(song.nbMeasures) + "</td>" ); 

  nm.row( "<th> t0 </th> <td> " + String(song.t0) + "</td>" ); 
  nm.row( "<th> tf </th> <td> " + String(song.tf) + "</td>" ); 
  nm.row( "<th> noteFirst </th> <td> " + String(song.noteFirst) + "</td>" ); 
  nm.row( "<th> noteLast </th> <td> " + String(song.noteLast) + "</td>" ); 
  nm.row( "<th> measureFirst </th> <td> " + String(song.measureFirst) + "</td>" ); 
  nm.row( "<th> measureLast </th> <td> " + String(song.measureLast) + "</td>" ); 
  nm.row( "<th> loop </th> <td> " +  String(song.loop ? "Vrai" : "Faux") + "</td>" ); 
  nm.row( "<th> withClic </th> <td> " +  String(song.withClic ? "Vrai" : "Faux") + "</td>" ); 
  nm.row( "<th> decompte </th> <td> " + String(song.decompte) + "</td>" ); 
  nm.row( "<th> timeSignatureNom </th> <td> " + String(song.timeSignatureNom) + "</td>" ); 
  nm.row( "<th> timeSignatureDenom </th> <td> " + String(song.timeSignatureDenom) + "</td>" ); 
  nm.row( "<th> ppqn </th> <td> " + String(song.ppqn) + "</td>" ); 
  nm.row( "<th> withSound </th> <td> " +  String(song.withSound ? "Vrai" : "Faux") + "</td>" ); 
  nm.row( "<th> metronome </th> <td> " +  String(song.metronome ? "Vrai" : "Faux") + "</td>" ); 
  nm.add( "</table><p>" ); 

  if (song.lNotes != NULL) {
    nm.add( "<table id='tnotes'>"); 
    nm.row( "<td>&nbsp;</td> <th>idxSound</th> <th>Note</th> <th>State</th> <th>velocity</th> <th>measure</th>  <th>timeMidiStart</th> <th>timeMidiStop</th> <th>timeMsStart</th> <th>timeMsStop</th> <th>lastPlayed</th>" );
    for (int i=0; i<song.nbNotes; i++) {
      T_SongNote * pNote = & song.lNotes[i];
      nm.add( "<tr><th>" + String(i) + "</th>" );
      nm.add( "<td>" + String(pNote->idxSound) + "</td>" );
      nm.add( "<td>" + String(pNote->noteMidi) + "</td>" );
      nm.add( "<td>" + String(pNote->state) + "</td>" );
      nm.add( "<td>" + String(pNote->velocity) + "</td>" );
      nm.add( "<td>" + String(pNote->measure) + "</td>" );
      nm.add( "<td>" + String(pNote->timeMidiStart) + "</td>" );
      nm.add( "<td>" + String(pNote->timeMidiStop) + "</td>" );
      nm.add( "<td>" + String(pNote->timeMsStart) + "</td>" );
      nm.add( "<td>" + String(pNote->timeMsStop) + "</td>" );
      nm.add( "<td>" + String(pNote->lastPlayed) + "</td>" );
      nm.add( "</tr>" );
    }
    nm.add( "</table><p>" ); 
  }

  nm.add("</body>");
  nm.add("</html>");
  nm.sendHTML();
}


#ifdef CAPTURE_PIEZZO
///------------------------------------------------------------------------------------------------------------------------
/// @brief HANDLE web to display piezzo hits (mode CAPTURE_PIEZZO)
/// @param request 
void _handleCapture(AsyncWebServerRequest *request) 
{

  nm._request = request;

  DEBUG1("----------------------");
  DEBUG1("_handleCapture()");
  DEBUG2("Core:",xPortGetCoreID());

  // find the max value
  uint16_t max_val = 0;
  int max_range = 0;
  for (int j=0; j<PIEZZO_NB; j++) {
    if  (piezzoVal[j] > max_val) {
      max_val = piezzoVal[j];
      max_range = j;
    }
  }
  nm.clear();
  nm.head( String(APPLI_NAME) + String("  - Capture") );
  nm.add( "" );
  nm.add( "<table id='tpiezzo'>"); 
//  nm.row( "<th>DUREE (micro sec): </th>  <td>" + String (piezzoTF-piezzoT0) + "</td>" );
  nm.row( "<th>Time</th>  <th>Value</th>" );
  for (int j=0; j<PIEZZO_NB; j++) {
    nm.add( "<tr><td>" + String (piezzoTime[j]-piezzoTime[0]) + "</td>" );
    if (j == max_range) {
      nm.add( "<th>" + String(piezzoVal[j]) + "</th>" );
    } else {
      nm.add( "<td>" + String(piezzoVal[j]) + "</td>" );
    }
  }  
  nm.add("</body>");
  nm.add("</html>");
  nm.sendHTML();}
#endif // CAPTURE_PIEZZO


void _handleIMGstart(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGstart,IMGstartLen);
}
void _handleIMGstop(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGstop,IMGstopLen);
}
void _handleIMGplus(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGplus,IMGplusLen);
}
void _handleIMGminus(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGminus,IMGminusLen);
}
void _handleIMGreset(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGreset,IMGresetLen);
}
void _handleIMGmetronome(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",IMGmetronome,IMGmetronomeLen);
}
void _handlefavicon(AsyncWebServerRequest *request) 
{
  request->send(200,"image/png",favicon,faviconLen);
}



//------------------------------------------------------------------------------------------------------------------------
/// @brief Setup Web contex : connect to WIFI + reference HTML handler
void setupWeb()
{
  DEBUG1("setupWeb ...");

  DEBUG1("  Setup WIFI...")
  IPAddress ip;
  IPAddress masqueip;
  bool ret;

  uint8_t mac_addr[6];
  esp_efuse_mac_get_default(mac_addr);
  sprintf(panID,"%s_%02X%02X%02X",PAN_WIFI_AP_SSID,mac_addr[3],mac_addr[4],mac_addr[5]);

  ip.fromString(PAN_WIFI_IP);
  masqueip.fromString(PAN_WIFI_MASQUE);
#ifdef PAN_WIFI_MODE_STA
  ret = nm.connectWifiSTA(PAN_WIFI_STA_SSID,PAN_WIFI_STA_PASSWORD,ip,ip,masqueip);
  DEBUG2("     connectWifiSTA",ret)
#else
  DEBUG2("SSID",panID);
  ret = nm.connectWifiAP(panID,PAN_WIFI_AP_PASSWORD,ip,ip,masqueip);
  DEBUG2("     connectWifiAP",ret)
#endif

  DEBUG1("  Setup Web pages...")
  nm.on("/",_handleRoot);
  nm.on("/piezzo",_handleConfigUser);
  nm.on("/config",_handleConfigAdmin);
  nm.on("/rest",_handleRest);
  nm.on("/test",_handleTest);
  nm.on("/debug",_handleDebug);

#ifdef CAPTURE_PIEZZO
nm.on("/capture",_handleCapture);
#endif
  nm.on("/start.png",_handleIMGstart);
  nm.on("/stop.png",_handleIMGstop);
  nm.on("/plus.png",_handleIMGplus);
  nm.on("/minus.png",_handleIMGminus);
  nm.on("/reset.png",_handleIMGreset);
  nm.on("/metronome.png",_handleIMGmetronome);
  nm.on("/favicon.ico",_handlefavicon);
  // run handleUpload function when any file is uploaded
  nm._server->on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200);
      }, _handleUpload);
  // DefaultHeaders::Instance().addHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  // DefaultHeaders::Instance().addHeader("Pragma", "no-cache");
  // DefaultHeaders::Instance().addHeader("Expires", "0");
  nm.begin();
  DEBUG1("      Web pages OK.")

  DEBUG1("setup OTA...");
  ElegantOTA.begin(nm._server); 

  DEBUG1("setupWeb OK."); 

}

void loopWeb()
{
  ElegantOTA.loop();
}


