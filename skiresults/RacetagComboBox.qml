import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

Column
{
    spacing: 10
    property string name: ""
    function getText()
    {
        return combo.currentText;
    }
    Text
    {
        text: name
    }
    ComboBox
    {
        id: combo
        currentIndex: 0
        textRole: "display"
        model: rctagmodel
    }
}
