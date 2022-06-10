// 读取Json文件的函数
function readTextFile(file, callback) {
    var rawFile = new XMLHttpRequest();
    rawFile.overrideMimeType("application/json");
    rawFile.open("GET", file, true);
    rawFile.onreadystatechange = function () {
        if (rawFile.readyState === 4 && rawFile.status == "200") {
            callback(rawFile.responseText);
        }
    }
    rawFile.send(null);
}
// 绘制地图的主函数
var MaskMainCity = '重庆市';
var MapObject;
var bmap;
function DrawMaps() {
    // 获取绘制地图的dom元素
    var dom = document.getElementById("Map");
    if (MapObject == null) {
        MapObject = echarts.init(dom);
    }
    // 声明特效配置
    var option = null;
    // 定义需要重点标记的点坐标
    var Location_1 = ["重庆理工大学(中山图书馆)", [106.537114, 29.459216]];
    var Location_2 = ["重庆理工大学(第一实验楼)", [106.534906, 29.460919]];
    var Location_3 = ["重庆理工大学(教务处)", [106.536397, 29.464051]];
    var MainPoint = [{
        name: Location_1[0],
        value: Location_1[1]
    },
    {
        name: Location_2[0],
        value: Location_2[1]
    },
    {
        name: Location_3[0],
        value: Location_3[1]
    }
    ];
    // 将这几个点连线在一起,最后一个与第一个同是为了首尾相接
    var LineData = [{
        coords: [
            Location_1[1],
            Location_2[1],
            Location_3[1],
            Location_1[1]
        ]
    }];
    // 配置特效
    option = {
        // //图例的底色
        // backgroundColor: '#a7c0e0',
        // animation:true使用动画效果,false不使用
        //图例的标题
        title: {
            show: false,
            text: '重庆理工大学',
            // subtext: 'data from CMS',
            sublink: 'http://www.cqut.edu.cn',
            left: 'center',
            textStyle: {
                color: '#9400D3'
            }
        },
        animation: true,
        // bmap.center:地图中心坐标,bmap.zoom:放大倍数,bmap.roam:是否允许滚轮控制
        bmap: {
            center: [106.534906, 29.460919],
            zoom: 1,
            roam: false,
        },
        // 开始具体的渲染
        series: [
            {// 划线渲染
                type: 'lines',
                name: 'MainPoint',
                coordinateSystem: 'bmap',
                polyline: true,
                //数据绑定
                data: LineData,
                //配置线条样式
                lineStyle: {
                    normal: {
                        width: 4,
                        color: '#E6E6FA'
                    }
                }
            },
            {// 点渲染
                type: 'effectScatter',
                name: 'MainPoint',
                coordinateSystem: 'bmap',
                // 数据绑定
                data: MainPoint,
                //
                symbolSize: 6,
                // 'render':绘制完成显示特效,'emphasis':高亮时显示特效
                showEffectOn: 'render',
                // 涟漪动画配置
                rippleEffect: {
                    brushType: 'stroke',
                    scale: 4
                },
                // 开启鼠标提示动画效果
                hoverAnimation: true,
                // 散点大小配置
                symbolSize: 10,
                // 散点文字标签配置
                label: {
                    normal: {
                        // 是否显示配置
                        show: false,
                        formatter: '{b}',
                        position: 'right',
                        textStyle: {
                            color: '#9370DB',
                            fontSize: 20
                        }
                    }
                },
                // 散点样式配置
                itemStyle: {
                    normal: {
                        borderWidth: 1,
                        color: '#9370DB',
                        // 蒙度配置
                        shadowBlur: 25,
                        // 光晕颜色
                        shadowColor: '#9370DB'
                    }
                }
            },
        ]
    }
    MapObject.setOption(option); //先渲染地图，然后再获取控制
    bmap = MapObject.getModel().getComponent('bmap').getBMap();
    // // 切换控件
    // bmap.addControl(new BMap.MapTypeControl());
    // // console.log(MapObject)
}
//尝试绘制遮罩函数
function Mask(cityName) {
    // let:创建局部变量,var 全局作用
    let bdary = new BMap.Boundary();
    bdary.get(cityName, rs => {  //获取行政区域

        let EN_JW = "180, 90;";  //东北角
        let NW_JW = "-180, 90;";  //西北角
        let WS_JW = "-180, -90;";  //西南角
        let SE_JW = "180, -90;"; //东南角
        // max length index
        let maxIndex = -1
        let maxLength = 0
        for (let i = 0; i < rs.boundaries.length; i++) {
            if (rs.boundaries[i].length > maxLength) {
                maxLength = rs.boundaries[i].length
                maxIndex = i
            }
        }

        // 添加环形遮罩层(圈出最大区域，剩余遮罩)/外遮罩
        let ply1 = new BMap.Polygon(rs.boundaries[maxIndex] + ';' + rs.boundaries[maxIndex].split(";")[0] + ';' + SE_JW + WS_JW + NW_JW + EN_JW + SE_JW, {
            strokeColor: "none",
            fillColor: "#ffffff",
            fillOpacity: 1,
            strokeOpacity: 0.5
        }
        );
        // 建立多边形覆盖物
        bmap.addOverlay(ply1);
        // 添加边界
        var pointArray = [];
        //建立多边形覆盖物
        for (var i = 0; i < rs.boundaries.length; i++) {
            var ply = new BMap.Polygon(rs.boundaries[i], {
                strokeWeight: 4,
                strokeColor: "#ffffff",
                fillColor: ""
            });
            // 添加覆盖物
            bmap.addOverlay(ply);
            pointArray = pointArray.concat(ply.getPath());
        }
        bmap.setViewport(pointArray);
    });
}
// 增添class元素
function AddClass(id_name, class_name) {
    document.getElementById(id_name).classList.add(class_name);
};
// 修改内容
function Change(id_name, content) {
    document.getElementById(id_name).innerHTML = content;
};
// 电荷作用力 已经移植到d3.v4
function force(path, where, width, height) {
    // let width = 50;
    // let height = 50;
    let color = d3.scaleOrdinal(d3.schemeCategory20);
    var force = d3.forceSimulation();
    let svg = d3.select(where).append("svg")
        .attr("width", width)
        .attr("height", height);
    d3.json(path, function (error, graph) {
        console.log(graph);
        force.nodes(graph.nodes)
            .force("link", d3.forceLink(graph.links).distance(40))   //distance设置连线距离
            .force("charge", d3.forceManyBody().strength(-460))
            .force("center", d3.forceCenter(width / 2, height / 2))  //设置力学仿真器的中心
            .on("tick", ticked);

        let node = svg.selectAll(".node")
            .data(graph.nodes)
            .enter().append("circle")
            .attr("class", "node")
            .attr("r", 10)
            .style("fill", function (d, i) {
                return color(i);
            }).call(d3.drag().on("start", dragstarted) //d3.drag() 创建一个拖曳行为
                .on("drag", dragged)
                .on("end", dragended));
        let link = svg.selectAll(".link")
            .data(graph.links)
            .enter().append("line")
            .attr("class", "link")
            .style("stroke-width", function (d) { return Math.sqrt(d.value); });
        // .style("transform",rotate(200deg));
        //监听拖拽开始    
        function dragstarted(d) {
            if (!d3.event.active) force.alphaTarget(0.9).restart(); //alpha是动画的冷却系数，运动过程中会不断减小，直到小于0.005为止，此时动画会停止。
            d.fx = d.x;    //fx为固定坐标，x为初始坐标  注3>  
            d.fy = d.y;
        }
        //监听拖拽中  
        function dragged(d) {
            d.fx = d3.event.x;  //fevent.x为拖拽移动时的坐标
            d.fy = d3.event.y;
        }
        //监听拖拽结束
        function dragended(d) {
            if (!d3.event.active) force.alphaTarget(0);
            d.fx = null;        //固定坐标清空
            d.fy = null;
        }
        //拖拽时的事件监听器  以实时更新坐标
        function ticked() {
            link.attr("x1", function (d) {
                return d.source.x;
            })
                .attr("y1", function (d) {
                    return d.source.y;
                })
                .attr("x2", function (d) {
                    return d.target.x;
                })
                .attr("y2", function (d) {
                    return d.target.y;
                });
            node.attr("cx", function (d) { return d.x; })
                .attr("cy", function (d) { return d.y; });
        }
    });
}

// 画饼(包含文字)
function Pie2(w, h, name, outerRadius) {
    var width = w * 0.98;
    var height = h * 0.96;
    d3.json("./src/json/pie.json", function (error, data) {
        var dataset = data;
        // 自学则:初始值11,课程学习过则:初始值+11,应用过课程实践则:初始值+11+11;

        // 内环声明
        var svg = d3.select(name)
            .append("svg")
            .attr("width", width)
            .attr("height", height);
        var pie = d3.pie()
            .value(function (d) { return d[1]; });
        var piedata = pie(dataset);
        // var outerRadius = 200;	//外半径
        var innerRadius = 0;	//内半径，为0则中间没有空白
        var arc = d3.arc()	//弧生成器
            /*---------内半径形成圆环--------*/
            .innerRadius(innerRadius)	//设置内半径
            /*---------内半径形成圆环--------*/
            .outerRadius(outerRadius);	//设置外半径
        var color = d3.scaleOrdinal(d3.schemeCategory20);
        var arcs = svg.selectAll("g")
            .data(piedata)
            .enter()
            .append("g")
            .attr("transform", "translate(" + (width / 2) + "," + (height / 2) + ")");
        arcs.append("path")//每个g元素都追加一个path元素用绑定到这个g的数据d生成路径信息
            .attr("fill", function (d, i) {
                return color(i);
            })
            .attr("d", function (d) {
                return arc(d);//将角度转为弧度（d3使用弧度绘制）
            })
            .on("mouseover", function (d, i) {
                d3.select(this)
                    .attr("fill", "#b700fbff");
            })
            .on("mouseout", function (d, i) {
                svg.selectAll('path')
                    .attr("fill", function (d, i) {
                        return color(i);
                    });
            });

        // 外圆环声明
        var svg_outer = d3.select("g_outer")
            .append("svg")
            .attr("width", width)
            .attr("height", height);
        var arc_outer = d3.arc()	//弧生成器
            .innerRadius(outerRadius + 20)	//设置内半径
            .outerRadius(outerRadius + 50);	//设置外半径
        var arcs_outer = svg.selectAll("g_outer")
            .data(piedata)
            .enter()
            .append("g")
            .attr("transform", "translate(" + (width / 2) + "," + (height / 2) + ")");
        arcs_outer.append("path")//每个g元素都追加一个path元素用绑定到这个g的数据d生成路径信息
            .attr("fill", function (d, i) {
                return color(i);
            })
            .attr("d", function (d) {
                return arc_outer(d);//将角度转为弧度（d3使用弧度绘制）
            })
            .on("mouseover", function (d, i) {
                d3.select(this)
                    .attr("fill", "#b700fbff");
            })
            .on("mouseout", function (d, i) {
                svg.selectAll('path')
                    .attr("fill", function (d, i) {
                        return color(i);
                    });
            });

        // 内圆环移位与响应事件配置	
        arcs.append("text")
            .attr("transform", function (d) {
                var x = arc.centroid(d)[0] * 0.99;
                var y = arc.centroid(d)[1] * 1.1;
                return "translate(" + x + "," + y + ")";
            })
            .attr("text-anchor", "middle")
            .attr("font-size", function (d) {
                if (d.data[1] > 10) return d.data[1] / (outerRadius / 25) + "px";
            })
            .text(function (d) {
                // return (d.value / 1.65).toFixed(2) + "%";
                return d.data[0];
            })
            .on("mouseover", function (d, i) {

                if (d.data[1] < 10) {
                    d3.select(this)
                        .attr("font-size", 10);
                }
            })
            .on("mouseout", function (d, i) {
                if (d.data[1] < 10) {
                    d3.select(this)
                        .attr("font-size", function (d) {
                            if (d.data[1] > 10) return d.data[1] / (outerRadius / 150) + "px";
                            else return 8 + "px";
                        });
                }
            });

        // 添加标题字 
        var Ttext = svg.append("text")
            .attr("transform", function (d) {
                var x = 200;
                var y = 40;
                return "translate(" + x + "," + y + ")";
            })
            .attr("text-anchor", "middle")
            .attr("font-size", 20)
            .text("对各门编程语言的熟练程度")
            .attr("stroke-width", 0.5)
            .attr("stroke", "black");
        //添加一个提示框
        var tooltip = d3.select("body")
            .append("div")
            .attr("class", "tooltip")
            .style("opacity", 0.0);
        // 内圆环
        arcs.on("mouseover", function (d) {
            tooltip.html(d.data[0] + "熟悉程度" + "<br />" + (d.data[1] / 1.65).toFixed(2) + "%")
                .style("left", (d3.event.pageX) + "px")
                .style("top", (d3.event.pageY) + "px")
                .style("opacity", 1.0);
            d3.select(this)
                .style("cursor", "move");
        })
            /*---------实现框在圆环中间---------*/
            .on("mousemove", function (d) {
                tooltip.style("left", d3.event.pageX + "px")
                    .style("top", d3.event.pageY + "px");
            })
            /*---------实现框在圆环中间---------*/
            .on("mouseout", function (d) {
                tooltip.style("opacity", 0.0);
            });
        // 外圆环
        arcs_outer.on("mouseover", function (d) {
            tooltip.html(d.data[0] + ":" + "<br />" + d.data[2])
                .style("left", (d3.event.pageX) + "px")
                .style("top", (d3.event.pageY) + "px")
                .style("opacity", 1.0);
            d3.select(this)
                .style("cursor", "move");
        })
            /*---------实现框在圆环中间---------*/
            .on("mousemove", function (d) {
                tooltip.style("left", d3.event.pageX + "px")
                    .style("top", d3.event.pageY + "px");
            })
            /*---------实现框在圆环中间---------*/
            .on("mouseout", function (d) {
                tooltip.style("opacity", 0.0);
            });
    })
}

// 画直方图
function Hist(width, height, where, path) {
    // var width = (window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth) * 0.98;
    // var height = (window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight) * 0.9;
    var color = d3.scaleOrdinal(d3.schemeCategory20);
    d3.json(path, function (error, data) {
        console.log(data);
        var dataset = new Array(data.length);
        console.log(dataset);
        for (let i = 0; i < data.length; i++) {
            dataset[i] = data[i][1] * 40;
        }
        console.log(dataset);
        var svg = d3.select(where)			//选择<body>
            .append("svg")			//在<body>中添加<svg>
            .attr("width", width)	//设定<svg>的宽度属性
            .attr("height", height);//设定<svg>的高度属性				
        //矩形所占的宽度（包括空白），单位为像素		
        var rectStep = width / dataset.length;
        //矩形所占的宽度（不包括空白），单位为像素
        var rectWidth = rectStep - 10;
        var rect = svg.selectAll("rect")
            .data(dataset)		//绑定数据
            .enter()			//获取enter部分
            .append("rect")	    //添加rect元素，使其与绑定数组的长度一致
            .attr("x", function (d, i) {		//设置矩形的x坐标
                return i * rectStep;
            })
            .attr("y", height)
            .attr("fill", function (i) {
                return color(i);
            })
            .attr("width", rectWidth)		//设置矩形的宽度
            .attr("height", 0)
            .on("mouseover", function (d, i) {
                d3.select(this)
                    .attr("fill", "#b700fbff");
            })
            .on("mouseout", function (d, i) {
                d3.selectAll("rect")
                    .attr("fill", function (d, i) {
                        return color(i);
                    });
            })
            .transition()
            .duration(2400)
            .ease(d3.easeElasticOut)
            .attr("height", function (d) {	//设置矩形的高度
                return d;
            })
            .attr("y", function (d) {		//设置矩形的y坐标
                return height - d;
            });
        var ttext = svg.append("text")
            .attr("transform", function (d) {
                var x = width / 2;
                var y = height - dataset[data.length - 2] - data[2][1] * 4.6;
                return "translate(" + x + "," + y + ")";
            })
            .attr("text-anchor", "middle")
            .attr("font-size", 20)
            .text("专业课绩点分布情况")
            .attr("stroke-width", 0.5)
            .attr("stroke", "black");
        var ButtonText = svg.selectAll("ButtonText")
            .data(dataset)
            .enter()
            .append("text")
            .attr("transform", function (d, i) {
                var x = (i * rectStep) + rectStep / 2.3;
                var y = height - d * 1.02;
                return "translate(" + x + "," + y + ")";
            })
            .attr("text-anchor", "middle")
            .attr("font-size", 10)
            .text(function (d, i) {
                return data[i][0] + "：" + (data[i][1] / 17).toFixed(2) * 100 + "%";
            })
            .attr("stroke-width", 0.5)
            .attr("stroke", "black");
    })
}

// 音乐可视化配置函数
function music(width, height, innerR, where) {
    alert(">>页面加载完成后请点击右下角【Active Audio】以激活音乐控件！\n>>如果已点击请忽略。\n>>Designed by 李锦川")
    console.log("music is running...");
    var audioCtx = new (window.AudioContext || window.webkitAudioContext)();//创建了一个AudioContext
    var audioElement = document.getElementById('audioElement');//
    var audioSrc = audioCtx.createMediaElementSource(audioElement);//音源节点的参数，它的上下文是AudioContext，媒体元素为音频元素audioElement
    var analyser = audioCtx.createAnalyser();//创建一个分析器节点，分析音频上下文的频率数据
    //
    //绑定分析器到音频媒体元素
    audioSrc.connect(analyser);
    audioSrc.connect(audioCtx.destination);
    //
    var frequencyData = new Uint8Array(100);//创建长度为100的数组，我其实不大明白为什么要用这个来创建
    // var width = 1200;
    // var height = 700;
    // var innerR = 50;//内半径
    //
    var dataset = new Array(100);//数据集
    for (var i = 0; i < dataset.length; i++) {
        dataset[i] = new Array();//这里又创建了一个数组，二维数组
        dataset[i][0] = 120;//第一位固定120
        dataset[i][1] = 100 + Math.floor(Math.random() * (255 - 100));
        //第二位javascript中Math.floor(x)返回小于等于x的最大整数；
        //例如：Math.floor(1.6)返回1；
        //Math.random()是0~1之间的数（0~155）
    }
    //转化数据为适合生成饼图的对象数组
    var pie = d3.pie()//d3.pie 可以根据输入的数据生成这些角度数据
        .value(function (d) { return d[0]; });
    //
    var arcPath = d3.arc()//内外半径
        .innerRadius(innerR);
    //
    var svg = d3.select(where)
        .append("svg")
        .attr("width", width)
        .attr("height", height);
    //
    var arcs = svg.selectAll("path")
        .data(pie(dataset))//原生数据-->起止角度
        .enter()
        .append("path")
        .attr("transform", "translate(" + width / 2 + "," + height / 2 + ")")//确定位置
        .attr("fill", function (d, i) {//填充颜色
            // return 'rgb(' + (255 - dataset[i][1]) + ',250,' + dataset[i][1] + ')';//这个颜色是随机的，难怪不好看
            return "#9400D3";
        })
        .attr("stroke", "#FFF")
        .attr("d", function (d, i) {
            arcPath.outerRadius(dataset[i][1]);
            return arcPath(d);   //起止角度(内外半径)——>路径的参数
        });
    // 连续循环更新
    function renderChart() {
        requestAnimationFrame(renderChart);
        analyser.getByteFrequencyData(frequencyData);//把获取到的频谱数据映射到数组
        //console.log(frequencyData);
        svg.selectAll('path')
            .data(pie(dataset))
            .attr("fill", function (d, i) {//填充颜色
                return "#9400D3";
            })
            .attr("d", function (d, i) {
                arcPath.outerRadius(frequencyData[i] / 3.5 + innerR);//外径
                return arcPath(d);
            });
    }
    renderChart();
}