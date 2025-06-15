import {Game2} from './game.js'
import { consts2, game_view } from "./game_view.js";

export var is_offline_running = false;
export var offlinegame = null;

export function remove_offgame_belong(){
    if (offlinegame)
    {
        offlinegame.runing = false;
        offlinegame.ayoubFuntionDelete();

        offlinegame = null;
        is_offline_running = false;
    }
  }


export function offline_game(img, event){
    offlinegame = new Game2(
        consts2,
        {
            'p1':{
                'name' : 'player1',
                'image' : img,
            },
            'p2':{
                'name' : 'player2',
                'image' : img,
            },
        },
        null
    );
    offlinegame.display();
    is_offline_running = true;
    const promise = offlinegame.gameloop(
        {
            "keyup"   : Offline_movment_keyup,
            "keydown" : Offline_movment_keydown,
            "keyaimfuction" : Offline_aim,
            "mouseDown"     : null,
            "ft_online"     : null,
        }
    );
    
    promise.then((data) =>{
        setTimeout((e)=>{
            if (offlinegame){
                offlinegame.ayoubFuntionDelete();
                is_offline_running = false;
                offlinegame = null;
            }
        }, 2100);

    })
    .catch((error) => {
        // console.log(`error => ${error}`);
        is_offline_running = false
        offlinegame = null;
    });
}


//offline aime
export function Offline_aim(obj, side)
{
    let vec = [];
    let p = null;
    if (side == 1)
    {
        vec = [this.consts.ballspeed, 0];
        p = {
                "up"    : obj.MvObj.p1up,
                "down"  : obj.MvObj.p1down,
            }
    }
    if (side == 2)
    {
        vec = [-this.consts.ballspeed, 0];
        p = {
            "up"    : obj.MvObj.p2up,
            "down"  : obj.MvObj.p2down,
        }
    }
    
    const shooting_angle = 60;
    let range = [];
    if (p.up == true && p.down == false)
        range = [shooting_angle / 3, shooting_angle];
    else if (p.down == true && p.up == false)
        range = [-shooting_angle, -(shooting_angle / 3)];
    else
        range = [-(shooting_angle / 3), shooting_angle / 3];

    let randomAngle = Math.floor(Math.random() * (range[1] - range[0] + 1)) + range[0];
    if(side == 1)
        randomAngle *= -1;
    const rotation = (vec, angle) =>{
            const rad = angle * (Math.PI / 180);
            const rotationMatrix = [
                [Math.cos(rad), -Math.sin(rad)],
                [Math.sin(rad), Math.cos(rad)]
            ]

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

    return rotation(vec, randomAngle);
}

//spetil funtions
export function    Offline_movment_keydown(PlayerStat, event)
{
    if (event.key === 'w' || event.key === 'W')
        PlayerStat.p1up = true;
    else if (event.key === 's' || event.key === 'S')
        PlayerStat.p1down = true;
    else if (event.code === 'ArrowUp')
        PlayerStat.p2up = true;
    else if (event.code === 'ArrowDown')
        PlayerStat.p2down = true;

    if(["Space","ArrowUp","ArrowDown","ArrowLeft","ArrowRight"].indexOf(event.code) > -1) {
        event.preventDefault();
    }
}

export function Offline_movment_keyup(PlayerStat,event)
{
    if (event.key === 'w' || event.key === 'W')
        PlayerStat.p1up = false;
    else if (event.key === 's' || event.key === 'S')
        PlayerStat.p1down = false;
    if (event.code === 'ArrowUp')
        PlayerStat.p2up = false;
    else if (event.key === 'ArrowDown')
        PlayerStat.p2down = false;
}