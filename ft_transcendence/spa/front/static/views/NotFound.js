import AbstractView from "../js/AbstractView.js";

export default class extends AbstractView {
  constructor() {
    super();
    this.setTitle("404 Not Found");
  }

  async getSidebar() {
    return "";
  }
  async getHtml() {
    return `     <div class="d-flex align-items-center justify-content-center vh-100 not-404">
    <div class="text-center ">
        <h1 class="display-1 fw-bold">404</h1>
        <p class="fs-3"> <span class="text-danger">Opps!</span> Page not found.</p>
        <p class="lead  text-wlc">
        
        </p>
        <a data-link href="/home" class="btn btn-primary">Go Home</a>
    </div>`;
  }
  async afterRender() {
    this.textWriter(".text-wlc", "The page you’re looking for doesn’t exist.!");
  }
  async inAuthpages() {
    return true;
  }
  async afterRenderAll() {}
  async searchHandle() {}
  async notificationsHandle() {}
  async textWriter(element, txt) {
    let textwr = document.querySelector(element);

    for (let index = 0; index < txt.length; index++) {
      setTimeout(() => {
        textwr.innerHTML += txt[index];
      }, 50 * index);
    }
  }
}
