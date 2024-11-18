
/*
#define NewTaskQuery        "QueryResult"
#define InitQuery           "Init"
#define ModelSwitchQuery    "SwitchModel"
#define SettingsUpdateQuery "UpdateSettings"
#define HistoryQuery        "QueryHistory"
#define QueryImage          "QueryImage"

*/
/*
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "Init");
    xhr.send();

*/

/**
 * 请求后端切换模型，算法、框架
 * @param {string} ModelName 模型名称 
 * @param {string} Algorithm 算法名称
 * @param {string} Framework 推理框架名称
 * @param {function(json): void} callback 
 */
function ModelSwitchCommand(ModelName, Algorithm, Framework, callback)
{
    const url = new URL(GetServerApiUrl());
    url.searchParams.append("ModelName", ModelName);
    url.searchParams.append("Algorithm", Algorithm);
    url.searchParams.append("Framework", Framework);

    const hdr = new Headers();    
    hdr.append("CMD", "SwitchModel");
    hdr.append("Content-Type", "application/x-www-form-urlencoded");

    fetch(url, {
        method: 'GET',
        headers: hdr
    }).then(response => {
        if(!response.ok) {
            throw new Error('[ModelSwitch] error in request: ' + response.status);
        }
        return response.json();
    }).then(data => {
        callback(data);
    }).catch(error => {
        console.log('[ModelSwitch] error in callback:', error);
    })
}


function SettingsUpdateCommand(paramsMap, callback)
{
    const url = new URL(GetServerApiUrl());
    const hdr = new Headers();    
    hdr.append("CMD", "UpdateSettings");
    hdr.append("Content-Type", "application/x-www-form-urlencoded");
    for (const key in paramsMap) {
        if (paramsMap.hasOwnProperty(key)) {
            const value = paramsMap[key];
            url.searchParams.append(key, value);
        }
    }

    fetch(url, {
        method: 'GET',
        headers: hdr
    }).then(response => {
        if(!response.ok) {
            throw new Error('[SettingsUpdate] error in request: ' + response.status);
        }
        return response.json();
    }).then(data => {
        callback(data);
    }).catch(error => {
        console.log('[SettingsUpdate] error in callback:',error);
    })

}

/**
 * 初始化，在window加载完成之后进行调用，主要是获取现有模型、算法类型、框架 
 * @param {function(json): void} callback 如果请求成功进行调用回调函数
 */
function InitializeCommand(callback)
{
    const url = new URL(GetServerApiUrl());
    const hdr = new Headers();
    hdr.append("CMD", "Init");
    hdr.append("Content-Type", "application/x-www-form-urlencoded");

    fetch(url, {
        method: 'GET',
        headers: hdr
    }).then(response => {
        if(!response.ok) {
            throw new Error('[Initialize] error in request: ' + response.status);
        }
        return response.json();
    }).then(data => {
        callback(data);
    }).catch(error => {
        console.log('[Initialize] error in callback:',error);
    })
}



/**
 * 请求图像，主要用于请求这个违禁物品图像
 * @param {string} filename 请求的图像的名称或者uid
 * @param {function(json): void} callback 
 */
// function ImageQueryCommand(filename, callback)
// {
//     const url = new URL(GetServerApiUrl() + '/' + filename);

//     const hdr = new Headers();
//     hdr.append("CMD", "QueryImage");
    
//     fetch(url, {
//         method: 'GET',
//         headers: hdr
//     }).then(response => {
//         if(!response.ok) {
//             throw new Error('[ImageQuery] error in request: ' + response.status);
//         }
//         return response.blob();
//     }).then(data => {
//         callback(data);
//     }).catch(error => {
//         console.log('[ImageQuery] error in callback:',error);
//     })
// }



/**
 * 查询历史指定一段时间违禁物品检测记录统计。
 * @param {string} modelname - 模型名称。
 * @param {Date | string} startTime - 查询的起始时间，Date 对象或 ISO 格式字符串。 // 2024-09-13, 
 * @param {Date | string} endTime - 查询的结束时间，Date 对象或 ISO 格式字符串。
 * @param {function(Object): void} callback - 查询结果的回调函数，接收查询结果, 返回json格式。
 */
function HistoryQueryCommand(modelname, startTime, endTime, callback)
{
    const url = new URL(GetServerApiUrl());
    url.searchParams.append("ModelName", modelname);
    url.searchParams.append("StartTime", startTime);
    url.searchParams.append("EndTime", endTime);

    const hdr = new Headers();
    hdr.append("CMD", "QueryHistory");
    hdr.append("Content-Type", "application/x-www-form-urlencoded");

    fetch(url, {
        method: 'GET',
        headers: hdr
    }).then(response => {
        if(!response.ok) {
            throw new Error('[HistoryQuery] error in request: ' + response.status);
        }
        return response.json();
    }).then(data => {
        callback(data);
    }).catch(error => {
        console.log('[HistoryQuery] error in callback:',error);
    })
}


function ModelInfoQueryCommand(modelname, callback) {
    const url = new URL(GetServerApiUrl());
    url.searchParams.append("ModelName", modelname);

    const hdr = new Headers();
    hdr.append("CMD", "QueryModelInfo");
    hdr.append("Content-Type", "application/x-www-form-urlencoded");

    fetch(url, {
        method: 'GET',
        headers: hdr
    }).then(response => {
        if(!response.ok) {
            throw new Error('[ModelInfoQuery] error in request: ' + response.status);
        }
        return response.json();
    }).then(data => {
        callback(data);
    }).catch(error => {
        console.log('[ModelInfoQuery] error in callback:',error);
    })
}