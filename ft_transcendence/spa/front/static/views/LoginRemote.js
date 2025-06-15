import AbstractView from "../js/AbstractView.js";
import { navigateTo } from "../js/index.js";
import { getCookie, SetCookie } from "../js/tools.js";
import { messageHandling } from "../js/utils.js";
export default class extends AbstractView {
    constructor() {
        super();
        this.setTitle("Login");
        
    }
    async getHtml() {   return ` `;}
    async getSidebar() { return ``;}

    getCodeState(){

        const urlParams = new URLSearchParams(window.location.search);
        const code = urlParams.get('code');
        const state = urlParams.get('state');
        return {code: code,state: state};
    }

    setTokens(access, refresh) {
        SetCookie('access_token', access);
        SetCookie('refresh_token', refresh);
    }

    async fetchRemoteTokens(code ,state) {
        try {
            const response = await fetch(`/api/rauth/auth_intra?code=${code}&state=${state}`, {
                method: 'GET',
            });
            const responseData = await response.json();
            if (response.ok) {
                const {access_token,refresh_token} = responseData;
                SetCookie('access_token', access_token);
                SetCookie('refresh_token', refresh_token);
                navigateTo("/home")
            } else {
                messageHandling("error",responseData.details);
                navigateTo("/login");
            }
        } catch (error) {
            messageHandling("error",error.message)
            navigateTo("/login");
        }
    }

    async searchHandle(){}  
    async inAuthpages(){return true;}

    afterRender() {
        const urlParams = new URLSearchParams(window.location.search);
        if (urlParams.has('code') && urlParams.has('state')) {
            this.fetchRemoteTokens(urlParams.get('code'),urlParams.get('state'));
        }
        else
            navigateTo("/notfound");
    }
}
