// 绘制地图
DrawMaps();
// 绘制遮罩
Mask(MaskMainCity);
// AddClass("bodies","container");
//修改内容
Change("title", "个人简历");
readTextFile("./src/json/information.json", function (text) {
    var data = JSON.parse(text);
    console.log(data)
    Change('Name', "姓名：" + data.data[0].name);
    Change('Tel', "电话：" + data.data[2].phone);
    Change('Email', "邮箱：" + data.data[1].email);
    Change('edu_content', data.data[4].本科大学[1].time + ' &nbsp; ' + data.data[4].本科大学[0].location + ' &nbsp; ' + data.data[3].专业 + ' &nbsp; ' + data.data[5].学位);
    Change('GPA', data.data[8].绩点[0].name + "：" + data.data[8].绩点[1].value)
    // 获取课程名，i指定课程类型，0:专业基础课，1:专业核心课，2:专业选修课
    function get_className(i) {
        var j = 0;
        let words = '';
        for (j; j < (data.data[7].修读课程[i].type[1].value.length); j++) {
            words = words + data.data[7].修读课程[i].type[1].value[j][j] + ' &nbsp; ';
        };
        return words;
    };
    function get_classType(i) {
        let words = data.data[7].修读课程[i].type[0].name + '：';
        return words;
    }
    Change('classes_basic', get_classType(0));
    Change('classes_basic_fill', get_className(0));
    Change('classes_core', get_classType(1));
    Change('classes_core_fill', get_className(1));
    Change('classes_option', get_classType(2));
    Change('classes_option_fill', get_className(2));
    Change('stu-work', data.data[9].经历[0][0][0].name + "：");
    Change('stu-work_fill', data.data[9].经历[0][0][1].time[0][0] + "：" + "<br>" + data.data[9].经历[0][0][2].job[0][0] + "<br>" + "<br>" + data.data[9].经历[0][0][1].time[1][1] + "：" + "<br>" + data.data[9].经历[0][0][2].job[1][1]);
    Change('com-work', data.data[9].经历[1][1][0].name + "：");
    function get_com() {
        let words = '';
        let i = 0;
        for (i; i < data.data[9].经历[1][1][1].details.length; i++) {
            words = words + data.data[9].经历[1][1][1].details[i][i] + "<br>";
        };
        return words;
    }
    Change('com-work_fill', get_com());
    function get_lan() {
        let words = "";
        let i = 0;
        for (i; i < data.data[10].技能[1].details.length; i++) {
            words = words + data.data[10].技能[1].details[i][i] + ' &nbsp; ';
        }
        return words;
    }
    Change('lan', data.data[10].技能[0].name + "：");
    Change('lan_fill', get_lan());
    Change('En_Level', data.data[6].专业技能[0].type[0].name+"：");
    Change('En_Level_fill', data.data[6].专业技能[0].type[1].fill);
});
for(let i=1;i<=6;i++){
    Change('forceSvg',"<script>"+force("./src/json/force.json","force_"+i,200,200)+"</script>")
};
Pie2(400,400,"svg_pie",80);
Hist(400,400,"svg_hist","./src/json/hist.json");
music(200,200,20,"svg_music");