import AbstractView from "../js/AbstractView.js";
import globalData, { clone_messageCurrent,clone_messageOther,getProfileById,setLoader } from "../js/tools.js";

import { getDataChats,blockUserChat,getMessages,sendMessageTo, setupChatToggleButton, setupFilterListeners, renderChatBoxHeaderUtil, setBlockOption } from "../js/ChatTools.js";
import { chatPageHTML,chatHtml,inputHtml, messageForBolocked } from "../js/HtmlPages.js";
import { messageHandling } from "../js/utils.js";
import WebSocketManager from "../js/Websocket.js";


export default class extends AbstractView {
  constructor() {
    super();
    globalData.inChatPage = true;
    this.lastActiveid= -1;
    this.getDataChats = getDataChats.bind(this);
    this.blockUserChat = blockUserChat.bind(this);
    this.getMessages = getMessages.bind(this);
    this.sendMessageTo = sendMessageTo.bind(this);
    this.setTitle("Chat");
    this.pageTitle= "CHAT";
    this.chatSelctMap = new Map();

 }
async getHtml() {
  await this.setDataProfiles();
  await this.getDataChats();
    const headernav = await this.getHeader();
    return headernav  + chatPageHTML;
}

removeChatSelect(id){
  const element = this.chatSelctMap.get(parseInt(id));
  if (element) {
    this.chatSelctMap.delete(parseInt(id));
      element.remove();
  }
}

getProfileById(id) {
  return this.profiles.find(profile => profile.user.id === id);
}


renderChatBoxHeader(user,avatar) {
  
  const [userProfileLink,inviteGame] = renderChatBoxHeaderUtil(user,avatar) 
  const profileLinkAnchor = userProfileLink?.querySelector("a");
  if (profileLinkAnchor) {
    profileLinkAnchor.addEventListener("click", (event) => {
      this.showFriendProfile(user.id);
    });
  }
  const inviteGameAnchor = inviteGame?.querySelector("a");
  if (inviteGameAnchor) {
    inviteGameAnchor.addEventListener("click", (event) => {
      const notificationSocket = WebSocketManager.socketMap.get("notf-socket");
      if (notificationSocket) {
        notificationSocket.send(
          JSON.stringify({
          type: "invite_game",
          avatar: this.data.avatar,
          message: {
            recever: user,
            sender: this.data.user,
          },
          user_id: user.id,
       })
        );
      } else {
        messageHandling("error","Notification Error not difine")
      }
    });
  }
}


setupBlockUser(user, { block, blocker }) {
  const blockUserElement = document.querySelector(".chat-box-header .block-user-chat");
  const formMessageElement = document.querySelector(".form-submit-messge");

  if (!blockUserElement || !formMessageElement) {
    return;
  }
  blockUserElement.idforBlock = user.id;
  if (!block)
    setBlockOption(blockUserElement, "Block", inputHtml);
  else {
    setBlockOption(blockUserElement, "UnBlock", messageForBolocked);
    if (blocker != this.payload.user_id){
      blockUserElement.innerHTML = "";
      return;
    }
  }
  blockUserElement.addEventListener("click", (e) => this.handleBlockUserClick(e, user));
}

updateBlockStatusUI() {
  const blockUserElement = document.querySelector(".chat-box-header .block-user-chat a");
  const formMessageElement = document.querySelector(".form-submit-messge");

  if (this.isBlock?.blocked) {
    if (blockUserElement) blockUserElement.innerHTML = "UnBlock";
    if (formMessageElement) formMessageElement.innerHTML = messageForBolocked;
  } else {
    if (blockUserElement) blockUserElement.innerHTML = "Block";
    if (formMessageElement) formMessageElement.innerHTML = inputHtml;
  }
}

handleBlockUserClick(e, user) {
  const blockId = e.currentTarget.idforBlock;
  if (!blockId) {
    messageHandling("error","No block ID found for the user.");
    return;
  }

  dialog.showDialog(`Are you sure you want to block ${user.username}?`, async () => {
    await this.blockUserChat(blockId);
    this.updateBlockStatusUI();
  });
}

renderMessages(messages, avatar) {
  const conver_chat_ = document.querySelector(".conversation-chat");
  if (!conver_chat_) return;  
  if (messages) {
    messages.forEach(msg => {
      if (msg.receiver === this.payload.user_id) {
        const messgHold = clone_messageOther(msg.message,avatar)
        if(messgHold) conver_chat_.appendChild(messgHold);
      } else if (msg.sender === this.payload.user_id) {
        conver_chat_.appendChild(clone_messageCurrent(msg.message, this.data.avatar));
      }
    });
  }
  conver_chat_.scrollTop = conver_chat_.scrollHeight;
}
updateActiveChatUser(user) {
  const element = this.chatSelctMap.get(parseInt(user.id));
  const lastActive = this.chatSelctMap.get(parseInt(this.lastActiveid));
  if (lastActive) {
    lastActive.classList.remove("active");
  }
  if (element) {
    element.classList.add("active");
    this.lastActiveid = user.id;
  }
}

addIcontBtn(){
  const chatBox = document.querySelector(".contact-chat-box");
  if(chatBox) chatBox.classList.add("openC");
  const toggleButton = document.querySelector(".btn-open-chat-list");
  if (toggleButton) {
    toggleButton.innerHTML = `  <i class="fa-solid fa-circle-chevron-right"></i>`
  }
}

async displayChatConversations(user_ppppp){
  this.addIcontBtn();
  setLoader(1);
  if(!user_ppppp){  setLoader(0);  return };
  await this.getMessages(user_ppppp.user.id);
  let msgs;
  if (!this.responseDataMsgs) {
    return;
  }
    msgs = this.responseDataMsgs.msgs;
    this.renderChatBoxHeader(user_ppppp.user,user_ppppp.avatar);
    this.setupBlockUser(user_ppppp.user,this.responseDataMsgs);
    this.renderMessages(msgs,user_ppppp.avatar);
    this.updateActiveChatUser(user_ppppp.user);
  setLoader(0);
  
  await this.allMessagesNotRead();

  const numofmsg = document.querySelector(".all-number-msg");
  if (numofmsg) numofmsg.innerHTML = this.number_msgs?.all_unread_mssgs || "0";
  this.emojiSetup();
  this.submitMessage();
}


// Function to create and display a selectable chat user
createSelectChats(userData, unreadMsg = 0, addFirst = false,last_msg = "") {
  const userSelect = document.querySelector(".chat-select-box");
  const template = document.querySelector(".select-chat-template");

  if (!userSelect || !template) return;

  const clone = template.content.cloneNode(true);
  const selectChatElement = clone.querySelector(".select-chat");
  const avatarImage = clone.querySelector("img");
  const usernameElement = clone.querySelector("h4");
  const messageCount = clone.querySelector(".number-messages");
  const lastMsg = clone.querySelector("p");

  if (selectChatElement && avatarImage && usernameElement && messageCount) {
    selectChatElement.dataset.select_id = userData?.user?.id;
    avatarImage.src = userData?.avatar || "";
    usernameElement.innerHTML = userData?.user?.username || "Unknown User";
    if (lastMsg) lastMsg.innerText   = last_msg;
    if (parseInt(unreadMsg)) {
      messageCount.innerHTML = unreadMsg;
    } else {
      messageCount.style.display = "none";
    }

    selectChatElement.addEventListener("click", (e) => {
      messageCount.style.display = "none";
      this.displayChatConversations(userData);
    });

    if (addFirst) {
      userSelect.insertBefore(clone, userSelect.firstElementChild);
    } else {
      userSelect.appendChild(clone);
    }
    this.chatSelctMap.set(parseInt(userData?.user?.id),selectChatElement);
  }
}

async getOrCreateChat(id){
  if (!id) return;
  await this.getMessages(id);
    if ( this.responseDataMsgs.created  ) 
      {
        const user_ppppp = this.getProfileById(parseInt(id));
        this.removeChatSelect(id);
        this.createSelectChats(user_ppppp,0,true);
        this.displayChatConversations(user_ppppp);
      }
      else {
        const user_ppppp = this.getProfileById(parseInt(id));
        this.displayChatConversations(user_ppppp);
      }
}

onlineUsersList() {
  const onlineContact = document.querySelector(".online-contact");
  const avatarTemplate = document.querySelector(".avatar-template");

  if (!onlineContact || !avatarTemplate) return;

  this.data.friends.forEach((profile) => {
    const friend = profile.user;
    // const profile = this.getProfileById(friend.id);
    if (!profile) return;

    const clone = avatarTemplate.content.cloneNode(true);
    const avatarImage = clone.querySelector("img");
    const chatAvatar = clone.querySelector(".chat-select-avatar");

    if (avatarImage) avatarImage.src = profile.avatar || "";
    if (chatAvatar)   chatAvatar.addEventListener("click",async e=>{ await this.getOrCreateChat(friend.id);   })
    if (profile.is_online) chatAvatar.classList.add("online-status-chat");
      onlineContact.appendChild(clone);
  });
}

submitMessage() {
  const conversationChat =  document.querySelector(".conversation-chat");
  const chatBoxHeader =  document.querySelector(".chat-box-header");
  const messageForm =  document.querySelector(".form-submit-messge");

  if (!conversationChat || !chatBoxHeader || !messageForm) return;

  conversationChat.scrollTop = conversationChat.scrollHeight;
  messageForm.addEventListener("submit", (event) => {

    event.preventDefault();
    const formData = new FormData(event.target);
    const message = formData.get("message")?.slice(0,10000);
    if (!message?.trim()) return;
    conversationChat.append(clone_messageCurrent(message, this.data.avatar));
    const recipientId = chatBoxHeader.idForSubmitMessage;
    this.sendMessageTo(recipientId, message);
    conversationChat.scrollTop = conversationChat.scrollHeight;
    const inp = event.target.querySelector("#chat-message-input");
    if (inp) inp.value = "";

    this.removeChatSelect(recipientId);
    this.createSelectChats(this.getProfileById(parseInt(recipientId)), 0, true,message);

    const activeChat = this.chatSelctMap.get( parseInt(recipientId));
    if (activeChat) activeChat.classList.add("active");
  });
}

async textWriter(element,txt){
  let textwr = document.querySelector(element);
  if (!textwr || !txt) return ;

  for (let index = 0; index < txt.length; index++) {
    setTimeout(() => {
      textwr.innerHTML += txt[index];
    }, 100 * index);  
  }
}

ChatList() {
  this.chats.forEach(chat => {
    const otherUserId = chat.user1_id !== this.payload.user_id ? chat.user1_id : chat.user2_id;
    const userProfile = this.getProfileById(otherUserId);
    this.removeChatSelect(otherUserId); 
    this.createSelectChats(userProfile, chat.unread_msg,false,chat.last_msg); 
  });
}

setEmojiInput(e){
  const input = document.querySelector("#chat-message-input");
  if (!input) {
    return;
  }
  input.value += e;
  input.focus();

}

emojiSetup(){
  const buttonemoj = document.querySelector(".emoji-label ")
  const emojiholder = document.querySelector(".emoji-menu");
  
  if (!emojiholder || !buttonemoj ) {
    return
  }

  buttonemoj.addEventListener("click",e =>{
    emojiholder.classList.toggle("visible");
  })

  emojiholder.addEventListener("click",e=> {
  const emoj = e.target.textContent;
  this.setEmojiInput(emoj);
})
}
 getProfilesHtmlClone(user_id, profiles, classselect, tmp) {
  const ulHolder = document.querySelector(classselect);
  const templi = document.querySelector(tmp);

  if (!ulHolder || !templi) {
    return;
  }

  profiles.forEach((user) => {
    if (user.user.id !== user_id) {
      const clone = templi.content.cloneNode(true);

      const img = clone.querySelector("img");
      const div = clone.querySelector("div");
      const li = clone.querySelector("li");

      if (img) img.src = user.avatar;
      if (div) div.innerHTML = user.user.username;
      if (li) {
        li.classList.toggle("hide");
        li.idTargetUser = user.user.id;
        li.addEventListener("click",async e=>{ await this.getOrCreateChat(user?.user?.id);})
      }
      ulHolder.append(clone);
    }
  });
}




async afterRender() {
  setupChatToggleButton();
  const chatBox = document.querySelector(".chat-box");
  if (chatBox) {
    chatBox.innerHTML = `
      <div class=""> <i class="fa-solid fa-comments"></i></div>
      <div class="no-chat text-wlc"></div>
    `;
  }
  this.getProfilesHtmlClone(this.payload.user_id,this.profiles,".chat-search ul",".li-temp");
  setupFilterListeners();
  this.ChatList();
  this.textWriter(".text-wlc","start new chat !");
  this.onlineUsersList();

  }
}