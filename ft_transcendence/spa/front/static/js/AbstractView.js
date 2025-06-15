
import { messageHandling } from "../js/utils.js";
import { getCookie, CheckTokenExpire } from "./tools.js";
import { navigateTo, establishSocket,refreshAccessToken, tokenIsValid } from "./index.js";
import globalData from "./tools.js";
import WebSocketManager from "./Websocket.js";
import { fetchDataBase, fetchErrorHandel, setActiveLink } from "./BaseUtils.js";
import { generateSidebarItems, headerHTML } from "./HtmlPages.js";
import { createHistoryEntry, getUserProfile, populateGameScores, populatePlayerData, renderTournamentStats, setProfileDetails, showProfileModal } from "../jstools/friendProfile.js";
export default class AbstractView {
  constructor() {
    this.data = null;
    this.payload ={user_id :null};
    this.profiles = null;
    this.friendsreq = null;
    this.mysendreq = null;
    this.trn_stat = null;
    this.pageTitle = null;
    this.myprofile = null;
    this.notifications = null;
    this.playerHistory = null;
    localStorage.setItem("tourn", 0);
    globalData.inChatPage = false;
    this.number_msgs = 0;
    this.access_token = getCookie("access_token");
    this.refresh_token = getCookie("refresh_token");
  }

  setTitle(title) {
    document.title = title;
  }

  async getHead() {
    return "";
  }
  async getHtml() {
    return "";
  }

  afterRender() {}

  async getSidebar() {
    const activeLink = [
      { name: "HOME", active: "active" },
      { name: "GAMES", active: "" },
      { name: "PROFILE", active: "" },
      { name: "TOURNAMENT", active: "" },
      { name: "FRIENDS", active: "" },
      { name: "LEADERBOARD", active: "" },
      { name: "SETTINGS", active: "" },
    ];
    setActiveLink(activeLink, this.pageTitle);
    const sidebarItems = generateSidebarItems(activeLink);
    return `
        <input type="checkbox" id="hamburger" class="hamburger-input">
        <label for="hamburger" class="hamburger-label">
            <span></span>
            <span></span>
            <span></span>
        </label>
        <div class="sidebar">
            <ul>
                ${sidebarItems}
            </ul>
            <div class="position-absolute bottom-0 start-50 translate-middle-x mb-3 dlg-btn" data-msgtxt="sure you want to logout?" data-url="/logout">
                <button type="button" class="btn btn-secondary">
                    <i class="fa-solid fa-right-from-bracket"></i>
                </button>
            </div>
        </div>
    `;
  }

  async setData() {
    try {
      this.data = await fetchDataBase(`/api/myprofile/`);
      this.payload.user_id = this.data.user.id;
    } catch (error) {
      fetchErrorHandel(error);
      navigateTo("/login");
    }
  }

  async setDataProfiles() {
    try {
      const responseData = await fetchDataBase(`/api/profile/`);
      this.profiles = responseData;
      globalData.profiles = responseData;
      return responseData
    } catch (error) {
      fetchErrorHandel(error);
    }
  }

  async setDataFriend(id_friend) {
    try {
      this.datafriend = await fetchDataBase(
        `/api/profile/${id_friend}/`,
        "GET",
        null
      );
      return this.datafriend;
    } catch (error) {
      fetchErrorHandel(error);
    }
  }

  async setDataFriendRequest() {
    try {
      const responseData = await fetchDataBase(`/api/frequest/`);
      this.friendsreq = responseData.ireceive;
      this.mysendreq = responseData.isend;
    } catch (error) {
      fetchErrorHandel(error);
    }
  }
  async myNotifications() {
    try {
      this.notifications = await fetchDataBase(`/api/notifications/`);
    } catch (error) {
      fetchErrorHandel(error);
    }
  }

  async removeNotification(id) {
    try {
      return await fetchDataBase(`/api/notif/${id}`, "DELETE");
    } catch (error) {
      throw error;
    }
  }

  async markNotificationRead(id) {
    try {
      await fetchDataBase(`/api/notif/${id}/`, "POST", { is_read: 1 });
      return true;
    } catch (error) {
      messageHandling("error", error);
      return false;
    }
  }
  async getTournStats() {
    try {
      this.trn_stat = await fetchDataBase(
        `/tournament/trn_stats/`,
        "POST",
        this.data
      );
    } catch (error) {
      messageHandling("error", error);
    }
  }
  async getTournStatsFriend(data) {
    try {
      this.trn_statFriend = await fetchDataBase(
        `/tournament/trn_stats/`,
        "POST",
        data
      );
    } catch (error) {
      messageHandling("error", error);
    }
  }

  async getHistoryOfgame(body) {
    try {
      const responseData = await fetchDataBase(
        "/game_service/api/stats/",
        "POST",
        body
      );
      this.playerHistory = responseData;
    } catch (error) {
      fetchErrorHandel(error);
    }
  }
  async allMessagesNotRead() {
    try {
      const data = { user_id: this.payload.user_id };
      this.number_msgs = await fetchDataBase(
        `chat/all_unread_msgs`,
        "POST",
        data
      );
    } catch (error) {
      fetchErrorHandel(error);
    }
  }

  async removeNotificationWid(notificationId, element) {
    this.removeNotification(notificationId)
      .then((response) => {
        let notfBell;
        notfBell = document.querySelector(".notif-nums");
        if (notfBell) notfBell.innerHTML = response.unread_count;
        element.remove();
      })
      .catch((error) => {
        messageHandling("error", error);
      });
  }

  async notficationAfterRender() {
    const notificationList = document.querySelector(".notification-list");
    if (!notificationList) return;
    notificationList.addEventListener("click", async (event) => {
      const button = event.target.closest(".rm-notification");
      if (button) {
        const notificationId = button.dataset.id;
        if (notificationId) {
          await this.removeNotificationWid(
            notificationId,
            button.parentElement
          );
        }
      } else if (event.target.classList.contains("mini-item-drop")) {
        const notificationId = event.target.dataset.id;
        if (notificationId) {
          this.markNotificationRead(notificationId);
        }
      }
    });
  }

  getProfilesHtmlClone_2(profiles) {
    const ulHolder = document.querySelector(".cards-ser");
    const templi = document.querySelector(".user-serch-temp");

    if (!ulHolder || !templi) {
      return;
    }
    profiles.forEach((profile) => {
      const clone = templi.content.cloneNode(true);
      const usernameElement = clone.querySelector(".username-ser");
      const avatarElement = clone.querySelector(".avatar-ser img");
      const goProfileButton = clone.querySelector(".go-profile");

      if (usernameElement)
        usernameElement.textContent = profile?.user?.username || "Unknown User";
      if (avatarElement) avatarElement.src = profile?.avatar || "";
      if (goProfileButton)
        goProfileButton.idTargetUser = profile?.user?.id || "";
      ulHolder.append(clone);
    });
  }

  setupFilterListeners_2() {
    const filterInput = document.querySelector(".search-filter");
    if (!filterInput) {
      return;
    }
    filterInput.addEventListener("input", (e) =>
      this.filterData_2(e.target.value)
    );

    filterInput.addEventListener("blur", () => {
      const searchResults = document.querySelectorAll(".user-ser");
      searchResults.forEach((item) => item.classList.add("hide"));
    });
  }

  filterData_2(value) {
    const allListSrch = document.querySelectorAll(".user-ser");
    allListSrch.forEach((item) => {
      item.addEventListener("mousedown", (e) => e.preventDefault());

      const usernameElement = item.querySelector(".username-ser");
      const username = usernameElement ? usernameElement.innerText : "";

      if (username.toLowerCase().includes(value.toLowerCase())) {
        item.classList.remove("hide");
      } else {
        item.classList.add("hide");
      }
    });
  }

  async searchHandle() {
    await this.setDataProfiles();
    this.getProfilesHtmlClone_2(this.profiles);
    this.setupFilterListeners_2();
  }

  getTime(isoTimestamp) {
    const date = new Date(isoTimestamp);
    const year = date.getUTCFullYear();
    const month = String(date.getUTCMonth() + 1).padStart(2, "0");
    const day = String(date.getUTCDate()).padStart(2, "0");
    const hours = String(date.getUTCHours()).padStart(2, "0");
    const minutes = String(date.getUTCMinutes()).padStart(2, "0");
    return `${year}-${month}-${day} ${hours}:${minutes}`;
  }
  async notificationsHandle() {
    await this.myNotifications();
    this.linkilnotification = this.notifications?.notifications
      .map((e) => {
        const isRead = e.is_read ? "" : "notif-not-read";
        return `<li  class="item-drop-custum   ${isRead}" data-link><a class="dropdown-item mini-item-drop " href="/friends" data-id="${
          e.id
        }"  data-link> ${e.message}  | ${this.getTime(e.timestamp)}</a>  
        
        <button type="button" class="btn  btn-rm-notf btn-danger bg-danger rm-notification"   data-id="${
          e.id
        }">
        <i class="fa fa-times"></i>
      </button>
        </li>\n`;
      })
      .join('');
  }

  async getHeader() {
    await this.notificationsHandle();
    await this.allMessagesNotRead();
    return headerHTML(
      this.number_msgs.all_unread_mssgs,
      this.notifications?.unread_count || 0,
      this.linkilnotification || '',
      this.data.avatar
    );
  }

  async inAuthpages() {
    const checkv = await tokenIsValid();
    if (!checkv) {
      return false;
    }
    await this.setData();
    establishSocket();
    return true;
  }

  async afterRenderAll() {
    document.querySelectorAll(".dlg-btn").forEach((element) => {
      const msg = element.dataset.msgtxt || "no message message";
      const tourl = element.dataset.url || "#";

      element.addEventListener("click", () => {
        dialog.showDialog(msg, () => navigateTo(tourl));
      });
    });
  }

  renderHistoryHtml(historic) {
    const template = document.querySelector(".history-template");
    const viewHistory = document.querySelector(
      ".freined-profile-user .scrool_histori"
    );

    if (!template || !viewHistory) {
      messageHandling("error","Required elements for history not found.");
      return;
    }
    viewHistory.innerHTML= "";
    if (historic.length <= 0) {
      viewHistory.innerHTML = `<div class="no-history"> No history </div>`;
    }
    historic.forEach((game) => {
      const clone = createHistoryEntry(template, game);
      if (!clone) return;
      viewHistory.appendChild(clone);
    });
  }

  async loadDataFriendProfile(e) {
    await this.setDataFriend(e);
    await this.getTournStatsFriend(this.datafriend);
    await this.setDataFriendRequest();

    const postBody = {
      id: this.datafriend?.user?.id ,
      name: this.datafriend?.user?.username || "Unknown",
      historycount: 5,
    };

    await this.getHistoryOfgame(postBody);
  }

  displayFriendProfile() {
    const { user, historic } = this.playerHistory || {};
    const parsedUser = JSON.parse(user || "{}");
    const parsedHistory = JSON.parse(historic || "[]");
    const fprContainer = document.querySelector(".freined-profile-user");
    if (!fprContainer) return;
    const isFriend = this.data?.friends.find((f) => f.id == this.datafriend.id)  || this.datafriend.id == this.data.id;
    setProfileDetails(fprContainer, parsedUser, this.datafriend,this.trn_statFriend.wins || 0,this.mysendreq,this.friendsreq,isFriend);
    renderTournamentStats(fprContainer, this.trn_statFriend);
    this.renderHistoryHtml(parsedHistory);
  }

  async showFriendProfile(e) {
    const fprContainer = document.querySelector(".freined-profile-user");
    if (!fprContainer) return;

    if (!(await tokenIsValid())) return;

    await this.loadDataFriendProfile(e);
    this.displayFriendProfile();
    showProfileModal();
  }

  async freindProfileHandle() {
    const allButtons = document.querySelectorAll(".go-profile");

    allButtons.forEach((button) => {
      button.addEventListener("click", (event) => {
        this.showFriendProfile(event.currentTarget.idTargetUser);
      });
    });

    const exitButton = document.querySelector(".btn-exit");
    if (exitButton) {
      exitButton.addEventListener("click", () => {
        const profileContainer = document.querySelector(
          ".freined-profile-user"
        );
        if (profileContainer) profileContainer.style.display = "none";

        const heightView = document.querySelector(".height-view");
        if (heightView) heightView.style.display = "none";

        const freezeAll = document.querySelector(".freez-all");
        if (freezeAll) freezeAll.style.display = "none";
      });
    }
  }
  checkGameSocket(){
    if (this.pageTitle != "GAMES") {
        if (globalData.soketQueue) globalData.soketQueue.close();
        globalData.soketQueue = null;
    }
  }
}
