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
                        color: '#9400D3'
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
                symbolSize: 20,
                // 'render':绘制完成显示特效,'emphasis':高亮时显示特效
                showEffectOn: 'render',
                // 涟漪动画配置
                rippleEffect: {
                    brushType: 'stroke',
                    scale: 6
                },
                // 开启鼠标提示动画效果
                hoverAnimation: true,
                // 散点大小配置
                symbolSize: 15,
                // 散点文字标签配置
                label: {
                    normal: {
                        // 是否显示配置
                        show: false,
                        formatter: '{b}',
                        position: 'right',
                        textStyle: {
                            color: '#800000',
                            fontSize: 20
                        }
                    }
                },
                // 散点样式配置
                itemStyle: {
                    normal: {
                        borderWidth: 1,
                        color: '#9400D3',
                        // 蒙度配置
                        shadowBlur: 25,
                        // 光晕颜色
                        shadowColor: '#9400D3'
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
                strokeColor: "#D3835D",
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
// 电荷作用力
function force(path,where,width,height) {
    // let width = 50;
    // let height = 50;
    let color = d3.scale.category20();
    var force = d3.layout.force()
        .charge(-120)
        .linkDistance(40)
        .size([width, height]);
    let svg = d3.select(where).append("svg")
        .attr("width", width)
        .attr("height", height);
    d3.json(path, function (error, graph) {
        console.log(graph);
        force.nodes(graph.nodes)
            .links(graph.links)
            .start();

        let node = svg.selectAll(".node")
            .data(graph.nodes)
            .enter().append("circle")
            .attr("class", "node")
            .attr("r", 10)
            .style("fill", function (d) { return color(d.group); })
            .call(force.drag);
        let link = svg.selectAll(".link")
            .data(graph.links)
            .enter().append("line")
            .attr("class", "link")
            .style("stroke-width", function (d) { return Math.sqrt(d.value); });
        force.on("tick", function () {
            link.attr("x1", function (d) { return d.source.x; })
                .attr("y1", function (d) { return d.source.y; })
                .attr("x2", function (d) { return d.target.x; })
                .attr("y2", function (d) { return d.target.y; });

            node.attr("cx", function (d) { return d.x; })
                .attr("cy", function (d) { return d.y; });
        });
    });
}