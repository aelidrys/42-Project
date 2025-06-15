// Login.js
import AbstractView from "../js/AbstractView.js";
import { messageForBolocked } from "../js/HtmlPages.js";
import WebSocketManager from "../js/Websocket.js";
import { getCookie, SetCookie } from "../js/tools.js";
import { messageHandling } from "../js/utils.js";
export default class extends AbstractView {
    constructor() {
        super();

        this.setTitle("Logout");
    }
    
    async searchHandle()
    {

    }      

    async getSidebar(){
        return ``;
    }
    async getHtml() {
        return `
    
    <div class="container-lander">
        <header class="h-colx">
            <div class="hser">
                <div class="logo-colx">
                    <img src="static/images/Untitled.png" alt="Logo">
                </div>
                <nav>
                    <ul>
                        <li><a href="#welcome">Home</a></li>
                        <li><a href="#features">Features</a></li>
                        <li><a href="#get-started">Get Started</a></li>
                    </ul>
                </nav>
                <div class="auth-buttons ">
                <a href="/login" data-link=""><button>Login</button></a>
               </div>
            </div>
        </header>

        <main class="content-lander">
            <div class="lander">
                <section class="hero-leader scroll-animate">
                    <div class="floating-paddle left"></div>
                    <div class="floating-paddle right"></div>
                    <div class="hero-content-leader">
                        <h1 class="fade-in-up">Welcome to the Ultimate Ping Pong Game!</h1>
                        <p class="fade-in-up delay-1">Experience the thrill of table tennis like never before.</p>
                    </div>
                </section>
                <img src="static/images/aad.png" alt="Ping Pong Player">
            </div>

            <section id="welcome" class="section">
                <div class="content-box">
                    <p>Are you ready to test your reflexes and skills in the fast-paced world of ping pong? Whether you're a beginner or a seasoned player, our game offers endless fun and challenge. Play solo against AI or compete with your friends in exciting multiplayer matches. With intuitive controls, customizable difficulty levels, and dynamic gameplay, every match will keep you on the edge of your seat!</p>
                    <img src="static/images/tour.png"  alt="Ping Pong Gameplay" class="floating-image">
                </div>
            </section>

            <div class="image-marquee">
                <div class="anime-name">
                    <h1>🏓</h1>
                    <h1>Ping Pong Game!</h1>
                    <h1>🏓</h1>
                    <h1>Ping Pong Game!</h1>
                    <h1>🏓</h1>
                    <h1>Ping Pong Game!</h1>
                    <h1>🏓</h1>
                    <h1>Ping Pong Game!</h1>
                </div>
            </div>

            <section id="features" class="section">
                <div class="content-box">
                    <h2>Game Features</h2>
                    <ul class="feature-list">
                        <li>Single-Player & Multiplayer Modes</li>
                        <li>Adjustable Difficulty Settings</li>
                        <li>Engaging Animations & Fun Power-Ups</li>
                        <li>Realistic Table Tennis Physics</li>
                    </ul>
                </div>
               
            </section>

            <section id="get-started" class="section">
                <div class="content-box">
                    <h2>Get Started</h2>
                    <p>Click below to dive into the action and experience the thrill of ping pong right at your fingertips. Get ready to serve, rally, and dominate the table!</p>
                    <a data-link href="/login" class="cta-button">Start Playing Now</a>
                </div>
            </section>
        </main>
    </div>
    `;
    }

    async inAuthpages(){
        return true;
      
    }

    async logOutHandel(){

        const access_token = getCookie("access_token");
        if(!access_token) return;
        try {
            const response = await fetch('/api/logout/', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${access_token}`
                },
            })
            if (response.ok) {
                SetCookie('access_token',null);
                WebSocketManager.closeAllSockets();
            }
        } catch (error) 
        {
            messageHandling("error",error);
        }
    }
    async afterRender(){
        await this.logOutHandel();
    }
}
