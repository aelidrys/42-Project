import { getCookie, setLoader } from "./tools.js";





export class CostumConfigDialog {
    
    constructor() {
        this.dlg = document.querySelector(".dlg-container");
        if(this.dlg){
            this.dlgmsg = this.dlg.querySelector(".dlg-message");
            this.okButton = this.dlg.querySelector(".dlg-ok");
            this.cancelButton = this.dlg.querySelector(".dlg-cancel");
            this.initEvents();  
        }
    }

    initEvents() {
       if (this.okButton) this.okButton.addEventListener("click", () => this.ok());
       if (this.cancelButton) this.cancelButton.addEventListener("click", () => this.close());
    }

    showDialog(msg, callback) {
        this.msg = msg;
        this.call = callback;

        if(this.dlgmsg)   this.dlgmsg.textContent = this.msg;
        if(this.dlg)  this.dlg.style.display = "block";

        const freez = document.querySelector(".freez-all");
        if (freez) freez.style.display = "";
    }

    ok() {
        if (typeof this.call === "function") {
            this.call();
        }
        this.close();
    }

    close() {
        if(this.dlg)  this.dlg.style.display = "none";
        
        const freez = document.querySelector(".freez-all");
        if (freez) freez.style.display = "none";
    }
}



function iconNotif(type){

    if (type == "success") 
        return `<i class="me-2 text-success fs-3 fa-solid fa-circle-check"></i>`;
    else if(type == "info")
        return `<i class="me-2  text-info  fa-solid fs-3 fa-circle-info"></i>`;
    else
        return `<i class=" me-2  fs-3 text-danger  fa-solid fa-circle-xmark"></i>`;
}

export function messageHandling(type,description) {
    if (type == "error") {
        const buttonEx = document.querySelector(".btn-exit");
        if(buttonEx) buttonEx.click();
        setLoader(0);
    }
    const templateMsg = document.querySelector(`#message-${type}-template`);
    const messageHolder =   document.querySelector(`.message-holder`);
    if (!templateMsg || !messageHolder ) return;

    const  cloneMsg = templateMsg.content.cloneNode(true);
    const msgContent =  cloneMsg.querySelector(".hold-msg-content");
    const msgType =  cloneMsg.querySelector(`.message-${type}`);

    if (!msgContent || !msgType)  return; 
    msgContent.innerHTML =  ` 
    <div class="position-absolute top-0 start-100 translate-middle close-alert"><i class="fa-solid fa-xmark"></i></div>
    <p> ${iconNotif(type)} </p>
                                                        <p> ${description}</p>
                                                `;
    msgType.appendChild(msgContent);
    messageHolder.appendChild(msgType);

    const closeButton = msgType.querySelector(".close-alert");
    if (closeButton ) closeButton.addEventListener("click", e=> msgType.remove());

    setTimeout(() => {
        msgType.remove();
    }, 10000);
}


function listElement(isRead){
    const listItem = document.createElement("li");
    
    if (!listItem) return null;
    // Add fixed and conditional classes
    listItem.classList.add("item-drop-custum");
    listItem.classList.add("notif-not-read");
    
    listItem.setAttribute("data-link", "");
    return listItem
}

export function getTime(isoTimestamp) {
    const date = new Date(isoTimestamp);
    const year = date.getUTCFullYear();
    const month = String(date.getUTCMonth() + 1).padStart(2, "0"); // Months are zero-indexed
    const day = String(date.getUTCDate()).padStart(2, "0");
    const hours = String(date.getUTCHours()).padStart(2, "0");
    const minutes = String(date.getUTCMinutes()).padStart(2, "0");
    return `${year}-${month}-${day} ${hours}:${minutes}`;
  }

function addInNotificationList(id,is_read,message,time){
 const notificationList = document.querySelector(".notification-list");
 if (!notificationList) return; 

 const listItem = listElement(is_read);
 if (listItem) {
    const content = `
    <a class="dropdown-item mini-item-drop " href="/friends" data-id="${id}"  data-link> ${message}  | ${getTime(time)}</a>  
        <button type="button" class="btn  btn-rm-notf btn-danger bg-danger rm-notification"   data-id="${id}">
            <i class="fa fa-times"></i>
        </button>`
    listItem.innerHTML = content;
    notificationList.insertBefore(listItem, notificationList.firstChild);
 }
 

}

export function notificationHtml({id,avatar,is_read,message,time}) {

    addInNotificationList(id,is_read,message,time);
    const messageHolder =   document.querySelector(`.message-holder`);
    const templateMsg = document.querySelector(`#message-request-template`);

    if (!templateMsg || !messageHolder ) return;

    const  cloneMsg = templateMsg.content.cloneNode(true);
    const msgContent =  cloneMsg.querySelector(".hold-msg-content");
    const msgType =  cloneMsg.querySelector(`.message-request`);

    if (!msgContent || !msgType)  return; 
    msgContent.innerHTML =  
    `     
    <div class="position-absolute top-0 start-100 translate-middle close-alert"><i class="fa-solid fa-xmark"></i></div>

    <p> ${message}</p>   
    <a href="/friends" data-link>
        <i class="fas fa-arrow-right"></i>
    </a>
    `;

    msgType.appendChild(msgContent);
    messageHolder.appendChild(msgType);

    const closeButton = msgType.querySelector(".close-alert");
    if (closeButton ) closeButton.addEventListener("click", e=> msgType.remove());

    setTimeout(() => {
        msgType.remove();
    }, 10000);

}