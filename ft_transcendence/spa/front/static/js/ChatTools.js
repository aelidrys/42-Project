
import { clone_messageOther ,getProfileById,getCookie,CheckTokenExpire,SetCookie, setLoader} from "../js/tools.js";
import { chatHtml } from "./HtmlPages.js";
import { tokenIsValid } from "./index.js";
import { messageHandling } from "./utils.js";



export async function getDataChats() {
    try {
  
      const ____data = {
        user_id : this.payload.user_id,
      }
      const response = await fetch(`chat/chats`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
          'Authorization': `Bearer ${getCookie("access_token")}`,

        },
        body: JSON.stringify(____data)
      });
      const responseData =  await handleResponse2(response);
      this.chats = responseData.chats;
    } catch (error) {
      messageHandling("error",error);
    }
  
  }
  
  export async function blockUserChat(id){
    try {
      const ____data = {
        current_id : this.payload.user_id,
        other_id : id, 
      }
      const response = await fetch(`chat/block`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
          'Authorization': `Bearer ${getCookie("access_token")}`,

        },
        body: JSON.stringify(____data)
      });
      this.isBlock = await handleResponse2(response);
    } catch (error) {
      messageHandling("error",error);
    }
  }



  export async function handleResponse2(response) {
    const responseData = await response.json();
  
    if (response.ok) {
      return responseData;
    } else if (response.status === 401 || response.status === 403) {
      const refreshed = await tokenIsValid();
      if (refreshed) {
        throw new Error("RetryRequest"); 
      }

      messageHandling("error", "Session expired, please log in again.");
    } else {
      const errorDetail = responseData.detail || 'An error occurred';
      throw new Error(errorDetail);
    }
  }
  

  export async function getMessages(id){
    try {
      const ____data = {
        current_uid : this.payload.user_id,
        other_uid : id, 
      }
      const response = await fetch(`chat/`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${getCookie("access_token")}`,

        },
        body: JSON.stringify(____data)
      });
      this.responseDataMsgs = await handleResponse2(response);
  
    } catch (error) {
      messageHandling("error",error);
    }
    
  }
  

  export async function  sendMessageTo(other_id,message){
    try {
  
      const ____data = {
        sender_id : this.payload.user_id,
        receiver_id : parseInt(other_id),
        message :message,
      }
      const response = await fetch(`chat/send_msg`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${getCookie("access_token")}`,

        },
        body: JSON.stringify(____data)
      });

      await handleResponse2(response);
    } catch (error) {
      messageHandling("error",error);
    }
  
  }



// Setup the chat toggle button to open/close chat list
export function setupChatToggleButton() { 
  const toggleButton = document.querySelector(".btn-open-chat-list");
  if (toggleButton) {
    toggleButton.addEventListener("click", (e) => {
      const chatBox = document.querySelector(".contact-chat-box");

      if (chatBox) {
        chatBox.classList.toggle("openC");
        e.currentTarget.innerHTML =``;
      }
    });
  }
}

// Setup filter input listeners for filtering chat contacts
export function setupFilterListeners() {
  const filterInput = document.querySelector("#filter");
  if (filterInput) {
    filterInput.addEventListener("input", (e) => filterData(e.target.value));
    
    filterInput.addEventListener("blur", () => {
      const searchResults = document.querySelectorAll(".chat-search ul li");
      searchResults.forEach((item) => item.classList.add("hide"));
    });
  } 
}
 

 // Filter data based on input value
export function filterData(value) {
  const allListSrch = document.querySelectorAll(".chat-search ul li");
  
  allListSrch.forEach((item) => {
    const usernameElement = item.querySelector("div");
    if (usernameElement) {
      const username = usernameElement.innerText;
      item.classList.toggle("hide", !username.toLowerCase().includes(value.toLowerCase()));
    }

    item.addEventListener("mousedown", (e) => {
      e.preventDefault();
    });
  });
}

export function renderChatBoxHeaderUtil(user,avatar) {
  const divChatBox = document.querySelector(".chat-box");
  if (!divChatBox) return; 
  divChatBox.innerHTML = chatHtml;

  const chatBoxHeader = divChatBox.querySelector(".chat-box-header");
  if (!chatBoxHeader) return; 

  const userAvatar = chatBoxHeader.querySelector("img");
  const userProfileLink = chatBoxHeader.querySelector(".profile-from-chat");
  const inviteGame = chatBoxHeader.querySelector(".invite-game-chat");

  if (userAvatar) userAvatar.src = avatar;
  
  chatBoxHeader.idForSubmitMessage = user.id;
  const userNameElement = chatBoxHeader.querySelector("h2");
  if (userNameElement) userNameElement.textContent = user.username;


  if (inviteGame) {
    inviteGame.innerHTML = `<a class="dropdown-item go-profile">Invite Game</a>`;
  }
  if (userProfileLink) {
    userProfileLink.innerHTML = `<a class="dropdown-item go-profile">Profile</a>`;
  }

  return [userProfileLink,inviteGame] ;
}


export function setBlockOption(element, actionText, formContent) {
  if (element) {
    element.innerHTML = `<a class="dropdown-item">${actionText}</a>`;
    const formMessageElement = document.querySelector(".form-submit-messge");
    if (formMessageElement) formMessageElement.innerHTML = formContent;
  }
}