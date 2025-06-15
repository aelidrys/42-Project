import Home from "/static/views/Home.js";
import Profile from "/static/views/Profile.js";
import Settings from "/static/views/Settings.js";
import Login from "/static/views/Login.js";
import Logout from "/static/views/Logout.js";
import Friends from "/static/views/Friends.js";
import Games from "/static/views/Games.js";
import Tournament from "/static/views/Tournament.js";
import LoginRemote from "/static/views/LoginRemote.js";
import NotFound from "/static/views/NotFound.js";
import Chat from "/static/views/Chat.js";
import { messageHandling } from "./utils.js";
import globalData from "./tools.js";

export const router = async () => {
  const routes = [
    { path: "/notfound", view: NotFound },
    { path: "/home", view: Home },
    { path: "/", view: Home },
    { path: "/profile", view: Profile },
    { path: "/settings", view: Settings },
    { path: "/login", view: Login },
    { path: "/logout", view: Logout },
    { path: "/friends", view: Friends },
    { path: "/games", view: Games },
    { path: "/tournament", view: Tournament },
    { path: "/loginremote/", view: LoginRemote },
    { path: "/chat", view: Chat },
  ];

  const potentialMatches = routes.map((route) => {
    return {
      route: route,
      isMatch: location.pathname === route.path,
    };
  });

  let match = potentialMatches.find(
    (potentialMatche) => potentialMatche.isMatch
  );
  if (!match) {
    match = {
      route: routes[0],
      isMatch: true,
    };
  }
  const view = await new match.route.view();
  globalData.currentView = view;
  const sidebar = document.querySelector(".sidebar-main");
  if(sidebar) sidebar.innerHTML = await view.getSidebar();

  view.checkGameSocket();
  const checkt = await view.inAuthpages();
  if (checkt) {
    var html = await view.getHtml();
    if (html) {
      document.querySelector(".content").innerHTML = html;
    }
    await view.afterRender();
    await view.notficationAfterRender();
    await view.searchHandle();
    await view.afterRenderAll();
    await view.freindProfileHandle();
  }
};
