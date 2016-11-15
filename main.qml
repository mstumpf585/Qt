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
    //to my knowledge we only need one signal as multiple signals gave me runtime errors
    signal qmlRequireData(string msg)
    //slot
    //a function for each slot that we know that we are going to want updated
    function qmlUpdateData(text){
        movieInput.text=text
    }
    function qmlUpdateTitle(text){
        movieTitleOutput.text=text
    }
    function qmlUpdatePrice(text){
        movieCostOutput.text=text
    }
    function qmlUpdateTime(text){
        movieRentedOutput.text=text
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
                //this will run RequireData which will update all of the other fields
                //in the process of executing
                window.qmlRequireData(movieInput.text)
            }

        }

        Text {
            id: movieTitleOutput
            x: 215
            y: 277
            width: 210
            height: 21
            color: "#fbfbfb"
            font.pixelSize: 12
        }

        Text {
            id: movieTitle
            x: 124
            y: 277
            width: 65
            height: 21
            color: "#fbfbfb"
            text: "Movie Title"
            font.pixelSize: 12
        }

        Text {
            id: movieCost
            x: 124
            y: 316
            width: 65
            height: 21
            color: "#fbfbfb"
            text: "Movie Cost"
            font.pixelSize: 12
        }

        Text {
            id: movieRented
            x: 124
            y: 358
            width: 65
            height: 21
            color: "#fbfbfb"
            text: "Last Rented"
            font.pixelSize: 12
        }

        Text {
            id: movieCostOutput
            x: 215
            y: 316
            width: 210
            height: 21
            color: "#fbfbfb"
            font.pixelSize: 12
        }

        Text {
            id: movieRentedOutput
            x: 215
            y: 358
            width: 210
            height: 21
            color: "#fbfbfb"
            font.pixelSize: 12
        }

        Button {
            id: button1
            x: 509
            y: 427
            text: qsTr("Done")
            onClicked: {
                //this will run RequireData which will update all of the other fields
                //in the process of executing
                window.close();
            }
        }
    }


}
