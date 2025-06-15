import AbstractView from "../js/AbstractView.js";
import { getCookie } from "../js/tools.js";
import globalData from "../js/tools.js  ";
import { messageHandling } from "../js/utils.js";
import { getXp, setCloneToProfile } from "../jstools/friendProfile.js";

export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("Profile");
    this.historycount = 20;
    this.pageTitle = "PROFILE";
    this.allWins = {winMatch:0 ,winTourn:0};
  }




  async getHtml() {
    await this.setDataProfiles();
    await this.getTournStats();

    const headernav = await this.getHeader();

    let postBody = {
        'id' : this.data.user.id,
        'name' : this.data.user.username,
        'historycount' : this.historycount
    };
    let url = window.location.origin + "/game_service/api/stats/";  
    // const url = wi
    let userobj;
    let gamesObj = [];
    try {
        const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${getCookie("access_token")}`,
                },
                body: JSON.stringify(postBody)
            });

        if (!response.ok) {
            // messageHandling("error", "Can't acces game history")
            // return;
            throw new Error("Can't access game's history");
        }
        
        const responseData = await response.json(); // Parse the JSON from the response
        userobj = JSON.parse(responseData.user);
        responseData.historic = JSON.parse(responseData.historic);
        responseData.historic.forEach(game => {
            gamesObj.push(game);
        });
    } catch (error) {
       messageHandling("error",error.message);
    }
    // await fetch()
   const  xp =  getXp(userobj?.wins || 0,this.trn_stat?.wins || 0) 
    let wins = userobj?.wins || 0;
    let loss = userobj?.loss || 0;
    let goals_scored = userobj?.goals_scored || 0;
    let goals_conceded = userobj?.goals_conceded || 0;
    
    //get all users
   
    let view = ""
    if (gamesObj.length == 0)
    {
        view = `<div class="no-game"> no games played </div>`;
    }
    else
    {
        view += "";
        gamesObj.forEach(game => {
            view += ``
            
            let p1profile =  globalData.profiles.find(profile => profile.user.id == game.player1);
            let p2profile =  globalData.profiles.find(profile => profile.user.id == game.player2);
            let gamedate = game?.created_at;
            view += `<div class="histor d-flex justify-content-evenly bd-highlight">
                        <div class="histor d-flex justify-content-evenly bd-highlight">
                            <div class="player_01">
                                <img src="${p1profile?.avatar || "avatar.png" }" alt="Profile Picture">
                                <div class="Usernametohistory">${p1profile?.user?.username || "undifine user"}</div>
                            </div>
                            <div class="player_03 d-flex justify-content-around align-items-center flex-column">
                                <div class="score_game_histori d-flex justify-content-between align-items-center">
                                    <div class="buut buut-1">${game?.p1goal || 0}</div>
                                    <div class="tow_poin">:</div>
                                    <div class="buut buut-2">${game?.p2goal || 0 }</div>
                                </div>
                                <div class="date_game_histori">
                                    ${gamedate || "00-00-00 00:00:00" }
                                </div>
                            </div>
                            <div class="player_02">
                                <img src="${p2profile?.avatar || "avatar.png"}" alt="Profile Picture">
                                <div class="Usernametohistory">${p2profile?.user?.username || "undifine user"}</div>
                            </div>
                        </div>
                    </div>
                    <div class="separator"></div>`;   
        });
    }

    return (
      headernav +
      `       <div class="content_profile myprofile-user">
<div class="pr-welcome m-2 d-flex justify-content-between">
  <p>  <i class="fa-solid fa-user  fa-fw"></i> My Profile </p> 
    <div class="btn-settings">
        <a class="d-flex p-3 align-items-center fs-5 rounded-2 mb-2 ms-3"  data-link href="/settings">
            <i class="fa-solid fa-gear"></i>
        </a>
    </div>
</div>

<div class="profile-container">
<div class="avatar">
    <img src="${this.data?.avatar || "avatar.png" }" alt="Profile Picture">
</div>
<h1>${this.data?.user?.username || "undifine user"}</h1>
<div class="xp">${xp} XP</div>
<div class="separator"></div>
<div class="stats">
    <div class="stat" id="wins">
        <div class="stat-value win">${wins}</div>
        <div class="stat-label ">Wins</div>
    </div>
    <div class="stat" id="draw">
        <div class="stat-value gf">${goals_scored}</div>
        <div class="stat-label ">GF</div>
    </div>
    <div class="stat" id="draw">
        <div class="stat-value ga">${goals_conceded}</div>
        <div class="stat-label ">GA</div>
    </div>
    <div class="stat" id="losses">
        <div class="stat-value los">${loss}</div>
        <div class="stat-label ">Losses</div>
    </div>
</div>
<div class="separator"></div>
<h1>Match History</h1>
<div class="scrool_histori">    
${view}
</div>
<div class="separator"></div>

<table class="tournament-table  t-table">
    <thead>
        <tr>
            <th>Tournaments</th>
            <th class="win">Wins</th>
            <th class="gf">GF</th>
            <th class="ga">GA</th>
        </tr>
    </thead>
</table>
</div>
</div>`
    );
  }
 async afterRender() {
    const trn_table = document.querySelector(".t-table");
    if (!trn_table) {
        return;
    }

    const clone = setCloneToProfile(this.trn_stat);
    trn_table.append(clone);

  }
}
