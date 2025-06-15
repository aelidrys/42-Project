import { consts2, game_view , controlls1text, controlls2text} from "./game_view.js";
import { DiplayManager2 } from "./display_manager.js";
import { Point, Rectangle } from "./shapes.js";
import { Player } from "./Player.js";


class Ball extends Point
{
    constructor(consts) {
        let x = consts.board_width / 2;
        let y = consts.board_heigth / 2;
        super(x, y);
        this.r = consts.ball_size / 2;
        this.dir = [0,0];
    }

    moveBall(){
        this.translate(this.dir);
    }
    clone() {
        // Create a new instance of Ball with the same properties
        const clone = new Ball({
            board_width: this.x * 2,  // Passing board_width as a parameter
            board_height: this.y * 2, // Passing board_height as a parameter
            ball_size: this.r * 2      // Passing ball_size as a parameter
        });

        // Copy the Ball-specific properties
        clone.dir = [...this.dir]; // Create a new array for dir to avoid reference issues
        clone.x = this.x;
        clone.y = this.y;
        clone.r = this.r;
            
        return clone;
    }
    
};

export class Game2
{
    constructor(consts, player_info, ws, is_turn=false){
        this.printer = new DiplayManager2(consts);
        this.consts = consts;
        this.is_turn = is_turn;
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
            "wh1"       :   null,
            "wh2"       :   null,
        }
        this.player_info = player_info;
        this.p1 = new Player(consts, 0, player_info.p1);
        this.p2 = new Player(consts, 1, player_info.p2);
        this.ball = new Ball(consts);
        this.MvObj = {
            "p1up"  : false,
            "p1down": false,
            "p2up"  : false,
            "p2down": false,
            "p1aim" : {"x": 0, "y": 0},
            "p2aim" : {"x": 0, "y": 0},
        };
        this.ft_event = {
            "keyevetUp" : null,
            "keyevetDown" : null,
            "mouseDown" : null,
        }
        this.ft_aim = null;
        this.sendOnline = null;
        this.onlinemsg = {};
        this.ws = ws;
        this.resizebind = null;
        this.runing = true;
        this.goals = [0,0];
        this.goalOrder = "";

    }

    readDom(dom){
        dom.Board       = document.getElementById('board');
        dom.ball        = document.getElementById('ball');
        dom.p1          = document.getElementById('playerLeft');
        dom.p2          = document.getElementById('playerRigth');
        dom.p1name      = document.querySelector(".p1name");
        dom.p2name      = document.querySelector(".p2name");
        dom.p1holder    = document.querySelector(".pimg1");
        dom.p2holder    = document.querySelector(".pimg2");
        dom.roundCout   = document.getElementById("roundCout");
        dom.overlay     = document.getElementById("overlay") ;
        dom.wh1         = document.getElementById('wh1');
        dom.wh2         = document.getElementById('wh2');
        dom.counter     = document.querySelector('.counet');
        dom.controltext1 = document.getElementById('controlls1');
        dom.controltext2 = document.getElementById('controlls2');
    }

    windowResize(){
        this.printer.onResize(this.dom);
    }
    
    display()
    {

        const newDiv = document.createElement('div');
        newDiv.id = 'myUniqueDiv';
        document.body.appendChild(newDiv);
        newDiv.innerHTML = game_view;

        this.readDom(this.dom);
        document.querySelector(".freez-all").style.display = "";
        

        //to change
        this.dom.p1name.textContent = this.p1.playername;
        this.dom.p2name.textContent = this.p2.playername;
        this.dom.p1holder.src = this.p1.playerimg;
        this.dom.p2holder.src = this.p2.playerimg;
        //resize loop

        if (this.ws == null)
        {
            this.dom.controltext1.innerHTML = controlls1text;
            this.dom.controltext2.innerHTML = controlls2text;
        }
        else{
            this.dom.controltext1.innerHTML = controlls2text;
        }
        this.printer.displayPlayers(
                this.p1, this.dom.p1,
                this.p2, this.dom.p2
            );

        this.resizebind = this.printer.fixfontsize.bind(null, this.dom);
        window.addEventListener('resize', this.resizebind);
        this.printer.fixfontsize(this.dom);

        // this.beforReload = window.addEventListener()
    }

    async countdown()
    {
        for (let i = 3; i > 0; i--)
        {
            this.dom.counter.textContent = i;
            if (this.sendOnline != null && this.ws != null)
            {
                this.setonline_msg(i.toString(), true);
                this.sendOnline(this.onlinemsg, this.ws);
            }
            await new Promise(r => setTimeout(r, 1000));
        }
    }

    allowMove()
    {
        if (this.ft_event.keyevetDown != null)
            document.addEventListener('keydown',this.ft_event.keyevetDown);
        if (this.ft_event.keyevetUp != null)
            document.addEventListener('keyup', this.ft_event.keyevetUp);
        if (this.ft_event.mouseDown != null)
            this.dom.Board.addEventListener('mousedown', this.ft_event.mouseDown);  
    
    }

    stopMove(){

        if (this.ft_event.keyevetDown != null)
            document.removeEventListener('keydown', this.ft_event.keyevetDown);
        if (this.ft_event.keyevetUp != null)
            document.removeEventListener('keyup', this.ft_event.keyevetUp);
        if ( this.ft_event.mouseDown != null)
            document.removeEventListener('mousedown', this.ft_event.mouseDown);
    }

    async resetRound()
    {
        this.stopMove();
        
        this.MvObj.p1up    = false;
        this.MvObj.p1down  = false
        this.MvObj.p2up    = false
        this.MvObj.p2down  = false;
        this.MvObj.p1aim.x = this.MvObj.p1aim.y = 0;
        this.MvObj.p2aim.x = this.MvObj.p2aim.y = 0;

        this.p1 = new Player(this.consts, 0, this.player_info.p1);
        this.p2 = new Player(this.consts, 1, this.player_info.p2);
        this.ball = new Ball(this.consts);

        this.dom.p1.style.display = 'none';
        this.dom.p2.style.display = 'none';
        this.dom.ball.style.display   = 'none';


        this.dom.controltext1.style.display = 'none';
        this.dom.controltext2.style.display = 'none';

        this.dom.overlay.style.display = 'flex';
        this.dom.counter.style.fontSize = this.dom.Board.clientWidth * 0.2 + 'px';

        this.dom.wh1.innerHTML = this.goals[0];
        this.dom.wh2.innerHTML = this.goals[1];
        this.dom.roundCout.innerHTML = this.goals[0] + this.goals[1];

        await this.countdown();
        this.dom.controltext1.style.display = 'flex';
        this.dom.controltext2.style.display = 'flex';

        this.dom.p1.style.display = 'inline';
        this.dom.p2.style.display = 'inline';
        this.dom.ball.style.display   = 'inline';
        this.dom.counter.textContent = '';
        this.dom.overlay.style.display = 'none';
        this.allowMove();

    }

    isBetween(num1, num2, num3) {
        return (num3 > Math.min(num1, num2)) && (num3 < Math.max(num1, num2));
    }
    movePlayers(){
        let point1 = null;
        let point2 = null;
        if (this.MvObj.p1up)
            point1 = this.p1.moveUp(this.consts.player_spreed);
        if (this.MvObj.p1down)
            point1 = this.p1.moveDown(this.consts.player_spreed);
        if (this.MvObj.p2up)
            point2 = this.p2.moveUp(this.consts.player_spreed);
        if (this.MvObj.p2down)
            point2 = this.p2.moveDown(this.consts.player_spreed);
        
        //print function
        this.printer.displayPlayers(
            this.p1, this.dom.p1,
            this.p2, this.dom.p2
        ); 

    }

    moveBall()
    {
        let oldx = this.ball.x;
        this.ball.moveBall();
        let newx = this.ball.x;

        const boardcord = [
            0 + this.ball.r,//x0
            0 + this.ball.r,//y0
            700 - this.ball.r,//x3
            500 - this.ball.r//y3
        ];

        const p1 = new Point(this.ball.x, this.ball.y);
        const p2 = new Point(
            this.ball.x - this.ball.dir[0],
            this.ball.y - this.ball.dir[1]
            );
        
        const slop = (p2.y - p1.y) / (p2.x - p1.x);
        const b = p1.y - slop * p1.x;
        let res = 0;
        if (this.ball.x >= boardcord[2])
        {
            this.ball.x = boardcord[2];
            this.ball.y = slop * this.ball.x + b;
            this.ball.dir[0] *= -1;
            res = 1; 
        }
        if (this.ball.x <= boardcord[0])
        {
            this.ball.x = boardcord[0];
            this.ball.y = slop * this.ball.x + b;
            this.ball.dir[0] *= -1;
            res = 2;   
        }
        if (this.ball.y >= boardcord[3])
        {
            this.ball.y = boardcord[3];
            this.ball.x = (this.ball.y - b) / slop;
            this.ball.dir[1] *= -1;
            res = 0;
        }
        if (this.ball.y <= boardcord[1])
        {
            this.ball.y = boardcord[1];
            this.ball.x = (this.ball.y - b) / slop;
            this.ball.dir[1] *= -1;
            res = 0;
        }

        const p1range = this.p1.points[1].x + this.ball.r;
        const p2range = this.p2.points[0].x - this.ball.r;
        if (this.isBetween(oldx, newx, p1range) == true){
            this.ball.x = p1range;
            this.ball.y = slop * this.ball.x + b;
        }
        if (this.isBetween(oldx, newx, p2range) == true){
            this.ball.x = p2range;
            this.ball.y = slop * this.ball.x + b;
        }
        return res; 
    }

    vectorRotation(vec ,angle)
    {
        const rad = angle * (Math.PI / 180);
        const rotationMatrix = [
            [Math.cos(rad), -Math.sin(rad)],
            [Math.sin(rad), Math.cos(rad)]
        ]
        //vector * matrix
        const numRows = rotationMatrix.length;
        const numCols = rotationMatrix[0].length;
        let result = [0,0];
        for (let i = 0; i < numRows; i++) {
            let sum = 0;
            for (let j = 0; j < numCols; j++) {
                sum += rotationMatrix[i][j] * vec[j];
            }
            result[i] = sum;
        }
        return result;
    }

    ballOpner()
    {
        let angle = 0;
        if (Math.random() > 0.5)
            angle = 0;
        else
            angle = 180;

        return this.vectorRotation([this.consts.ballspeed, 0], angle);
    }

    isBallOverlappingRectangle(cx, cy, r, rectanglePoints) {
        // Extract rectangle points
        const [x1, y1, x2, y2, x3, y3, x4, y4] = rectanglePoints;
      
        // Step 1: Calculate the AABB of the rectangle
        const minX = Math.min(x1, x2, x3, x4);
        const maxX = Math.max(x1, x2, x3, x4);
        const minY = Math.min(y1, y2, y3, y4);
        const maxY = Math.max(y1, y2, y3, y4);
      
        // Step 2: Find the closest point on the rectangle to the ball's center
        const closestX = Math.max(minX, Math.min(cx, maxX));
        const closestY = Math.max(minY, Math.min(cy, maxY));
      
        // Step 3: Calculate the distance from the ball's center to the closest point
        const dx = cx - closestX;
        const dy = cy - closestY;
        const distance = Math.sqrt(dx * dx + dy * dy);
      
        // Step 4: Check if the distance is less than or equal to the radius
        return distance <= r;
      }

    Colision()
    {
        const p1range = this.p1.points[1].x + this.ball.r;
        const p2range = this.p2.points[0].x - this.ball.r;
        if (this.ball.dir[0] < 0)
        {
            if (this.ball.x == p1range){
                const p = new Point(this.ball.x - this.ball.r, this.ball.y);
                const minp1 = this.p1.points[0].y - this.ball.r;
                const maxp1 = this.p1.points[3].y + this.ball.r;
                if (this.isBetween(minp1, maxp1, p.y) == true)
                {
                    this.ball.dir = this.ft_aim({
                        "player" : this.p1,
                        "ball"   : this.ball,
                        "MvObj"  : this.MvObj
                    }, 1);
                }
    
            }
            else if(this.isBetween(this.p1.getPoint(0).x - this.ball.r, this.p1.getPoint(1).x + this.ball.r, this.ball.x) == true)
            {   
                if (this.isBetween(this.p1.getPoint(0).y - this.ball.r, this.p1.getPoint(2).y + this.ball.r, this.ball.y))
                {
                    this.ball.dir = this.ft_aim({
                        "player" : this.p1,
                        "ball"   : this.ball,
                        "MvObj"  : this.MvObj
                    }, 1);
                }
            }   
        }
    
        // let bonusval2 = this.p2.getPoint(1).x;
        // let bonusval1 = p2range - this.ball.r;  
        if (this.ball.dir[0] > 0)
        {
            if (this.ball.x == p2range)
            {
                const p = new Point(this.ball.x - this.ball.r, this.ball.y);
                const minp1 = this.p2.points[0].y - this.ball.r;
                const maxp1 = this.p2.points[3].y + this.ball.r;
                if (this.isBetween(minp1, maxp1, p.y) == true)
                {
                    this.ball.dir = this.ft_aim({
                        "player" : this.p2,
                        "ball"   : this.ball,
                        "MvObj"  : this.MvObj
                    }, 2);
                }
            }
            else if(this.isBetween(this.p2.getPoint(0).x + this.ball.r, this.p2.getPoint(1).x + this.ball.r, this.ball.x) == true)
            {
                if (this.isBetween(this.p2.getPoint(0).y + this.ball.r, this.p2.getPoint(2).y + this.ball.r, this.ball.y))
                {
                    this.ball.dir = this.ft_aim({
                        "player" : this.p2,
                        "ball"   : this.ball,
                        "MvObj"  : this.MvObj
                    }, 2);
                }
            }
    
        }    
    }

    endGame(winner)
    {
        this.dom.p1.style.display = 'none';
        this.dom.p2.style.display = 'none';
        this.dom.ball.style.display   = 'none';

        this.dom.overlay.style.display = 'flex';
        this.dom.counter.style.fontSize = this.dom.Board.clientWidth * 0.2 + 'px';

        this.dom.wh1.innerHTML = this.goals[0];
        this.dom.wh2.innerHTML = this.goals[1];
        this.dom.roundCout.innerHTML = this.goals[0] + this.goals[1];
        if (this.ws != null)
        {

            this.setonline_msg("", true);
            this.sendOnline(this.onlinemsg, this.ws);
            this.ws.send(JSON.stringify({
                'subject' : 'end',
                'winer' : winner,
                "p1score" : this.goals[0],
                "p2score" : this.goals[1],
                "order"   : this.goalOrder
            }));
        }
        else
        {
            if (this.runing == false)
            {
                return null;
            }
            this.end(winner)
        }

    }

    setonline_msg(counter_text, overlay)
    {
        this.onlinemsg = {
            "subject" : 'update',
            "p1x": this.p1.points[0].x,
            "p1y": this.p1.points[0].y,
            "p2x": this.p2.points[0].x,
            "p2y": this.p2.points[0].y,
            
            "p1score" : this.goals[0],
            "p2score" : this.goals[1],

            "ballx": this.ball.x,
            "bally": this.ball.y,

            "counter" : counter_text,
            "view"    : overlay,
            "round"   : this.goals[0] + this.goals[1]
        }
    }

    async gameloop(ft_mv)
    {
        
        try{
            // Window.addEventListener('beforeunload',e => (this.beforReloadevent(e)));
            this.ft_aim = ft_mv.keyaimfuction;
            this.sendOnline = ft_mv.ft_online;
            if (ft_mv.keydown != null)
                this.ft_event.keyevetDown = ft_mv.keydown.bind(null, this.MvObj);
            if (ft_mv.keyup != null)
                this.ft_event.keyevetUp = ft_mv.keyup.bind(null, this.MvObj);
            if (ft_mv.mouseDown != null)
                this.ft_event.mouseDown = ft_mv.mouseDown.bind(null, this.MvObj, this.dom.Board, this.consts);
                
            let rounds = 0;
            this.goals = [0, 0];
            while (this.goals[0] < 5 && this.goals[1] < 5)
            {
                if (this.runing == false)
                {
                    return null;
                }
                await this.resetRound();
                this.ball.dir = this.ballOpner();
                let i = 0;
                let stat = 0;
                while(true)
                {
                    if (this.runing == false)
                    {
                        return null;
                    }
                    this.movePlayers();
                    
                    stat =  this.moveBall();
                    if (stat == 0)
                    {
                        this.Colision();
                    }
                    else
                    {  
                        this.goals[stat - 1]++;
                        this.goalOrder += stat.toString();
                        break;
                    }
                    this.printer.displayBall(this.ball.x, this.ball.y, this.dom.ball);
                    if (this.sendOnline && this.ws)
                    {
                        this.setonline_msg("", false);
                        this.sendOnline(this.onlinemsg, this.ws);
                    }
                    await new Promise(r => setTimeout(r, 30));
                    // console.log('running '+ this.player_info.p1.name + " " +this.runing);
                }
                if (this.runing == false)
                {
                    return null;
                }
            }

            if (this.goals[0] == 5)
            {
                this.endGame(1);

                return {
                        'winer' : 1,
                        'p1score' : this.goals[0],
                        'p2score' : this.goals[1]
                    };
            }
            else
            {
                this.endGame(2);
                return {
                    'winer' : 2,
                    'p1score' : this.goals[0],
                    'p2score' : this.goals[1]
                };
            }
        }
        catch(err)
        {
        // console.log('loop interupted reason ' + err);
            return {
                'winer' : 1,
                'p1score' : 5,
                'p2score' : 0
            };
        }
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
        this.removeKeys();
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

        if (this.ws != null)
        {
            this.dom.counter.innerHTML = `You win!!`;;
            if (winner == 2)
                this.dom.counter.innerHTML = `You lose!!`;    
        }
        else
        {
            let winname = winner == 1 ? this.dom.p1name.textContent : this.dom.p2name.textContent;
            this.dom.counter.innerHTML = `${winname} win!!`;
        }
        this.dom.counter.style.fontSize   = (this.dom.Board.clientWidth * 0.07) + 'px';
    }

    removeKeys()
    {
        if (this.ft_event.keyevetDown != null)
            document.removeEventListener('keydown',this.ft_event.keyevetDown);
        if (this.ft_event.keyevetUp != null)
            document.removeEventListener('keyup', this.ft_event.keyevetUp);
        if (this.ft_event.mouseDown != null)
            this.dom.Board.removeEventListener('mousedown', this.ft_event.mouseDown);  
    }
    // let msg = {
    //     'subject' : 'update',
    //     'event': 'Keyup',
    //     'key'    : 'up'
    //   };
    update(msg)
    {
        let boolval = false;
        if (msg.event == 'Keyup')
            boolval = false;
        if (msg.event == 'Keydown')
            boolval = true;

        if (msg.key == 'up')
            this.MvObj.p2up = boolval;
        if (msg.key == 'down')
            this.MvObj.p2down = boolval;
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
        this.dom = null

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
}