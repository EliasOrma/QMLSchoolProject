import QtQuick 2.0
import QtQuick.Controls 1.4

Column
{
    spacing: 10

    property string name: "Attributename"
    property string txt: textInput.text

    function getText()
    {
        return textInput.text
    }

    Text
    {
        text: name
    }



    Rectangle
    {
        anchors.right: parent.right
        width: 120
        height: 22
        color: "white"
        border.color: "black"
        TextInput{
            id: textInput
            anchors.fill: parent
            maximumLength: 15
        }
    }
}
