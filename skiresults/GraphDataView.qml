import QtQuick 2.0
import QtQuick.Controls 2.2
import QtCharts 2.0
import qt.chart 1.0

Item {

    ChartView {
        id: chart
        visible: false
        anchors.fill: parent

        ValueAxis {
            id: axisX
            min: 0
            max: 10000
        }

        ValueAxis {
            id: axisY
            min: 0
            max: 10000
        }

        LineSeries {
            id: line
            axisX: axisX
            axisY: axisY
        }

        VXYModelMapper {
            id: modelMapper
            model: ChartModel
            series: line
            firstRow: 0
            xColumn: 0
            yColumn: 1
        }

    }

}
