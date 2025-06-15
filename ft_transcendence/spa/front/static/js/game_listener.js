import { consts2, game_view , controlls1text, controlls2text} from "./game_view.js";
import { DiplayManager2 } from "./display_manager.js";

export class Game_listner
{
    constructor(consts, player_info, ws)
    {
        this.printer = new DiplayManager2(consts);
        this.consts = consts;
        this.player_info = player_info;
        this.dom = {
            "Board"     : null,
            "ball"      : null,
            "p1"        : null,
            "p2"        : null,
            "p1name"    : null,
            "p2name"    : null,
            "p1holder"  : null,
            "p2holder"  : null,
            "roundCout" : null,
            "overlay"   : null,
            "counter"   : null,
            "wh1"       : null,
            "wh2"       : null,
        }
        this.ws = ws;
        this.event_up = null;
        this.event_down = null;
        this.event_aim = null;
        this.resizebind = null;
        this.runing = true;
    }

    readDom(){
        this.dom.Board       = document.getElementById('board');
        this.dom.ball        = document.getElementById('ball');
        this.dom.p1          = document.getElementById('playerLeft');
        this.dom.p2          = document.getElementById('playerRigth');
        this.dom.p1name      = document.querySelector(".p1name");
        this.dom.p2name      = document.querySelector(".p2name");
        this.dom.p1holder    = document.querySelector(".pimg1");
        this.dom.p2holder    = document.querySelector(".pimg2");
        this.dom.roundCout   = document.getElementById("roundCout");
        this.dom.overlay     = document.getElementById("overlay") ;
        this.dom.wh1         = document.getElementById('wh1');
        this.dom.wh2         = document.getElementById('wh2');
        this.dom.counter     = document.querySelector('.counet');
        this.dom.controltext1 = document.getElementById('controlls1');
        this.dom.controltext2 = document.getElementById('controlls2');

    }

    setkeys(ft_mv)
    {
        this.event_up = ft_mv.up.bind(null, this.ws)
        this.event_down = ft_mv.down.bind(null, this.ws)  
        this.event_aim = ft_mv.aim.bind(
                null, this.ws, this.dom.Board,
                    {
                        'x': this.consts.board_width,
                        'y': this.consts.board_heigth
                    }
            );

        document.addEventListener('keyup', this.event_up);
        document.addEventListener('keydown', this.event_down);
        document.addEventListener('mousedown', this.event_aim);
    }

    removeKeys()
    {
        document.removeEventListener('keyup', this.event_up);
        document.removeEventListener('keydown', this.event_down);
        document.removeEventListener('mousedown', this.event_aim);
    }


    display()
    {
        const newDiv = document.createElement('div');
        newDiv.id = 'myUniqueDiv';
        document.body.appendChild(newDiv);
        newDiv.innerHTML = game_view;

        this.readDom();
        document.querySelector(".freez-all").style.display = "";
        
        //to change
        this.dom.p1name.textContent = this.player_info.p1.name;
        this.dom.p2name.textContent = this.player_info.p2.name;
        this.dom.p1holder.src = this.player_info.p1.image;
        this.dom.p2holder.src = this.player_info.p2.image;
        
        const midle        = this.consts.board_heigth / 2;
        const playerHeigth  = this.consts.player_h;
        const playerWidth   = this.consts.player_w;
        const tmp           = this.consts.distense_between_player_and_wall_in_percent;
        const distpwall = 700 * (tmp / 100);

        this.dom.controltext2.innerHTML = controlls2text;
        
        this.resizebind = this.printer.fixfontsize.bind(null, this.dom);
        window.addEventListener('resize', this.resizebind);
        this.printer.fixfontsize(this.dom);            
    }

    createEvents(ft_mv)
    {

    }

    readysignal()
    {
        try {
            this.ws.send(
                JSON.stringify({
                    'subject' : 'ready'
                })
            );
        } catch (e){
            while (true){
                if (this.ws.readyState === WebSocket.OPEN)
                {
                    this.ws.send(
                        JSON.stringify({
                            'subject' : 'ready'
                        })
                    );
                    break;
                }
                else {
                    // console.log('socker not ready')
                }
            }
        }
    }

    update(msg)
    {
        // { Sender meg
        //     view = true,
        //     counter = "bigmidletext",
        //     round = 0,
        //     p1score = 0
        //     p2score = 0,

        //     p1x = 20
        //     p1y = 135
        //     p2x = 213
        //     p2y = 46

        //     ballx = 123
        //     bally = 56

        // }
        if (msg.view == true)
        {
            this.dom.overlay.style.display = 'flex';
            this.dom.p1.style.display = 'none';
            this.dom.p2.style.display = 'none';
            this.dom.ball.style.display   = 'none';
            this.dom.controltext1.style.display = 'none';
            this.dom.controltext2.style.display = 'none';

        }
        else
        {
            this.dom.overlay.style.display = 'none';
            this.dom.p1.style.display = 'inline';
            this.dom.p2.style.display = 'inline';
            this.dom.ball.style.display   = 'inline';
            this.dom.controltext1.style.display = 'flex';
            this.dom.controltext2.style.display = 'flex';
        }
        this.dom.counter.innerHTML = msg.counter;
        this.dom.roundCout.innerHTML = msg.round;
        this.dom.wh1.innerHTML = msg.p1score;
        this.dom.wh2.innerHTML = msg.p2score;

        this.printer.displayPoint(this.dom.p1, msg.p1x, msg.p1y);
        this.printer.displayPoint(this.dom.p2, msg.p2x, msg.p2y);
        this.printer.displayPoint(this.dom.ball, msg.ballx, msg.bally);
    }

    ayoubFuntionDelete()
    {
        this.removeKeys();
        window.removeEventListener('resize', this.resizebind);
        var btn = document.getElementById("game_buttun");
        document.querySelector(".freez-all").style.display = "none";
        let divToRemove = document.getElementById('myUniqueDiv');
        if (divToRemove) {
            divToRemove.parentNode.removeChild(divToRemove);
        }

    }

    end(winner)
    {
        this.dom.counter.innerHTML = `You win!!`;;
        if (winner == 1)
            this.dom.counter.innerHTML = `You lose!!`;
    
        this.dom.counter.style.fontSize   = (this.dom.Board.clientWidth * 0.07) + 'px';

        this.removeKeys();
        this.dom.overlay.style.display = 'flex';
        setTimeout((event) => {

            if (this.runing == false)
            {
                return null;
            }
            window.removeEventListener('resize', this.resizebind);
            var btn = document.getElementById("game_buttun");
            document.querySelector(".freez-all").style.display = "none";
            let divToRemove = document.getElementById('myUniqueDiv');
            if (divToRemove) {
                divToRemove.parentNode.removeChild(divToRemove);
            }
            
        }, 2000);
    }

    surrender(side)
    {
        this.removeKeys();
        this.dom.overlay.style.display = 'flex';
        this.dom.wh1.innerHTML = side == 1 ? 5 : 0;
        this.dom.wh2.innerHTML = side == 2 ? 5 : 0;
        // this.dom.counter.style.fontSize = this.consts.ball_size * 1.5 + 'px';
        this.dom.counter.innerHTML = 'opponent left';
        this.dom.counter.style.fontSize   = (this.dom.Board.clientWidth * 0.07)+'px';


        setTimeout((event) => {
            window.removeEventListener('resize', this.resizebind);
            var btn = document.getElementById("game_buttun");
            document.querySelector(".freez-all").style.display = "none";
            let divToRemove = document.getElementById('myUniqueDiv');
            if (divToRemove) {
                divToRemove.parentNode.removeChild(divToRemove);
            }
        }, 2000);
    }

}