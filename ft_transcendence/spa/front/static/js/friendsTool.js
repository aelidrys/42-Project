import { establishSocket, navigateTo, tokenIsValid } from "./index.js";
import { getCookie } from "./tools.js";
import { messageHandling } from "./utils.js";
import WebSocketManager from "./Websocket.js";

// Utility to handle fetch errors and messages
 export async function handleResponse(response) {
    const responseData = await response.json();
    if (response.ok) {
      const keyserr = Object.keys(responseData)[0];
      const valueerr = Object.values(responseData)[0];
       messageHandling(keyserr, valueerr);
      return responseData;
    } else if (response.status === 401) {
      await tokenIsValid();
      messageHandling("info", "Something went wrong, please try again!");
    } else {
      const keyserr = Object.keys(responseData)[0];
      const valueerr = Object.values(responseData)[0];
      messageHandling(keyserr, valueerr);
      throw new Error(responseData);
    }
  }
  
  // Utility to perform fetch requests
 export async function fetchWithAuth(url, method = 'POST', data = null) {
    const options = {
      method: method,
      headers: {
        'Authorization': `Bearer ${getCookie("access_token")}`
      }
    };
    if (data) {
      options.body = JSON.stringify(data);
    }
    return await fetch(url, options);
  }

  
 export function getUserStatusClass(pr,mysendreq,friendsreq) {
    let reqsend = mysendreq.find(e => e.receiver?.user?.username === pr.user?.username);
    let reqrecive = friendsreq.find(e => e.sender?.user?.username === pr.user?.username);
    let reqId = null;
    let classStat = '';
  
    if (reqsend) {
      reqId = reqsend.id;
      classStat = `<a class="deletef text-center btn"><i class=" fa-solid fa-user-xmark"></i></a>`;
    } else if (reqrecive) {
      reqId = reqrecive.id;
      classStat = `<a class="acceptf text-center btn"><i class="fas fa-check"></i></a>`;
    } else {
      classStat = `<a class="addf text-center btn"><i class="fa-solid fa-user-plus"></i></a>`;
    }
  
    return { classStat, reqId };
  }


 export async function acceptRequestFriend(friendsreq,id){
    if (!id){
      messageHandling("error", "Failed to accept friend: Invalid ID.");
      return;
    }
    try {
      const req = friendsreq.find(e => e.id ===  id);
      const response = await fetchWithAuth(`api/acceptfriend/${id}/`);
  
      await handleResponse(response);
      sendTroughSocket("notf-socket",JSON.stringify({ type: 'update', user_id : req.sender.id}))
      navigateTo("/friends");
    } catch (error) {
      messageHandling( "error", `Failed to accept friend request: ${error})`);
    }
  }



 export async function sendRequestFriend(id){
    if (!id){
      messageHandling("error", "Failed to send request  friend: Invalid ID.");
      return;
    }
    try {
      const response = await fetchWithAuth(`/api/addfriend/${id}/`);
      await handleResponse(response);
      navigateTo("/friends");
    } catch (error) {
      messageHandling( "error", `Failed to send friend request: ${error})`);
    }
  }



 export async function deleteRequestFriend(id,friendsreq,mysendreq){
    if (!id){
      messageHandling("error", "Failed to remove friend: Invalid ID.");
      return;
    }
    try {
  
      const srId = giveReqUserId(id,friendsreq,mysendreq);
      const response = await fetchWithAuth(`api/acceptfriend/${id}/`, 'DELETE');
      await handleResponse(response);

      sendTroughSocket("notf-socket",JSON.stringify({ type: 'update', user_id : srId}) )
      navigateTo("/friends");
    } catch (error) {
      messageHandling( "error", `Failed to delete friend request: ${error})`);
    }
  }

  export function sendTroughSocket(id,message){
    if (WebSocketManager.sendMessage(id,message) )
      {
        WebSocketManager.closeSocket(id);
        establishSocket();
      }
  }

 export function  giveReqUserId(id,friendsreq,mysendreq){
    const reqRe =  friendsreq.find(e => e.id ===  id);
    const reqSe =  mysendreq.find(e => e.id ===  id);
    if(reqRe)
      return reqRe.sender.id;
    if (reqSe) {
      return reqSe.receiver.id;
    }
  }
  

  export async function  addManageUserFriend(e,reqId,userId ,friendsreq,mysendreq){
    if (e.currentTarget.classList.contains("deletef")) 
          await deleteRequestFriend(reqId,friendsreq,mysendreq)
    else if (e.currentTarget.classList.contains("acceptf")) 
          await acceptRequestFriend(friendsreq,reqId)
    else if (e.currentTarget.classList.contains("addf")) 
          await sendRequestFriend(userId)
  }
  