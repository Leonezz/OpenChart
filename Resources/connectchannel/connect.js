
document.write("<script type='text/javascript' src='Resources/connectchannel/qwebchannel.js'></script>");

function connectQt() {
    if (location.search != "")
        var baseUrl = (/[?&]webChannelBaseUrl=([A-Za-z0-9\-:/\.]+)/.exec(location.search)[1]);
    else
        var baseUrl = "ws://localhost:12138";
    //output("Connecting to WebSocket server at " + baseUrl + ".");
    var socket = new WebSocket(baseUrl);
    socket.onclose = function () {
        console.error("web channel closed");
    };
    socket.onerror = function (error) {
        console.error("web channel error: " + error);
    };
    socket.onopen = function () {
        //output("WebSocket connected, setting up QWebChannel.");
        new QWebChannel(socket, function (channel) {
            // make brige object accessible globally
            window.brige = channel.objects.brige;
            brige.receiveMsg();
            brige.showLoading.connect(function () {
                myChart.showLoading();
            });
            brige.sendMsg.connect(function (message) {
                //output("Received message: " + message);
                myChart.showLoading();
                var ErrorCode;
                var userOption = JSON.parse(message);
                try {
                    myChart.clear();
                    myChart.setOption(userOption);
                    ErrorCode = 0;
                }
                catch (err) {
                    alert(err);
                    ErrorCode = 1;
                }
                brige.jsError(ErrorCode);
                myChart.hideLoading();
            });
            /* document.getElementById("send").onclick = function () {
                 var input = document.getElementById("input");
                 var text = input.value;
                 if (!text) {
                     return;
                 }
 
                 //output("Sent message: " + text);
                 input.value = "";
                 brige.receiveMsg(text);
             }*/
        });
    };
    return window;
}
