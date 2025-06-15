import AbstractView from "../js/AbstractView.js";
import { Local_trn } from "./local_trn.js";
import {online_game, gameend, empty_, remove_game_belong} from '../js/online2.js';
// import { vars } from "./Games.js";
import { removeFrame } from "../js/tools.js";
import { fetch_data } from "../js/BaseUtils.js";
import { tokenIsValid } from "../js/index.js";

let butn1 = null;
let joined = false;
let socket = null;
let trnInfoSocket = null;
let type = 'none';
let trns_id = [];
let matche_res = null

export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("Tournament");
    this.pageTitle = "TOURNAMENT";  
  }


  async afterRender()
  {
    if (joined == false){
      if (type == 'remotTrn'){
        butn1 = document.querySelector(".start-R-trn-bottun");
        if (butn1)
          butn1.addEventListener("click" , this.trn_subscribe.bind(this, 'update'));

        await this.trn_mumbers('trn4_info');
        for (let id of trns_id){
          let trn_btn = document.getElementById(id);
          if (trn_btn)
            trn_btn.addEventListener('click', this.trn_history_choose.bind(this, id));
        }
      }
      if (type == 'none'){
        let localTrn = document.getElementById('localTrn');
        if (localTrn)
          localTrn.addEventListener("click", this.local_tournament.bind(this));
        let remotTrn = document.getElementById('remotTrn');
        if (remotTrn)
          remotTrn.addEventListener("click", this.remot_tournament.bind(this));
      }
    }
    if (type == 'remotTrn' && joined){
      let elem = document.getElementById('leav_trn');
      if (elem)
        elem.addEventListener('click', this.leave_trn.bind(this));
    }

  }


  async in_trn(){
    let data = JSON.stringify(this.data);
    const url = '/tournament/is_inTourn/';
    return await fetch_data(url, 'POST', data)
  }

  // For Unsubscribe players
  async trn_mumbers(element_id){
    let url = `/tournament/tourn_info/`;
    let trn_data = await fetch_data(url, 'GET');
    let display = false;
    if (trn_data.created)
      display = this.display_trn_mumbers(element_id, trn_data);
    if (!display) {
      let btn = document.querySelector(".start-R-trn-bottun");
      if (btn)
          btn.innerHTML = "Create New";
    }
  }
  
  display_trn_mumbers(element_id, trn_data){
    let content = '';
    let players = trn_data.players;
    let unknown = trn_data.unknown;
    for (const player of players){
      content += `
      <div class="player_tour">
        <img src="${player.image_url}">
      </div>
      `;
    }
    for (let i = 0 ; i < unknown; i++){
      content += `
      <div class="player_tour">
        <img src="media/unkonu_p.png">
      </div>
      `;
    }

    if (players.length == 0 || players.length == 4)
      return false;
    let trn_info = document.getElementById(element_id);
    if (trn_info){
      trn_info.style.display = "flex";
      trn_info.innerHTML = content;
    }
    return true;
  }


  onmsg_trn_info(trn_data) {
    let display = this.display_trn_mumbers('trn4_info', trn_data);
    if (!display) {
      let btn = document.querySelector(".start-R-trn-bottun");
      if (btn)
          btn.innerHTML = "Create New";
      let trn_info = document.getElementById('trn4_info');
      if (trn_info){
        trn_info.style.display = "none";
        trn_info.innerHTML = "";
      }
    }
    else{
      let btn = document.querySelector(".start-R-trn-bottun");
      if (btn)
          btn.innerHTML = "Join";
    }
  }
  
  async trn_subscribe(task){
    
    let content = "";
    let url = `/tournament/trn_subscribe/?trn_size=4`;
    let data = JSON.stringify(this.data);
    let response = await fetch_data(url, 'POST', data);

    if (response)
    {
      type = response.type;
      localStorage.setItem('inTourn', true);
      joined = true;
      if (task == 'update' && trnInfoSocket != null){
        trnInfoSocket.close();
      }

      if (socket)
        socket.close();

      // Tourn
      if (response.type == 'remotTrn'){
        content = `
        <div class='trn_players-in' id="trn">
          ${this.trn_Players(response, task)}
        </div>`;
      }
      // Matche
      if (response.type == 'matche'){
        content = await this.display_matche(response, task);
      }
      
      // WEB SOCKET //
      let loc = window.location;
      let wsPrefix = 'ws://';
      if (loc.protocol == 'https:') {
          wsPrefix = 'wss://'
      }
      socket = new WebSocket(wsPrefix+ window.location.host +`/ws/tourn/`)

      socket.onmessage = async e =>{
        const trn_data = JSON.parse(e.data);
        if (trn_data.type == 'tourn')
          this.trn_Players(trn_data, 'update');

        if (trn_data.type == "matche"){
          await this.display_matche(trn_data, 'update');
        }

        if (trn_data.type == "matche_end"){
          if (trn_data.user_id == this.data.user.id){
            let _matche_res = trn_data.matche_res
            _matche_res.type = 'op_left'
            _matche_res.subject = ''
            matche_res = _matche_res
          }
        }
      };
    }
    else
      content = "error";
  
    return content;
  }
    
  // for subscribed users
  trn_Players(data, task) {
    let content = `
    <div class="button_div1">
      <div class="leave_trn"  id="leav_trn">Leave Tournament</div>
    </div>
    <div class="trn_players_box">
    `;
    let players = data.players;
    let unknown = data.unknown;
    for (const playr of players)
      content += this.generatePlayerHTML(playr);
    for (let i = 0 ; i < unknown; i++)
      content += this.generatePlaceholderHTML();
    
    content = ` 
    ${content} 
    </div>
    `;
    if (task == 'update'){
      let trn = document.getElementById('trn');
      if (trn){
        trn.innerHTML = content;
        trn.className = 'trn_players-in';
      }
      let elem = document.getElementById('leav_trn');
      if (elem)
        elem.addEventListener('click', this.leave_trn.bind(this));
    }
    else{
      return content;
    }
  }
    
  async leave_trn(){
    let url = `/tournament/leave_trn/`;
    
    let data = JSON.stringify(this.data);
    let response = await fetch_data(url, 'POST', data);
    if (response){
      if (socket)
        socket.close();
      this.remot_tournament()
    }
    
  }
  
  async trn_history_choose(id, cancel){

    let url = `tournament/trn_history/?trn_id=${id}`;
    let trn_hstry = await fetch_data(url, 'GET', null);
    if (trn_hstry.status == 'ok'){
      this.show_trn_history(trn_hstry, cancel);
      if (cancel){
        let bottun = document.querySelector(".btn___exit");
        if (bottun)
          bottun.addEventListener("click" , this.remove_trnHistory.bind(this, true))
      }
    }
  }

  remove_trnHistory(close_socket=false){
    if (close_socket && socket){
      socket.close()
    }
    let trn_hstry = document.querySelector('.parent-container-4');
    if (trn_hstry)
      trn_hstry.style.display = "none";
    let freez = document.querySelector(".trn_freez-all");
    if (freez)
      freez.style.display = "none";
  }

  generateTrnMatche(matche, p_top){
    let p_bottm = matche.p1
    if (p_top == matche.p1)
      p_bottm = matche.p2
    return `
        <div class="plyr-box player-up">
          <img src='${p_top.img}'>
          <div class='text'>${p_top.name}</div>
          <div class="score1">${p_top.score}</div>
        </div>
        <div class="plyr-box player-down">
          <img src='${p_bottm.img}'>
          <div class='text'>${p_bottm.name}</div>
          <div class="score1">${p_bottm.score}</div>
        </div>`;
  }

  generateTrnMatche_vid(){
    return `        
      <div class="plyr-box">
        <img src='media/unkonu_p.png'>
        <span class='text'>unkown</span>
        <div class="score1">0</div>
      </div>
      <div class="plyr-box">
        <img src='media/unkonu_p.png'>
        <span class='text'>unkown</span>
        <div class="score1">0</div>
      </div>
    `;
  }

  show_trn_history(data, cancel){
    let content = ``;
    if (cancel){
      content = `
      <div class="position-absolute top-0 end-0 btn___exit">
        <button type="button" class="btn btn-danger bg-danger">
          <i class="fa-solid fa-x"></i>
        </button>
      </div>`
    }
    content += `<div class="child-col m-r  part-r">`;
  
    for (let i = 0; i < 2; i++){4
      if (i < data.matches.length){
        let matche = data.matches[i]
        let p_top =  matche.p1.score==5 ? matche.p1 : matche.p2
        if (i)
          p_top =  matche.p1.score==5 ? matche.p2 : matche.p1
        content += this.generateTrnMatche(matche, p_top);
      }
      else
        content += this.generateTrnMatche_vid();
      if (i)
        content += `</div>`;
      else
        content += `<div class='vid'></div>`;
    }
    if (data.matches.length == 3){
      let matche = data.matches[2]
      content += `
      <div class="child-col m-l part-l">
        ${this.generateTrnMatche(matche, matche.p1)}
      </div>
      `;
    }
    else{
      content += `
      <div class="child-col m-l part-l">
        ${this.generateTrnMatche_vid()}
      </div>
      `;
    }

    let trn = document.getElementById('trn_hstry');
    if (trn){
      trn.className = `parent-container-4`;
      trn.style.display = "grid";
      trn.innerHTML = content;
    }
    document.querySelector(".trn_freez-all").style.display = "block";
  }

  

  async display_matche(data, task){
    let id = this.data.user.id;
    let matches = data.matches;
    let matche = null;
    removeFrame();
    for (let m of matches){
      if (m.p1_id == id || m.p2_id == id){
        matche = m;
        break;
      }
    }
    if (matche){
      // console.log('PLAYER HAVE A MATCHE')
      return await this.matche_animation(matche, task, data, id);
    }
    else {
      // console.log('PLAYER DONT HAVE A MATCHE')
      let content = await this.remot_tournament();
      await this.trn_history_choose(data.trn_id, 1);
      if(socket)
        socket.close();
      return content
    }
  }

  async matche_animation(matche, task, data, id){
    let vars = {
      "headers" : {
        "access_token" : localStorage.getItem('access_token'),
        "login" : this.data.user.username,
        "id" : id,
        "image" : this.data.avatar,
      }
    }
    // vars.headers.access_token = localStorage.getItem('access_token');
    // vars.headers.login = this.data.user.username;
    // vars.headers.id = id;
    // vars.headers.image = this.data.avatar;
    let content = "";
    let create_time = new Date(matche.create_time);
    let now = new Date();
    let wDuration = 5000;
    content = this.generateMatcheHtml(matche);
    if (create_time.getTime() + wDuration >= now.getTime()){
      let timeleft = create_time.getTime() + wDuration - now.getTime();
      
      // displaye matche
      empty_();
      setTimeout(async()=>{
        this.remove_trnHistory();
        const valid = await tokenIsValid();
        if(valid)
        {
          online_game(vars);
          var trn = document.getElementById('trn');
          if (trn)
            trn.innerHTML = '';
        }
      }, timeleft);

      let set_interval = setInterval(async ()=>{
        if (gameend || matche_res){
          clearInterval(set_interval);
          let _gamend = gameend? gameend : matche_res
          matche_res = null
          if (_gamend.type == 'op_left'){
            remove_game_belong()
          }
          setTimeout(async ()=> {
            // console.log('gameend is filld: ', _gamend);
            await this.save_matche(matche, _gamend);
          }, 2000);
        }}, 1000);
    }
    else{
      if (matche.status == 'unplayed'){
        let gameres = {
          'p1score': (id != matche.p1_id)*5, 
          'p2score': (id != matche.p2_id)*5,
          'winer': (id != matche.p1_id)+(id != matche.p2_id)*2,
        }
        if(socket)
          socket.close()
        content = await this.save_matche(matche, gameres)
        content = `
        <div class="container_tour" id="trn">
          ${content}
        </div>`;
        return content
      }
      content = await this.remot_tournament();
      await this.trn_history_choose(data.trn_id, 0);
    }

    if (task == 'return'){
      content = `
      <div class='matche' id="trn">
        ${content}
      </div>`;
      return content;
    }
    let trn = document.getElementById('trn');
    if (trn){
      trn.className = 'matche';
      this.remove_trnHistory();
      trn.innerHTML = content;
    }
  }


  async save_matche(matche, game_res){
    // console.log('-------matche_save-----')
    let id = this.data.user.id;
    let url = `/tournament/matchresult/`;
    let p1_score = (game_res.winer == 1) * 5
    let p2_score = (game_res.winer == 2) * 5
    if (game_res.subject == 'end'){
      p1_score = game_res.p1score
      p2_score = game_res.p2score
    }
    else if (matche.status == "played")
      return
    let data = JSON.stringify({
      'id': matche.id,
      'p1_score': p1_score,
      'p2_score': p2_score,
      'winner': game_res.winer,
    });
    let response = await fetch_data(url, 'POST', data);
    let content = ''
    let cond = (!(response.new_round) && !(response.trn_end));
    if (response.winner_id == id && cond){
      content = await this.remot_tournament();
      await this.trn_history_choose(response.trn_id, 0);
    }
    else if (response.winner_id != id || response.trn_end){
      content = await this.remot_tournament();
      await this.trn_history_choose(response.trn_id, 1);
    }
    return content
  }

  async generateTournChoiceHtml(render)
  {
    let content = `
    <div class="option_4" id="trn4">
      <div class='players' id='players'>
        <div class="players_holder" id='trn4_info'></div>
      </div>
      <div class="start-remot-tourn">
        <div class="start-R-trn-bottun">Join</div>
      </div>
    </div>
    <div class="trns_list scrool-friend-tour">
    `;
    
    let url = `/tournament/trn_history/`;
    let data = JSON.stringify(this.data);
    let response = await fetch_data(url, 'POST', data)
    let trns = response.trns;
    for (let trn of trns){
      let icon = '';
      let Date = trn.created_at;
      if (trn.won)
        icon = '<i class="fas fa-trophy trophy-icon"></i>';
      content += `
        <div class="choose">
          <img src="/media/pong_trn.webp" class="choose_image">
          <div class="choose-info">
            <div class="choose-name">${trn.name} ${icon}</div>
            <div class="choose-level">Date: ${trn.created_at}</div>
          </div>
          <div id="bracket"></div>
          <div id="${trn.id}" class="choose-button">
            show
          </div>
        </div>
      `;
      trns_id.push(trn.id);
    }
    content += `
    </div>`;

    type = 'remotTrn';
    return content;
  }

  generatePlayerHTML(player)
  {
    return `
      <div class="player_tour-in">
          <img src="${player.image_url}" alt="No image" width="140" class="player_img">
          <div class='name'>${player.name}</div>
      </div>
    `;
  }

  generatePlaceholderHTML()
  {
    return `
      <div class="player_tour-in">
          <img src="media/unkonu_p.png" alt="No image" width="140" class="player_img">
          <div class='name'>waiting player...</div>
      </div>
    `;
  }

  generateMatcheHtml(matche) {
    return `
        <div class="player p_1">
            <div class="p_img"><img src="${matche.p1_img}"></div>
            <div class="name">${matche.p1_name}</div>
        </div>
        <div class='m_vs'>VS</div>
        <div class="player p_2">
            <div class="p_img"><img src="${matche.p2_img}"></div>
            <div class="name">${matche.p2_name}</div>
        </div>
    `;
  }


  async remot_tournament(){

    let content = "";
    joined = false;
    
    content = await this.generateTournChoiceHtml("true");
    let loc = window.location;
    let wsPrefix = 'ws://';
    if (loc.protocol == 'https:') {
        wsPrefix = 'wss://'
    }
    trnInfoSocket = new WebSocket(wsPrefix+ window.location.host +`/ws/tourn_info/`);
    trnInfoSocket.onmessage = e =>{
      let trn_data = JSON.parse(e.data);
      this.onmsg_trn_info(trn_data)
    };
    let trn = document.getElementById('trn');
    if (trn){
      trn.className = 'container_tour';
      trn.innerHTML = content;
      type = "remotTrn";
    }
    this.afterRender();
    return content
  }
  
  async getHtml() {
    let content = '';
    type = 'none';
    let data = await this.in_trn();
    if (data.intourn == 'yes')
      content = await this.trn_subscribe('return');
    if (data.intourn == 'no'){
      joined = false
      content = `
      <div class="tournament-section" id ="trn">
        <div class="cards-container"> 
            <div class="content-tour-1  d-flex align-items-center justify-content-center">
              <img src="static/images/cup.png" alt="Online Tournament Trophy" class="online-trophy">
              <div class="tap-tap d-flex align-items-start justify-content-around ">
                <h2>Online Tournament</h2>
                <p>PLAY WITH FRIENDS ONLINE IN A SHARED ENVIRONMENT FOR FACE-TO-FACE MATCHES.</p>
                <button class="join-btn" id="remotTrn">Join</button>
              </div>
            </div>
              <div class="content-tour-1  d-flex align-items-center justify-content-center ">
              <img src="static/images/cup-manita.png" alt="Local Tournament Trophy" class="local-trophy">
              <div class="tap-tap d-flex align-items-start justify-content-around ">
                <h2>Local Tournament</h2>
                <p>COMPETE ONLINE AGAINST PLAYERS WORLDWIDE IN REAL-TIME TOURNAMENTS.</p>
                <button class="join-btn"  id="localTrn">Join</button>
              </div>
            </div>
        </div>
      </div>
      `;
    }

    const headernav = await this.getHeader();
    return headernav + `
    <div class='content_tour'>
      <div class="Tournament-brack"> Tournament Break </div>
        ${content}
    </div>
    `;  
    
  }
  
  local_tournament(){
    let trn = document.getElementById('trn');
    let local_trn = new Local_trn;
    if (local_trn)
      trn.innerHTML = local_trn.rejester();
    let strt_trn = document.querySelector('.rejister_trn');
    if (strt_trn){
      strt_trn.addEventListener('submit', e=> {
        local_trn.trn_start(event);
      });
    }
  }

}