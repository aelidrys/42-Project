
const globalData ={

    profiles : null,
    data:null,
    inChatPage: false,
    currentView : null,
    soketQueue : null,

}
export default globalData;


export function setLoader(b) {
  const loadPage = document.querySelector(".load-page");
  const freezeAll = document.querySelector(".freez-all");

  if (loadPage && freezeAll) {
    if (b) {
      loadPage.style.display = "block";
      freezeAll.style.display = "block";
    } else {
      loadPage.style.display = "none";
      freezeAll.style.display = "none";
    }
  }
}


// Function to clone a message for another user (received message)
export function clone_messageOther(messg, img) {
  const youTempMsg = document.querySelector(".you-tempmsg");

  if (youTempMsg) {
    const _clone = youTempMsg.content.cloneNode(true);
    const messageElement = _clone.querySelector(".you-message");
    const imgElement = _clone.querySelector("img");

    if (messageElement) messageElement.innerText = messg  || "not difine";
    if (imgElement) imgElement.src = img || "";

    return _clone;
  }
  return null;
}

  
  export function  clone_messageCurrent(messg,img) {
    const  meTempMsg = document.querySelector(".me-tempmsg")
    if (!meTempMsg) return;
    const  clone = meTempMsg.content.cloneNode(true);

    const meMsg = clone.querySelector(".me-message");
    const imgMsg = clone.querySelector("img");
    if (meMsg) meMsg.innerText = messg;
    if (imgMsg) imgMsg.src = img;
    return clone;
  }


  export function getProfileById(id) {
    return globalData.profiles.find(profile => profile.user.id === id);
  }

//   export function SetCookie(name, value) {
//     document.cookie = `${name}=${value}; path=/`;
// }
export function SetCookie(name, value, days = 0) {
  let expires = '';
  // if (days) {
  //     const date = new Date();
  //     date.setTime(date.getTime() + days * 24 * 60 * 60 * 1000);
  //     expires = `; expires=${date.toUTCString()}`;
  // } else 
  if (value === null) {
      // Set to a past date to delete the cookie
      expires = '; expires=Thu, 01 Jan 1970 00:00:00 UTC';
  }
  document.cookie = `${name}=${value || ''}${expires}; path=/`;
}


  export function getCookie(name){

    const cookieDecoded = decodeURIComponent(document.cookie);
    const arrayCookie = cookieDecoded.split("; ")
    let result ;
    arrayCookie.forEach(e=> {

      if (e.indexOf(name) == 0) {
        result =  e.substring(name.length +1);
      }
    })
    return result ;
  }


  export function CheckTokenExpire(time){

    const currnetTime =Math.floor( Date.now() / 1000);
    const refreshTime = time - currnetTime;
    return refreshTime;
  }


  export function removeFrame() {
    const fuser = document.querySelector(".freined-profile-user");
    const holdvi = document.querySelector(".height-view");
    if (fuser) fuser.style.display = "none";
    if (holdvi) holdvi.style.display = "none";
    
  }