export const chatPageHTML =`     
    
    <div class="  chat-container  position-relative">
      <div class="btn-open-chat-list  position-absolute top-0 start-0">
        <i class="fa-solid fa-rectangle-list"></i>
      </div>
      <div class="contact-chat-box">
          <div class="contact-chat-box-header">
              <div class="chat-search">
                <input type="text" id="filter" placeholder="Search">
                <ul>
                </ul>
              </div>
          </div>
            <div class="online-contact">
            </div>
            <div class="chat-select-box">
              <div class="last-chat"></div>
            </div>


      </div>
        <div class="chat-box">
        </div>
    </div>`;

   export let chatHtml = `
    <div class="chat-box-header">
                    <div class="chat-profile">
                    <h2></h2>
                    <div class="">
                        <img src="images/rem.jpg" alt="">
                    </div>
                     <button type="button" class="btn btn-danger  bg-transparent  m-0 dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown" aria-expanded="false">
                      <span class="visually-hidden">Toggle Dropdown</span>
                        <ul class="dropdown-menu">
                        <li class="profile-from-chat"></li>
                        <li class="block-user-chat"></li>
                        <li class="invite-game-chat"></li>
                        </ul>
                    </div>
                </div>
                <div class="conversation-chat">
                </div>
                <form class="form-submit-messge" action="">
                </form>`
    
   export let inputHtml =` 
      <div class="input-container">
   <input id="chat-message-input" name="message" type="text" maxlength=10000 placeholder="type  message ..."   />
   <label for="submit-message" class="submit-button-style">
        <i class="fa-solid fa-paper-plane"></i>
    </label>
    <label  class="submit-button-style emoji-label">
    <div class="emoji-menu">
            
    <div class="emoji">😀</div>

    <div class="emoji">😃</div>

    <div class="emoji">😄</div>

    <div class="emoji">😁</div>

    <div class="emoji">😆</div>

    <div class="emoji">😅</div>

    <div class="emoji">😂</div>

    <div class="emoji">🤣</div>

    <div class="emoji">😊</div>

    <div class="emoji">😇</div>

    <div class="emoji">🙂</div>

    <div class="emoji">🙃</div>

    <div class="emoji">😉</div>

    <div class="emoji">😌</div>

    <div class="emoji">😍</div>

    <div class="emoji">🥰</div>

    <div class="emoji">😘</div>

    <div class="emoji">😗</div>

    <div class="emoji">😙</div>

    <div class="emoji">😚</div>

    <div class="emoji">😋</div>

    <div class="emoji">😜</div>

    <div class="emoji">😝</div>

    <div class="emoji">😛</div>

    <div class="emoji">🤑</div>

    <div class="emoji">🤗</div>

    <div class="emoji">🤔</div>

    <div class="emoji">🤭</div>

    <div class="emoji">🤫</div>

    <div class="emoji">🤥</div>

    <div class="emoji">😶</div>

    <div class="emoji">😐</div>

    <div class="emoji">😑</div>

    <div class="emoji">😒</div>

    <div class="emoji">🙄</div>

    <div class="emoji">😬</div>

    <div class="emoji">🤥</div>

    <div class="emoji">😏</div>

    <div class="emoji">😌</div>

    <div class="emoji">😔</div>

    <div class="emoji">😪</div>

    <div class="emoji">🤤</div>

    <div class="emoji">😴</div>

    <div class="emoji">😷</div>

    <div class="emoji">🤒</div>

    <div class="emoji">🤕</div>

    <div class="emoji">🤢</div>

    <div class="emoji">🤮</div>

    <div class="emoji">🤧</div>

    <div class="emoji">🥵</div>

    <div class="emoji">🥶</div>

    <div class="emoji">🥴</div>

    <div class="emoji">😵</div>

    <div class="emoji">🤯</div>

    <div class="emoji">🤠</div>

    <div class="emoji">🥳</div>

    <div class="emoji">😎</div>

    <div class="emoji">🤓</div>

    <div class="emoji">🧐</div>

    <div class="emoji">😕</div>

    <div class="emoji">😟</div>

    <div class="emoji">🙁</div>

    <div class="emoji">☹️</div>

    <div class="emoji">😮</div>

    <div class="emoji">😯</div>

    <div class="emoji">😲</div>

    <div class="emoji">😳</div>

    <div class="emoji">🥺</div>

    <div class="emoji">😦</div>

    <div class="emoji">😧</div>

    <div class="emoji">😨</div>

    <div class="emoji">😰</div>

    <div class="emoji">😥</div>

    <div class="emoji">😢</div>

    <div class="emoji">😭</div>

    <div class="emoji">😱</div>

    <div class="emoji">😖</div>

    <div class="emoji">😣</div>

    <div class="emoji">😞</div>

    <div class="emoji">😓</div>

    <div class="emoji">😩</div>

    <div class="emoji">😫</div>

    <div class="emoji">🥱</div>

    <div class="emoji">😤</div>

    <div class="emoji">😡</div>

    <div class="emoji">😠</div>

    <div class="emoji">🤬</div>

    <div class="emoji">😈</div>

    <div class="emoji">👿</div>

    <div class="emoji">💀</div>

    <div class="emoji">☠️</div>

    <div class="emoji">💩</div>

    <div class="emoji">🤡</div>

    <div class="emoji">👹</div>

    <div class="emoji">👺</div>

    <div class="emoji">👻</div>

    <div class="emoji">👽</div>

    <div class="emoji">👾</div>

    <div class="emoji">🤖</div>

    <div class="emoji">😺</div>

    <div class="emoji">😸</div>

    <div class="emoji">😹</div>

    <div class="emoji">😻</div>

    <div class="emoji">😼</div>

    <div class="emoji">😽</div>

    <div class="emoji">🙀</div>

    <div class="emoji">😿</div>

    <div class="emoji">😾</div>

    <div class="emoji">👋</div>

    <div class="emoji">🤚</div>

    <div class="emoji">🖐️</div>

    <div class="emoji">✋</div>

    <div class="emoji">🖖</div>

    <div class="emoji">👌</div>

    <div class="emoji">🤌</div>

    <div class="emoji">🤏</div>

    <div class="emoji">✌️</div>

    <div class="emoji">🤞</div>

    <div class="emoji">🤟</div>

    <div class="emoji">🤘</div>

    <div class="emoji">🤙</div>

    <div class="emoji">👈</div>

    <div class="emoji">👉</div>

    <div class="emoji">👆</div>

    <div class="emoji">👇</div>

    <div class="emoji">☝️</div>

    <div class="emoji">👍</div>

    <div class="emoji">👎</div>

    <div class="emoji">✊</div>

    <div class="emoji">👊</div>

    <div class="emoji">🤛</div>

    <div class="emoji">🤜</div>

    <div class="emoji">👏</div>

    <div class="emoji">🙌</div>

    <div class="emoji">👐</div>

    <div class="emoji">🤲</div>

    <div class="emoji">🤝</div>

    <div class="emoji">🙏</div>
    </div>
        <i class="fa-solid fa-face-smile"></i>
        </label>
        <input type="submit" value="send" id="submit-message" hidden>
        </div>

        `;

export const loginHTML = `
        
        <div class="kolx d-flex justify-content-center align-items-center">
        <div class="container_login" id="container_login">
            <div class="form-container sign-up">
                <form class="register-input" action=""  method="post" >
                    <h1>Create Account</h1>

                    <div class="social-icons   "  >
                        <a  class="login-with-intra  " >
                            <img    src="/media/intraLogo.svg" alt="">
                        </a>
                    </div>
                    <span>or use your email for registeration</span>
                        <div class="input-box">
                            <input type="text"
                            name="username"
                            placeholder="Enter Username"/>
                            <i class='bx bxs-user'></i>
                        </div>
                        <div class="input-box">
                            <input type="email"
                            name="email"
                            placeholder="Enter Email"/> 
                            <i class='bx bxs-envelope'></i>
                        </div>
                        <div class="input-box">
                            <input type="password"
                            name="password1"
                            placeholder="Enter Password"/>
                            <i class='bx bxs-lock-alt'></i>
                        </div>
                        <div class="input-box">
                            <input type="password"
                            name="password2"
                            placeholder="Confirm Password"/>
                            <i class='bx bxs-lock'></i>
                        </div>
                        <button   type="submit" class="sigin" value="SIGIN UP">Sign Up</button>
                        <div class="pragraph_UP">
                            <button class="hidden" id="login">Sign In</button>
                        </div> 
                    </form>
                </div>


                <div class="form-container sign-in" >
                    <form class="login-input" action=""  method="post"  >
                        <h1>Sign In</h1>
                        <div class="social-icons">     
                            <a class="login-with-intra ">
                                <img class="login-with-intra pe-auto"   src="/media/intraLogo.svg" alt="">
                            </a>
                        </div>
                        <span>or use your email password</span>
                            <div class="input-box">
                                <input  type="text" name="username"  placeholder="Enter Username" required>
                                <i class='bx bxs-user'></i>
                            </div>
                            <div class="input-box">
                                <input type="password" name="password"  placeholder="Enter Password" required>
                        <i class='bx bxs-lock-alt'></i>
                    </div>
                    <button  type="submit" class="signin" value="SIGN IN">Sign In</button>
                    <div class="pragraph_up">
                        <button type="button" class="hidden" id="register">Sign Up</button>
                    </div> 
                        
                </form>
            </div>

            <div class="toggle-container">
                <div class="toggle">
                    <div class="toggle-panel toggle-left">      
                        <div class="pragraph">
                            <h1>Welcome Back!</h1>
                            <p>Enter your personal details to use all of site features</p>
                        </div>
                        <div class="dawn">
                            <div class="pingpong">
                                <div class="table-ping">
                                    <div class="line"></div>
                                    <div class="net-top"></div>
                                    <div class="net-middle"></div>
                                    <div class="net-bottom"></div>
                                    <div class="net-shadow"></div>
                                </div>
                                <div class="c1">
                                    <div class="b1"></div>
                                </div>
                                <div class="c2">
                                    <div class="b2"></div>
                                </div>
                                <div class="c3">
                                    <div class="b3"></div>
                                </div>
                                <div class="c4">
                                    <div class="b4"></div>
                                </div>
                                <span class="ping">PING</span>
                                <span class="pong">PONG</span>
                            </div>
                        </div>
                    </div>
                    <div class="toggle-panel toggle-right">
                    
                    <div class="pragraph">
                        <h1>Hello, Friend!</h1>
                        <p>Register with your personal details to use all of site features</p>
                    </div> 
                        <div class="dawn">
                            <div class="pingpong">
                                <div class="table-ping">
                                    <div class="line"></div>
                                    <div class="net-top"></div>
                                    <div class="net-middle"></div>
                                    <div class="net-bottom"></div>
                                    <div class="net-shadow"></div>
                                </div>
                                <div class="c1">
                                    <div class="b1"></div>
                                </div>
                                <div class="c2">
                                    <div class="b2"></div>
                                </div>
                                <div class="c3">
                                    <div class="b3"></div>
                                </div>
                                <div class="c4">
                                    <div class="b4"></div>
                                </div>
                                <span class="ping">PING</span>
                                <span class="pong">PONG</span>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div> `;



   export function generateSidebarItems(activeLink) {
        return `
            <li data-link>
                <a class="${activeLink[0].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" href="/home" data-link>
                    <i class="fa-solid fa-house fa-fw"></i>
                </a>
            </li>
            <li data-link>
                <a id="game_buttun" class="${activeLink[1].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" data-link href="/games">
                    <i class="fa-solid fa-gamepad fa-fw"></i>
                </a>
            </li>
            <li data-link>
                <a class="${activeLink[2].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" data-link href="/profile">
                    <i class="fa-solid fa-user fa-fw"></i>
                </a>
            </li>
            <li data-link>
                <a class="${activeLink[3].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" data-link href="/tournament">
                    <i class="fa-solid fa-trophy fa-fw"></i>
                </a>
            </li>
            <li data-link>
                <a class="${activeLink[4].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" data-link href="/friends">
                    <i class="fa-solid fa-user-group fa-fw"></i>
                </a>
            </li>
            <li data-link>
                <a class="${activeLink[6].active} d-flex p-3 align-items-center fs-5 rounded-2 ms-3" data-link href="/settings">
                    <i class="fa-solid fa-gear"></i>
                </a>
            </li>
        `;
    }
    


    export function headerHTML(msgs,notfnums,linkilnotification,avatar){
        return `
        <header class="headbar d-flex w-100 justify-content-between align-items-center p-2">
            <img class="img-fluid mt-0" src="static/images/Untitled.png" alt="Logo">
            
            <div class="search position-relative">
                <input type="search" class="search-filter   ps-5 rounded-3" placeholder="Type A Keyword">
                <div class="cards-ser">
                  
                </div>
            </div>
            
            <div class="icons header-hold-icons  d-flex align-items-center">
            <div class="chat-icon">
                <a data-link href="/chat"><i class="fa-solid fa-message"></i></a>
                <span class="position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger all-number-msg">
                    ${msgs || ""}
                    <span class="visually-hidden">unread messages</span>
                </span>
            </div>
                
                <div class="dropdown me-3 bell-notif">
                    <button class="btn btn-primary dropdown-toggle bg-transparent position-relative" type="button" id="dropdownMenuButton1" data-bs-toggle="dropdown" aria-expanded="false">
                        <i class="fa-solid fa-bell fa-lg"></i>
                        <span class=" notif-nums position-absolute top-0 start-100 translate-middle badge rounded-pill bg-danger">
                            ${notfnums || ""}
                            <span class="visually-hidden">unread notifications</span>
                        </span>
                    </button>
                    <ul class="dropdown-menu scrollable-menu  notification-list " aria-labelledby="dropdownMenuButton1">
                        ${linkilnotification}
                    </ul>
                </div>
                
                <div class="user-menu dropdown">
                    <img src="${avatar}" class="avatar-header   ms-3" alt="">
                    <button type="button" class="btn btn-danger  bg-transparent  m-0 dropdown-toggle dropdown-toggle-split" data-bs-toggle="dropdown" aria-expanded="false">
                    <span class="visually-hidden">Toggle Dropdown</span>
                    <ul class="dropdown-menu">
                        <li><a class="dropdown-item" data-link href="/profile">Profile</a></li>
                        <li><a class="dropdown-item" data-link href="/settings">Settings</a></li>
                        <li><hr class="dropdown-divider"></li>
                        <li class="dlg-btn" data-url="/logout" data-msgtxt="Are you sure you want to logout?">
                            <a class="dropdown-item">Logout</a>
                        </li>
                    </ul>
                </div>
            </div>
        </header>
        `;
    }


    export const messageForBolocked = `<div class="chat-message blocked-message">
    You have been blocked from this chat. You can no longer send messages or interact with this conversation.
</div>
`;