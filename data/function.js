var xmlHttp=createXmlHttpObject();
function createXmlHttpObject(){
 if(window.XMLHttpRequest){
  xmlHttp=new XMLHttpRequest();
 }else{
  xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');
 }
 return xmlHttp;
}
function load(){
 if(xmlHttp.readyState==0 || xmlHttp.readyState==4){
  xmlHttp.open('PUT','/config.xml',true);
  xmlHttp.send(null);
  xmlHttp.onload = function(e) {
   loadBlock();
  }
 }
}

function loadBlock(data2) {
 data2 = xmlHttp.responseXML;
 data = document.getElementsByTagName('body')[0].innerHTML;
 var new_string;
 var $kids = data2.getElementsByTagName("Donnees")[0].childNodes;
 [].forEach.call($kids, (el) => {
  var tagName = el.tagName;
  var cols = data2.getElementsByTagName(tagName)[0].textContent;
  new_string = data.replace(new RegExp('{{'+tagName+'}}', 'g'), cols);
  data = new_string;
 });
 document.getElementsByTagName('body')[0].innerHTML = new_string;
 handleServerResponse();
}

function val(id){
 var v = document.getElementById(id).value;
 return v;
}
function xml(id){
 xmlResponse=xmlHttp.responseXML;
 var n = xmlResponse.getElementsByTagName(id)[0].firstChild.nodeValue;
 return n;
}
function xml_to_val(xml, val){
 xmlResponse=xmlHttp.responseXML;
 document.getElementById(val).value = xmlResponse.getElementsByTagName(xml)[0].firstChild.nodeValue;
}
function send_request(submit,server){
 request = new XMLHttpRequest();
 request.open("GET", server, true);
 request.send();
 save_status(submit,request);
}
function save_status(submit,request){
 old_submit = submit.value;
 request.onreadystatechange = function() {
  if (request.readyState != 4) return;
  submit.value = request.responseText;
  setTimeout(function(){
   submit.value=old_submit;
   submit_disabled(false);
  }, 1000);
 }
 submit.value = 'Подождите...';
 submit_disabled(true);
}
function submit_disabled(request){
 var inputs = document.getElementsByTagName("input");
 for (var i = 0; i < inputs.length; i++) {
  if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
 }
}
function toggle(target) {
 var curVal = document.getElementById(target).className;
 document.getElementById(target).className = (curVal === 'hidden') ? 'show' : 'hidden';
}
