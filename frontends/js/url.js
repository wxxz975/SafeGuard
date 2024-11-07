
function getServerUrl()
{
    return "http://" + window.location.hostname + ":" + window.location.port;
}


function getQueryDataUrl()
{
    return getServerUrl() + "/QueryData";
}

function getQueryAssetUrl()
{
    return getServerUrl() + "/QueryAsset";
}

