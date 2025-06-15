import { tokenIsValid } from "./index.js";
import globalData from "./tools.js";
import { messageHandling } from "./utils.js";




export function NormalQueue(vars, callback) {

  if (vars.pressed1 == true){
    vars.crono1.dom = null;
    vars.dom_btn_normal.innerHTML = vars.version1_of_buteen1;
    vars.dom_btn_normal.style.background ="var(--color-light-dark)";
    
    vars.crono1.sec = 0;
    vars.crono1.min = 0;
    clearInterval(vars.crono1.task);
    vars.crono1.task = null;

    vars.sock.close();
    vars.sock = null;
    
    vars.pressed1 = false;
    return;
  }
  
  vars.pressed1 = true;
  vars.dom_btn_normal.innerHTML = vars.version2_of_buteen1;
  vars.dom_btn_normal.style.backgroundColor = 'black';

  vars.sock = new WebSocket(vars.sock_url);
  globalData.soketQueue =  vars.sock;
  vars.sock.onopen = function() {
    vars.sock.send(JSON.stringify(vars.headers));
  };

  vars.sock.onclose = function(event) {
    if (!event.wasClean) {
      messageHandling("error",`match making service didnt respond`);
      NormalQueue(vars);
    }
  };

  vars.sock.onmessage = function(event){

    try {
      let obj = JSON.parse(event.data);
      if (obj.action == 'redirect')
      {
        vars.sock.close();
        NormalQueue(vars);
        // start game
        tokenIsValid().then(e=>{
          if(e)
            callback(vars);

        })
      }
      if (obj.action == 'cancel_search')
      {
        vars.sock.close();

        messageHandling("error",obj.message);
        NormalQueue(vars);
      }
    } catch (error) {
      // console.log("error couth:");
      // console.log(error);
      messageHandling("error",error.message);
    }
  }
  vars.crono1.dom = document.getElementById('crono1')
  vars.crono1.task = setInterval(clock, 1000, vars.crono1);
}

export function get_string_of_time_unit(t)
{
  var ss_str =  t.toString();
  return (ss_str.length === 1) ? '0' + ss_str : ss_str;
}

export function inc_time(time){

  var extra = (time.sec === 59) ? 1 : 0
  time.sec = (time.sec === 59) ? 0 : time.sec + 1
  time.min +=  extra
  //remove user from queue if queue time raches 60 min
  if (time.min == 60)
    NormalQueue(vars)
}

export function clock(crono1){

  inc_time(crono1)
  let time = get_string_of_time_unit(crono1.min)
  time += " : "
  time += get_string_of_time_unit(crono1.sec)
  crono1.dom.innerText = time
}