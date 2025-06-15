import { addManageUserFriend, getUserStatusClass } from "../js/friendsTool.js";
import globalData, { getProfileById } from "../js/tools.js";
export function getXp(normal_game_wins, tournament_wins){

  return (( normal_game_wins *  5) +(tournament_wins * 20) ) 

}



function setupFriends(manageFriendElement,mysendreq,friendsreq,pr)
{
  const { classStat, reqId } = getUserStatusClass(pr,mysendreq,friendsreq);
  if(manageFriendElement) manageFriendElement.innerHTML = classStat;


  const addManageLink = manageFriendElement.querySelector("a");
  
  if (addManageLink) {
    addManageLink.addEventListener("click",async (e) =>  { await addManageUserFriend(e,reqId,pr.id,friendsreq,mysendreq); addManageLink.remove(); });
  }
}


export function setProfileDetails(container, userData,datafriend,tournwins,mysendreq,friendsreq,isFriend) {
    const { wins, loss, goals_scored, goals_conceded } = userData;
    const xp = getXp(wins,tournwins) || 0;
    const avatarElement = container.querySelector(".avatar img");
    const usernameElement = container.querySelector(".user-h1");
    const winsElement = container.querySelector("#wins .win");
    const gfElement = container.querySelector("#draw .gf");
    const gaElement = container.querySelector("#draw .ga");
    const lossElement = container.querySelector("#losses .los");
    const xpElement = container.querySelector(".profile-container .xp");
    const manageFriendElement = container.querySelector(".profile-friends-manage");



    if (avatarElement)
      avatarElement.src = datafriend.avatar || "/path/to/default-avatar.png";
    if (usernameElement)
      usernameElement.textContent = datafriend.user?.username || "Unknown User";
    if (winsElement) winsElement.textContent = wins || 0;
    if (gfElement) gfElement.textContent = goals_scored || 0;
    if (gaElement) gaElement.textContent = goals_conceded || 0;
    if (lossElement) lossElement.textContent = loss || 0;
    if(xpElement) xpElement.innerHTML = `${xp} XP`;
    if(!isFriend){
      if(manageFriendElement) setupFriends(manageFriendElement,mysendreq,friendsreq,datafriend);
    }

  }


  export function   showProfileModal() {
    const fprContainer = document.querySelector(".freined-profile-user");
    const heightView = document.querySelector(".height-view");
    const freezAllOverlay = document.querySelector(".freez-all");

    if (fprContainer) fprContainer.style.display = "block";
    if (heightView) heightView.style.display = "block";
    if (freezAllOverlay) freezAllOverlay.style.display = "";
  }

  export function setCloneToProfile(trn_stat) {
    const temp = document.querySelector(".temp-stat-tourn");
    const clone = temp ? temp.content.cloneNode(true) : null;

    if (!clone) {
      return null;
    }

    const { wins, tourns_num, goals_achieved, goals_received } =  trn_stat || {};

    clone.querySelector(".win").textContent = wins || 0;
    clone.querySelector(".gf").textContent = goals_achieved || 0;
    clone.querySelector(".ga").textContent = goals_received || 0;
    clone.getElementById("trn_nums").textContent = tourns_num || 0;

    return clone;
  }
  export function   renderTournamentStats(container,trn_stat) {
    const statTrnClone = setCloneToProfile(trn_stat).querySelector("tr");
    const statsTableBody = container.querySelector(".t-table-1 tbody");

    if (statsTableBody && statTrnClone) {
      statsTableBody.innerHTML = "";
      statsTableBody.appendChild(statTrnClone);
    }
  }


  export function  getUserProfile(username) {
    return globalData.profiles.find((profile) => profile.user.username === username);
  }

  export  function populatePlayerData(clone, profile, playerClass) {
    if (profile) {
      const imgElement = clone.querySelector(`${playerClass} img`);
      const usernameElement = clone.querySelector(`${playerClass} .Usernametohistory`);
  
      if (imgElement) imgElement.src = profile.avatar;
      if (usernameElement) usernameElement.textContent = profile.user.username;
    }
  }

  export function   populateGameScores(clone, game) {
    const p1ScoreElement = clone.querySelector(".player_03 .buut-1");
    const p2ScoreElement = clone.querySelector(".player_03 .buut-2");
    const dateMatch = clone.querySelector(".date_game_histori");
    if (dateMatch) dateMatch.innerHTML = game?.created_at|| "00-00-00 00:00:00";
    if (p1ScoreElement) p1ScoreElement.textContent = game.p1goal || 0;
    if (p2ScoreElement) p2ScoreElement.textContent = game.p2goal || 0;
  }


  export  function    createHistoryEntry(template, game) {
    const clone = template.content.cloneNode(true);
    if (!clone) return null;

    const p1profile = getProfileById(game.player1);
    const p2profile = getProfileById(game.player2);
    
    populatePlayerData(clone, p1profile, ".player_01");
    populatePlayerData(clone, p2profile, ".player_02");
    populateGameScores(clone, game);

    return clone;
  }