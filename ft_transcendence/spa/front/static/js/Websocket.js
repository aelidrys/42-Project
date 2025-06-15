
import globalData, { removeFrame } from "./tools.js";
import { notificationHtml, messageHandling} from "./utils.js";
import { clone_messageOther ,getProfileById} from "../js/tools.js";
import { online_game , remove_game_belong} from "./online2.js";
import {is_offline_running, remove_offgame_belong} from "./offline.js"
import { navigateTo, tokenIsValid } from "./index.js";
import { f_cancel_Ltrn } from "../views/local_trn.js";

const WebSocketManager = {
    socketMap : new Map(),
    addSocket(id,url,onmessageHandel){
        if (this.socketMap.has(id)) {
            return ; 
        }
        const socket = new WebSocket(url);
        socket.onopen = () =>{
            if (id === "chat-socket") 
                socket.send( JSON.stringify({ type: 'start', user_id : globalData.currentView.payload.user_id})); 
        } 
        socket.onmessage = onmessageHandel;
        socket.onclose = (e) =>{
        } 
        socket.onerror = (error) => {messageHandling("error","Connection Error")}
        this.socketMap.set(id, socket);
    },
    sendMessage(id,message){
        const socket = this.socketMap.get(id);
        if (socket && socket.readyState === WebSocket.OPEN) {
            socket.send(message);
        } else {
            messageHandling("error",` Please check your connection or try refreshing the page.`)
            return 1;
        }
        return 0
    },
    closeSocket(id){
        const socket = this.socketMap.get(id);
        if (socket) {
            socket.close();
            this.socketMap.delete(id);
        }
    },
    closeAllSockets(){
        this.socketMap.forEach((socket,id)=>{
            socket.close();
        });
        this.socketMap.clear();
    },

}

export default WebSocketManager;

const markMessageAsRead = (receivedData) => {
    receivedData.all_unread_msgs--;
    WebSocketManager.socketMap.get("chat-socket").send(JSON.stringify({
        user_id: globalData.currentView.payload.user_id,
        type: "msg_isRead",
        msg_id: receivedData.msg_id
    
    }));
};

const appendMessageToChat = (receivedData, conver_chat_) => {
    const avatar = getProfileById(receivedData.sender_id).avatar;
    const messgHold = clone_messageOther(receivedData.msg_text, avatar);

    if(messgHold) conver_chat_.appendChild(messgHold);
    conver_chat_.scrollTop = conver_chat_.scrollHeight;
};

const updateChatSelection = (senderId,Msg="") => {
    let profile = getProfileById(senderId)
    if (!profile){
        globalData.currentView.setDataProfiles().then(e =>{
            profile = getProfileById(senderId);
            globalData.currentView.removeChatSelect(senderId);
            globalData.currentView.createSelectChats(profile, 0, true,Msg);
        }  
        );
    }
    else{
        globalData.currentView.removeChatSelect(senderId);
        globalData.currentView.createSelectChats(profile, 0, true,Msg);
    }
};

// Handle message reception in chat
const handleChatMessage = (receivedData) => {
    const convheader = document.querySelector(".chat-box-header");
    const conver_chat_ = document.querySelector(".conversation-chat");
    if (convheader) {
        const currentOtherId = convheader.idForSubmitMessage;
        if (receivedData.sender_id == currentOtherId) {
            markMessageAsRead(receivedData);
            receivedData.unread_msgs--;
           if(conver_chat_) appendMessageToChat(receivedData, conver_chat_);
            updateChatSelection(receivedData.sender_id,receivedData.msg_text);
        }
    }
};

//Notification Of new messages 
function removeMessageNotification(prentelement){
    if(prentelement)
        prentelement.remove();
}

function userMessageClone(sender_id,msg_text=""){
    const  MsgTmp = document.querySelector(".recieve-chat-message-tmp");
    if(!MsgTmp) return null;

    let _clone = MsgTmp.content.cloneNode(true);
    let profile = getProfileById(sender_id);    
    const img = _clone.querySelector("img");
    const username_ = _clone.querySelector(".wasla-name");
    const  message_ = _clone.querySelector(".wasla-status p");
    const  cancelbtn = _clone.querySelector(".wasla-meta");
    const  prentelement = _clone.querySelector(".wh-container");
    
    if (img) img.src = profile?.avatar;
    if (username_) username_.innerHTML = profile?.user?.username || "Undifinde user";
    if (message_) message_.innerText = msg_text;
    if (cancelbtn) cancelbtn.addEventListener("click", () => removeMessageNotification(prentelement));
    setTimeout(() => {
        removeMessageNotification(prentelement)
    }, 10000);
    return _clone;
}

function trnMessageClone(){
    const  MsgTmp = document.querySelector(".recieve-chat-message-tmp");
    if(!MsgTmp) return null;

    let _clone = MsgTmp.content.cloneNode(true);
    const  img = _clone.querySelector("img");
    const username_ = _clone.querySelector(".wasla-name");
    const  message_ = _clone.querySelector(".wasla-status p");
    const  cancelbtn = _clone.querySelector(".wasla-meta");
    let prentelement = _clone.querySelector(".wh-container");
    
    if (img) img.src = "/static/images/cup.png";
    if (username_) username_.innerHTML = "Tournmeant";
    if (message_) message_.innerText = `⚠️Your tournament match has started! Join immediately to avoid disqualification.`;
    if (cancelbtn) cancelbtn.addEventListener("click", () => removeMessageNotification(prentelement));

    setTimeout(() => {
        removeMessageNotification(prentelement)
    }, 10000);
    return _clone;
}
function alertNewMessage({type,sender_id,msg_text}){
    const  messageHolder =   document.querySelector(`.message-holder`);
    if (!messageHolder)  return;
    let _clone = null;
    if (type == "warn") 
        _clone = trnMessageClone()
    else if(type == "msg"){
        _clone = userMessageClone(sender_id,msg_text);
    }
    if(_clone) messageHolder.append(_clone);
}

// Update unread messages count for the sender in the UI
const updateUnreadMessages = (receivedData ) => {
    
    if(!globalData?.currentView?.chatSelctMap) {  return;}
    const element = globalData.currentView.chatSelctMap.get(parseInt(receivedData.sender_id));
    if (element) {
        const unreadMessagesElement = element.querySelector(".number-messages");
        if(unreadMessagesElement){
            unreadMessagesElement.innerHTML = receivedData.unread_msgs;
            unreadMessagesElement.style.display =  receivedData.unread_msgs ?  "block" : "none";
        }
    }
};

// Update total unread messages count in the UI
const updateTotalUnreadMessages = (totalUnread) => {
    const numofmsg = document.querySelector(".all-number-msg");
    if (numofmsg) numofmsg.innerHTML = totalUnread;
};


function warnCloneAlert() {
    const temp = document.querySelector(".temp-warn");
    const chat_box = document.querySelector(".contact-chat-box");
    if (chat_box) {
        const _clone = temp.content.cloneNode(true);
        const clonedElement = chat_box.appendChild(_clone);
        if(!clonedElement) return;
        setTimeout(() => {
            const ch = _clone.querySelector(".tourn-warn-chat");
            if (ch) {
                ch.removeChild(clonedElement);
            }
        }, 60000);
    }
}


export  const  listenForMessage = (event)=>{
    let receivedData;
    receivedData = JSON.parse(event.data);
    if (globalData.inChatPage)  {
        if(receivedData.type == "msg")
        {
            handleChatMessage(receivedData);
            updateChatSelection(receivedData.sender_id,receivedData.msg_text);
        }
        else if(receivedData.type == "warn"){
            const chatBox = document.querySelector(".contact-chat-box");
            if(chatBox)
                chatBox.classList.remove("openC");
            warnCloneAlert();
        }
        else if(receivedData.type == "block"){
            globalData.currentView.displayChatConversations(getProfileById(receivedData.other_uid))
        }
    }
    if (receivedData.type != "block") {
        if (!globalData.inChatPage)  alertNewMessage(receivedData);
        updateTotalUnreadMessages(receivedData.all_unread_msgs);
        updateUnreadMessages(receivedData);
    }
}

export  const  lisenForNotifications  = async (e)=> {
    let data ;
    
    const notfBell = document.querySelector(".notif-nums");
    data = JSON.parse(e.data);
    if(globalData.currentView.pageTitle == "FRIENDS")
    {
        await globalData.currentView.inAuthpages();
        await globalData.currentView.setFunctions();
        await globalData.currentView.afterRender();
    
    }
    if (data._type == "update") {
        return ;
    }
    if (notfBell)
        notfBell.innerHTML = data.size_notf;

    if (data._type == "invite_game") {
        let recever = data.message.recever;
        let sender   = data.message.sender;

        let msgtmp = document.querySelector(".recieve-chat-message-game");
        let _clone = msgtmp.content.cloneNode(true);
        let messageHolder =   document.querySelector(`.message-holder`);
        let img = _clone.querySelector("img");
        let message_ = _clone.querySelector(".wasla-status p");
        let cancelbtn = _clone.querySelector(".wasla-cancel");
        let acceptbtn = _clone.querySelector(".wasla-accepte");
        let prentelement = _clone.querySelector(".wh-container");
        prentelement.id = `game_invite_${sender.id}_${recever.id}`
    // han
        if (is_offline_running == true)
        {
            WebSocketManager.socketMap.get("notf-socket").send(
                JSON.stringify({ 
                    user_id : recever.id,
                    type : 'player_is_ingame',
                    recever : recever,
                    sender : sender,
                    message : `${recever.username} is in a ofline game`,
                    invite_key :`game_invite_${sender.id}_${recever.id}`,    
                }));
            return;
        }

        img.src = data.avatar;
        message_.innerText = "game invite from " + sender.username;

    
        cancelbtn.addEventListener("click", () => {
            WebSocketManager.socketMap.get("notf-socket").send(
                JSON.stringify({ 
                    user_id : recever.id,
                    type : 'inivte_cancel',
                    recever : recever,
                    sender : sender,
                    message : `${recever.username} has declined`,
                    invite_key :`game_invite_${sender.id}_${recever.id}`,    
                }));
            removeMessageNotification(prentelement);
        });
        acceptbtn.addEventListener("click", () => {
            f_cancel_Ltrn()
            if(globalData.currentView.pageTitle == "TOURNAMENT"){
                navigateTo('/tournament')
            }
            if (globalData.currentView.pageTitle == "GAMES")
            {
                let soketQ = globalData.currentView.vars.sock;
                if (soketQ &&  soketQ.readyState != WebSocket.CLOSED)
                {
                    globalData.currentView.closeQueue();
                }
            }
            WebSocketManager.socketMap.get("notf-socket").send(
                JSON.stringify({
                    user_id : recever.id,
                    type : 'inivte_accept',
                    recever : recever,
                    sender : sender,
                    message : `${recever.username} has accepted`,
                    channel_name : data.id,
                    invite_key :`game_invite_${sender.id}_${recever.id}`,    
                }));
            removeMessageNotification(prentelement);
        });

        messageHolder.append(_clone);
        return ;
    }
    
    if (data._type == "player_is_ingame")
    {
        messageHandling('info', data.message);
        return;
    }

    if (data._type == "invite_decline")
    {
        messageHandling('info', data.message);
        return;
    }

    if (data._type == "remove_invites")
    {
        data.message.forEach(
            (e) => {
                var elem = document.getElementById(e)
                if (elem !== null) {
                    removeMessageNotification(elem)
                }
            }
        )
        return;
    }
    
    if (data._type == 'eng_game_view')
    {
        remove_game_belong();
        messageHandling("error", "game hase beed terminated.")
        return;
    }

    if (data._type == 'error_game')
    {
        messageHandling("error", "game service can't start the match");
        return;
    }

    if (data._type == 'start_playing')
    {
        f_cancel_Ltrn()
        if(globalData.currentView.pageTitle == "TOURNAMENT"){
            navigateTo('/tournament')
        }

        if (globalData.currentView.pageTitle == "GAMES")
        {
            let soketQ = globalData.currentView.vars.sock;
            if (soketQ &&  soketQ.readyState != WebSocket.CLOSED)
            {
                globalData.currentView.closeQueue();
            }
        }
        const valid = await tokenIsValid();
        if(valid){

            online_game({
                "headers" : {
                    'login'        : "",
                    'id'           : data.message,
                    'access_token' : null,
                    'image'        : null,
                },
            })
            removeFrame();
        }
        else
        {
            const url = "";
            const headers = {
                'Authorization': `Bearer ${access_token}`,
                'Content-Type': 'application/json'
            };
            const body = {
                'player_id' : globalData?.currentView?.payload?.user_id
            }

            fetch(
                url,{
                    headers : headers,
                    method : "POST",
                    body: JSON.stringify(body)
                }
            ).then()
            
        }
        return;
    }
    if (data._type == "error")
    {
        messageHandling("error", data.message);
        return;
    }
    
    notificationHtml(data);

}