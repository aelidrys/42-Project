import AbstractView from "../js/AbstractView.js";
import { navigateTo, tokenIsValid } from "../js/index.js";
import { getCookie } from "../js/tools.js";

import { messageHandling , CostumConfigDialog} from "../js/utils.js";

export default class extends AbstractView {
    constructor() {
        super();
        this.setTitle("Settings");
        this.pageTitle = "SETTINGS";

   }


   
    async getHtml() {
        const headernav = await this.getHeader();
        return headernav  +   `  
       
        <div class="content_setting">
  <div class="main-content p-4 m-1">
    <h1 class="position-relative mb-1">Settings</h1>
    <form method="post" action="" class="profileinfo">
      <div class="profile-picture-container image-container">
        <img
          src="${this.data.avatar}"
          alt="Profile Picture"
          class="profile-picture"
          id="profile-image"
        />
        <div id="test">
          <label class="edit-button" for="file-input2" id="edit-profile-picture"
            >Edit</label
          >
          <input
            type="file"
            id="file-input2"
            name="avatar"
            class="form-control-file form-control-file"
            hidden
            accept="image/*"
            id="id_avatar"
          />
        </div>
      </div>
    </form>
    <h3>Details</h3>
    <form method="post" class="userinfo" action="">
      <div class="profile-section two-column">
      </div>
      <div class="profile-section two-column">
        <div class="input-group">
          <label for="id_username">User Name</label>
          <input
            type="text"
            name="username"
            value="${this.data.user.username}"
            maxlength="100"
            id="id_username"
          />
        </div>
        <div class="input-group">
          <label for="id_email">Email</label>
          <input
            type="text"
            name="email"
            value="${this.data.user.email}"
            maxlength="320"
            id="id_email"
          />
        </div>
      </div>

      <button type="submit">Update</button>
      <button type="reset">Reset</button>
    </form>

    <h3 class="mt-5">Change Password</h3>

    <form method="post" class="changepassword" action="">
      <div class="profile-section two-column">
        <div class="input-group">
          <label for="oldpassword">Current Password</label>
          <input type="password" name="oldpassword" required id="oldpassword"">
        </div>

        <div class="input-group">
          <label for="newpassword">New Password</label>
          <input type="password" name="newpassword" required id="newpassword"">
        </div>
      </div>
      <button type="submit">Update</button>
      <button type="reset">Reset</button>
    </form>

    <h3 class="mt-5">Tournament Settings</h3>

    <form method="post" class="profileinfo-trn" action="">
      <div class="profile-section two-column">
        <div class="input-group">
          <label for="tn-id">Tournament Name</label>
          <input
            type="text"
            name="tournament_name"
            required
            value="${this.data.tournament_name}"
            maxlength="100"
            id="tn-id"
          />
        </div>
      </div>
      <button type="submit">Update</button>
      <button type="reset">Reset</button>
    </form>
  </div>
</div>

        
            `;
    }



    async handleRequest(url, method, formData) {
        const access_token = getCookie("access_token");
        try {
            const response = await fetch(url, {
                method: method,
                headers: {
                    'Authorization': `Bearer ${access_token}`
                },
                body: formData
            });
            let responseData 
            try {
                responseData = await response.json();
            } catch (error) {
                if (response.status === 413) throw new Error('Image Too Large');
                throw new Error('An Undefined Error Has Occurred. Please Try Again Later');
            }
            if (response.ok) {
                const successMessage = Object.values(responseData)[0];
                messageHandling("success", successMessage); // 
                return { success: true, data: responseData };
            } else if (response.status === 401) {
               await  tokenIsValid();
                messageHandling("info", "Session refreshed. Please click again.");
                return { success: false, error: "Unauthorized" };
            } else {
                const errorMessages = Object.values(responseData);
                messageHandling("error", errorMessages);
                return { success: false, error: errorMessages };
            }
        } catch (error) {
            messageHandling("error",error.message)
            return { success: false, error: error.message };
        }
    }


    async updateProfile(event) {
        event.preventDefault();
        let regex = /[^a-zA-Z0-9_-]/
        const formData = new FormData(event.target);
        const tournament_name = formData.get('tournament_name');

        if(tournament_name)
        {
          if (tournament_name.match(regex)){
            messageHandling("error","Tournament Name  is not valid. Please correct it.");
            return;
            }
        }
        else{ messageHandling("error","Tournament Name Is Required"); return ;}

        const url = `/api/profile/${this.payload.user_id}/`;
    
        const result = await this.handleRequest(url, 'PUT', formData);
        if (result.success) {
            navigateTo("/profile");
        }
    }


    async changePassword(event) {
        event.preventDefault();
        const formData = new FormData(event.target);
        const url = `/api/changepassword/${this.payload.user_id}/`;
    
        const result = await this.handleRequest(url, 'PUT', formData);
        if (result.success) {
            navigateTo("/profile");
        }
    }

    async updateUser(event) {
        event.preventDefault();
        const formData = new FormData(event.target);
        const username = formData.get("username"); 
        if (username) {
            formData.set("username", username.toLowerCase());
        }
        const url = `/api/userupdate/`;
        const result = await this.handleRequest(url, 'PUT', formData);
        if (result.success) {
            navigateTo("/profile");
        }
    }

    afterRender() {
      const settingTourn = document.querySelector(".profileinfo-trn");
      const settingUser = document.querySelector(".userinfo");
      const settingPassword = document.querySelector(".changepassword");
      const changeImg = document.querySelector(".form-control-file");

      if (settingTourn) settingTourn.addEventListener("submit",(e) =>{this.updateProfile(e)});
      if (settingUser) settingUser.addEventListener("submit",this.updateUser.bind(this));
      if (settingPassword) settingPassword.addEventListener("submit",this.changePassword.bind(this));

      if (changeImg) {
        changeImg.onchange = () => {
          const file = changeImg.files[0];
          this.updateProfileAvatar(file);
        };
      }
    }
    
    async updateProfileAvatar(file) {
        const formData = new FormData();
        formData.append('avatar', file);
        const url = `/api/profile/${this.payload.user_id}/`;
    
        const result = await this.handleRequest(url, 'PUT', formData);
        if (result.success) {
            navigateTo("/profile");
        }
    }
    
}