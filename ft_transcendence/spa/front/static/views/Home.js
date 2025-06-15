import AbstractView from "../js/AbstractView.js";
import { CheckTokenExpire } from "../js/tools.js";
export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("Home");
    this.pageTitle = "HOME";
  }

  async getHtml() {
    const headernav = await this.getHeader();
    return (
      headernav +
      `  
      <div class="content_index flex-grow-1 p-3">
      <div class="wrapper d-grid  gap-2">
        <div class=" d-flex align-items-center justify-content-between box2 rounded-5 ">
        <img src="static/images/droitvs.png" alt="">
          <div class="ktab text-center  m-2">
            <h3>Pingpong</h3>
            <p class="text-wlc  m-3">W</p>
          </div>
          <img src="static/images/qauchevs.png" alt="">
        </div>
        <div class=" d-flex align-items-end  justify-content-between  box1 rounded-5"> 
          <img src="static/images/file-12.png" alt="">
          <div class="ktab-box-1 ">
             <p class="text-box-3 ">Ready to play?</p>
            <p class="text-home m-3">Join a quick match to test your skills against other players. Dive into the game, challenge yourself, and enjoy the action right away!</p>
            <div class="play-now">
            <a data-link class="text-center  btn btn-box-3" href="/games"><i class="fa-solid fa-play"></i>
                <span>Play</span></a>
              </div>
          </div>
        </div>
        <div class=" d-flex align-items-end justify-content-between box3 rounded-5"> 
          <div class="ktab-box-3">
            <p class=" text-box-1 ">Compete for the ultimate title!</p>
            <p class="text-home m-3">Join our tournaments to face off against top players and rise through the ranks. Each tournament offers exciting rewards and a chance to showcase your skills. Prepare yourself for intense, competitive matches!</p>
          <div class="play-now" >
          <a data-link  class="text-center btn btn-box  " href="/tournament"><span>Join</span></a></div>
          </div>
          <img src="static/images/file-11.png" alt="" >
          </div>
      </div>
      </div>
      `
    );
  }
  async afterRender() {
    CheckTokenExpire(this.payload.exp);
    this.textWriter(
      ".text-wlc",
      "elcome to the pingpong world come join us for a game!"
    );

  }
  async textWriter(element, txt) {
    const textwr = document.querySelector(element);
    if (!textwr) return;
    for (let index = 0; index < txt.length; index++) {
      setTimeout(() => {
        textwr.innerHTML += txt[index];
      }, 50 * index);
    }
  }
}
