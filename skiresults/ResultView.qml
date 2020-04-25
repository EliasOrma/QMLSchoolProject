import QtQuick 2.12
import QtQuick.Controls 1.2
import QtQuick.Window 2.2

Item
{
    id: view
    width: parent.width
    height: parent.height
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    function initResultView(tableType)
    {
        if(tableType === 1)
        {
            // Table
            tabledataview.visible = true;
            graphdataview.visible = false;
        }
        else if(tableType === 2)
        {
            // Graph
            tabledataview.visible = false;
            graphdataview.visible = true;
        }
        else
        {
            // Table & Graph
        }
    }

    TableDataView
    {
        id: tabledataview
    }

    GraphDataView
    {
        id: graphdataview
    }
}
