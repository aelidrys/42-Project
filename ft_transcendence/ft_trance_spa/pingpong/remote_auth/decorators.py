from django.http import HttpResponse
from django.shortcuts import redirect
from usercontent.models import Profile
from django.contrib import messages
def unauthentication_user(view_fun):
    def wrapper_fun(request, *args, **kwargs):
        user_prf = get_user(request)
        if user_prf:
            return redirect('home')
        return view_fun(request, *args, **kwargs)
    return wrapper_fun

def autenticated_only(view_fun):
    def wrapper_fun(request, *arg, **args):
        user_prf = get_user(request)
        if user_prf:
            request.user = user_prf.user
            return view_fun(request, *arg, **args)
        messages.error(request, 'Login required to access')
        return redirect('login')
    return wrapper_fun



def get_user(request):
    # local user
    if request.user.is_authenticated:
        try:
            user_prf = Profile.objects.get(user=request.user)
            return user_prf
        except:
            return None

    # remote user 
    try:
        access_token = request.session['access_token']
        # print('access_token: ', access_token)
    except:
        return None
    user_prf = None
    if access_token:
        try:
            user_prf = Profile.objects.get(access_token=access_token)
        except:
            return None
    return user_prf