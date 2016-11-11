import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {

    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //signal
    signal qmlRequireData(string msg)
    //slot
    function qmlUpdateData(text){
        movieInput.text=text
    }

    Image {
        id: image1
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        sourceSize.height: 200
        anchors.fill: parent
        sourceSize.width: 200
        source: "Wallpapers-room_com___Black_Background_Set_Wood_3_by_iAmFreeman_1920x1200.jpg"

        TextInput {
            id: movieInput
            x: 280
            y: 189
            width: 80
            height: 20
            color: "#fbfbfb"
            text: qsTr("1")
            clip: false
            opacity: 1
            horizontalAlignment: Text.AlignHCenter
            selectionColor: "#0a0a82"
            font.pixelSize: 12
        }

        Button {
            id: play
            x: 290
            y: 230
            width: 61
            height: 21
            text: qsTr("play")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                window.qmlRequireData(movieInput.text)
            }

        }
    }


}
