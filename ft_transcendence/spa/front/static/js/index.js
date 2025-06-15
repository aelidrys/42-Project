import  {router}   from "./router.js";
import {CostumConfigDialog,messageHandling} from "./utils.js";
import { clone_messageOther ,getProfileById,getCookie,CheckTokenExpire,SetCookie, setLoader} from "../js/tools.js";
import WebSocketManager from "./Websocket.js";
import { listenForMessage ,lisenForNotifications} from "./Websocket.js";
import { fetch_data, getDataUtils } from "./BaseUtils.js";
window.dialog = new CostumConfigDialog();

export function establishSocket(){
    let loc = window.location;
    let wsStart = 'ws://';
    if (loc.protocol == 'https:') {
        wsStart = 'wss://'
    }
    let endpoint = wsStart + loc.host ;
    WebSocketManager.addSocket("chat-socket",`${endpoint}/ws/chat/`,listenForMessage);
    WebSocketManager.addSocket("notf-socket",`${endpoint}/ws/notf/`,lisenForNotifications);
}
export const navigateTo = url => {
    history.pushState(null ,null,url);
    router();
}

window.addEventListener("load",e=>{
    setLoader(0);
})

window.addEventListener("popstate", router);
document.addEventListener("DOMContentLoaded", async ()=>{
    document.body.addEventListener("click", e => {
        const linkElement = e.target.closest("[data-link]");
        if (linkElement) {
            e.preventDefault();
            const href = linkElement.getAttribute('href');
            if (href) {
                navigateTo(href);
            }
        }
    });
    var _data = await getDataUtils()
    const url = '/tournament/is_inTourn/';
    var data = null
    if (_data)
        data = await fetch_data(url, 'POST', JSON.stringify(_data))
    if (data?.intourn == 'yes'){
        navigateTo('/tournament')
    }
    else
        router();
})

 export const refreshAccessToken = async () => {
    try {
        const response = await fetch('/api/refresh/', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
    });
    const data = await response.json();
    if (response.ok) {
        SetCookie("access_token",data.access)
        return true;
    } else {
        WebSocketManager.closeAllSockets();
        SetCookie("access_token",null);
        SetCookie("refresh_token",null);
        navigateTo('/login');
        return false
    }
    } catch (error) {
        messageHandling('error','An unexpected error occurred. Please try again later.');
        return false;
    }
};


async function checkAfterRefreshToken(){
    const accessToken = getCookie('access_token');
    if(!accessToken)return false;
    try {
        
        const retryResponse = await fetch(`/api/protected/`, {
            method: 'GET',
        headers: {
            'Content-Type': 'application/json',
            'Authorization': `Bearer ${getCookie('access_token')}`,
        },
    });
    if (retryResponse.ok) {
        return true;
    } else {
        
        WebSocketManager.closeAllSockets();
        SetCookie("access_token",null);
        SetCookie("refresh_token",null);
        navigateTo("/login");
        return false;
    }
    } catch (error) {
        messageHandling('error','An unexpected error occurred. Please try again later.');
        navigateTo("/login");
        return false;
        
    }
}
export async   function tokenIsValid() {

    try {
        const response = await fetch(`/api/protected/`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${getCookie('access_token')}`,
            },
        });
        if (response.ok) {
        return true;
    } else {
        messageHandling("info","Session is invalid. Attempting to refresh.");
        const check = await refreshAccessToken()
        if(!check) return false;
        return await checkAfterRefreshToken();
    }
    } catch (error) {
        navigateTo('/login');
        return false;
    }
};

window.addEventListener('offline', () => {
    messageHandling("error",'You are currently offline. Please check your internet connection.');
  });