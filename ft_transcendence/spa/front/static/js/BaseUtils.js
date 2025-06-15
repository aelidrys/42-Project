import { navigateTo, tokenIsValid } from "./index.js";
import { getCookie } from "./tools.js";
import { messageHandling } from "./utils.js";

export function setActiveLink(activeLink, pageTitle) {
    activeLink.forEach((element) => {
        element.active = (element.name === pageTitle) ? "active" : "";
    });
}

export async function fetchDataBase(url, method = 'GET', body = null) {
    const access_token = getCookie("access_token");
    if (!access_token) {
      return ;
    }
    try {
      const headers = {
        'Authorization': `Bearer ${access_token}`,
        'Content-Type': 'application/json'
      };

      const options = { method, headers };
      if (body) options.body = JSON.stringify(body);
  
      const response = await fetch(url, options);
      if (!response.ok) {
        const errorData = await response.json();
        // if (response.status === 401 || response.status == 403) {
          
        // }
        throw new Error(errorData.detail || errorData.error || 'Request failed');
      }
  
      return await response.json();
    } catch (error) {
      throw error;  
    }
  }
  

export function fetchErrorHandel(error){
  if (error.message === 'Failed to fetch') {
    messageHandling("error",'Unable to connect to the server. Please check your connection.');
  } else {
    messageHandling("error",'An unexpected error occurred. Please try again later.');
  }
}

export async function fetch_data(url, _method, data=null) {
  const access_token = getCookie("access_token");
  var response = null;
  if (_method == 'POST'){
    response = await fetch(url, {
     method: _method,
      headers: {
        'Content-Type': 'application/json',
          'Authorization': `Bearer ${access_token}`,
      },
      body: data,
    });
  }
  else
    response = await fetch(url, {
      method: _method,
      headers: {
        'Content-Type': 'application/json',
          'Authorization': `Bearer ${access_token}`,
      }
    });

  if (response.ok)
  {
    const resp_data = await response.text();
    var data = JSON.parse(resp_data);
    return data;
  }
  else if (response.status === 401 || response.status == 403) {
    var isValid = await tokenIsValid();
    messageHandling("info", "Session refreshed. Please click again.");
    if (isValid)
      return await fetch_data(url, _method, data);
    // return { success: false, error: "Unauthorized" };
  } 
  else {
      const errorMessages = Object.values(data);
      messageHandling("error", errorMessages);
      // return { success: false, error: errorMessages };
  }
}

export async function getDataUtils() {
  try {
    var data = await fetchDataBase(`/api/myprofile/`);
    return data
  } 
  catch (error) {
    // console.log('======> ', error);
  }
}


async function   FetchProfileId(id) {
  try {
    const datafriend = await fetchDataBase(
      `/api/profile/${id_friend}/`,
      "GET",
      null
    );
    return datafriend;
  } catch (error) {
    return null;
  }
}