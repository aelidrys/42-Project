import AbstractView from "../js/AbstractView.js";
import {NormalQueue, get_string_of_time_unit, inc_time, clock} from "../js/queue.js";
import {offline_game} from "../js/offline.js";
import {online_game} from "../js/online2.js";
import { tokenIsValid } from "../js/index.js";
import { messageHandling } from "../js/utils.js";

const {
  host, hostname, href, origin, pathname, port, protocol, search
} = window.location

export function clearVars(varlist)
{
  varlist.pressed1 = false;
  varlist.sock = null;
  varlist.dom_btn_normal = null;
  varlist.crono1 = {
            'sec' :0,
            'min' :0,
            'task' : null,
            'dom' : null,
          };
  varlist.headers = {
              'login'     : null,
              'access_token' : null,
              'image'     : null,
            };
}

var gameWS = null;


export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("Games");
    this.pageTitle = "GAMES";
    this.type = "queue";
    this.vars = {
      "pressed1" : false,
      "sock"     : null,
      "version1_of_buteen1" : "Play",
      "version2_of_buteen1" : ` <div class="play-bot-2"><div id =\"crono1\">00 : 00</div></div>`,
      "dom_btn_normal" : null,
      // (name === 'true') ? 'Y' :'N';
      "sock_url" : ((protocol == "https:") ? "wss://" : "ws://") + host + "/ws/queue/",
      "crono1" : {
          'sec' :0,
          'min' :0,
          'task' : null,
          'dom' : null,
        },
    
      "headers" : {
        'id'        : null,
        'login'     : null,
        'access_token' : null,
        'image'     : null,
      },
    };
  }

  async getHtml() {
    return await this.QueueHtml();
  }

  afterRenderQueue()
  {
    clearVars(this.vars);
    this.vars.headers.access_token = localStorage.getItem('access_token');
    this.vars.headers.id = this.data.user.id;
    this.vars.headers.login = this.data.user.username;
    this.vars.headers.image = this.data.avatar;
  
    this.vars.dom_btn_normal = document.getElementById("noraml_btn");
    document.getElementById("noraml_btn").addEventListener("click", async() => {
      const valid = await tokenIsValid();
      if (!valid) {
        messageHandling("error","Senssion Invalid try again");
      }
      else
      {
        NormalQueue(
          this.vars,
          online_game
        );
      }

    });
    let img = this.data.avatar;
    let cop = img;
    document.getElementById("offline_btn").addEventListener("click", function(event) {
      offline_game(img, event); // Pass img and event as arguments
    });

    // window.addEventListener("popstate", () => {
    //   console.log("URL changed (e.g., browser back/forward button pressed)");
    // }, {once : true});
  }  

  async afterRender() {
    
    this.afterRenderQueue();
  }

  closeQueue()
  {
    NormalQueue(this.vars);
  }

  async QueueHtml()
  {

    const headernav = await this.getHeader();
    return headernav  + `  
          <div class="game-section d-flex align-items-center justify-content-center ">
          <h1>GAME SECTION</h1>
          <div class="cards-container-2"  id="mainqueueBox">
              <div class="content-game-2 d-flex align-items-center justify-content-center">
                  <img src="static/images/manita.png" alt="Game Controller" class="online-games">
                  <div class="tap-tap-game-2-1 d-flex align-items-start justify-content-around">
                      <h2>Online Play</h2>
                      <p>Challenge players worldwide in competitive online team or fun matches! Make new friends. Take your skills and make every game count!</p>
                      <button class="play-btn-2 play-bot-2" id="noraml_btn">Play</button>
                  </div>
              </div>
              <div class="content-game-2 d-flex align-items-center justify-content-center">
                  <img src="static/images/racit.png" alt="Ping Pong Paddle" class="local-games">
                  <div class="tap-tap-game-2-2 d-flex align-items-start justify-content-around">
                      <h2>Local Play</h2>
                      <p>Return your friends for fun and exciting matches right at home. Perfect for practice and friendly competition. Save your moves offline!</p>
                      <button class="play-btn-2" id="offline_btn">Play</button>
                  </div>
              </div>
          </div>
         
        </div>
    `
      ;
  }
} 
