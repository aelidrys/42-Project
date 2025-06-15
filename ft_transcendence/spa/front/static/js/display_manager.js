export class DiplayManager2
{
    constructor(consts){
        this.defX = consts.board_width;
        this.defY = consts.board_heigth;
    }

    displayBall(ballx, bally, dom){
        let y = (bally / this.defY) * 100;
        let x = (ballx / this.defX) * 100;

        dom.style.top   = y.toString() + '%';
        dom.style.left  = x.toString() + '%';
    }

    displayPlayers(p1, dom1, p2, dom2){ 
        let y = (p1.points[0].y / this.defY) * 100;
        let x = (p1.points[0].x / this.defX) * 100;
        dom1.style.top  = y.toString() + '%';
        dom1.style.left  = x.toString() + '%';

        y = (p2.points[0].y / this.defY) * 100;
        x = (p2.points[0].x / this.defX) * 100;
        dom2.style.top  = y.toString() + '%';
        dom2.style.left  = x.toString() + '%';
    }
    
    displayPoint(dom, x, y)
    {
        let newy = (y / this.defY) * 100;
        let newx = (x / this.defX) * 100;
        dom.style.top  = newy.toString() + '%';
        dom.style.left  = newx.toString() + '%';
    }

    fixfontsize(dom)
    {
        dom.p1name.style.fontSize    = (dom.Board.clientWidth * 0.04) + 'px';
        dom.p2name.style.fontSize    = (dom.Board.clientWidth * 0.04) + 'px'
        if (dom.counter.textContent.length > 1)
            dom.counter.style.fontSize   = (dom.Board.clientWidth * 0.07) + 'px';
        else
            dom.counter.style.fontSize   = (dom.Board.clientWidth * 0.2) + 'px';
        dom.wh1.style.fontSize       = (dom.Board.clientWidth * 0.04) + 'px';
        dom.wh2.style.fontSize       = (dom.Board.clientWidth * 0.04) + 'px';
        dom.roundCout.style.fontSize = (dom.Board.clientWidth * 0.04) + 'px';
        
        dom.controltext1.style.fontSize = (dom.Board.clientWidth * 0.02) + 'px';
        dom.controltext2.style.fontSize = (dom.Board.clientWidth * 0.02) + 'px';
    }
}
