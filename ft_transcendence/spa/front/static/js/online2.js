import {Game2} from './game.js';
import { consts2 } from "./game_view.js";
import {Game_listner} from './game_listener.js';
import {remove_offgame_belong}from './offline.js';


// should removed
var preveGame = null;
var onlineGame = null;
var objtype = null;
var socket = null;
var arrowclickstat = false;


export function remove_game_belong(){
  if (onlineGame)
  {
    onlineGame.runing = false;
    onlineGame.ayoubFuntionDelete();
  }else{
    if (preveGame)
    {
      preveGame.runing = false;
      preveGame.ayoubFuntionDelete();
    }
  }
  onlineGame = null;
  objtype = null;
  if (socket)
    socket.close();
  socket = null;
  arrowclickstat = false;
}

export let gameend = null;

function setsender(msg){
  objtype = 'sender'
  onlineGame = new Game2(
    consts2,
    {
     'p1':{
        'name'  : msg.p1name,
        'image' : msg.p1img,
      },
      'p2':{
        'name'  : msg.p2name,
        'image' : msg.p2img,
      },
    },
    socket
  );
  onlineGame.display();
  onlineGame.readysignal();
}

function setlistner(msg)
{
  
  objtype = 'listner';
  onlineGame = new Game_listner(
    consts2,
    {
      'p1':{
        'name'  : msg.p1name,
        'image' : msg.p1img,
      },
      'p2':{
        'name'  : msg.p2name,
        'image' : msg.p2img,
      },
     },
     socket
  );
  onlineGame.display();
  
  onlineGame.setkeys(
    {
      'up' : lisner_keyup,
      'down': lisner_keydown,
      'aim' : lisner_aim_keydown,
    }
  );
  arrowclickstat = false;

  onlineGame.readysignal();

}

export function empty_(){
  gameend = null;
}

export function online_game(vars){
    const messageQueue = [];
    const protocol =  ((window.location.protocol == "https:") ? "wss://" : "ws://");
    const host = window.location.host;
    const url = "/ws/game_service/online/";
    const fullUrl = protocol + host + url;
    
    remove_game_belong();
    remove_offgame_belong();
    socket = new WebSocket(fullUrl);
    // socket = new WebSocket(`ws://${window.location.host}/ws/game_service/online/`);
    
    socket.onclose = function(event) {
      if (!event.wasClean) {
        messageHandling("error",`game service didnt respond`);
        remove_game_belong()
      }
    };

    socket.onmessage = function(event){
      try
      {
        let msg = JSON.parse(event.data);

        if (msg.subject == 'eng_game_view')
        {
          if (onlineGame) onlineGame.ayoubFuntionDelete();
        } 

        if (msg.subject == 'init')
        {
          if (msg.type == 'sender'){
            setsender(msg);
          }
          else if (msg.type == 'listner'){
            setlistner(msg);
          }
        }
        
        if (msg.subject == 'senderNotReady' && objtype == 'listner')
        {
          setTimeout((event) => {
            if (onlineGame)
              onlineGame.readysignal();
          }, 1000)
        }
  
        if (msg.subject == 'startgame' && objtype == 'sender')
        {
          const Promise = onlineGame.gameloop(
            {
              "keyup"   : online_movment_keyup,
              "keydown" : online_movment_keydown,
              "keyaimfuction" : online_aim,
              "mouseDown"     : null,
              "ft_online"     : brodcast,
            } 
          )
          Promise.then((data) => {
            gameend = data;
          })
          .catch((error) => {
              // console.log(`error => ${error}`);
          });
  
        }
        if (msg.subject == 'update' && objtype == 'listner')
          onlineGame.update(msg)
        
        if (msg.subject == 'update' && objtype == 'sender')
          onlineGame.update(msg)
        
        if (msg.subject == 'surrender')
        {
          onlineGame.surrender(msg.winer)
          objtype = null;
          arrowclickstat = false;
          this.close();
          gameend = msg;
          preveGame = onlineGame;
          onlineGame = null;
          setTimeout(() => {
            preveGame = null;
          }, 2100)
        }
  
        if (msg.subject == 'end')
        {
          onlineGame.end(msg.winer)
          objtype = null;
          arrowclickstat = false;
          this.close(); 
          gameend = msg;
          preveGame = onlineGame;
          onlineGame = null;
          setTimeout(() => {
            preveGame = null;
          }, 2100)
        } 
      }
      catch (e) {
        onlineGame?.ayoubFuntionDelete();
      }
      
    };

    socket.onopen = function(event) {
      while (messageQueue.length > 0) {
          const message = messageQueue.shift();
          this.send(message);
      }
    };

    let message = JSON.stringify(vars.headers);
    if (socket.readyState === WebSocket.OPEN) {
      socket.send(message);
    } else {
        messageQueue.push(message);
    }
}

function brodcast(msg, sock)
{
  sock.send(JSON.stringify(msg));
}

//offline aime MvObj //add ball
function  online_aim(obj, side)
{
  let vec = [];
  let p = null;
  if (side == 1)
  {
      vec = [this.consts.ballspeed, 0];
      p = {
            "up"    : obj.MvObj.p1up,
            "down"  : obj.MvObj.p1down,
        }
  }
  if (side == 2)
  {
      vec = [-this.consts.ballspeed, 0];
      p = {
          "up"    : obj.MvObj.p2up,
          "down"  : obj.MvObj.p2down,
      }
  }
  
  const shooting_angle = 60;
  let range = [];
  if (p.up == true && p.down == false)
      range = [shooting_angle / 3, shooting_angle];
  else if (p.down == true && p.up == false)
      range = [-shooting_angle, -(shooting_angle / 3)];
  else
      range = [-(shooting_angle / 3), shooting_angle / 3];

  let randomAngle = Math.floor(Math.random() * (range[1] - range[0] + 1)) + range[0];
  if(side == 1)
      randomAngle *= -1;
  const rotation = (vec, angle) =>{
          const rad = angle * (Math.PI / 180);
          const rotationMatrix = [
              [Math.cos(rad), -Math.sin(rad)],
              [Math.sin(rad), Math.cos(rad)]
          ]

          const numRows = rotationMatrix.length;
          const numCols = rotationMatrix[0].length;
          let result = [0,0];
          for (let i = 0; i < numRows; i++) {
              let sum = 0;
              for (let j = 0; j < numCols; j++) {
                  sum += rotationMatrix[i][j] * vec[j];
              }
              result[i] = sum;
          }
          return result;
      }

  return rotation(vec, randomAngle);
}

//spetil funtions
function  online_movment_keydown(PlayerStat, event)
{
  if (event.code === 'ArrowUp')
    PlayerStat.p1up = true;
  else if (event.code === 'ArrowDown')
    PlayerStat.p1down = true;

  if(["Space","ArrowUp","ArrowDown","ArrowLeft","ArrowRight"].indexOf(event.code) > -1) {
    event.preventDefault();
  }
}

function online_movment_keyup(PlayerStat,event)
{
  if (event.code === 'ArrowUp')
      PlayerStat.p1up = false;
  else if (event.key === 'ArrowDown')
      PlayerStat.p1down = false;
}

function online_aim_keydown(PlayerStat,board, consts, event)
{
  // var x =  parseFloat(event.offsetX) / board.clientWidth;
  // var y =  parseFloat(event.offsetY) / board.clientHeight;
  // PlayerStat.p1aim.x = x * consts.board_width;
  // PlayerStat.p1aim.y = y * consts.board_heigth;
  // console.log(PlayerStat.p1aim.x)
  // console.log(PlayerStat.p1aim.y)
  // console.log('---------')
}

//lisner events
function lisner_keydown(ws, event)
{
  let msg = {
    'subject' : 'update',
    'event' : 'Keydown',
    'key' : ''
  };

  if (arrowclickstat == true)
    return;
  
  arrowclickstat = true;

  if (event.code === 'ArrowUp')
    msg.key = 'up'
  else if (event.key === 'ArrowDown')
    msg.key = 'down'
  
  if(["Space","ArrowUp","ArrowDown","ArrowLeft","ArrowRight"].indexOf(event.code) > -1) {
    event.preventDefault();
  }

  if (event.code == "Space")
    return

  ws.send(JSON.stringify(msg));
}

function lisner_keyup(ws, event)
{
  let msg = {
    'subject' : 'update',
    'event': 'Keyup',
    'key'    : ''
  };

  arrowclickstat = false;

  if (event.code === 'ArrowUp')
    msg.key = 'up'
  else if (event.key === 'ArrowDown')
    msg.key = 'down'
  else
    return
    ws.send(JSON.stringify(msg));
}

function lisner_aim_keydown(ws, board, deffsize, event)
{
  let msg = {
    'subject' : 'update',
    'event': 'aim',
    'x'    : '',
    'y'    : '',
  }
  var x =  parseFloat(event.layerX) / board.clientWidth;
  var y =  parseFloat(event.layerY) / board.clientHeight;
  msg.x = x * deffsize.x;
  msg.y = y * deffsize.y;
  // ws.send(JSON.stringify(msg));
}