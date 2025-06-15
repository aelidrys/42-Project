export var consts2 = {
        board_width: 700,
        board_heigth: 500,
        distense_between_player_and_wall_in_percent: 10,
        ballspeed: 10,
        player_spreed: 10,
        ball_size: 500 * 0.03,  // Calculate based on board_height
        player_heigth_in_percent: 10,
        player_width_in_percent: 1,
        player_h : 500 * (10/ 100),//board_heigth * (player_heigth_in_percent/ 100)
        player_w : 700 * (1 / 100),//board_width * (player_width_in_percent / 100)
  };

export var controlls1text = `
        <p>⬆️ : W key</p>
        <p>⬇️ : S key</p>
`

export var controlls2text = `
        <p>⬆️ : arrowUP key</p>
        <p>⬇️ : arrowDown key</p>
`

export  const game_view = `<div id="gamecard">
        <div class = "gameview" id="gameview">
    
        <div id="gameHolder">
            
            <div id="scorePannel">

                <div id="rounddiplayer">
                    <h2>Round</h2>
                    <h1 id="roundCout">0</h1>
                </div>

                <div id="Playerscore1">
                    <div class="containerScore1">
                        <p class="pname p1name">player</p>
                        <p id="wh1" class="score">0</p>
                    </div>
                </div>

                <div id="Playerscore2">
                    <div class="containerScore2">
                        <p id="wh2" class="score">0</p>
                        <p class="pname p2name">player</p>
                    </div>
                </div>

            </div>

            <div id="board">

                <div id="overlay">
                    <p class="counet"></p>
                    <div class="half half1">
                        <div class="corner corner1">
                            <img class="Pimg pimg1" src="https://cdn.intra.42.fr/users/2aaa24c2f68fc8417922ec999682f612/monabid.jpg">
                        </div>
                    </div>

                    <div class="half half2">
                        <div class="corner corner2">
                            <img class="Pimg pimg2" src="https://cdn.intra.42.fr/users/3e7d3dd26c2be1f602ed1d631b17bdbb/mkatfi.JPG">
                        </div>
                    </div>

                </div>

                <div id="controlls1">
                </div>
                <div id="controlls2">
                </div>
                <div id="ball"></div>
                <div id="playerLeft" class="player"></div>
                <div id="midleline"></div>
                <div id="playerRigth" class="player"></div>  
            </div>
        </div>
    </div>
    </div>`
