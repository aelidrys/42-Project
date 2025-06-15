import { Point, Rectangle } from "./shapes.js";

export class Player extends Rectangle {
    constructor(consts, side, info) {
        let arr = [];
        for (let index = 0; index < 4; index++) {
            let pt = new Point(0, 0);
            arr.push(pt);
        }
        const midle        = consts.board_heigth / 2;
        const playerHeigth  = consts.player_h;
        const playerWidth   = consts.player_w;
        const tmp     = consts.distense_between_player_and_wall_in_percent;
        const distpwall = 700 * (tmp / 100);
        arr[0].y = arr[1].y = midle - (playerHeigth / 2);
        arr[2].y = arr[3].y = midle + (playerHeigth / 2);
        if (side == 0) {
            arr[0].x = arr[2].x = distpwall;
            arr[1].x = arr[3].x = distpwall + playerWidth;
        }
        else {
            arr[0].x = arr[2].x =  consts.board_width - (distpwall + playerWidth);
            arr[1].x = arr[3].x =  consts.board_width - distpwall;
        }
        //member attributes
        super(arr[0], arr[1], arr[2], arr[3]);
        this.playername = info.name;
        this.playerimg  = info.image;
        this.plyerscor = 0;
        this.side = side;

        this.toplimit = 0;
        this.botlimit = consts.board_heigth;
    }
    
    

    moveUp(speed)
    {
        const current_position = this.getPoint(0).y;
        let crossdist = Math.max(current_position - speed, this.toplimit);
        const newspeed = Math.abs(crossdist - current_position);
        this.move([0, -newspeed]);
    }

    moveDown(speed)
    {
        const current_position = this.getPoint(2).y;
        let crossdist = Math.min(current_position + speed, this.botlimit);
        const newspeed = Math.abs(crossdist - current_position);
        this.move([0, newspeed]);
    }
}