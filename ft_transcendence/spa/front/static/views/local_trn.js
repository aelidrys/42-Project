import {Game2} from '../js/game.js'
import { consts2 } from "../js/game_view.js";
import { navigateTo } from '../js/index.js';

import {Offline_movment_keyup, Offline_movment_keydown, Offline_aim} from '../js/offline.js'
import { messageHandling } from '../js/utils.js';
let g = null

let cancel_Ltrn = true;

export function f_cancel_Ltrn(){
    // console.log('----------- cancel_local_trn = ', cancel_Ltrn)
    if (cancel_Ltrn)
        return
    cancel_Ltrn = true
    if (g)
    {
        g.runing = false;
        // console.log('stop' + g.runing);
        g.ayoubFuntionDelete();
    }
    g = null
    // console.log('----------- g = ',g,'-------')
}

class Matche {
    p1_name = '';
    p1_score = 0;
    
    p2_name = '';
    p2_score = 0;

    winner = '';
    status = 'unplayed';
    round = 'half';
}



export class Local_trn  {
    m1 = new Matche();
    m2 = new Matche();
    mf = new Matche();
    rejester(){
        return `
        <form class='rejister_trn'>
            <input class='plyr_name' name='p1_name' value="Player1" maxlength="10">
            <input class='plyr_name' name='p2_name' value="Player2" maxlength="10">
            <input class='plyr_name' name='p3_name' value="Player3" maxlength="10">
            <input class='plyr_name' name='p4_name' value="Player4" maxlength="10">
            <input type='submit' class='trn_strt' id='start_trn' value="Start">
            <div class='error-message'>
            </div>
        </form>`;
    };


    escapeHTML(str) {
        return str.replace(/&/g, "&amp;")
                  .replace(/</g, "&lt;")
                  .replace(/>/g, "&gt;")
                  .replace(/"/g, "&quot;")
                  .replace(/'/g, "&#39;");  
    }

    trn_start(event){
        event.preventDefault();
        
        const formdata = new FormData(event.target);
        const data = Object.fromEntries(formdata.entries());
        this.m1.p1_name = data.p1_name;
        this.m1.p2_name = data.p2_name;
        this.m1.round = 'm1';
        this.m2.p1_name = data.p3_name;
        this.m2.p2_name = data.p4_name;
        this.m2.round = 'm2';
        let regex = /[^a-zA-Z0-9_-]/

        const set = new Set();
        for (const value of Object.values(data)){
            if (value.trim() == ''){
                messageHandling("error","name is empty. Please fill it.");
                return;
            }
            if (value.match(regex)){
                messageHandling("error","name '" + this.escapeHTML(value) + "' is not valid. Please correct it.");
                return;
            }
            set.add(value.trim());
        }
        if (set.size < 4)
            messageHandling("error","duplicates names. Please correct them.");
        else {
            var l_trn = document.getElementById('trn');
            if (l_trn){
                l_trn.innerHTML = this.generateMatcheHtml(this.m1, 'm1');
                l_trn.innerHTML += this.generateMatcheHtml(this.m2, 'm2');
            }
            this.add_ev_listner(this.m1, 'm1');
            this.add_ev_listner(this.m2, 'm2');
        }
    };
    add_ev_listner(matche, id){
        var elem = document.getElementById(id);
        if (elem)
            elem.addEventListener('click', this.start_matche.bind(this, matche));
    }
    
    start_matche(matche){
        cancel_Ltrn = false
        g = new Game2(
            consts2,
            {
                'p1':{
                    'name' : matche.p1_name,
                    'image' : 'media/loin.jpg',
                },
                'p2':{
                    'name' : matche.p2_name,
                    'image' : 'media/tiger.jpg',
                },
            },
            null,
            true,
        );
        g.display();
        const promise = g.gameloop(
            {
                "keyup"   : Offline_movment_keyup,
                "keydown" : Offline_movment_keydown,
                "keyaimfuction" : Offline_aim,
                "mouseDown"     : null,
                "ft_online"     : null,
            }
        );
        promise.then((data) =>{
            // console.log('----------- promise enter ------ cancel_Ltrn: ', cancel_Ltrn)
            if (g)
                g.runing = false;
            if (!cancel_Ltrn){
                cancel_Ltrn = false
                matche.status = 'played';
                matche.p1_score = data.p1score;
                matche.p2_score = data.p2score;
                matche.winner = matche.p2_name;
                if (data.winer == 1)
                    matche.winner = matche.p1_name;
                setTimeout( async () => {
                    if (g){
                        g.ayoubFuntionDelete();
                        g = null
                    }
                    this.next_matche();
                }, 2000);
            } 
        }).catch(error => {
            // console.log('ERROR', error)
            g = null
        })
        var l_trn = document.getElementById('trn');
        if (l_trn)
            l_trn.innerHTML = ''
    }

    next_matche(){
        
        var l_trn = document.getElementById('trn');
        if (l_trn == null)
            return;
        if (this.m1.status == 'unplayed'){
            l_trn.innerHTML = this.generateMatcheHtml(this.m1, 'm1');
            this.add_ev_listner(this.m1, 'm1');
            return;
        }
        if (this.m2.status == 'unplayed'){
            l_trn.innerHTML = this.generateMatcheHtml(this.m2, 'm2');
            this.add_ev_listner(this.m2, 'm2');
            return;
        }
        if (this.mf.status == 'played'){
            this.show_trn_history();
            return;
        }
        this.mf.p1_name = this.m1.winner;
        this.mf.p2_name = this.m2.winner;
        this.mf.round = 'final';
        l_trn.innerHTML = this.generateMatcheHtml(this.mf, 'm3');
        this.add_ev_listner(this.mf, 'm3');
    }

    generateMatcheHtml(matche, id){
        return `
        <div class="l-matche">
            <div class='l-plyr l-plyr-right m-r l-p'>
                ${matche.p1_name}
            </div>
            <div class='lm_vs'>
                VS
                <div class='strt-mtche' id='${id}'>
                    Play
                </div>
            </div>
            <div class='l-plyr l-plyr-left  m-l m-r r-p'>
                ${matche.p2_name}
            </div>
           
        </div>
        `;
    }

    show_trn_history(){
        var content = `
        <div class="child-col m-r">
            <div class="plyr-box">
                <span class='text'> ${this.m1.p1_name}</span>
                <div class="score1">${this.m1.p1_score}</div>
            </div>
            <div class="plyr-box">
                <span class='text'> ${this.m1.p2_name}</span>
                <div class="score1">${this.m1.p2_score}</div>
            </div>
        <div class='vid'></div>
            <div class="plyr-box">
                <span class='text'> ${this.m2.p1_name}</span>
                <div class="score1">${this.m2.p1_score}</div>
            </div>
            <div class="plyr-box">
                <span class='text'> ${this.m2.p2_name}</span>
                <div class="score1">${this.m2.p2_score}</div>
            </div>
        </div>
        <div class="child-col m-l">
            <div class="plyr-box">
            <span class='text'> ${this.mf.p1_name}</span>
            <div class="score1">${this.mf.p1_score}</div>
            </div>
            <div class="plyr-box">
            <span class='text'> ${this.mf.p2_name}</span>
            <div class="score1">${this.mf.p2_score}</div>
            </div>
        </div>
        `;
        content = `
        <div class="local-trn-result" style="grid">
        ${content}
        </div>
        <div class="trnBack_div">
            <a class="back_toTrn-bottun" data-link href="/tournament"> Back to Tournamnt</a>
        </div>
        `; 
        var trn = document.getElementById('trn')
        if (trn)
            trn.innerHTML = content;
    }
};