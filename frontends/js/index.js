



let con = document.querySelector(".conversion")   //导航栏
let mainbox = document.querySelector(".mainbox")    //5个页面
let menu = document.querySelector(".menu")
let updata_name_src = {}   //更新页面名字 图片地址列表  name:src
let progress_load_timer_i = 0   //帮助界面进度条初始化

//初始化，全部隐藏， 除了第一个页面主页面
setTimeout(() => {
    for (let i = 0; i < mainbox.children.length; i++) {
        mainbox.children[i].style.display = 'none'
    }
    mainbox.children[0].style.display = "block"
}, 2000)


let bla_name = 0   //设置页面内容 是否更新

//默认index样式
con.children[0].classList.add("change_be")
con.children[0].classList.add("change_af")
con.children[0].children[0].classList.add("change_be")
con.children[0].children[0].classList.add("change_af")
con.children[0].children[0].style.color = '#f4e925'


//点击切换界面
con.onclick = function (e) {
    if (e.target.nodeName.toLowerCase() == 'a') {
        // console.log(e.target);

        // 重置样式
        for (let c = 0; c < con.children.length; c++) {
            con.children[c].classList.remove("change_be")
            con.children[c].classList.remove("change_af")
            con.children[c].children[0].classList.remove("change_be")
            con.children[c].children[0].classList.remove("change_af")
            con.children[c].children[0].style.color = '#fff'
        }


        for (let i = 0; i < mainbox.children.length; i++) {
            // console.log(mainbox.children[i]);
            if (mainbox.children[i].getAttribute("name") == e.target.name) {
                e.target.classList.add("change_be")
                e.target.classList.add("change_af")
                e.target.parentNode.classList.add("change_be")
                e.target.parentNode.classList.add("change_af")
                e.target.style.color = "#f4e925"



                mainbox.children[i].style.display = 'block'
                if (e.target.name == 'settings') {   //如果进入到setting页面
                    bla_name = 1   //设置准备更新


                } else {  //当转换别的页面时候

                    if (bla_name == 1) {
                        SettingsUpdata()   //进行更新

                    }
                    bla_name = 0  //初始化
                }

                if (e.target.name == 'update') {
                    updata_name_src = {}  //清空

                    // 进度条置空
                    progress_load_timer_i = 0
                    progress_load.style.width = 0 + 'px';
                    progress_load_result.innerText = 0 + '%';

                }

            } else {
                mainbox.children[i].style = ''
                mainbox.children[i].style.display = 'none'
            }
        }

    }
}


var appNamelist = document.querySelector("#selectElem")
//不可选
// appNamelist.remove(0)
// appNamelist.disabled = "true"   
// option.disabled
let body = document.querySelector("body")

// // 切换模型    全局
var label = []   //类别
var statistics = []  //数量 key:value



var DetectedItem = []   //存储违禁物品信息 即使更换模型也不重置 除关闭程序

var flages = 0   //有违禁物品就是1  反之0


var g_CurrentModelName = "";

// label : Checked
var g_CurrentLabelsMap = {

}


function InitCallback (data) {
    console.log("callback");
    
    if (data["Args"] == null) {
        alert("failed to init!")
        return 
    }

    ModelNames = data["Args"]["ModelNames"];
    modelIndex =  data["Args"]["CurrentModelIndex"];

    g_CurrentModelName = ModelNames[modelIndex];
    console.log("Current Model Name:", g_CurrentModelName);
}

function ModelInfoQueryCallback(json)
{
    if(json["Status"]) {
        let labels = json["Args"]["Labels"];
        for(let idx = 0; idx < labels.length; ++idx) {
            g_CurrentLabelsMap[labels[idx]] = true
        }

        for (let g = 0; g < lefttime_text.length; g++) {
            while (lefttime_text[g].firstChild) { // 清空初始的li内容
                lefttime_text[g].removeChild(lefttime_text[g].firstChild);
            }
        
            for (let i = 0; i < labels.length; i++) { // 赋值创建类别
                let li = document.createElement("li");
                li.innerHTML = labels[i];
                li.classList.add("bg");
                li.classList.add("active");
                
                li.onclick = function () {
                    if (li.getAttribute("selected") === "on") {
                        li.setAttribute("selected", "off");
                        li.classList.remove("active");
                        g_CurrentLabelsMap[li.innerHTML] = false;
                    } else {
                        li.setAttribute("selected", "on");
                        li.classList.add("active");
                        g_CurrentLabelsMap[li.innerHTML] = true;
                    }
                };

                lefttime_text[g].appendChild(li);
            }
        }
    }
}

window.onload = function () {
    // ani  切换模型等待加载    以及首先进入的加载
    let result = InitializeCommand(InitCallback)
    setTimeout(() => {
        ModelInfoQueryCommand(g_CurrentModelName, ModelInfoQueryCallback)
    }, 1000); 

    InitDefaultSettings();
    
    // let xhr = new XMLHttpRequest()
    // xhr.onreadystatechange = function () {
    //     if (xhr.status === 200 && xhr.readyState === 4) {
    //         let res = JSON.parse(xhr.responseText)
    //         let model = res.args.ModelNames

    //         for (let i = 0; i < model.length; i++) {
    //             let option = document.createElement("option")
    //             option.value = model[i]
    //             option.innerHTML = model[i]
    //             appNamelist.appendChild(option)

    //         }
    //         LoadModel();
    //     }
    // }
    // console.log(ModelSwitchCommand());
    
    // xhr.open("get", getQueryDataUrl())
    // xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    // xhr.setRequestHeader("cmd", "Init");
    // xhr.send();

    // setTimeout(LoadModel, 2000)
};





// 动画  
var ani = document.querySelector(".ani")
setTimeout(() => {
    ani.style.transition = '1s'
    ani.style.opacity = 0
    setTimeout(() => {
        ani.style.display = 'none'

    }, 1000)
}, 3000);


// 警告
let vi_back = document.querySelector(".vi_back")


// 是否有违禁物品显示相应图片
let tds = document.querySelector(".tds")


//违禁物品信息
let statusList = document.querySelectorAll(".statusList")

//违禁物品截图
let right_top = document.querySelector(".right_top");


let timers = null  //实时


//模型选择 
var sortedStatistics = null
var titlename = []
var titlenum = []

let data_pie = []   //统计

let box_type_name = []



LoadModel = function () { //每切换一次model都调用一次
    let ModelName = "";

    if (appNamelist.children[0].value != "") {
        ModelName = appNamelist.children[0].value
    }
    else {
        ModelName = appNamelist.children[1].value
    }
    //let ModelName = appNamelist.children[0].value

    let xhr = new XMLHttpRequest()
    xhr.onreadystatechange = function () {
        if (xhr.status === 200 && xhr.readyState === 4) {
            let res = JSON.parse(xhr.responseText)

            label = res.args.label  //返回违禁类别种类
            // console.log(label);
            label = label.map(label => name_map[label] || label)
            // console.log(label);
            
            statistics = res.args.statistics  //key:value  类别:数量

            // 违禁物品类别   数据    主页面和设置界面
            sortedStatistics = Object.entries(statistics).sort((a, b) => b[1] - a[1]); //用于主页面和统计界面
            // console.log(sortedStatistics);
            
            // [[类别,数量],[类别,数量],[],[]]

            //    进行排序分割  //用于主页面和统计界面
            titlename = []  //类别名
            titlenum = []  //对应数量
            for (let n = 0; n < sortedStatistics.length; n++) {
                titlename[n] = name_map[sortedStatistics[n][0]]
                titlenum[n] = sortedStatistics[n][1]
            }

            box_type_name = titlename
            while (titlename.length < 8) {
                box_type_name.push("1")
                titlenum.push(0)
            }

            data_type()

            // 统计界面  制作数据
            data_pie = []
            for (let p = 0; p < titlename.length; p++) {
                data_pie[p] = { "name": titlename[p], "value": titlenum[p] }
            }


            // mainbox.children[2].style.display="block"

            //统计界面图画
            echarts_1()
            echarts_3()
            // mainbox.children[2].style.display="none"
            //每次都清空主界面的违禁物品类别
            click_effect()

        }


    }
    xhr.open("get", getQueryDataUrl())
    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    xhr.setRequestHeader("cmd", "SwitchModel");
    xhr.setRequestHeader("ModelName", ModelName);
    xhr.send()

    clearInterval(timers)
    ju_model(ModelName)
};



var filter = []  //过滤

//点击类别事件效果 两个分别是主界面和设置    之后过滤
let lefttime_text = document.querySelectorAll(".lefttime_text ul")


function click_effect() {
    for (let g = 0; g < lefttime_text.length; g++) {
        for (let d = 0; d < lefttime_text[g].children.length; d++) {

            
            lefttime_text[g].children[d].setAttribute("selected", "on")  //初始化，都选中
            lefttime_text[g].children[d].onclick = function () {   //给予每个按钮点击事件
                if (lefttime_text[g].children[d].getAttribute("selected") == 'on') {   //如果选中后，再次点击
                    lefttime_text[0].children[d].setAttribute("selected", "off");   //则主页面和设置界面都为off
                    lefttime_text[1].children[d].setAttribute("selected", "off");
                    filter.push(lefttime_text[0].children[d].innerHTML)

                } else {                                                              //如果未选中后，再次点击
                    lefttime_text[0].children[d].setAttribute("selected", "on");
                    lefttime_text[1].children[d].setAttribute("selected", "on");
                    filter = filter.filter((item) => {
                        return item !== lefttime_text[0].children[d].innerHTML
                    })


                }
                lefttime_text[0].children[d].classList.toggle("active")
                lefttime_text[1].children[d].classList.toggle("active")
                // filter.push(lefttime_text[g].children[d].innerHTML)
            }
        }
    }

    

}

//主界面
function echarts_2() {

    sortedStatistics = Object.entries(update_echarts).sort((a, b) => b[1] - a[1]);

    titlename = []
    titlenum = []

    for (let n = 0; n < sortedStatistics.length; n++) {
        titlename[n] = name_map[sortedStatistics[n][0]]
        titlenum[n] = sortedStatistics[n][1]
    }

    // box_type_name = titlename
    // while (titlename.length < 8) {
    //     box_type_name.push("1")
    //     titlenum.push(0)
    // }

    // 基于准备好的dom，初始化echarts实例   左下
    var myChart2 = echarts.init(document.getElementById('echart2'));

    option2 = {
        grid: {
            left: '0%',
            top: '0',
            right: '20%',
            bottom: '0%',
            containLabel: true
        },
        xAxis: {
            show: false
        },
        yAxis: [{
            show: true,
            data: box_type_name,
            inverse: true,
            animationDuration: 300,
            animationDurationUpdate: 300,

            axisLabel: {

                textStyle: {
                    color: '#fff'
                },
            },

        }, {
            // 限制不要超出
            show: false,

            data: titlenum,

            axisLabel: { textStyle: { color: '#fff' } },

        }
        ],
        dataZoom: [{   //滚动体
            type: 'slider',
            yAxisIndex: 0,
            startValue: 0, // 数据窗口范围的起始数值
            endValue: 5, // 数据窗口范围的结束数值（可以根据需要进行调整）


        }],
        series: [{
            // realtimeSort: true,

            name: '条',
            type: 'bar',
            data: titlenum,
            barWidth: '30px',
            // barGap: '5%',
            // barCategoryGap:"10px",
            itemStyle: {
                normal: {
                    barBorderRadius: 40,
                    color: '#1089E7',
                },
            },
            // 柱子上数据
            label: {
                normal: {
                    show: true,
                    position: 'right',
                    formatter: '{c}',
                    textStyle: { color: 'rgba(255,255,255,1)' }
                }
            },
        },],

    };
    // 使用刚指定的配置项和数据显示图表。


    myChart2.setOption(option2);

    window.addEventListener("resize", function () {
        myChart2.resize();
    });

}

update_echarts = {}   //构建字典形式  类别：数量

var data_type = function () {

    var data_type = label  //获取类别名

    //以字典形式存储  类别：数量
    for (let l = 0; l < data_type.length; l++) {
        update_echarts[data_type[l]] = 0
    }

    // 类别
    for (let g = 0; g < lefttime_text.length; g++) {
        while (lefttime_text[g].firstChild) {  //清空初始的li内容

            lefttime_text[g].removeChild(lefttime_text[g].firstChild);
        }

        for (let i = 0; i < data_type.length; i++) {  //赋值创建类别
            li = document.createElement("li")
            li.innerHTML = data_type[i]
            li.classList.add("bg")
            li.classList.add("active")
            lefttime_text[g].appendChild(li)
        }
    }

    // 统计
    echarts_2()
};

data_type();


// 判断是否有违禁物   显示对应图片      
function warn() {

    let img = ""
    if (flages == 1) {
        img = 'img/false.png'  //  true   false medium 切换  

        tds.classList.add("tds_add")

    } else if (flages == 0) {
        img = 'img/true.png'

        tds.classList.remove("tds_add")

    }
    tds.children[0].src = img
};


function remove_cla() {  //清空 检测违禁品详情  和  违规物品记录图样式
    let resultList = document.querySelectorAll(".statusList");
    let right_top = document.querySelector(".right_top");
    for (let r = 0; r < resultList[1].children.length; r++) {
        resultList[1].children[r].classList.remove("add_info_main")

    }
    for (let r = 0; r < right_top.children.length; r++) {
        right_top.children[r].classList.remove("add_info_main")
    }
}

//  设置界面
//let range = document.querySelector("#range")   //粗细
let linear_color_div = document.querySelectorAll(".linear_color div") // 线框颜色
let ser = document.querySelector(".ser")  //展示图
let color = linear_color_div[0].style.background

//置信度
let confidence_label = document.querySelector(".confidence_label")

// 放大容器
let max_img = document.querySelector(".max_img")
let db_img = document.querySelector(".db_img ul")


let bor_color = color
//let bor_value = range.value
let img_width = 0   //原始图片的宽度
let img_height = 0  //原始图片的高度
let width_ratio = 0  //原始图片与控件的宽度比值
let height_ratio = 0  //原始图片与控件的高度比值


function ParseNewResult (raw_data) {
    let result;
    if(raw_data != null) {
        result = JSON.parse(raw_data)
        if(result["CMD"] != "NewResultMessage") return null; 
    }
    
    return result;
}

const socket = new WebSocket(GetServerSocketUrl());

// 当接收到来自服务器的消息时，执行以下回调函数
socket.onmessage = function(event) {
    json = ParseNewResult(event.data);
    if(json != null) {
        RenderResult(json);
    }
   
};

function IsValidProhibitedItem(item, conf_threshold)
{
    return g_CurrentLabelsMap[item.Label] && item.Confidence >= conf_threshold;
}

var g_StatisticsToday = {
    
}

var g_DetectedItemList = []


function RenderResult(json) {
    let filename = json["Args"]["Filename"];
    let boxes = json["Args"]["DetectedItem"];
    let conf_threshold = document.querySelector('.confidence_label').innerHTML
    let has_prohibit_item = true;
    let ulist = document.createElement('ul')

    for(let idx = 0; idx < boxes.length; ++idx) {
        let res_label = name_map[boxes[idx].Label]   //获取检测到的类别: chinese 
        if(IsValidProhibitedItem(boxes[idx], conf_threshold)) {
            has_prohibit_item = true;
        }

        if(has_prohibit_item) 
        {
            ba_matrix.push(boxes[idx].Coordinate)       // 
                    //主界面的违禁物品数量统计图实时叠加
            update_echarts[name_map[boxes[idx].Label]] += 1 // g_StatisticsToday[boxes[idx].Label] += 1;
                    //详情
            let ul = document.createElement('ul')       
            DetectedItem.push(boxes[idx])               // g_DetectedItemList.push(boxes[idx]);
            let date = new Date()
            ul.classList.add("add_info")
    
            let id = document.createElement("li")
            let name = document.createElement("li")
            let position = document.createElement("li")
            let confidence = document.createElement("li")
            let time = document.createElement("li")
    
            id.innerHTML = DetectedItem.length
            name.innerHTML = name_map[boxes[idx].label]
            position.innerHTML = boxes[idx].coordinate
            confidence.innerHTML = boxes[idx].confidence
            time.innerHTML = date.getFullYear() + "\\" + (date.getMonth() + 1) + "\\" + date.getDate() + "\\" + date.getHours() + "\\" + date.getMinutes() + "\\" + date.getSeconds()
            ul.appendChild(id)
            ul.appendChild(name)
            ul.appendChild(position)
            ul.appendChild(confidence)
            ul.appendChild(time)
            ulist.prepend(ul)
            ulist.setAttribute("flages", "1")
        }

        ulist.classList.add("add_info_main")
        statusList[1].prepend(ulist)
        let div_cj = document.createElement("div")

        div_cj.classList.add("add_info_main")
        div_cj.style.height = "auto"
        div_cj.style.marginTop = '20px'
        div_cj.style.padding = '10px'
        

        for (let m = 0; m < ba_matrix.length; m++) {     //框线矩阵  违禁物品
            let [a, b, c, d] = [ba_matrix[m][0], ba_matrix[m][1], ba_matrix[m][2], ba_matrix[m][3]]
            setTimeout(() => {

                div_cj.appendChild(cropImage(`${img_url}/${res.args.OriginalImage}`, a, b, c, d))

            }, 1000)
        }
        // 裁剪
        right_top.appendChild(div_cj)

        // // 滚动到容器的底部   每次都追加div_cj的高度  累加
        setTimeout(() => {
            console.log(div_cj.clientHeight);
            right_top.scrollTop += div_cj.clientHeight
        }, 2000)

    }

}


// banner
let box_center_banner = document.querySelector(".box_center")
let box_center_ul = document.querySelector(".box_center_banner ul")
let jt_left = document.querySelector(".box_center_left")
let jt_right = document.querySelector(".box_center_right")

let box_center_span = document.querySelector(".max_img span")
let index = box_center_ul.children.length-1
let jl = true  //节流器
let bw = box_center_ul.children[0].clientWidth


// // banner
function banner() {


    //最大个数
    // 防止banner 数量过多

    if (box_center_ul.children.length >= 100) {

        //设置动画  
        setTimeout(() => {
            // ani.style.transition = '1s'
            ani.style.opacity = 1
            ani.style.display = 'block'
            setTimeout(() => {
                ani.style.opacity = 0
                ani.style.display = 'none'


            }, 1500)
        }, 150);
        // 去除一半
        for (let i = 0; i < parseInt(box_center_ul.children.length / 2); i++) {
            box_center_ul.removeChild(box_center_ul.children[i]);    //主界面图片
            right_top.removeChild(right_top.children[i]);   //记录图

        }
        index = box_center_ul.children.length - 2
        setTimeout(() => {
            box_center_ul.style.transition = "none"
            box_center_ul.style.left = index * -bw + 'px'

        }, 500)

    }



    function play() {

        // 清除详细信息样式
        if (!jl) return
        
        if ((box_center_ul.children.length-1) - index > 1) {
            index = box_center_ul.children.length-1
        }else {
            index++
        }
        
        box_center_ul.style.transition = '1.5s'
        box_center_ul.style.left = index * -bw + 'px'

        remove_cla()
        statusList[1].children[box_center_ul.children.length - index - 1].classList.add("add_info_main")
        right_top.children[index - 1].classList.add("add_info_main")

        if (statusList[1].children[box_center_ul.children.length - index - 1].getAttribute("flages") == "1") {
            flages = 1
            warn()
            vi_back.classList.add("tds_add")

        } else {
            flages = 0
            warn()
            vi_back.classList.remove("tds_add")
        }



        jl = false
        setTimeout(() => {
            jl = true
        }, 1500)

        // right_top.children[]
    }

    play()



    // statusList[1].children[index].style.boxShadow=' inset -3px -2px 5px 3px #add3ff, inset 3px 2px 5px 3px #add3ff;'
    // box_center_banner.onmousever

    //移入移出
    box_center_banner.addEventListener("mouseenter", () => {
        clearInterval(timers)
        timers = null
        // mouseenter
    })
    box_center_banner.addEventListener('mouseleave', () => {
        clearInterval(timers)
        timers = setInterval(r_time, 3000)
        // mouseleave
    })

    jt_left.onclick = function () {
        if (!jl) return
        index--
        box_center_ul.style.transition = '1.5s'
        box_center_ul.style.left = index * -bw + 'px'

        // 清除详细信息样式
        remove_cla();
        statusList[1].children[box_center_ul.children.length - index - 1].classList.add("add_info_main")
        right_top.children[index - 1].classList.add("add_info_main")


        if (statusList[1].children[box_center_ul.children.length - index - 1].getAttribute("flages")) {
            flages = 1
            warn()
            vi_back.classList.add("tds_add")

        } else {
            flages = 0
            warn()
            vi_back.classList.remove("tds_add")
        }

        jl = false
        setTimeout(() => {
            jl = true
        }, 1500)
    }

    jt_right.onclick = play


    t = setInterval(() => {
        if (index >= box_center_ul.children.length - 1) {  //选择 -1  或不

            jt_right.style.display = 'none'

            //console.log("wul");

        } else {
            jt_right.style.display = 'block'

        }

        if (index > 1) {
            jt_left.style.display = 'block'
        } else if (index <= 1) {
            jt_left.style.display = 'none'
        }
    }, 100)



    let on_db_timers = null


    let or_bw = parseFloat(window.getComputedStyle(db_img.children[0]).width)  //获取宽度
    // 且双击放大了变红色
    box_center_banner.ondblclick = function () {

        on_db_timers = setInterval(() => {
            db_img.style.width = `${box_center_ul.children.length}00%`

            db_img.style.transition = '1.5s'
            db_img.style.marginLeft = (index - 1) * -or_bw + 'px'
            console.log(index, or_bw);
        }, 1000)

        max_img.style.display = 'block'
        if (flages != 1) {
            vi_back.classList.remove("tds_add")

        } else {
            vi_back.classList.add("tds_add")
        }
        vi_back.style.display = 'block'

    }
    box_center_span.onclick = function () {
        // clearInterval(timers)
        // timers = setInterval(r_time, 3000)
        clearInterval(on_db_timers)
        max_img.style.display = 'none'
        // max_img.children[0].src = ""

        vi_back.style.display = 'none'
    }



    // 图片滚轮局部放大缩小


    let all_li = box_center_ul.children

    let scale = 1; // 初始缩放比例
    let minScale = 1;
    let maxScale = 5;
    // 监听鼠标滚动事件
    // 监听鼠标滚动事件
    box_center_banner.addEventListener("wheel", function (e) {
        e.preventDefault();

        // 根据滚动方向调整缩放比例
        if (e.deltaY > 0) {
            scale -= 0.1; // 缩小
            scale = Math.max(scale, minScale); // 最小缩放比例限制
        } else {
            scale += 0.1; // 放大
            scale = Math.min(scale, maxScale); // 最大不超过5倍大小
        }
        for (var m = 0; m < all_li[index].children.length; m++) {
            // 获取鼠标在图片中的相对位置
            let mouseX = e.clientX - all_li[index].children[m].offsetLeft - 500;
            let mouseY = e.clientY - all_li[index].children[m].offsetTop;

            // 计算鼠标相对于图片的偏移比例
            let offsetX = mouseX / all_li[index].children[m].offsetWidth;
            let offsetY = mouseY / all_li[index].children[m].offsetHeight;

            // 设置图片的样式属性，实现局部放大效果
            all_li[index].children[m].style.transform = `scale(${scale})`;
            all_li[index].children[m].style.transformOrigin = `${offsetX * 100}% ${offsetY * 100}%`;
        }

    });

};








function ju_model(ModelName) {

    if (ModelName) {
        timers = setInterval(r_time, 3000)
        // clearInterval(timer)

    } else {
        console.log("选择模型后无返回的label");
    }
}

// crop image
function cropImage(ele, x, y, w, h) {
    // 创建一个新的 canvas 元素
    var canvas = document.createElement('canvas');
    var ctx = canvas.getContext('2d');


    // 设置 canvas 的尺寸与裁剪区域的尺寸一致
    canvas.width = w + 80; // 设置为裁剪的宽度
    canvas.height = h + 80; // 设置为裁剪的高度

    // 在 canvas 上绘制裁剪区域
    let box_img = document.createElement("img")

    box_img.src = ele;
    let can = document.createElement("img")
    box_img.onload = function () {
        // ctx.drawImage(box_img, x, y, w, h, 0, 0, w, h);
        //ctx.drawImage(box_img, x - w - 30, y + 50, w + 60, h + 60, 0, 0, w + 80, h + 80);
        ctx.drawImage(box_img, x, y, w, h, 0, 0, w + 80, h + 80);

        can.style.display = 'block'
        can.style.margin = 'auto'
        can.style.marginTop = '10px'

        // 将裁剪后的图片添加到 #croppedImage 的 src 属性中
        can.src = canvas.toDataURL('image/jpeg');
    }
    return can
}


// change back
let back_color = document.querySelectorAll(".back_color div")
for (let j = 0; j < back_color.length; j++) {
    back_color[j].onclick = function () {

        background_color = back_color[j].style.background
        body.style.background = background_color
    }
}

// 粗细






//    col()

// 线框默认值
// ser.style.border = range.value + "px solid " + color


for (let i = 0; i < linear_color_div.length; i++) {

    linear_color_div[i].onclick = function () {

        for (let z = 0; z < linear_color_div.length; z++) {
            linear_color_div[z].className = ''
        }
        linear_color_div[i].className = 'zt_on'
        ser.style.border = bor_value + "px solid " + linear_color_div[i].style.background
        // 获取线框颜色传递index
        bor_color = linear_color_div[i].style.background
        // col()
        color = linear_color_div[i].style.background

    }
}

// the confidence default value
var g_conf_default_value = 0.5;
var g_line_thickness_default_value = 1;
function InitDefaultSettings()
{
    let conf_input = document.querySelector("#confidence")
    let confidence_label = document.querySelector(".confidence_label");

    confidence_label.innerHTML = g_conf_default_value;
    confidence.value = g_conf_default_value;

    conf_input.addEventListener("input", function () {
        confidence_label.innerHTML = conf_input.value;
    });

    let line_thickness_label = document.querySelector(".line_thickness_label");
    let line_thickness = document.querySelector('#line_thickness');
    let ser = document.querySelector(".ser");
    line_thickness.addEventListener("input", function () {
        line_thickness_label.innerHTML = line_thickness.value;
        
        ser.style.border = line_thickness.value + "px solid " + color
    });
}




function SetttingsCallback(data) {
    console.log(data);
    
}
/*
        {
            "cmd": ""
            "args": {
                "DetectedItem": 
                    [
                        {
                            "Label": "Gun"
                            "Confidence": 0.55
                            "Coordinate": [10, 20, 89, 99]
                        },
                        {}
                    ]
                
            }
        }
    */

function SettingsUpdata() {
    let conf_input = document.querySelector("#confidence");
    setting_json = {};
    setting_json["conf_threshold"] = conf_input.value
    setting_json["iou_threshold"] = 0.55
    SettingsUpdateCommand(setting_json, SetttingsCallback)
};


let total_day 

// 统计界面  时间筛选处理
(function () {

    // time
    let time_start = document.querySelector("#time_start")
    let time_end = document.querySelector("#time_end")


    // 初始化 第二个 为当天日期
    let today = new Date().toISOString().split('T')[0]
    time_end.value = today
    time_end.max = today

    //初始化 第一个时间       即为：time_start时间是 time_end的前一个月
    // 计算一个月前的日期
    var endDate = new Date(time_end.value);
    endDate = new Date(endDate.setMonth(endDate.getMonth() - 2));
    // 将 time_end 的 max 属性设置为一个月后的日期
    // 注意：toISOString() 返回的是 UTC 时间，可能需要根据您的时区进行调整
    endDate = endDate.toISOString().split('T')[0];
    time_start.max = endDate
    time_start.value = endDate


    time_start.onchange = function () {

        change_data(time_start, "start")
        // console.log(time_start.value);
        // console.log(time_end.value);
        total_day = new Date(time_end.value) - new Date (time_start.value)
        console.log(new Date(total_day));
        

    }

    time_end.onchange = function () {

        change_data(time_end, "end")
        // console.log(time_start.value);
        // console.log(time_end.value);
    }
})();


function change_data(date, fla) {
    var date = new Date(date.value);  //获取传递过来的时间
    if (fla == "start") {  //如果为开始时间
        date = new Date(date.setMonth(date.getMonth() + 1));   //计算结束时间，基本为一个月
        
        
        date = date.toISOString().split('T')[0];
        console.log(date);
        
        
        
        time_end.value = date     //赋值给结束时间显示


        // HistoryQueryCommand()

    } else {
        date = new Date(date.setMonth(date.getMonth() - 1));
        date = date.toISOString().split('T')[0];
        time_start.value = date
    }


}



//统计   柱状图
function echarts_1() {

    sortedStatistics = Object.entries(update_echarts).sort((a, b) => b[1] - a[1]);

    titlename = []
    titlenum = []
    for (let n = 0; n < sortedStatistics.length; n++) {
        titlename[n] = sortedStatistics[n][0]
        titlenum[n] = sortedStatistics[n][1]
    }
    box_type_name = titlename
    while (titlename.length < 8) {
        box_type_name.push("1")
        titlenum.push(0)
    }

    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart1'));

    option = {

        grid: {
            // width:"330px",
            left: '0%',
            top: '20px',
            right: '1px',
            bottom: '1px',
            containLabel: true
        },
        xAxis: [{
            name: "类别",
            type: 'category',
            data: titlename,
            // titlename
            axisLabel: {
                interval: 0,
                // rotate:50,
                show: true,
                splitNumber: 15,
                textStyle: {
                    color: "rgba(255,255,255,.9)",
                    fontSize: '12',
                },
            },
        }],
        yAxis: [{
            name: "数量",
            type: 'value',
            axisLabel: {
                //formatter: '{value} %'
                // show: true,
                textStyle: {
                    color: "rgba(255,255,255,.9)",
                    fontSize: '12',
                },
            },
            splitLine: {
                lineStyle: {
                    color: "rgba(255,255,255,.1)",
                }
            }
        }],
        series: [
            {
                type: 'bar',
                data: titlenum, // data:[123,543,756,333,23,65,8,8,76,777],
                barWidth: '35%', //柱子宽度
                // barGap: 1, //柱子之间间距
                itemStyle: {
                    normal: {
                        color: '#27d08a',
                        opacity: 1,
                        barBorderRadius: 5,

                    }
                },
                label: {
                    show: true,
                    position: 'top', // 设置标签显示在柱形顶部
                    textStyle: {
                        color: "#fff" // 设置标签文本颜色为白色
                    }
                }
            }

        ], dataZoom: [
            {
                type: "inside",  // 支持内部鼠标滚动平移
                start: 0,
                // end: 20,
                startValue: 0, // 从头开始。
                endValue: 5,  // 最多5个
                zoomOnMouseWheel: false,  // 关闭滚轮缩放
                moveOnMouseWheel: true, // 开启滚轮平移
                moveOnMouseMove: true  // 鼠标移动能触发数据窗口平移

            },
        ],
    };

    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);
    window.addEventListener("resize", function () {
        myChart.resize();
    });
};


//统计  拼图
function echarts_3() {
    data_pie = []
    for (let p = 0; p < titlename.length; p++) {
        data_pie[p] = { "name": titlename[p], "value": titlenum[p] }
    }

    // 基于准备好的dom，初始化echarts实例
    var myChart = echarts.init(document.getElementById('echart3'));
    option = {
        legend: {
            //orient: 'vertical',
            type: "scroll",
            selected: 10,

            top: '20',
            left: 'center',
            itemWidth: 10,
            itemHeight: 10,
            data: titlename,
            textStyle: {
                color: 'rgba(255,255,255,.5)',
                fontSize: '12',
            }
        },
        tooltip: {
            trigger: 'item',
            formatter: "{b} : {c} ({d}%)"
        },

        visualMap: {
            show: false,
            min: 500,
            max: 600,
            inRange: {
                //colorLightness: [0, 1]
            }
        },
        series: [{
            name: '分布',
            type: 'pie',
            radius: ['30%', '60%'],
            center: ['50%', '60%'],
            color: ['#0086e5', '#30c5ed', '#9fe7b8', '#fedb5b', '#ff9f7d', '#fb7293', '#e7bcf2'], //'#FBFE27','rgb(11,228,96)','#FE5050'
            data: data_pie,    //此处为数据 格式为 { "name": 类别, "value": 值 }
            roseType: 'radius',

            label: {
                normal: {
                    formatter: ['{d|{d}%}', '{b|{b}}'].join('\n'),
                    rich: {
                        d: {
                            color: 'rgb(241,246,104)',
                            fontSize: 14,
                            fontWeight: 'bold',

                        },
                        b: {
                            color: 'rgb(98,137,169)',
                            fontSize: 12,

                        },
                    },
                }
            },
            labelLine: {
                normal: {
                    lineStyle: {
                        color: 'rgb(98,137,169)',
                    },
                    smooth: 0.2,
                    length: 5,
                    length2: 9,

                }
            },
            itemStyle: {
                normal: {
                    shadowColor: 'rgba(0, 0, 0, 0.1)',
                    shadowBlur: 50,
                }
            }
        }]
    };
    // 使用刚指定的配置项和数据显示图表。
    myChart.setOption(option);

    window.addEventListener("resize", function () {
        myChart.resize();
    });
}

//词云图  统计
function wordcloud() {
    // 词云
    let cloudData = []
    for (let p = 0; p < titlename.length; p++) {
        cloudData.push({ name: titlename[p], value: titlenum[p] })
    }

    wordCloud = echarts.init(document.getElementById('wordCloud'));
    wordCloud_option = {
        // left: 'center',
        // top: 'center',        
        tooltip: {
            textStyle: {
                color: '#FFF',   //提示的字体颜色
                fontSize: 24    //提示字体大小
            }
        },
        series: [{
            type: 'wordCloud',
            shape: 'smooth',
            drawOutOfBound: true,
            size: ['90%', '90%'],
            gridSize: 50,   //词云中每个词的间距
            sizeRange: [10, 80],
            rotationRange: [0, 0],
            textStyle: {
                normal: {
                    color: function (params) {
                        return `rgba(6, 195, 255)`; // 修正颜色值格式
                        // 获取词语相对于词云中心的位置
                        // var distanceToCenter = Math.sqrt(
                        //     Math.pow(params.data.coord[0], 2) +
                        //     Math.pow(params.data.coord[1], 2)
                        // );
                        // // 计算透明度，距离中心越远，透明度越低
                        // var opacity = 1 - distanceToCenter / maxDistance;
                        // // 返回颜色值，使用 RGBA 格式，并设置透明度
                        // return 'rgba(6, 195, 255, ' + opacity + ')';
                    }
                },
                emphasis: {
                    shadowBlur: 30,     //鼠标触碰时候，模糊度
                    shadowColor: 'rgba(0, 183, 238, 1)'   //颜色
                }
            },
            data: cloudData
        }]
    };

    wordCloud.setOption(wordCloud_option);

}




// 获取后端数据 返回天数对应值
// line chart 折线图 统计
x_day_list = []
for (let day = 1; day <= 31; day++) {
    x_day_list.push(`${day}日`)
}
//text  随机数
let randomNumbers = [];
for (let i = 0; i < 31; i++) {
    let randomNumber = Math.floor(Math.random() * (1000 - 100 + 1)) + 100;
    randomNumbers.push(randomNumber);
}


function line_chart() {
    var myChart = echarts.init(document.getElementById('line_chart'));

    option = {
        //  backgroundColor: '#00265f',
        tooltip: {
            trigger: 'axis',
            axisPointer: {
                type: 'shadow'
            }
        },

        xAxis: [{
            name: '天数',
            nameTextStyle: {
                color: 'rgba(255,255,255,.7)',

            },
            type: 'category',
            data: x_day_list,
            axisLine: {
                show: true,
                lineStyle: {
                    color: "rgba(255,255,255,.1)",
                    width: 1,
                    type: "solid"
                },
            },

            axisLabel: {
                interval: 0,
                // rotate:50,
                show: true,
                splitNumber: 5,
                textStyle: {
                    color: "rgba(255,255,255,.6)",
                    fontSize: '12',
                },
            },
        }],
        yAxis: [{
            name: '数量',
            nameTextStyle: {
                color: 'rgba(255,255,255,.7)',

            },
            type: 'value',
            axisLabel: {
                //formatter: '{value} %'
                show: true,
                textStyle: {
                    color: "rgba(255,255,255,.6)",
                    fontSize: '12',
                },
            },


            //横线设置透明度
            splitLine: {
                lineStyle: {
                    color: "rgba(255,255,255,.1)",
                }
            }
        }],
        series: [{

            type: 'line',
            smooth: true,
            data: randomNumbers,
            label: {
                show: true,
                position: 'top',
                color: '#fff' // 设置字体颜色为白色
            },

            itemStyle: {
                normal: {
                    color: '#62c98d',
                    opacity: 1,

                    barBorderRadius: 5,
                }
            }
        }
        ]
    };

    myChart.setOption(option);

}
line_chart()




// update




// 加载条
let progress_load = document.querySelector(".progress_load")
let progress_load_result = document.querySelector(".progress_load_result")
let progress_load_timer = null



//检查更新
let jc_update = document.querySelector("#jc_update")
let bb_update = document.querySelector("#bb_update")
let lt = true   //判断是否可以点击更新版本    默认不可按


function progress_bar() {
    if (lt) {

        bb_update.disabled = true;    //禁止按
    } else {
        bb_update.disabled = false;   //允许按
    }
}
progress_bar()


//发送请求  是否有可更新
jc_update.onclick = function () {

    lt = false
    progress_bar()

    // let xhr = new XMLHttpRequest()
    // xhr.onreadystatechange = function () {
    //     if (xhr.status === 200 && xhr.readyState === 4) {
    //         let res = JSON.parse(xhr.responseText)

    //     }
    // }
    // xhr.open("get", getQueryDataUrl())
    // xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded")
    // xhr.setRequestHeader("cmd", "");
    // xhr.setRequestHeader("", updata_name);
    // xhr.send();
}




// 开始更新

bb_update.onclick = function () {
    console.log("更新版本");
    bb_update.disabled = true;

    progress_load_timer = setInterval(() => {
        if (progress_load_timer_i < 100) {
            progress_load_timer_i += 1;
            progress_load.style.width = progress_load_timer_i * 4 + 'px';
            progress_load_result.innerText = progress_load_timer_i + '%';
        }
        if (progress_load_timer_i >= 100) {
            clearInterval(progress_load_timer);
            // bb_update.disabled = false;
        }
    }, 100)



}




