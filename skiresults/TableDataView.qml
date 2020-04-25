import QtQuick 2.12

Item {
    property int rHeight: 20
    property int rWidth: 80

    function addRow()
    {

    }

    id: tableroot
    width: parent.width
    height: parent.height
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    TableView
    {
        id: table
        anchors.fill: parent
        columnSpacing: 0
        rowSpacing: 0
        clip: true


        model: tablemodel

        delegate: Rectangle {
            implicitWidth: 150
            implicitHeight: 50
            border.color: "black"
            border.width: 0.5
            color: (heading==true)?"cyan":"white"
            Text {
                text: tabledata
                font.pointSize: 12
                anchors.centerIn: parent
            }
        }
    }

}
