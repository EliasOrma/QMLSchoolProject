import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls 1.4


Window {
    visible: true
    width: 1080
    height: 540
    maximumWidth: 1080
    maximumHeight: 540
    minimumWidth: 1080
    minimumHeight: 540

    color: "White"
    title: qsTr("Ski Results")

    function showResults(resultType)
    {
        searchview.visible = false;
        resultview.initResultView(resultType);
        resultview.visible = true;
    }

    function showSearch()
    {
        searchview.visible = true;
        resultview.visible = false;
    }

    Connections {
        target: controller
        onShowResults: {
            showResults(tableType)
        }
    }




    Rectangle {
        opacity: 1
        color: "Gray"
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightcyan" }
            GradientStop { position: 1.0; color: "whitesmoke" }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            padding: 10
            text: "SkiResults"
            font.family: "Helvetica"
            font.pointSize: 24
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height - 50
            color: "transparent"

            SearchView
            {
                id: searchview
                visible: true
            }
            ResultView
            {
                id: resultview
                visible: false
                Button
                {
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    text: "Back"
                    onClicked: showSearch()
                }
            }
        }





    }//Rect
}
