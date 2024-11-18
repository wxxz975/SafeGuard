
function GetServerUrl()
{
    return "http://" + window.location.hostname + ":" + window.location.port;
}

function GetServerApiUrl()
{
    return GetServerUrl()  + "/main";
}


function GetServerSocketUrl()
{
    return GetServerUrl() + "/ws";
}