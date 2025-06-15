import AbstractView from "../js/AbstractView.js";
import {  acceptRequestFriend, addManageUserFriend, deleteRequestFriend, fetchWithAuth, getUserStatusClass, handleResponse, sendRequestFriend, sendTroughSocket } from "../js/friendsTool.js";
import { establishSocket, navigateTo, tokenIsValid } from "../js/index.js";
import { getCookie } from "../js/tools.js";

import { messageHandling , CostumConfigDialog} from "../js/utils.js";
import WebSocketManager from "../js/Websocket.js";

export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("Friends");
    this.pageTitle= "FRIENDS";
  }
async setFunctions(){
  await this.setDataProfiles();
  await this.setDataFriendRequest();
}

  async getHtml() {

  await this.setFunctions();
  const headernav = await this.getHeader();
  let  texthtml = headernav +`<div class="content_frined">
      <ul>
          <li><a id="1" class=" active display-friend-mk ">Friends Suggestions</a></li>
          <li><a id="2" class="display-friend-mk ">Friends</a></li>
          <li><a id="3" class="display-friend-mk">Invitations</a></li>
      </ul>
      <div class="send-request-friend send-request friends-page scrool-friend gap-2 active show-friend-m mk1">  
      </div>
      <div class="scrool-friend friends-page gap-2 dletefriendevent show-friend-m mk2">
      </div>       
      <div class="scrool-invitations  accept-delete-request show-friend-m mk3">
        <div class="invitations">
        </div>
      </div>  
  </div>  `;

return texthtml;
}

shouldAddUser(pr) {
  return pr.user.id !== this.payload.user_id && 
    !this.data.friends.some(e => e.user.username === pr.user.username);
}

appendUserClone(prClone) {
  const sendRequest = document.querySelector(".send-request");
  if(sendRequest) sendRequest.append(prClone);
}



createUserClone(pr, classStat, reqId) {
  let temp = document.querySelector(".all-users-template");
  if (!temp) return null;
  let prClone = temp.content.cloneNode(true);

  const addManage = prClone.querySelector(".add-manage");
  if (addManage) {
    addManage.innerHTML = classStat;
  }
  const addManageLink = prClone.querySelector(".add-manage a");
  const userImage = prClone.querySelector(".txt-c img");
  const username = prClone.querySelector(".txt-c h4");
  const goProfile = prClone.querySelector(".show-profile");
  
  if (addManageLink) {

    addManageLink.addEventListener("click",async(e) =>  {await addManageUserFriend(e,reqId,pr.id,this.friendsreq,this.mysendreq);});
  }

  if (userImage)  userImage.src = pr.avatar;
  if (username)  username.innerHTML = pr.user.username;
  if (goProfile)  goProfile.addEventListener("click",e=>{this.showFriendProfile(pr.user.id)})  ;
  return prClone;
}

addCloneUser(pr){
  if(this.shouldAddUser(pr)){
    const { classStat, reqId } = getUserStatusClass(pr,this.mysendreq,this.friendsreq);
    const prClone = this.createUserClone(pr, classStat, reqId);
    if(!prClone) return;
    this.appendUserClone(prClone);
  }
}
allUserHtml(){
  const sendRequest = document.querySelector(".send-request");
  if (sendRequest) sendRequest.innerHTML = "";
  this.profiles.forEach(pr =>{
  this.addCloneUser(pr);
})
}

getProfileById(id) {
  return this.profiles.find(profile => profile.user.id === id);
}


// Clones a friend into the user's friend list with online/offline status
cloneFriendInUser(profile) {
  const addFriendList = document.querySelector(".dletefriendevent");
  const template = document.querySelector(".friends-list-template");
  const pWithF = this.getProfileById(profile.user.id);


  if (!addFriendList || !template) {
    return;
  }
  const friend= profile.user;
  if (!profile || !friend)  return;
  const friendClone = template.content.cloneNode(true);
  const status = profile.is_online ? "active_frind" : "not-active_frind";

  const nameElement = friendClone.querySelector(".txt-c h4");
  const avatarElement = friendClone.querySelector(".txt-c img");
  const deleteButton = friendClone.querySelector(".deletefriend");
  const profileButton = friendClone.querySelector(".show-profile");
  const statusElement = friendClone.querySelector(".status-frind");
  const statusDiv = friendClone.querySelector(".status-frind div");
  const friendTotal = friendClone.querySelector(".friend-total");
  
  if (nameElement) nameElement.textContent = friend?.username || "Unknown";
  if (avatarElement) avatarElement.src = profile?.avatar || "/path/to/default-avatar.png";
  if (friendTotal) friendTotal.innerHTML = `${pWithF?.friends?.length || 0} Friend`
  if (deleteButton) deleteButton.addEventListener("click",e =>{ this.deleteFriendSure(e,profile.id)})
  if (profileButton) profileButton.addEventListener("click",e=>{this.showFriendProfile(friend.id)});
  if (statusElement) statusElement.classList.add(status);
  if (statusDiv) statusDiv.classList.add(`${status}_1`);
  addFriendList.append(friendClone);
}

allUserFriendsList() {
  const addFriendList = document.querySelector(".dletefriendevent");
  if (!addFriendList) {
    return;
  }
  addFriendList.innerHTML = "";
  const profile = this.data
  if (!profile || !profile.friends) {
    return;
  }
  profile.friends.forEach((friend) =>   this.cloneFriendInUser(friend ));
}

allFriendRequestHtml() {
  const inviteContainer = document.querySelector(".invitations");
  const template = document.querySelector(".invitations-template");

  if (!inviteContainer || !template) {
    return;
  }
  inviteContainer.innerHTML = "";
  this.friendsreq.forEach((request) => {
  const freqClone = template.content.cloneNode(true);
  const inviteAvatar   =   freqClone.querySelector("img");
  const senderName   =   freqClone.querySelector(".request-name");
  const timeOfRequest   =   freqClone.querySelector(".request-time");
  const addIdReqDelete  =  freqClone.querySelector(".deletef");
  const  addIdReqAccept =  freqClone.querySelector(".acceptf");
  if (timeOfRequest) timeOfRequest.innerHTML = this.getTime(request.timestamp);
  if (senderName) senderName.innerHTML = request?.sender?.user?.username || "Undifine";
  if (inviteAvatar) inviteAvatar.src = request.sender?.avatar || "/path/to/default-avatar.png";
  if (addIdReqDelete) addIdReqDelete.addEventListener("click",(e) => deleteRequestFriend(request.id,this.friendsreq,this.mysendreq));
  if (addIdReqAccept) addIdReqAccept.addEventListener("click",(e) => acceptRequestFriend(this.friendsreq,request.id));

  inviteContainer.append(freqClone);
  });
}

showcontent(paragraphNumber) {
  document.querySelectorAll('.show-friend-m').forEach(ele => {
      ele.classList.remove('active');
      });
      document.querySelectorAll('.show-friend-m').forEach(ele => {
        ele.classList.remove('active');
        });
  const content =  document.querySelector(`.mk${paragraphNumber}`)
  if (content) content.classList.add('active');
};

listenForDisplay(){
const allButtonDisplay = document.querySelectorAll(".display-friend-mk");

allButtonDisplay.forEach(melement =>{
 
    melement.addEventListener("click", e => {
    allButtonDisplay.forEach(element =>{element.classList.remove('active');    })
    melement.classList.add('active');
      this.showcontent(melement.id)});
 })
}
  async afterRender() {
    this.allUserFriendsList();
    this.allUserHtml();
    this.allFriendRequestHtml();
    this.listenForDisplay()


  }

  removeFriendFromMyprofile(id){
    this.data.friends = this.data.friends.filter(friend => friend.id !== id);
  }
  async deleteFriend(deletefriend,id){
    if (!id){
      messageHandling("error", "Failed to remove friend: Invalid ID.");
      return;
    }
    try {
      const response = await fetchWithAuth(`/api/deletefriend/${id}/`, 'DELETE');
      const responseData = await handleResponse(response);

      sendTroughSocket(
        "notf-socket",
        JSON.stringify({ type: 'update', user_id : id})

      );
      const parentElement = deletefriend.closest('.dletefriendevent');
      this.removeFriendFromMyprofile(id)
      if (parentElement) parentElement.remove();
      await this.afterRender();

    } catch (error) {
      messageHandling("error","Failed to delete friend:")
    }
  }
  async deleteFriendSure(e,id){
    const deletefriend = e.target;
    if (!deletefriend) {
      return ; 
    } 
    dialog.showDialog("Sure you want to remove this friend ?", ()=> {this.deleteFriend(deletefriend,id)}  );
  }
}