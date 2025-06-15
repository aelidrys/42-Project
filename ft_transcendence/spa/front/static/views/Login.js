import AbstractView from "../js/AbstractView.js";
import { navigateTo,establishSocket,refreshAccessToken} from "../js/index.js";
import { messageHandling } from "../js/utils.js";
import { CheckTokenExpire, SetCookie,getCookie } from "../js/tools.js";
import { loginHTML } from "../js/HtmlPages.js";

export default class extends AbstractView {
    constructor() {
        super();
        this.setTitle("Login");
    }

    async getHtml() {return loginHTML;}
    
    async  sendRequest(url, data) {
        try {
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(data)
            });
            return response;
        } catch (error) {
            messageHandling("error", error);
            throw error;
        }
    }
    
    handleResponse(response, responseData) {
        if (response.ok) {
            return responseData;
        } else {
            const errorMessage = `${Object.keys(responseData)[0]} : ${Object.values(responseData)[0]}`;
            throw new Error(errorMessage);
        }
    }
    
     setTokens(access, refresh) {
        SetCookie('access_token', access);
        SetCookie('refresh_token', refresh);
    }
    
     handleSuccess(message, redirectUrl) {
        messageHandling("success", message);
        navigateTo(redirectUrl);
    }

    getFormData(formElement) {
        const formdata = new FormData(formElement);
        return Object.fromEntries(formdata.entries());
    }
    async loginUser(event) {
        event.preventDefault();
        const data = this.getFormData(event.target);

        try {
            const response = await this.sendRequest('/api/login/', data);
            const responseData = await response.json();
            const result = this.handleResponse(response, responseData);
            this.setTokens(result.access, result.refresh);
            this.handleSuccess("User login successfully", "/home");
        } catch (error) {
            messageHandling("error",error.message)
        }
    }
    async  registerUser(event) {
        event.preventDefault();
        const data = this.getFormData(event.target);    
        try {
            const response = await this.sendRequest('/api/register/', data);
            const responseData = await response.json();
            this.handleResponse(response, responseData);
            this.handleSuccess("User registered successfully", "/login");
        } catch (error) {
            messageHandling("error",error.message)
        }
    }

    async searchHandle(){}  
    async getSidebar(){return ``;}
    async authorizeIntra() {window.location.href = "/api/rauth/intra_authorize";}
    async loginWithIntra() { await this.authorizeIntra();}
    async inAuthpages(){return true;}

    afterRender() {
        const loginInput = document.querySelector(".login-input");
        const loginIntra =  document.querySelectorAll(".login-with-intra");
        const registerInput = document.querySelector(".register-input");
        if (loginInput)   loginInput.addEventListener("submit", this.loginUser.bind(this));
        if (registerInput) registerInput.addEventListener("submit", this.registerUser.bind(this));
        
        loginIntra.forEach((e)=>{   e.addEventListener("click", this.loginWithIntra.bind(this));   });                 

        const container = document.getElementById('container_login');
        const registerBtn = document.getElementById('register');
        const loginBtn = document.getElementById('login');

      if (registerBtn) registerBtn.addEventListener('click', () => {if (container)  container.classList.add("active");});
      if (loginBtn)   loginBtn.addEventListener('click', () => { if (container)  container.classList.remove("active");});
    }
 
}
